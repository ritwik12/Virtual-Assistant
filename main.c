#include <stdio.h>
#include <string.h>


int main () {

   char str[1000];
   char * x="Hey, How can I help you?";
   printf("%s\n",x);                                      
   fgets (str, 1000, stdin);
      if ((strlen(str)>0) && (str[strlen (str) - 1] == '\n'))
          str[strlen (str) - 1] = '\0';

    char buf[9999];
    char buffer[9999];
    char buff[9999];
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
   else  
   {
      sprintf(buff,"say Do you mean \%s",str);
      system(buff);
      sprintf(buf, "firefox https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ", str); 
      system(buf);
   }
      return 0;
   
}