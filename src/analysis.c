
/* 
 * File:   analysis.c
 *
 * Created on April 10, 2018, 9:56 AM
 */

/*
 * split incoming strings to individual words array
 * change uppercase letters in string to lowercase for convenience
 */


#include <stdlib.h>
#include "../utils/defines.h"

size_t word = 0, character = 0;
for (size_t iter_char = 0; iter_char < strlen(example); iter_char++) {
    example[iter_char] = tolower(example[iter_char]);
    if (example[iter_char] == ' ') {
        if (example[iter_char + 1] != ' ') {
            split[word][character] = '\0';
            character = 0;
            word++;
        }
        continue;
    } else {
        split[word][character++] = example[iter_char];
    }
}

split[word][character] = '\0';


int classification_score = 0;
WordCategory *search_result;
for (int i = 0; i < LAST_FIELD; i++)
	scores[i] = 0;

/* performs a binary search for each word in the input array,
* if the word is found, the score of each class to which this word belongs to is incremented
*/
for (size_t iter_input = 0; iter_input <= word; iter_input++) {
  	search_result = (WordCategory *)bsearch(split[iter_input], word_list,word_list_length,sizeof(WordCategory),_compareFunction);
  	if (search_result != NULL) {
	  	for (int class = 0; class < LAST_FIELD; class++)
	  		scores[class] += (search_result->category & (1 << class)) != 0; // comparing category
  	}
}

/*
 * find highest classifier score
 */

int score = 0;
strcpy(result,"");
for (size_t class = 0; class < LAST_FIELD; class++) {
	if (scores[class] > score) {
		score = scores[class];
		strcpy(result, catagories_str[class]);
	}
}
