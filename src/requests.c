
/*
 * File:   requests.c
 *
 * Created on April 10, 2018, 8:51 AM
 */

int c = 0, d = 0, len = 0;
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


strcpy(example, str);
