/*
 * File:  defines.h 
 * Author: Omer Dagan
 * Author: Riya
 * Author: Ritwik
 * Created on September 3, 2019, 10:00 AM
 * 
 * Contribution: mcavazotti
 */

#ifndef V_A_DEFINES
#define V_A_DEFINES
#define WORD_LEN 15 /* the maximal length of each word in a classifier */
#define NUM_WORDS 10 /* the number of words per catagory classifier */

/* catagories enum - DO NOT evaluate elements
 * LAST_FIELD must remain last
 */
enum categories {
	WEATHER,
	GREETING,
	MEDIA,
	GOOGLE,
	EMAIL,
	CALENDAR,
	YOUTUBE,
	HELP,
	RESTAURANT,
	MATH,
	LAST_FIELD
};

/* scores array - used for classification of input*/
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
	"restaurant",
	"math"
};

/* 3D array of all catagory classifiers*/
const char *classifier[LAST_FIELD][NUM_WORDS][WORD_LEN] = {
	[WEATHER] =
	{
		{"please", "show", "outside", "condition"},
		{"how", " ", "weather", "today"},
		{"weather", " ", "desired", "place"}
	},
	[GREETING] = {
		{"hey", "how", "are", "you"},
		{"how", "welcome", "morning", "doing"},
		{"hello", "there", "good", "afternoon"}
	},
	[MEDIA] = {
		{"can", "you", "list", "media"},
		{"video", "listen", "play", "music"},
		{"play", "something", "nice", "song"}
	},
	[GOOGLE] = {
		{"open", "google", "for", "me"},
		{"I", "want", "search", "browse"},
		{"can", "you", "open", "google"}
	},
	[EMAIL] = {
		{"can", "I", "send", "email"},
		{"mail", "new", "mails", "write"},
		{"Want", "to", "read", "emails"}
	},
	[CALENDAR] = {},
	[YOUTUBE] = {},
	[HELP] = {},
	[RESTAURANT] = {
		{"Please", "find", "some", "restaurants"},
		{"Find", " ", "some", "restaurants"},
		{"Show", " ", " ", "restaurants"},
		{"Find", "places", "to", "eat"}
	},
	[MATH] = {}
	
};

/* globally defined variables */
char buf[9999];
char buffer[9999];
char buff[9999];
char weather[9999];
char song[9999];
char calendar[100];
char example[1000];
char split[NUM_WORDS][WORD_LEN] = {};
int compare[10];
char result[20];



/* data structures for word lookup */
#define TOTAL_WORDS 1000

// binary code for each category
#define WEATHER_CAT (1 << WEATHER)
#define GREETING_CAT (1 << GREETING)
#define MEDIA_CAT (1 << MEDIA)
#define GOOGLE_CAT (1 << GOOGLE)
#define EMAIL_CAT (1 << EMAIL)
#define CALENDAR_CAT (1 << CALENDAR)
#define YOUTUBE_CAT (1 << YOUTUBE)
#define HELP_CAT (1 << HELP)
#define RESTAURANT_CAT (1 << RESTAURANT)
#define MATH_CAT (1 << MATH)


typedef struct {
	char word[WORD_LEN];
	int category;
} WordCategory;

WordCategory word_list[TOTAL_WORDS];
unsigned int word_list_length;

int _compareFunction(const void *a, const void *b);



char tmp_string[1000];
char TTS[20];

#endif
