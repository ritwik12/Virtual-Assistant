#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include "encode.c"
#include "smtp.c"


#ifndef SIZE_MAX
#define SIZE_MAX 200
#endif

int config_email_function(){
  char* from = malloc(sizeof(char));
  char* pass = malloc(sizeof(char)); 
  FILE* new_config_email =NULL;
  new_config_email = fopen("config_email","w+");
  printf("This is the first time you are using Virtual-Assistant to send emails.\nPlease enter your email adress : ");
  scanf("%s", from);
  printf("Please enter your password: ");
  scanf("%s", pass);
  char* auth = malloc(sizeof(char));
  strcpy(auth, from);
  strcat(auth,pass);
  printf("email : %s\n", auth);
  //fprintf(new_config_email,"%s\n",from);
  char *result = calloc(sizeof(auth),sizeof(char));
  //printf("Encodé : %s\n", b64_encode(auth, strlen(auth)));
  strcpy(result, b64_encode(auth, strlen(auth)));
  printf("%s\n", result);

  fprintf(new_config_email, "%s",result);
  printf("%s : adress saved. \n", from);
  fclose(new_config_email);
  return 0;
}

int read_email(){
  //TODO
  // n stores the return value for 'read()' and 'write()' calls
  int n;
  //portno is the number port for SMTP
  int portno=995;
  //sockfd file descriptor used to store the value returned by the 'socket' sytem call and the 'accept' system call
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      perror("ERROR opening socket");

  //serv_addr contains the address of the server
  //server defines the host
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char hostbuffer[256]="pop.gmail.com";

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

int send_email(){
    //calling email2 on another processus
  const pid_t pid = fork();
  if(pid == 0) {
    smtp_send();
  }else{
    waitpid(pid, NULL, 0);
  }
  return 0;
}

int email(){
  //searching for config_email
  FILE* config_email = NULL;
  config_email = fopen("config_email", "r+");

  if(config_email==NULL){
    //Creating config_email
    config_email_function();
  }


  //Asking action to user
  printf("What do you want to do with your emails ? (read/send)\n");
  char action[20]="";
  scanf("%s", action);
  if(strcmp(action,"send")==0 || strcmp(action,"sned")==0 ){
    send_email();
  }else if(strcmp(action,"read")==0 || strcmp(action,"raed")==0){
    printf("READING EMAIL : NOT IMPLEMENTED YET\n");
    //TODO
  } else{
    printf("Sorry I can't do that.\n\n");
  }
}



void SMTPrequest(int sock,char *req,char *from,char *to,char *title,char *body){
  FILE* email = fopen("config_email", "r+");
  char* auth;
  fgets(auth, 100, email);
  //resp contains the response from SMTP protocol
  char resp[100]="";

  //wrinting informations in req using SMTP format and send it to the socket
  sprintf(req, "HELO localhost\r\n");
  send(sock,req, strlen(req),0);
  recv(sock, resp, strlen(resp), 0);

  sprintf(req, "AUTH PLAIN %s\r\n", auth);
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
