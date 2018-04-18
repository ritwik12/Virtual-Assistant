#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>
#include "functions.c"


int main() {
    
#include "init_config.c"

    //Inform user about preferred media player, as to config file
    char preferred_media_player[1000];
    sprintf(preferred_media_player, "say Your preferred media player is %s", M_P);
    system(preferred_media_player);
    
<<<<<<< HEAD
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

    //For Restaurant-----------------------------------
    for(int v=0;v<=k;v++)
        for(int b=0;b< 3 ;b++)
        {
            for(int c=0;c< 4 ;c++)
            {
                if(strcmp(restaurant_class[b][c],split[v])== 0)
                {
                   res++; 
                }   
            }
        }
        restaurant_score=res;

	 

    if(weather_score>greeting_score)
    {
       if(weather_score>media_score)
       {
          if(weather_score>restaurant_score)
          {
              if(weather_score>google_score)
                 strcpy(result,"weather");
              else
                 strcpy(result,"google");
          }
          else
          {
              if(restaurant_score>google_score)
                 strcpy(result,"restaurant");
              else
                 strcpy(result,"google");
          }
        }
        else
        {
          if(media_score>restaurant_score)
          {
              if(media_score>google_score)
                 strcpy(result,"media");
              else
                 strcpy(result,"google");
          }
          else
          {
             if(restaurant_score>google_score)
                 strcpy(result,"restaurant");
             else
                 strcpy(result,"google"); 
          }
        }
    }
        else
        {
          if(greeting_score>media_score)
          {
             if(greeting_score>restaurant_score)
             {
                 if(greeting_score>google_score)
                    strcpy(result,"greeting");
                 else
                    strcpy(result,"google");
             }
             else
             {
                 if(restaurant_score>google_score)
                     strcpy(result,"restaurant");
                 else
                     strcpy(result,"google");
             }
          }
        else
        {
          if(media_score>restaurant_score)
          {

              if(media_score>google_score)
                 strcpy(result,"media");
              else            
                 strcpy(result,"google");
          }
          else
          {
              if(restaurant_score>google_score)
                 strcpy(result,"restaurant");
              else
                 strcpy(result,"google");
          }
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
    else if(strcmp(str, "open gmail")== 0 || strcmp(str, "show gmail") == 0 || strcmp(str, "gmail") == 0)
    {
	    system("say opening gmail");
	    system("gnome-gmail");
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
		sprintf(weather,"http://wttr.in/\%s",location);
		int counter_weather = 0;
		while(weather[counter_weather]!='\n')
		{
			counter_weather++;
		}
		weather[counter_weather]= '\0';
		show_weather (weather);
            //system(weather);
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
            sprintf(buf, "%s https://www.youtube.com/results?search_query=\%s", WebBrowser,start);
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
            sprintf(song,"%s %smedia/\%s",M_P,HOME_DIR,songs);
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
    //Restaurant
    else if((strcmp(result,"restaurant"))==0)
    {

		find_restaurants();

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


				if(strcmp(str,"stop")!=0)
				{
                	//--------------------------------
                	sprintf(buff,"say Do you mean \%s",str);
                	system(buff);
                	sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
                	system(buf);
				}
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

                sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
                system(buf);

             }

    }
}	
    while((strcmp(str,"stop")!=0));
=======
    //Inform user about preferred web browser, as to config file
    char preferred_webbrowser[1000];
    sprintf(preferred_webbrowser, "say Your preferred webbrowser is %s", WebBrowser);
    system(preferred_webbrowser);

    do {
        
        //---------------------------------------------------------------------------------------------------------------------
        
        //Artificial Intelligence 
#include "requests.c"
        //Artificial Intelligence {REQUESTS}
        
#include "analysis.c"
        //Artificial Intelligence {ANALYSIS}
        
#include "response.c"
        //Artificial Intelligence {RESPONSE}

        //---------------------------------------------------------------------------------------------------------------------

    } while ((strcmp(str, "stop") != 0));
>>>>>>> 67062f5e9b8ad8e9184cf52acb88ce671a2b015a

    return 0;

}
