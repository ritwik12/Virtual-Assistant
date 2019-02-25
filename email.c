#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include "encode.c"
#include "ssl.c"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

int config_email_function(){
  char from[BUFFER_SIZE] = "";
  char pass[BUFFER_SIZE] = "";
  FILE* new_config_email =NULL;
  new_config_email = fopen("config_email","w+");
  system("say This is the first time you are using Virtual-Assistant to send emails. Please enter your email adress.");
  printf("This is the first time you are using Virtual-Assistant to send emails.\nPlease enter your email adress : ");
  scanf("%s", from);
  fprintf(new_config_email,"%s\n",from);
  fprintf(new_config_email,"%s\n",b64_encode(from,strlen(from)));
  system("say please enter your password.");
  printf("Please enter your password: ");
  scanf("%s", pass);
  fprintf(new_config_email,"%s\n",b64_encode(pass,strlen(pass)));
  system("say Your email account is now saved.");
  printf("%s : adress saved. \n", from);
  fclose(new_config_email);
  return 0;
}

int email(){
  //searching for config_email, create it if it does not exist
  FILE* config_email = NULL;
  config_email = fopen("config_email", "r+");
  if(config_email==NULL){
    config_email_function();
  }

  //Asking action to user
  system("say what do you want to do with your emails ?");
  printf("What do you want to do with your emails ? (read/send)\n");
  char action[20]="";
  scanf("%s", action);
  if(strcmp(action,"send")==0 || strcmp(action,"sned")==0 ){
    system("say You can write your email.");
    ssl_connect("send");
  }else if(strcmp(action,"read")==0 || strcmp(action,"raed")==0){
    system("say you can consult your emails.");
    //printf("READING EMAIL : NOT IMPLEMENTED YET\n");
    ssl_connect("read");
  } else{
    printf("Sorry I can't do that.\n\n");
  }
}
