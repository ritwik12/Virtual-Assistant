#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SPACE ' '


int main () 
{

  char str[1000], *start, pv, location[1000],youtube[1000],songs[100],cal[100],search[100];
  int c, d, len=0;

  //Getting home directory out of configuration file
  FILE *fp;
  fp=fopen("config","rw");
  int i=0;
  char cfg_line[1000];
  cfg_line[i]=fgetc(fp);
  i++;
  while(cfg_line[i-1]!='\n')
  {
  	cfg_line[i]=fgetc(fp);
  	i++;
  }
  cfg_line[i-1]='\0';
  char * HOME_DIR = strchr(cfg_line, '=');
  HOME_DIR = HOME_DIR+2;
  fclose(fp);
 

  do
  {
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

//---------------------------------------------------------------------------------------------------------------------
//Artificial Intelligence
    
    char example[1000];
    strcpy(example,str);
	  int compare[10];
    char split[10][10]={0};
    int k=0,n,j=0,w=0,g=0,go=0,me=0,c=0,u=0,h=0,temp=0;
    char result[20];
    int weather_score,greeting_score,media_score,google_score,calendar_score,youtube_score,help_score;

    //for weather---------------

    char *weather_class[10][10]={{"please","show","outside","condition"},
          {"how"," ","weather","today"},
          {"weather"," ","desired","place"}};

    //for greeting--------------

    char *greeting_class[10][10]={{"hey","how","are","you"},
          {"how"," "," ","doing"},
          {"hello","there"," "," "}};

    //for google----------------

    char *google_class[10][10]={{"open","google","for","me"},
          {"I","want","search","browse"},
          {"can","you","open","google"}};

    //for media-----------------

    char *media_class[10][10]={{"can","you","list","media"},
          {"video","listen","play","music"},
          {"play","something","nice","song "}};

	  

    for(int i=0;i<strlen(example);i++)
    {
      if(example[i]==' ')
      { 
        if(example[i+1]!=' ')
        {
           split[k][j]='\0';
           j=0;
           k++;
        }
        continue;
      }
      else
      {
        split[k][j++]=example[i];       
      }       
    }

    split[k][j]='\0';
      
    
    //For Weather---------------------------------------

    for(int v=0;v<=k;v++)
       for(int b=0;b< 3 ;b++)
       { 
      
          for(int c=0;c< 4 ;c++)
          {
              if(strcmp(weather_class[b][c],split[v])== 0)
              {
                 w++;
          
              }   
          }
        }
        weather_score=w;

    //For Greeting-----------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        { 
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(greeting_class[b][c],split[v])== 0)
                {
                   g++;  
                }    
            }
        }
        greeting_score=g;


    //For Google-------------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
    {
      for(int c=0;c< 4 ;c++)
      {
          if(strcmp(google_class[b][c],split[v])== 0)
          {
             go++; 
          }   
      }
    }
    google_score=go;


    //For Media---------------------------------------

    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        {
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(media_class[b][c],split[v])== 0)
                {
                   me++; 
                }   
            }
        }
        media_score=me;

	 

    if(weather_score>greeting_score)
    {
       if(weather_score>media_score)
       {
          if(weather_score>google_score)
             strcpy(result,"weather");
          else
             strcpy(result,"google");
        }
        else
        {
          if(media_score>google_score)
             strcpy(result,"media");
          else
             strcpy(result,"google");
        }
    }
        else
        {
          if(greeting_score>media_score)
          {
             if(greeting_score>google_score)
                strcpy(result,"greeting");
             else
                strcpy(result,"google");
          }
        else
        {
          if(media_score>google_score)
             strcpy(result,"media");
          else            
             strcpy(result,"google");
        }
        }

//---------------------------------------------------------------------------------------------------------------------


      


    if((strcmp(result, "greeting") == 0))
    {
        system("say I am good");
        printf("I am good \n");
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
    else if((strcmp(result, "weather") == 0))
    {
            printf("Please enter location to get weather forecast \n" );
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
            for(d=c=0; youtube[c]; ++c)
            {
                if(youtube[c] == SPACE)
                {
                   if(pv != SPACE)
                   start[d++] = '+';
                   pv = SPACE;
                } 
                else 
                {
                   pv = start[d++] = youtube[c];
                }
            }
            start[d] = '\0';



            //--------------------------------
            sprintf(buff,"say searching youtube for \%s",youtube);
            system(buff);
            sprintf(buf, "firefox   https://www.youtube.com/results?search_query=\%s", start);
            system(buf);

    }
    else if((strcmp(result, "media") == 0))
    {
    		system("say here are the list of available media");
            printf("Here are the list of available media\n");
          	char * sys_cmd1;
          	char sys_cmd[1000];
          	sys_cmd1 = "ls ";
          	sprintf(sys_cmd,"%s%s%s",sys_cmd1,HOME_DIR,"media/");
            system(sys_cmd);
            system("say which media do you want me to play");
            printf("Which media do you want me to play? \n");
            fgets (songs, 1000, stdin);
            sprintf(song,"vlc %smedia/\%s",HOME_DIR,songs);
            system(song);

    }
    else if((strcmp(str, "calendar") == 0) || (strcmp(str, "open calendar") == 0))
    {
    		system("say which year calendar you want to see");
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
    else if((strcmp(result, "google") == 0))
    {
            if( (google_score==0) && (greeting_score==0) && (weather_score==0) && (media_score==0))
            {
      
                // fgets (search, 1000, stdin);
                //-------------------------------------------------
                start = malloc(strlen(str)+1);
                pv = 0;//previous character
                for(d=c=0; str[c]; ++c)
                {
                    if(str[c] == SPACE)
                    {
                       if(pv != SPACE)
                          start[d++] = '+';
                          pv = SPACE;
                    } 
                    else 
                    {
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
            else 
            {
                printf("What can I search for you on Google?\n");
                fgets (search, 1000, stdin);
                //-------------------------------------------------
                start = malloc(strlen(str)+1);


                pv = 0;//previous character
                for(d=c=0; search[c]; ++c)
                {
                    if(search[c] == SPACE)
                    {
                       if(pv != SPACE)
                          start[d++] = '+';
                          pv = SPACE;
                    } 
                    else 
                    {
                          pv = start[d++] = search[c];
                    }
                }
                start[d] = '\0';



                //--------------------------------

               
                sprintf(buf, "firefox https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ", start);
                system(buf);

             }

    }
}	
    while((strcmp(str,"stop")!=0));

    return 0;

}
