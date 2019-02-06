#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


//#define SIZE_MAX 200

int email(){
  //init
  char from[30] ="";
  char to[30] ="";
  char title[30]="";
  char body[200]="";
  char smtp_adr[20]="";
  char req[1000] ="";

  //searching for config_email
  FILE* config_email = NULL;
    config_email = fopen("config_email", "r+");

    if(config_email==NULL){

      //Creating config_email
      FILE* new_config_email =NULL;
      new_config_email = fopen("config_email","w+");
      printf("This is the first time you are using Virtual-Assistant to send emails.\nPlease enter your email adress : ");
      scanf("%s", from);
      fprintf(new_config_email,"%s",from);
      printf("%s : adress saved. \n", from);
      fclose(new_config_email);
    }


    printf("What do you want to do ? (read/send)");
    char action[20]="";
    // TODO: choose action




}

int send(){
  //TODO
  // //sockfd file descriptor used to store the value returned by the 'socket' sytem call and the 'accept' system call
  // //n stores the return value for 'read()' and 'write()' calls
  // int sockfd, n;
  // int portno=25;  //number port for SMTP
  //
  // //serv_addr contains the address of the server
  // //server defines the host
  // struct sockaddr_in serv_addr;
  // struct hostent *server;
  //
  // serv_addr.sin_family = AF_INET;
  // serv_addr.sin_port = htons(portno);
}

int read(){
  //TODO
}

void SMTPrequest(int sock,char *req,char *from,char *to,char *title,char *body){
  //resp contains the response from SMTP protocol
  char resp[100]="";

  //wrinting informations in req using SMTP format and send it to the socket
  sprintf(req, "HELO Virtual-Assistant\r\n");
  send(sock,req, strlen(req),0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "MAIL FROM: <%s>", from);
  send(sock, req, strlen(req), 0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "RCPT TO: <%s>", to);
  send(sock, req, strlen(req), 0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "DATA\r\n");
  send(sock, req, strlen(req), 0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "Subject: <%s> \r\n%s\r\n.\r\n", title, body);
  send(sock, req, strlen(req), 0);
  recv(sock, resp, strlen(resp), 0);

  //Print response for tests
  printf("%s",resp);

  //Close SMTP
  sprintf(req, "QUIT\r\n");
  send(sock, req, strlen(req), 0);
  recv(sock, resp, strlen(resp), 0);
}
