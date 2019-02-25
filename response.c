
/*
 * File:   response.c
 *
 * Created on April 10, 2018, 8:51 AM
 */


if ((strcmp(result, "greeting") == 0)) {
    system("say I am good");
    printf("I am good \n");
} else if (strcmp(str, "firefox") == 0 || strcmp(str, "open firefox") == 0 || strcmp(str, "run firefox") == 0 || strcmp(str, "start firefox") == 0) {
    system("say opening firefox");
    system("firefox");
} else if ((strcmp(str, "vlc") == 0) || (strcmp(str, "open vlc") == 0) || (strcmp(str, "run vlc") == 0) || (strcmp(str, "start vlc") == 0)) {
    system("say opening vlc");
    system("vlc");
}// Weather
else if ((strcmp(result, "weather") == 0)) {
    printf("Please enter location to get weather forecast \n");
    fgets(location, 1000, stdin);
    system("say showing weather");
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
    sprintf(buff, "say searching youtube for \%s", youtube);
    system(buff);
    sprintf(buf, "%s https://www.youtube.com/results?search_query=\%s", WebBrowser, start);
    system(buf);

} else if ((strcmp(result, "media") == 0)) {
    system("say here are the list of available media");
    printf("Here are the list of available media\n");
    char * sys_cmd1;
    char sys_cmd[1000];
    sys_cmd1 = "ls ";
    sprintf(sys_cmd, "%s%s%s", sys_cmd1, HOME_DIR, "media/");
    system(sys_cmd);
    system("say which media do you want me to play");
    printf("Which media do you want me to play? \n");
    fgets(songs, 1000, stdin);
    sprintf(song, "%s %smedia/\%s", M_P, HOME_DIR, songs);
    system(song);

} else if ((strcmp(str, "calendar") == 0) || (strcmp(str, "open calendar") == 0)) {
    system("say which year calendar you want to see");
    printf("Which year calendar you want to see? \n");
    fgets(cal, 1000, stdin);
    sprintf(calendar, "cal \%s", cal);
    system(calendar);
}//Restaurant
else if ((strcmp(result, "restaurant")) == 0) {

    find_restaurants();

}else if((strcmp(result, "email") == 0)){
    system("say I am going to access to your email account. Do you want to send or read an email ?");
    email();

}    //Help
else if ((strcmp(str, "help") == 0)) {
    char * help1 = "less ";
    char help[1000];
    sprintf(help, "%s%s%s", help1, HOME_DIR, "help.txt");
    system(help);
} else if ((strcmp(result, "google") == 0)) {
    printf("google command\n");
    if ((google_score == 0) && (greeting_score == 0) && (email_score == 0) && (weather_score == 0) && (media_score == 0)) {

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
            sprintf(buff, "say Do you mean \%s", str);
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
