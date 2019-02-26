
/*
 * File:   requests.c
 *
 * Created on April 10, 2018, 8:51 AM
 */

bool only_spaces = true;
char * x = "Hey, How can I help you?";
printf("%s\n", x);
fgets(str, 1000, stdin);

//Check for spaces as input
for (int i = 0; str[i]!='\n'; i++)
{
    if (str[i] != ' ')
        only_spaces = false;
}

if (only_spaces)
    continue;

//Check for string length to be greater than 1. Since fgets gets the new line character, the length is 1 no matter if any input is given or not
if ((strlen(str) > 1) && (str[strlen(str) - 1] == '\n'))
    str[strlen(str) - 1] = '\0';
else
    continue;

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

char example[1000];
strcpy(example, str);
int compare[10];
char split[10][10] = {0};
int k = 0, n, j = 0, w = 0, g = 0, go = 0, em = 0, me = 0, res = 0, c = 0, u = 0, h = 0, temp = 0;
char result[20];
int weather_score=0,greeting_score=0,media_score=0,google_score=0,email_score=0,calendar_score=0, youtube_score=0, help_score=0, restaurant_score=0;

//for weather---------------

char *weather_class[10][10] = {
    {"please", "show", "outside", "condition"},
    {"how", " ", "weather", "today"},
    {"weather", " ", "desired", "place"}
};

//for greeting--------------

char *greeting_class[10][10] = {
    {"hey", "how", "are", "you"},
    {"how", " ", " ", "doing"},
    {"hello", "there", " ", " "}
};

//for google----------------

char *google_class[10][10] = {
    {"open", "google", "for", "me"},
    {"I", "want", "search", "browse"},
    {"can", "you", "open", "google"}
};

//for media-----------------

char *media_class[10][10] = {
    {"can", "you", "list", "media"},
    {"video", "listen", "play", "music"},
    {"play", "something", "nice", "song "}
};

//for Restaurant

char *restaurant_class[10][10] = {
    {"Please", "find", "some", "restaurants"},
    {"Find", " ", "some", "restaurants"},
    {"Show", " ", " ", "restaurants"},
    {"Find", "places", "to", "eat"}
};

//for Emails

char *email_class[10][10] = {
    {"can", "I", "send", "email"},
    {"mail", " ", " ", "write"},
    {"Want", "to", "read", "emails"}
};
