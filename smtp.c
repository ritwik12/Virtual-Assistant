/*
 * File:   main.c
 * Author: rahul
 *
 * Created on 22 February, 2016, 11:25 AM
 */

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


void SMTP_request(SSL *ssl){
  char resp_buff[4096]="";
  char buff[4096]="";

  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);

  strcpy(buff, "EHLO localhost \r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "AUTH PLAIN AG1hbmdhYm91bnR5bmFpYUBnbWFpbC5jb20ATUFOR0FCT1VOVFlOQUlB\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "MAIL FROM: <mangabountynaia@gmail.com>\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "RCPT TO: <mangabountynaia@gmail.com>\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "DATA\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);

  strcpy(buff, "Subject: coucou\r\nj'aime les croquettes\r\n.\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
  bzero(resp_buff,sizeof(resp_buff));

  strcpy(buff, "QUIT\r\n");
  SSL_write(ssl, buff, strlen(buff));
  printf("\n[Send] %s\n", buff);
  SSL_read(ssl,resp_buff, sizeof (resp_buff));
  printf("[RECEIVED] %s",resp_buff);
}

const char* get_ip_adress(const char* target_domain){
  const char* target_ip;
  struct in_addr *host_address;
  struct hostent *raw_list = gethostbyname(target_domain);
  int i = 0;
  for(i; raw_list->h_addr_list[i] != 0; i++) {
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
  addr.sin_port = htons(465);
  if (inet_pton(AF_INET, get_ip_adress(server_address), &addr.sin_addr) == 1) {
    connect(socket_fd, (struct sockaddr*)&addr, sizeof (addr));
  }
  return socket_fd;
}

int main() {
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
      connceted_fd = connect_to_server("smtp.gmail.com");
      if (connceted_fd != 0) {
        BIO_printf(obj_out, "Connected Successfully");
        SSL_set_fd(ssl, connceted_fd);
        if (SSL_connect(ssl) != 1) {
          BIO_printf(obj_out, "SLL session not created");
        } else {
          SMTP_request(ssl);
        }
      }
    }
  }
    return (EXIT_SUCCESS);
}
