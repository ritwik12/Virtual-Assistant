#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "safe_system.h"

int safe_system(const char *cmd)
{
    if (cmd == NULL)
        return -1;

    size_t n = strlen(cmd);
    char *buf = malloc(n + 2);
    char **argv = malloc(sizeof(char *) * (n / 2 + 2));
    if (!buf || !argv) {
        free(buf);
        free(argv);
        return -1;
    }

    int argc = 0, quiet = 0;
    size_t o = 0;
    const char *p = cmd;

    while (*p) {
        while (isspace((unsigned char)*p)) p++;
        if (!*p) break;

        char *tok = buf + o;
        int quoted = 0;

        while (*p && !isspace((unsigned char)*p)) {
            if (*p == '\'') {
                quoted = 1;
                p++;
                while (*p && *p != '\'') buf[o++] = *p++;
                if (*p) p++;
            } else if (*p == '"') {
                quoted = 1;
                p++;
                while (*p && *p != '"') {
                    if (*p == '\\' && (p[1] == '"' || p[1] == '\\' ||
                                       p[1] == '$' || p[1] == '`'))
                        p++;
                    buf[o++] = *p++;
                }
                if (*p) p++;
            } else if (*p == '\\' && p[1]) {
                quoted = 1;
                p++;
                buf[o++] = *p++;
            } else {
                buf[o++] = *p++;
            }
        }
        buf[o++] = '\0';

        if (!quoted && strcmp(tok, "2>/dev/null") == 0)
            quiet = 1;
        else
            argv[argc++] = tok;
    }
    argv[argc] = NULL;

    if (argc == 0) {
        free(buf);
        free(argv);
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        free(buf);
        free(argv);
        return -1;
    }

    if (pid == 0) {
        if (quiet) {
            int fd = open("/dev/null", O_WRONLY);
            if (fd >= 0) {
                dup2(fd, STDERR_FILENO);
                close(fd);
            }
        }
        execvp(argv[0], argv);
        _exit(127);
    }

    free(buf);
    free(argv);

    int status;
    while (waitpid(pid, &status, 0) < 0) {
        if (errno != EINTR)
            return -1;
    }
    return status;
}