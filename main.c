#include "defines.h"
//#include "functions.c"
//#include "email.c"


int main() {

//#include "init_config.c"
	init();

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
//#include "requests.c"
		get_user_input(example);
        //Artificial Intelligence {REQUESTS}
		analyze(example, result);
//#include "analysis.c"
        //Artificial Intelligence {ANALYSIS}

		response(result);
//#include "response.c"
        //Artificial Intelligence {RESPONSE}

        //---------------------------------------------------------------------------------------------------------------------

    } while ((strcmp(str, "stop") != 0));

    return 0;

}
