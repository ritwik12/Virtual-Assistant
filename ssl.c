
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
#define BUFFER_SIZE 104096
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

void display_header(SSL* ssl, int n){
    char resp[BUFFER_SIZE]="";
    char resp_buff[BUFFER_SIZE]="";
    char buff[BUFFER_SIZE]="";
    char from[BUFFER_SIZE]="";
    char subject[BUFFER_SIZE]="";
    char date[BUFFER_SIZE]="";
    char temp_num[BUFFER_SIZE] = "";
    char* temp = calloc(BUFFER_SIZE, sizeof(char));

    sprintf(temp_num, "%d", n);
    printf(" N°: %s  ", temp_num);

    strcpy(buff, "from fetch ");
    strcat(buff, temp_num);
    strcat(buff, " (body[header.fields (from date subject)])\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG printf("[RECEIVED] %s",resp_buff);
    strcpy(resp, resp_buff);

    temp = strtok(resp_buff, "\r\n");
    while(strcmp(temp,"from OK Success") != 0){
      SSL_read(ssl,resp_buff, sizeof (resp_buff));
      strcat(resp, resp_buff);
      temp = strtok(resp_buff, "\r\n");
    }
    temp =strtok(resp, "\r\n");
    for(int i = 0; i < 3; i++)
    {
      temp =strtok(NULL, "\r\n");
      if(temp[0]=='F')      strcpy(from, temp);
      else if(temp[0]=='S') strcpy(subject, temp);
      else if(temp[0]=='D'){
        strncpy(date, temp, 31);
      }
    }

    //temp = calloc(BUFFER_SIZE, sizeof(char));
    printf("%s\n",from);
    printf("         %s\n",subject);
    printf("         %s      \n",date);
    bzero(resp_buff,sizeof(resp_buff));

    strcpy(buff, "str store ");
    strcat(buff, temp_num);
    strcat(buff, " flags unseen\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff)); //fetch
    //DEBUG printf("[RECEIVED] %s",resp_buff);
    temp = strtok(resp_buff, "\r\n");
    int success = 0;
    while(success!=1){
      while (temp != NULL) {
        if(strcmp(temp,"str OK Success") == 0) success = 1;
        temp = strtok(NULL, "\r\n");
      }
      if(success==0){
        SSL_read(ssl,resp_buff, sizeof (resp_buff));
        temp = strtok(resp_buff, "\r\n");
      }
    }
    bzero(resp_buff,sizeof(resp_buff));
}


int display_list(SSL *ssl){
    char resp_buff[BUFFER_SIZE]="";
    char buff[BUFFER_SIZE]="";
    int new_messages[100] = {0};
    int total_unseen = 0;

    strcpy(buff, "sel select inbox\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG printf("[RECEIVED] %s",resp_buff);
    bzero(resp_buff,sizeof(resp_buff));

    strcpy(buff, "sea search (unseen)\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG printf("[RECEIVED] %s",resp_buff);
    int i = 0;
    char* temp = malloc(BUFFER_SIZE*sizeof(char));
    temp = strtok(resp_buff, " "); //*
    temp = strtok(NULL, " "); //SEARCH
    while(strcmp(temp = strtok(NULL, " "), "OK") != 0 ) {
      new_messages[i++] = atoi(temp);
      total_unseen++;
    }
    //temp = malloc(BUFFER_SIZE*sizeof(char));
    bzero(resp_buff,sizeof(resp_buff));

    printf("You have %d new email(s)\n", total_unseen);
    printf(" _____________________________________________________________________________________________________________________________________________\n");
    printf("| New emails                                                                                                                                  |\n");
    printf("|_____________________________________________________________________________________________________________________________________________|\n");
    int num=0;
    while(new_messages[num] != 0){
      display_header(ssl, new_messages[num++]);
      printf("|____________________________________________________________________________________________________________________________________________|\n");
    }

    return total_unseen;
}



void display_email(SSL *ssl, int n){
    char resp[BUFFER_SIZE]="";
    char resp_buff[BUFFER_SIZE]="";
    char buff[BUFFER_SIZE]="";
    char num[10]="";
    char* temp = calloc(BUFFER_SIZE, sizeof(char));

    sprintf(num, "%d", n);
    printf("\n\n");
    printf("_____________________________________________________________________________________________________________________________________________\n");

    display_header(ssl, n);

    strcpy(buff, "display fetch ");
    strcat(buff, num);
    strcat(buff, " body[text]\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff)); //fetch
    //DEBUG printf("[RECEIVED] %s",resp_buff);
    strcpy(resp, resp_buff);
    temp = strtok(resp_buff, "\r\n");
    while(strcmp(temp,"display OK Success") != 0){
      SSL_read(ssl,resp_buff, sizeof (resp_buff));
      strcat(resp, resp_buff);
      temp = strtok(resp_buff, "\r\n");
    }
    temp = strtok(resp, "\r\n");
    temp = strtok(NULL,"\r\n");
    while(strcmp(temp, ")") != 0 ){
       printf("%s\n",temp);
       temp = strtok(NULL, "\r\n");
    }
    bzero(resp_buff,sizeof(resp_buff));
    printf("_____________________________________________________________________________________________________________________\n");

}

void IMAP_request(SSL *ssl){
  char resp_buff[BUFFER_SIZE]="";
  char buff[BUFFER_SIZE]="";
  char from[BUFFER_SIZE]="";
  char authlog[BUFFER_SIZE]="";
  char authpass[BUFFER_SIZE]="";
  char decodepass[BUFFER_SIZE]="";
  char temp[BUFFER_SIZE]="";


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

  strcpy(buff,"log login ");
  strcat(buff,from);
  strcat(buff," ");
  strcat(decodepass, (char*)b64_decode(authpass, strlen(authpass)));
  strcat(buff,decodepass);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  char line[BUFFER_SIZE] = "";
  display_list(ssl);
  printf("Please enter a command.\nEnter 'help' to display command list.(Enter 'quit' to close your connection)\n");

  while(strcmp(temp,"quit")!=0){
    fgets(line, BUFFER_SIZE, stdin);
    strncpy(temp, line, 4);
    if(strcmp(temp, "show")==0){
      strncpy(temp, line+5, strlen(line)-1);
      int n = atoi(temp);
      display_email(ssl, n);
      printf("Please enter a command.\nEnter 'help' to display command list.(Enter 'quit' to close your connection)\n");
    }
    else if(strcmp(temp, "help")==0){
      printf("___________________________________________________\n");
      printf("User commands :                                    |\n");
      printf("show (n°email)  display a specific email           |\n");
      printf("quit            close the connection               |\n");
      printf("help            diplay commands list               |\n");
      printf("___________________________________________________|\n");
      printf("Please enter a command.\nEnter 'help' to display command list.(Enter 'quit' to close your connection)\n");

    }

  }

  strcpy(buff, "LOGOUT\r\n");
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
        connceted_fd = connect_to_server("imap.gmail.com",993);
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
              system("say email sent");
              printf("Email sent \xE2\x9C\x93\n");
            }else{
              system("say Error. Please verify your email adress and password.");
              printf("Error \xe2\x9C\x97\nPlease verify your email adress and password.\n");
            }
          }else if (strcmp(arg,"read")==0){
            IMAP_request(ssl);
          }
        }
      }
    }
  }
    return (EXIT_SUCCESS);
}
