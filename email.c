#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
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
  char from[50] ="";
  char to[50] ="";
  char title[100]="";
  char body[BUFFER_SIZE]="";

  //calling email2 on another processus
  const pid_t pid = fork();
  if(pid == 0) {
    char *arg[] = { "./email2", (char *) 0 };
    execvp( "./email2", arg);
   }else{
    waitpid(pid, NULL, 0);
   }

   printf("OK \n");

  return 0;

}

int email(){

  //searching for config_email, create it if it does not exist
  FILE* config_email = NULL;
    config_email = fopen("config_email", "r+");
    if(config_email==NULL){
      config_email_function();
    }


    printf("What do you want to do with your emails ? (read/send)\n");
    char action[20]="";
    scanf("%s", action);
    if(strcmp(action,"send")==0 || strcmp(action,"sned")==0 ){
        //  printf("SENDING EMAIL : NOT IMPLEMENTED YET\n");
        send_email();
    }else if(strcmp(action,"read")==0 || strcmp(action,"raed")==0){
        printf("READING EMAIL : NOT IMPLEMENTED YET\n");
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
