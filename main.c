#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include "utils/defines.h"
#include <stdbool.h>
#include "src/init_config.h"
#include "src/functions.c"
#include "src/email.c"

#include "src/word_list.c"
#include "utils/defines.h"
#include <stdbool.h>

FILE *conffile;
char *HomeDir, *Mediaplay, *browser;
int retval = 0;
int len = 0;


int main()
{

        if (!system("say --version 2>/dev/null")) {
                strcpy(TTS,"say");
        } else if (!system("espeak --version 2>/dev/null")) {
                strcpy(TTS,"espeak -g 3");
        } else {
                printf("Could not find a text-to-speech program. Echoing messages to console");
                strcpy(TTS,"echo");
        }

        conffile = get_Config_File();
        HomeDir = set_HomeDir_Var(conffile);
        Mediaplay = set_MediaPlayer_Var(conffile);
        browser = set_WebBrowser_Var(conffile);
        retval = config_Cleanup_Status(conffile);
        /* Make sure initial configuration succeeded*/
        if (!retval && HomeDir && Mediaplay && browser)
        {
                //Inform user about preferred media player, as to config file
                char preferred_media_player[1000];
                sprintf(preferred_media_player, "%s \"Your preferred media player is %s\" 2>/dev/null",TTS, Mediaplay);
                system(preferred_media_player); 

                //Inform user about preferred web browser, as to config file
                char preferred_webbrowser[1000];
                sprintf(preferred_webbrowser, "%s \"Your preferred webbrowser is %s\" 2>/dev/null",TTS, browser);
                system(preferred_webbrowser);  
        }

        // pre-process words
        fillWordList();
      do
        {

             //---------------------------------------------------------------------------------------------------------------------

                //Artificial Intelligence
#include "src/requests.c"
                //Artificial Intelligence {REQUESTS}

#include "src/analysis.c"
                //Artificial Intelligence {ANALYSIS}

#include "src/response.c"
                //Artificial Intelligence {RESPONSE}

                //---------------------------------------------------------------------------------------------------------------------

        } while ((strcmp(str, "stop") != 0)); 

        return 0;
}
