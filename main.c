#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SPACE ' '


int main () {

      char str[1000], *start, pv, location[1000],youtube[1000],songs[100];
      int c, d, len=0;

      char * x="Hey, How can I help you?";
       printf("%s\n",x);                                      
       fgets (str, 1000, stdin);
          if ((strlen(str)>0) && (str[strlen (str) - 1] == '\n'))
              str[strlen (str) - 1] = '\0';

      char buf[9999];
      char buffer[9999];
      char buff[9999];
      char weather[9999];
      char song[9999];

      sprintf(buffer, "say opening \%s",str);

 
  if((strcmp(str, "google") == 0) || (strcmp(str, "open google") == 0) || (strcmp(str, "google") == 0))
   { 
      system("say opening google");
      system("firefox www.google.com");
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
      sprintf(buf, "firefox   https://www.youtube.com/results?search_query=\%s", start); 
      system(buf);
      



   }
   else if((strcmp(str, "play song") == 0))
   {
    
      printf("Here are the list of available songs\n");
      system("ls /home/ritwik/songs/");
      printf("Which song do you want me to play? \n");
      fgets (songs, 1000, stdin);
      sprintf(song,"vlc /home/ritwik/songs/\%s",songs);
      system(song); 
    

   } 

    else  
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
      sprintf(buf, "firefox https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ", start); 
      system(buf);
      
   } 
  
      return 0;
   
}
