#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SPACE ' '


int main () {

      char str[1000], *start, pv, location[1000],youtube[1000],songs[1000],cal[100];
      int c, d, len=0;

//Getting home directory out of configuration file
FILE *fp;
fp=fopen("config","rw");
int i=0;
char cfg_line[1000];
cfg_line[i]=fgetc(fp);
i++;
while(cfg_line[i-1]!='\n'&&cfg_line[i-1]!=EOF)
{
	cfg_line[i]=fgetc(fp);
	i++;
}
cfg_line[i-1]='\0';
char * HOME_DIR = strchr(cfg_line, '=');
HOME_DIR = HOME_DIR+2;
//---------------------
//Get preffered media player from config file
i=0;
char media_player[1000];
media_player[i]=fgetc(fp);
i++;
while(media_player[i-1]!='\n'&&media_player[i-1]!=EOF)
{
	media_player[i]=fgetc(fp);
	i++;
}

media_player[i-1]='\0';
char * M_P = strchr(media_player, '=');
M_P = M_P+2;
//-----------------------
//Get preffered Webbrowser out of config file
i=0;
char webbrowser[1000];
webbrowser[i]=fgetc(fp);
i++;
while(webbrowser[i-1]!='\n'&&webbrowser[i-1]!=EOF)
{
	webbrowser[i]=fgetc(fp);
	i++;
}

webbrowser[i-1]='\0';
char * WebBrowser = strchr(webbrowser, '=');
WebBrowser = WebBrowser+2;


fclose(fp);

//Inform user about preffered media player, as to config file
char preffered_media_player[1000];
sprintf(preffered_media_player,"say Your preffered media player is %s",M_P);
system(preffered_media_player);
//Inform user about preffered web browser, as to config file
char preffered_webbrowser[1000];
sprintf(preffered_webbrowser,"say Your preffered webbrowser is %s",WebBrowser);
system(preffered_webbrowser);
      do{
      char * x="Hey, How can I help you?";
       printf("%s\n",x);
       fgets (str, 1000, stdin);
          if ((strlen(str)>0) && (str[strlen (str) - 1] == '\n'))
              str[strlen (str) - 1] = '\0';
//change uppercase letters in str to lowercase for convenience
	int i, s = strlen(str);
	for (i = 0; i < s; i++)
	    str[i] = tolower(str[i]);

      char buf[9999];
      char buffer[9999];
      char buff[9999];
      char weather[9999];
      char song[9999];
      char calendar[100];

      sprintf(buffer, "say opening \%s",str);


  if((strcmp(str, "google") == 0) || (strcmp(str, "open google") == 0) || (strcmp(str, "google") == 0))
   {
      system("say opening google");
	  char google[1000];
	  sprintf(google,"%s www.google.com",WebBrowser);
      system(google);
   }
   else if(strcmp(str, "firefox") == 0 || strcmp(str, "open firefox") == 0 || strcmp(str,"run firefox") == 0 || strcmp(str, "start firefox") == 0)
      {
      system("say opening firefox");
      system("firefox");
      }
   else if((strcmp(str, "vlc") == 0) || (strcmp(str, "open vlc") == 0) || (strcmp(str,"run vlc") == 0) || (strcmp(str, "start vlc") == 0))
   {
      system("say opening vlc");
      system("vlc");
   }
   // Weather
   else if((strcmp(str, "weather") == 0) || (strcmp(str, "today's weather") == 0))
   {
      printf("Please enter location \n" );
      fgets (location, 1000, stdin);

      system("say showing weather");
      sprintf(weather,"curl wttr.in/\%s",location);

      system(weather);
   }
  else if(strstr(str,"search youtube")!= NULL)
   {
      //Extract substring after "FOR"
      len=strlen(str);
      strncpy(youtube, str+19, len);


      //Youtube search
       //-------------------------------------------------
      start = malloc(strlen(youtube)+1);


      pv = 0;//previous character
      for(d=c=0; youtube[c]; ++c){
          if(youtube[c] == SPACE){
              if(pv != SPACE)
                  start[d++] = '+';
              pv = SPACE;
          } else {
              pv = start[d++] = youtube[c];
          }
      }
      start[d] = '\0';



      //--------------------------------
      sprintf(buff,"say Do you mean \%s",youtube);
      system(buff);
      sprintf(buf, "%s https://www.youtube.com/results?search_query=\%s", WebBrowser,start);
      system(buf);




   }
   else if((strcmp(str, "play song") == 0))
   {

      printf("Here are the list of available songs\n");
	char * sys_cmd1;
	char sys_cmd[1000];
	sys_cmd1 = "ls ";
	sprintf(sys_cmd,"%s%s%s",sys_cmd1,HOME_DIR,"media/");
      system(sys_cmd);
      printf("Which song do you want me to play? \n");
      fgets (songs, 1000, stdin);
      sprintf(song,"%s %smedia/\%s",M_P,HOME_DIR,songs);
      system(song);


   }
   else if((strcmp(str, "calendar") == 0) || (strcmp(str, "show calendar") == 0))
   {
   	printf("Which year calendar you want to see? \n");
   	fgets (cal, 1000, stdin);
   	sprintf(calendar,"cal \%s",cal);
   	system(calendar);


   }

   //Help
   else if((strcmp(str, "help") == 0))
   {
	char * help1 = "less ";
	char help[1000];
	sprintf(help,"%s%s%s",help1,HOME_DIR,"help.txt");
         system(help);
   }


   else if((strcmp(str, "stop") != 0))
   {
      //-------------------------------------------------
      start = malloc(strlen(str)+1);


      pv = 0;//previous character
      for(d=c=0; str[c]; ++c){
          if(str[c] == SPACE){
              if(pv != SPACE)
                  start[d++] = '+';
              pv = SPACE;
          } else {
              pv = start[d++] = str[c];
          }
      }
      start[d] = '\0';



    //--------------------------------

      sprintf(buff,"say Do you mean \%s",str);
      system(buff);
      sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
      system(buf);

   }
}	while((strcmp(str,"stop")!=0));

      return 0;

}
