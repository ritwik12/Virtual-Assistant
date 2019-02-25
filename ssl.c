
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

int display_list(SSL *ssl){
    char resp_buff[BUFFER_SIZE]="";
    char buff[BUFFER_SIZE]="";
    char* messages;


    strcpy(buff, "STAT\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG  printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG  
    printf("[RECEIVED] %s",resp_buff);
    //strcpy(messages, resp_buff);
    messages = strtok(resp_buff, " ");
    messages = strtok(NULL, " ");
    int nb_messages = atoi(messages);
    bzero(resp_buff,sizeof(resp_buff));

    for(int i = 1; i <= nb_messages; i++)
    {   
        char num[10] ="";
        sprintf(num, "%d", i);
        printf("Message n°%s\n", num);
        strcpy(buff, "TOP ");
        strcat(buff, num);
        strcat(buff, " 3\r\n");
        SSL_write(ssl, buff, strlen(buff));
        //DEBUG printf("\n[Send] %s\n", buff);
        SSL_read(ssl,resp_buff, sizeof (resp_buff));
        //DEBUG  printf("[RECEIVED] %s",resp_buff);
        printf("%s\n",messages);
        printf("_______________________________________________________________________________________________________________\n");
        bzero(resp_buff,sizeof(resp_buff));
    }
    return nb_messages;
}

void display_email(SSL *ssl, int n){
    char resp_buff[BUFFER_SIZE]="";
    char buff[BUFFER_SIZE]="";
    char num[10]="";
    printf("\n\n\n");
    sprintf(num,"%d",n);
    printf("Message n°%s:\n", num);
    strcpy(buff, "TOP ");
    strcat(buff, num);
    strcat(buff, " 200\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG  printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG  
    printf("[RECEIVED] %s",resp_buff);
    printf("_______________________________________________________________________________________________________________\n");
    bzero(resp_buff,sizeof(resp_buff));
}

void POP_request(SSL *ssl){
  char resp_buff[BUFFER_SIZE]="";
  char buff[BUFFER_SIZE]="";
  char from[BUFFER_SIZE]="";
  char authlog[BUFFER_SIZE]="";
  char authpass[BUFFER_SIZE]="";
  char decodepass[BUFFER_SIZE]="";
  int nb_messages = 0;


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

  strcpy(buff,"USER ");
  strcat(buff,from);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  strcpy(buff,"PASS ");
  strcat(decodepass, (char*)b64_decode(authpass, strlen(authpass)));
  strcat(buff,decodepass);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  char line[BUFFER_SIZE] = "";
  nb_messages = display_list(ssl);
  printf("Please enter a command.\nEnter 'help' to display command list.(Enter 'quit' to close your connection)\n");
  fgets(line,BUFFER_SIZE,stdin);
  while(strcmp(line,"quit\n")!=0){
    if(strcmp(line,"list\n")==0){
      for(int i = 1; i <= nb_messages; i++)
      {   
        char num[10] ="";
        sprintf(num, "%d", i);
        printf("Message n°%s\n", num);
        strcpy(buff, "TOP ");
        strcat(buff, num);
        strcat(buff, " 3\r\n");
        SSL_write(ssl, buff, strlen(buff));
        //DEBUG printf("\n[Send] %s\n", buff);
        SSL_read(ssl,resp_buff, sizeof (resp_buff));
        //DEBUG  
        printf("[RECEIVED] %s",resp_buff);
        printf("_______________________________________________________________________________________________________________\n");
        bzero(resp_buff,sizeof(resp_buff));
      }
    } 
    if(strcmp(line, "show\n")==0){
      printf("Please enter the corresponding number of the email you want to read : ");
      fgets(line,BUFFER_SIZE,stdin);
      int n = atoi(line);
      while(n<1 || n>nb_messages){
        fgets(line,BUFFER_SIZE,stdin);
        n = atoi(line);
      }
      display_email(ssl, n);
    }
    if(strcmp(line, "help\n")==0){
      printf("___________________________________________________\n");
      printf("User commands :                                    |\n");
      printf("list            display list of emails             |\n");
      printf("show            display a specific email           |\n");
      printf("delete          delete a specific email            |\n");
      printf("quit            close the connection               |\n");
      printf("help            diplay commands list               |\n");
      printf("___________________________________________________|\n");

    }
    printf("Please enter a command.\nEnter 'help' to display command list.(Enter 'quit' to close your connection)\n");
    fgets(line,BUFFER_SIZE,stdin);
  }

  strcpy(buff, "QUIT\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
}

void SMTP_request(SSL *ssl, char* to, char* title, char* body){
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
  printf("%s\n", server_address);
  printf("%d\n", portno);
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
            printf("Write your email and type 'finish' on one line to end your email: \n");
            fgets(line,BUFFER_SIZE,stdin);
            while(strcmp(line,"finish\n")!=0){
              strcat(body,line);
              fgets(line,BUFFER_SIZE,stdin);
            }
            printf("Email sent \xE2\x9C\x93\n");
            SMTP_request(ssl,to,title,body);

          }else if (strcmp(arg,"read")==0){
            POP_request(ssl);
          }

        }
      }
    }
  }
    return (EXIT_SUCCESS);
}
