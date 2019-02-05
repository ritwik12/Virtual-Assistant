#include <stdlib.h>
#include <stdio.h>

#define SIZE_MAX 200

int main(int argc, char* argv[]){
  //init
  char from[30] ="";
  char to[30] ="";
  char title[30]="";
  char body[SIZE_MAX]="";
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
    scanf("%s", action);
    if(action)



  return 0;
}
