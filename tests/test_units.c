#define _GNU_SOURCE
#include <assert.h>
#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../src/init_config.h"
#include "../src/safe_system.h"

static int mock_system_calls;
static int smtp_read_count;
static int smtp_fail_read;
static char smtp_writes[8192];

static int test_system(const char *command)
{
    assert(command != NULL);
    mock_system_calls++;
    return 0;
}

#define system(command) test_system(command)
#include "../src/email.c"
#undef system

int __wrap_SSL_read(SSL *ssl, void *buffer, int count)
{
    (void)ssl;
    const char *reply = smtp_read_count == smtp_fail_read ? "550 Rejected\r\n" : "250 OK\r\n";
    size_t reply_size = strlen(reply);
    if (reply_size > (size_t)count)
        reply_size = (size_t)count;
    memcpy(buffer, reply, reply_size);
    smtp_read_count++;
    return (int)reply_size;
}

int __wrap_SSL_write(SSL *ssl, const void *buffer, int count)
{
    (void)ssl;
    size_t used = strlen(smtp_writes);
    size_t available = sizeof(smtp_writes) - used - 1;
    size_t write_size = (size_t)count < available ? (size_t)count : available;
    memcpy(smtp_writes + used, buffer, write_size);
    smtp_writes[used + write_size] = '\0';
    return count;
}

static FILE *original_stdin;
static FILE *test_input;

static void set_stdin_text(const char *text)
{
    test_input = fmemopen((void *)text, strlen(text), "r");
    assert(test_input != NULL);
    stdin = test_input;
}

static void restore_stdin(void)
{
    stdin = original_stdin;
    fclose(test_input);
    test_input = NULL;
}

static void write_config(const char *contents)
{
    FILE *file = fopen("config_email", "w");
    assert(file != NULL);
    assert(fputs(contents, file) >= 0);
    assert(fclose(file) == 0);
}

static void test_email_configuration(void)
{
    mock_system_calls = 0;
    set_stdin_text("person@example.com\nsecret\n");
    assert(config_email_function() == 0);
    restore_stdin();
    assert(mock_system_calls == 3);

    FILE *file = fopen("config_email", "r");
    assert(file != NULL);
    char email_line[128], login_line[128], password_line[128];
    assert(fgets(email_line, sizeof(email_line), file) != NULL);
    assert(fgets(login_line, sizeof(login_line), file) != NULL);
    assert(fgets(password_line, sizeof(password_line), file) != NULL);
    fclose(file);
    assert(strcmp(email_line, "person@example.com\n") == 0);
    assert(strcmp(login_line, "cGVyc29uQGV4YW1wbGUuY29t\n") == 0);
    assert(strcmp(password_line, "c2VjcmV0\n") == 0);
}

static void test_email_menu(void)
{
    mock_system_calls = 0;
    assert(unlink("config_email") == 0);
    set_stdin_text("person@example.com\nsecret\nread\nunknown\nexit\n");
    assert(email() == 0);
    restore_stdin();
    assert(mock_system_calls >= 6);
}

static void test_smtp_request(void)
{
    write_config("sender@example.com\nbG9naW4=\ncGFzcw==\n");
    smtp_read_count = 0;
    smtp_fail_read = -1;
    smtp_writes[0] = '\0';
    assert(SMTP_request(NULL, "to@example.com", "subject", "body") == 0);
    assert(smtp_read_count == 10);
    assert(strstr(smtp_writes, "EHLO localhost \r\n") != NULL);
    assert(strstr(smtp_writes, "AUTH LOGIN \r\n") != NULL);
    assert(strstr(smtp_writes, "bG9naW4=\r\n") != NULL);
    assert(strstr(smtp_writes, "cGFzcw==\r\n") != NULL);
    assert(strstr(smtp_writes, "MAIL FROM: <sender@example.com>\r\n") != NULL);
    assert(strstr(smtp_writes, "RCPT TO: <to@example.com>\r\n") != NULL);
    assert(strstr(smtp_writes, "Subject: subject\r\nbody\r\n.\r\n") != NULL);
    assert(strstr(smtp_writes, "QUIT\r\n") != NULL);

    smtp_read_count = 0;
    smtp_fail_read = 5;
    smtp_writes[0] = '\0';
    assert(SMTP_request(NULL, "to@example.com", "subject", "body") == 1);
    assert(smtp_read_count == 6);
    assert(strstr(smtp_writes, "RCPT TO:") == NULL);
    smtp_fail_read = -1;
}

static void test_safe_system(void)
{
    assert(safe_system(NULL) == -1);
    assert(safe_system(" \t\n") == -1);
    assert(WIFEXITED(safe_system("true")));
    assert(WEXITSTATUS(safe_system("true")) == 0);
    assert(WEXITSTATUS(safe_system("false")) == 1);
    assert(WEXITSTATUS(safe_system("/usr/bin/test 'alpha beta' = \"alpha beta\"")) == 0);
    assert(WEXITSTATUS(safe_system("/usr/bin/test alpha\\ beta = 'alpha beta'")) == 0);
    assert(WEXITSTATUS(safe_system("/usr/bin/test \"a\\$b\" = 'a$b'")) == 0);
    assert(WEXITSTATUS(safe_system("/usr/bin/test '' = \"\"")) == 0);
    assert(WEXITSTATUS(safe_system("/usr/bin/test '2>/dev/null' = '2>/dev/null'")) == 0);
    assert(WEXITSTATUS(safe_system("virtual_assistant_test_missing 2>/dev/null")) == 127);
}

int main(void)
{
    char working_directory[PATH_MAX];
    char temporary_directory[] = "/tmp/virtual-assistant-tests-XXXXXX";
    assert(getcwd(working_directory, sizeof(working_directory)) != NULL);
    assert(mkdtemp(temporary_directory) != NULL);
    assert(chdir(temporary_directory) == 0);
    original_stdin = stdin;

    test_email_configuration();
    test_email_menu();
    test_smtp_request();
    test_safe_system();

    assert(unlink("config_email") == 0);
    assert(chdir(working_directory) == 0);
    assert(rmdir(temporary_directory) == 0);
    puts("All unit tests passed.");
    return 0;
}