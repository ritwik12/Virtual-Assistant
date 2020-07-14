
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "decode.c"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

int SMTP_request(SSL *ssl, char* to, char* title, char* body){
  char resp_buff[BUFFER_SIZE]="";
  char buff[BUFFER_SIZE]="";
  char from[BUFFER_SIZE]="";
  char authlog[BUFFER_SIZE]="";
  char authpass[BUFFER_SIZE]="";

  FILE* config_email = NULL;
  config_email = fopen("config_email", "r+");
  fgets(from,BUFFER_SIZE,config_email);
  fgets(authlog,BUFFER_SIZE,config_email);
  fgets(authpass,BUFFER_SIZE,config_email);
  from[strlen(from) - 1] = '\0';
  authlog[strlen(authlog) - 1] = '\0';
  authpass[strlen(authpass) - 1] = '\0';

  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);

  strcpy(buff, "EHLO localhost \r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "AUTH LOGIN \r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  strcpy(buff,"");
  strcat(buff,authlog);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  strcpy(buff,"");
  strcat(buff,authpass);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);

  strcpy(buff, "MAIL FROM: <");
  strcat(buff,from);
  strcat(buff,">\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  if (strstr(resp_buff, "OK")== NULL)
    return 1;
  //DEBUG  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "RCPT TO: <");
  strcat(buff,to);
  strcat(buff,">\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "DATA\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);

  strcpy(buff, "Subject: ");
  strcat(buff,title);
  strcat(buff,"\r\n");
  strcat(buff,body);
  strcat(buff,"\r\n.\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "QUIT\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);

  return 0;
}

const char* get_ip_adress(const char* target_domain){
  const char* target_ip;
  struct in_addr *host_address;
  struct hostent *raw_list = gethostbyname(target_domain);
  int i;
  for(i=0; raw_list->h_addr_list[i] != 0; i++) {
    host_address = (struct in_addr *)raw_list->h_addr_list[i];
    target_ip = inet_ntoa(*host_address);
  }
  return target_ip;
}

int connect_to_server(const char* server_address, int portno) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof (addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(portno);
  if (inet_pton(AF_INET, get_ip_adress(server_address), &addr.sin_addr) == 1) {
    connect(socket_fd, (struct sockaddr*)&addr, sizeof (addr));
  }
  return socket_fd;
}

int ssl_connect(char *arg) {
  BIO *obj_out = NULL;
  const SSL_METHOD *method;
  SSL_CTX *ctx;
  SSL *ssl;
  int connceted_fd = 0;

  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();

  obj_out = BIO_new_fp(stdout, BIO_NOCLOSE);

  if (SSL_library_init() < 0) {
    BIO_printf(obj_out, "OpenSSL not initialize");
  } else {
    method = SSLv23_client_method();
    if ((ctx = SSL_CTX_new(method)) == NULL) {
      BIO_printf(obj_out, "OpenSSL context not initialize");
    } else {
      SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
      ssl = SSL_new(ctx);
      if(strcmp(arg,"send")==0){
        connceted_fd = connect_to_server("smtp.gmail.com",465);
      }else if (strcmp(arg,"read")==0){
        connceted_fd = connect_to_server("pop.gmail.com",995);
      }
      if (connceted_fd != 0) {
        SSL_set_fd(ssl, connceted_fd);
        if (SSL_connect(ssl) != 1) {
          BIO_printf(obj_out, "SLL session not created");
        } else {

          if(strcmp(arg,"send")==0){
            //Initialize
            char to[BUFFER_SIZE] ="";
            char title[BUFFER_SIZE]="";
            char body[BUFFER_SIZE]="";
            char line[BUFFER_SIZE]="";

            //Asking infos to user (to, title,body)
            printf("To :");
            scanf("%s", to);
            printf("Subject :");
            scanf("%s", title);
            printf("Write your email and type 'finish' on one line to end your email: \n\n");
            fgets(line,BUFFER_SIZE,stdin);
            while(strcmp(line,"finish\n")!=0){
              strcat(body,line);
              fgets(line,BUFFER_SIZE,stdin);
            }
            printf("\nSending email ... ");
            if(SMTP_request(ssl,to,title,body)==0){
              sprintf(tmp_string, "%s \"email sent\" 2>/dev/null", TTS);
              system(tmp_string);
              printf("Email sent \xE2\x9C\x93\n");
            }else{
              sprintf(tmp_string, "%s \"Error. Please verify your email adress and password.\" 2>/dev/null", TTS);
              system(tmp_string);
              printf("Error \xe2\x9C\x97\nPlease verify your email adress and password.\n");
            }
          }else if (strcmp(arg,"read")==0){
            //TODO
          }
        }
      }
    }
  }
    return (EXIT_SUCCESS);
}
