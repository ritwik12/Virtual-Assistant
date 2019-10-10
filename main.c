#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include "src/functions.c"
#include "src/email.c"
#include "utils/defines.h"
#include <stdbool.h>


int main() {

#include "src/init_config.c"

    //Inform user about preferred media player, as to config file
    char preferred_media_player[1000];
    sprintf(preferred_media_player, "say Your preferred media player is %s", M_P);
    system(preferred_media_player);

    //Inform user about preferred web browser, as to config file
    char preferred_webbrowser[1000];
    sprintf(preferred_webbrowser, "say Your preferred webbrowser is %s", WebBrowser);
    system(preferred_webbrowser);

    do {

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
