#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>


#define SPACE ' '

//Function used by libcurl to allocate memory to data received from the HTTP response

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

int find_restaurants()
{
	char *encoded_address,*url;
	char *api_key="AIzaSyAjfVvnaDMYiR9i2DjeCSjZ76PR4qRCNTM";
	char address[1000];
	CURL *curl=NULL;
	CURLcode result;
	int i,len;
	int j,head_length,length; //variables for output formatting
	char location[1000];
	struct json_object *jobj,*obj1,*obj2,*obj3,*obj4,*lat,*lng; //Geocoding API json objects
	struct json_object *pl1,*pl2,*idx,*name,*price,*vic,*rate,*open,*hrs; //Google Place API json Objects
	struct MemoryStruct geo,places;
	geo.memory=malloc(4096);
	geo.size=0;
	places.memory=malloc(4096);
	places.size=0;	


	curl=curl_easy_init();
	
	system("say Please enter your area/locality");
	printf("Please enter your area/locality\n\n");
	fgets(address,1000,stdin);

	//-----------------------Google Geocoding API to convert Area name into co-ordinates needed by Places API------------------------	
	
	if(curl)
	{
		encoded_address=curl_easy_escape(curl,address,0);
		if(!encoded_address)
		{
			fprintf(stderr, "Could not encode address\n");
            		curl_easy_cleanup(curl);
            		return -1;
		}
		
		url=malloc(strlen(encoded_address)+200);
		if(!url)
		{
			 fprintf(stderr, "Could not allocate memory for url\n");
            		 free(encoded_address);
            		 curl_easy_cleanup(curl);
            		 return -1;
		}
		
		//url for geocoder api
 		sprintf(url, "https://maps.googleapis.com/maps/api/geocode/json?key=%s&address=%s", api_key, encoded_address);

		curl_easy_setopt(curl, CURLOPT_URL, url);
        	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        	curl_easy_setopt(curl, CURLOPT_CAPATH, "/usr/ssl/certs/crt");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&geo);
		
		
		result=curl_easy_perform(curl);

		if(result!=CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

		}

		//---------------Parsing JSON result from geocoding API----------------------------------------------------------------
		jobj=json_tokener_parse(geo.memory);
		json_object_object_get_ex(jobj,"results",&obj1);
		obj2=json_object_array_get_idx(obj1,0);
		json_object_object_get_ex(obj2,"geometry",&obj3);
		json_object_object_get_ex(obj3,"location",&obj4);
		json_object_object_get_ex(obj4,"lat",&lat);
		json_object_object_get_ex(obj4,"lng",&lng);
		
		//-----------------------------JSON Parsed-------------------------------------------------------------------------------
		sprintf(location,"%s,%s",json_object_get_string(lat),json_object_get_string(lng));		
		
		//------------------------------Google Places API---------------------------------------------------------------------
		
		sprintf(url,"https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=%s&radius=500&type=restaurant&key=%s",location,api_key);

		curl_easy_setopt(curl, CURLOPT_URL, url);
        	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        	curl_easy_setopt(curl, CURLOPT_CAPATH, "/usr/ssl/certs/crt");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&places);

		
			
		result=curl_easy_perform(curl);
		
		if(result!=CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

		}
				
		
		
		pl1=json_tokener_parse(places.memory);	
		json_object_object_get_ex(pl1,"results",&pl2);
		len=json_object_array_length(pl2);
		
		system("say Here are some restaurants in the area");
		printf("Here are some restaurants in the area\n\n");
		for(i=0;i<len&&i<=7;i++)
		{
			idx=json_object_array_get_idx(pl2,i);
			json_object_object_get_ex(idx,"name",&name);
			
			json_object_object_get_ex(idx,"rating",&rate);
			json_object_object_get_ex(idx,"vicinity",&vic);
			json_object_object_get_ex(idx,"opening_hours",&hrs);
			json_object_object_get_ex(hrs,"open_now",&open);
			json_object_object_get_ex(idx,"price_level",&price);
			
			//------------------- Code to display output in tables---------------------------------------
			head_length=strlen("Restaurant Name:")+strlen(json_object_get_string(vic))+40;
						
			for(j=0;j<head_length;j++)
				printf("-");
			
			
			printf("\n| ");
			printf("Restaurant Name:");
			length=strlen("Restaurant Name:");
			for(j=length;j<=40;j++)
				printf(" ");
			printf("|");
			
			printf(" %s",json_object_get_string(name));
			length=length+(40-length)+strlen(json_object_get_string(name));
			for(j=length;j<head_length-4;j++)
				printf(" ");

			printf("|\n");			

			for(j=0;j<head_length;j++)
				printf("-");				
				
			printf("\n| ");
			printf("Address:");
			length=strlen("Address:");
			for(j=length;j<=40;j++)
				printf(" ");
			printf("|");
			
			printf(" %s",json_object_get_string(vic));
			length=length+(40-length)+strlen(json_object_get_string(vic));
			for(j=length;j<head_length-4;j++)
				printf(" ");
			printf("|\n");
			for(j=0;j<head_length;j++)
				printf("-");				
				
			printf("\n| ");

			if(json_object_get_double(rate)>0.0)
			{
				printf("Rating:");
				length=strlen("Rating:");
				for(j=length;j<=40;j++)
					printf(" ");
				printf("|");
				printf(" %.1f",json_object_get_double(rate));
				length=length+(40-length)+3;
				for(j=length;j<head_length-4;j++)
					printf(" ");

				printf("|\n");
				for(j=0;j<head_length;j++)
				printf("-");				
				
				printf("\n| ");
			
			}
			if(json_object_get_double(price)>0.0)
			{
				printf("Price Rating:");
				length=strlen("Price Rating:");
				for(j=length;j<=40;j++)
					printf(" ");
				printf("|");
				printf(" %.1f",json_object_get_double(rate));
				length=length+(40-length)+3;
				for(j=length;j<head_length-4;j++)
					printf(" ");

				printf("|\n");
				for(j=0;j<head_length;j++)
					printf("-");				
				
				printf("\n| ");
			}
			if(json_object_get_boolean(open))
			{
				printf("open now");
				length=strlen("Open now");
				for(j=length;j<head_length-1;j++)
					printf(" ");
				printf("|\n");
			}
			else
			{
				printf("closed now");
				length=strlen("Closed now");
				for(j=length;j<head_length-1;j++)
					printf(" ");
				printf("|\n");
			}
			for(j=0;j<head_length;j++)
				printf("-");
			printf("\n\n");

		}
				
								
		free(places.memory);
		free(geo.memory);
		free(url);
        	free(encoded_address);
        	curl_easy_cleanup(curl);

	}
 
  
  return 0;

}



int main () 
{

  char str[1000], *start, pv, location[1000],youtube[1000],songs[1000],cal[100],search[100];
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

  do
  {
    char * x="Hey, How can I help you?";
    printf("%s\n",x);
    fgets (str, 1000, stdin);
    if ((strlen(str)>0) && (str[strlen (str) - 1] == '\n'))
{
        str[strlen (str) - 1] = '\0';
	return 0;
}
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
    int k=0,n,j=0,w=0,g=0,go=0,me=0,res=0,c=0,u=0,h=0,temp=0;
    char result[20];
    int weather_score,greeting_score,media_score,google_score,calendar_score,youtube_score,help_score,restaurant_score;

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

    //for Restaurant

    char *restaurant_class[10][10]={{"Please","find","some","restaurants"},
          {"Find"," ","some","restaurants"},
          {"Show"," "," ","restaurants"},
          {"Find","places","to","eat"}};
	  

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



                //--------------------------------
                sprintf(buff,"say Do you mean \%s",str);
                system(buff);
                sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
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

                sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ",WebBrowser, start);
                system(buf);

             }

    }
}	
    while((strcmp(str,"stop")!=0));

    return 0;

}
