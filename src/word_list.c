/* 
 * File:   word_list.c
 * Author: mcavazotti
 * Created on July 15, 2020
 */


#include "../utils/defines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* comparison function for sorting and searching */
int _compareFunction(const void *a, const void *b) {
  WordCategory *x = (WordCategory *)a;
  WordCategory *y = (WordCategory *)b;
  return strcmp(x->word, y->word);
}

/* fills the word_list array*/
void fillWordList() {
    unsigned int tmp_size = 0;
    WordCategory tmp[TOTAL_WORDS];
    
    // inserts all the non empty strings from classifier into a temporary array, hence reducing the search space
    for (short class_iter = 0; class_iter < LAST_FIELD; class_iter++) {
        for (short phrase_iter = 0; phrase_iter < NUM_WORDS; phrase_iter++) {
            for (short word_iter =0; word_iter < WORD_LEN; word_iter ++) {
              if (classifier[class_iter][phrase_iter][word_iter] != NULL 
                    && strlen(classifier[class_iter][phrase_iter][word_iter]) 
                    && strcmp(classifier[class_iter][phrase_iter][word_iter]," ") != 0) {
                strcpy(tmp[tmp_size].word, classifier[class_iter][phrase_iter][word_iter]);
                tmp[tmp_size].category = 1 << class_iter;
                tmp_size++;
              }
            }
        }
    }

    // sort temporary array
    qsort(tmp,tmp_size, sizeof(WordCategory),_compareFunction);


    // removes duplicate words and merges category codes
    char prev_word[WORD_LEN] = "---";
    word_list_length = 0;
    for (int i = 0; i < tmp_size; i++){
        if (strcmp(prev_word, tmp[i].word) == 0) {
            word_list[word_list_length-1].category |= tmp[i].category;
        } else {
            word_list[word_list_length].category = tmp[i].category;
            strcpy(word_list[word_list_length].word,tmp[i].word);
            word_list_length++;
        }
        strcpy(prev_word,tmp[i].word);
    }
}
