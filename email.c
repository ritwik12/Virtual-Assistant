#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#ifndef SIZE_MAX
#define SIZE_MAX 200
#endif

int config_email_function(){
  char from[30] ="";
  FILE* new_config_email =NULL;
  new_config_email = fopen("config_email","w+");
  printf("This is the first time you are using Virtual-Assistant to send emails.\nPlease enter your email adress : ");
  scanf("%s", from);
  fprintf(new_config_email,"%s",from);
  printf("%s : adress saved. \n", from);
  fclose(new_config_email);
  return 0;
}

int send_email(){
  //TODO
  // n stores the return value for 'read()' and 'write()' calls
  int n;
  //portno is the number port for SMTP
  int portno=465;
  //sockfd file descriptor used to store the value returned by the 'socket' sytem call and the 'accept' system call
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      perror("ERROR opening socket");

  //serv_addr contains the address of the server
  //server defines the host
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char hostbuffer[256]="smtp.gmail.com";

  server = gethostbyname(hostbuffer);

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
     (char *)&serv_addr.sin_addr.s_addr,
     server->h_length);
  serv_addr.sin_port = htons(portno);
  printf("Trying to connect using host %s... \n",hostbuffer);
  int co = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
  if (co < 0)
    perror("\n\n");
  else
    printf("ok \n\n");

}

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
      config_email_function();
    }


    printf("What do you want to do with your emails ? (read/send)\n");
    char action[20]="";
    scanf("%s", action);
    if(strcmp(action,"send")==0 || strcmp(action,"sned")==0 ){
        //  printf("SENDING EMAIL : NOT IMPLEMENTED YET\n", from);
        send_email();
    }else if(strcmp(action,"read")==0 || strcmp(action,"raed")==0){
        printf("READING EMAIL : NOT IMPLEMENTED YET\n", from);
    } else{
      printf("Sorry I can't do that.\n\n");
    }
}



int read_email(){
  //TODO
}



void SMTPrequest(int sock,char *req,char *from,char *to,char *title,char *body){
  //resp contains the response from SMTP protocol
  char resp[100]="";

  //wrinting informations in req using SMTP format and send it to the socket
  sprintf(req, "HELO localhost\r\n");
  send(sock,req, strlen(req),0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "AUTH PLAIN AG1hbmdhYm91bnR5bmFpYUBnbWFpbC5jb20ATUFOR0FCT1VOVFlOQUlB\r\n");
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
