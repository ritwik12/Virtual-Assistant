
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

void POP_request(SSL *ssl, char* req){
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
  //DEBUG 
  printf("[RECEIVED] %s",resp_buff);


  strcpy(buff,"USER ");
  strcat(buff,authlog);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG 
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG 
  printf("[RECEIVED] %s",resp_buff);
  strcpy(buff,"PASS ");
  strcat(buff,authpass);
  strcat(buff,"\r\n");
  SSL_write(ssl, buff, strlen(buff));
  //DEBUG 
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  //DEBUG 
  printf("[RECEIVED] %s",resp_buff);

  if(strcmp(req,"list")==0){
    strcpy(buff, "LIST\r\n");
    SSL_write(ssl, buff, strlen(buff));
    //DEBUG  
    printf("\n[Send] %s\n", buff);
    SSL_read(ssl,resp_buff, sizeof (resp_buff));
    //DEBUG  
    printf("[RECEIVED] %s",resp_buff);
    bzero(resp_buff,sizeof(resp_buff));
  }else if(strcmp(req,"list")==0){

  }


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

int connect_to_server(const char* server_address) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof (addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(995);
  if (inet_pton(AF_INET, get_ip_adress(server_address), &addr.sin_addr) == 1) {
    connect(socket_fd, (struct sockaddr*)&addr, sizeof (addr));
  }
  return socket_fd;
}

int main(){
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
      connceted_fd = connect_to_server("pop.gmail.com");
      if (connceted_fd != 0) {
        SSL_set_fd(ssl, connceted_fd);
        if (SSL_connect(ssl) != 1) {
          BIO_printf(obj_out, "SLL session not created");
        } else {
            printf("Connected !\n");
            POP_request(ssl, "list");
        }
      }
    }
  }
    return (EXIT_SUCCESS);
}