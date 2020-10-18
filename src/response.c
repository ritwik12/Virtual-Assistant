
/*
 * File:   response.c
 *
 * Created on April 10, 2018, 8:51 AM
 */


if ((strcmp(result, "greeting") == 0)) {
    sprintf(tmp_string, "%s \"I am good\" 2>/dev/null", TTS);
    system(tmp_string);
    printf("I am good \n");
} else if (strcmp(str, "firefox") == 0 || strcmp(str, "open firefox") == 0 || strcmp(str, "run firefox") == 0 || strcmp(str, "start firefox") == 0) {
    sprintf(tmp_string, "%s \"opening firefox\" 2>/dev/null", TTS);
    system(tmp_string);
    system("firefox");
} else if ((strcmp(str, "vlc") == 0) || (strcmp(str, "open vlc") == 0) || (strcmp(str, "run vlc") == 0) || (strcmp(str, "start vlc") == 0)) {
    sprintf(tmp_string, "%s \"opening vlc\" 2>/dev/null", TTS);
    system(tmp_string);
    system("vlc");
}// Weather
else if ((strcmp(result, "weather") == 0)) {
    printf("Please enter location to get weather forecast \n");
    fgets(location, 1000, stdin);
    sprintf(tmp_string, "%s \"showing weather\" 2>/dev/null", TTS);
    system(tmp_string);
    sprintf(weather, "http://wttr.in/\%s", location);
    int counter_weather = 0;
    while (weather[counter_weather] != '\n') {
        counter_weather++;
    }
    weather[counter_weather] = '\0';
    show_weather(weather);
    //system(weather);
} else if (strstr(str, "search youtube") != NULL) {
    //Extract substring after "FOR"
    len = strlen(str);
    strncpy(youtube, str + 19, len);
    //Youtube search
    //-------------------------------------------------
    start = malloc(strlen(youtube) + 1);


    pv = 0; //previous character
    for (d = c = 0; youtube[c]; ++c) {
        if (youtube[c] == SPACE) {
            if (pv != SPACE)
                start[d++] = '+';
            pv = SPACE;
        } else {
            pv = start[d++] = youtube[c];
        }
    }
    start[d] = '\0';



    //--------------------------------
    sprintf(buff, "%s \"searching youtube for \%s\" 2>/dev/null",TTS, youtube);
    system(buff);
    sprintf(buf, "%s https://www.youtube.com/results?search_query=\%s", WebBrowser, start);
    system(buf);

} else if ((strcmp(result, "media") == 0)) {
    sprintf(tmp_string, "%s \"here are the list of available media\" 2>/dev/null", TTS);
    system(tmp_string);
    printf("Here are the list of available media\n");
    char * sys_cmd = "ls media";
    system(sys_cmd);
    sprintf(tmp_string, "%s \"which media do you want me to play\" 2>/dev/null", TTS);
    system(tmp_string);
    printf("Which media do you want me to play? \n");
    fgets(songs, 1000, stdin);
    sprintf(song, "%s %smedia/\%s", MediaPlayer, HOMEDIR, songs);
    system(song);

} else if ((strcmp(str, "calendar") == 0) || (strcmp(str, "open calendar") == 0)) {
    sprintf(tmp_string, "%s \"which year calendar you want to see\" 2>/dev/null", TTS);
    system(tmp_string);
    printf("Which year calendar you want to see? \n");
    fgets(cal, 1000, stdin);
    sprintf(calendar, "cal \%s", cal);
    system(calendar);
    
}else if(strcmp(str,"math") == 0) {
    sprintf(tmp_string, "%s \"what can i calculate for you\" 2>/dev/null", TTS);
    system(tmp_string);
	printf("Please enter the calculation you wish to perform: \n");
	system("bc -q");

}else if(strcmp(str,"calculator") == 0 || strcmp(str,"open calculator")==0){
	printf("openning calculator\n");
    sprintf(tmp_string, "%s \"openning calculator\" 2>/dev/null", TTS);
    system(tmp_string);	
	system("gnome-calculator");


//Restaurant
}else if ((strcmp(result, "restaurant")) == 0) {

    find_restaurants();

}else if((strcmp(result, "email") == 0)){
    email();
}
else if((strcmp(result, "schedule") == 0)){
	schedule();
}
else if((strcmp(result, "reminder") == 0)){
	add_reminder();
}
    //Help
else if ((strcmp(str, "help") == 0)) {
    char * help = "less utils/help.txt";
    system(help);
} else if ((strcmp(result, "google") == 0)) {

    if ((scores[GOOGLE] == 0) && (scores[GREETING] == 0) && (scores[EMAIL] == 0) && (scores[WEATHER] == 0) && (scores[MEDIA] == 0)) {

        // fgets (search, 1000, stdin);
        //-------------------------------------------------
        start = malloc(strlen(str) + 1);
        pv = 0; //previous character
        for (d = c = 0; str[c]; ++c) {
            if (str[c] == SPACE) {
                if (pv != SPACE)
                    start[d++] = '+';
                pv = SPACE;
            } else {
                pv = start[d++] = str[c];
            }
        }
        start[d] = '\0';


        if (strcmp(str, "stop") != 0) {
            //--------------------------------
            
            sprintf(buff, "%s \"Do you mean \%s\" 2>/dev/null",TTS, str);
            system(buff);
            sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ", WebBrowser, start);
            system(buf);
        }
    } else {
        printf("What can I search for you on Google?\n");
        fgets(search, 1000, stdin);
        //-------------------------------------------------
        start = malloc(strlen(str) + 1);


        pv = 0; //previous character
        for (d = c = 0; search[c]; ++c) {
            if (search[c] == SPACE) {
                if (pv != SPACE)
                    start[d++] = '+';
                pv = SPACE;
            } else {
                pv = start[d++] = search[c];
            }
        }
        start[d] = '\0';



        //--------------------------------

        sprintf(buf, "%s https://www.google.co.in/search?q=%s&ie=utf-8&oe=utf-8&client=firefox-b-ab&gfe_rd=cr&ei=zkWgWc3fNeXI8AeCr5LYBw ", WebBrowser, start);
        system(buf);

    }

}
