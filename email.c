#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>

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


  //calling email2 on another processus
  const pid_t pid = fork();
  if(pid == 0) {
    char *arg[] = { "./smtp", (char *) 0 };
    execvp( "./smtp", arg);
  }else{
    waitpid(pid, NULL, 0);
  }
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



int read_email(){
  //TODO
}
