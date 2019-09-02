
/*
 * File:   requests.c
 *
 * Created on April 10, 2018, 8:51 AM
 */

#define WORD_LEN 10
#define NUM_WORDS 10

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
char split[NUM_WORDS][WORD_LEN] = {0};
int k = 0, n, j = 0, w = 0, g = 0, go = 0, em = 0, me = 0, res = 0, c = 0, u = 0, h = 0, temp = 0;
char result[20];
enum catagories {
	WEATHER,
	GREETING,
	MEDIA,
	GOOGLE,
	EMAIL,
	CALENDAR,
	YOUTUBE,
	HELP,
	RESTAURANT,
	LAST_FIELD
};
int scores[LAST_FIELD] = {0};
const char *catagories_str[LAST_FIELD] =
{
	"weather",
	"greeting",
	"media",
	"google",
	"email",
	"calendar",
	"youtube",
	"help",
	"restaurant"
};

char *classifier[LAST_FIELD][NUM_WORDS][WORD_LEN] = {

//for weather---------------
[WEATHER] =
{
    {"please", "show", "outside", "condition"},
    {"how", " ", "weather", "today"},
    {"weather", " ", "desired", "place"}
},

//for greeting--------------

[GREETING] = {
    {"hey", "how", "are", "you"},
    {"how", "welcome", "morning", "doing"},
    {"hello", "there", "good", "afternoon"}
},

//for google----------------

[GOOGLE] = {
    {"open", "google", "for", "me"},
    {"I", "want", "search", "browse"},
    {"can", "you", "open", "google"}
},

//for media-----------------

[MEDIA] = {
    {"can", "you", "list", "media"},
    {"video", "listen", "play", "music"},
    {"play", "something", "nice", "song "}
},

//for Restaurant

[RESTAURANT] = {
    {"Please", "find", "some", "restaurants"},
    {"Find", " ", "some", "restaurants"},
    {"Show", " ", " ", "restaurants"},
    {"Find", "places", "to", "eat"}
},

//for Emails

[EMAIL] = {
    {"can", "I", "send", "email"},
    {"mail", "new", "mails", "write"},
    {"Want", "to", "read", "emails"}
},
[CALENDAR] = {0},
[YOUTUBE] = {0},
[HELP] = {0}
};
