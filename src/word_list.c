#include "../utils/defines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int _compareFunction(const void *a, const void *b) {
  WordCategory *x = (WordCategory *)a;
  WordCategory *y = (WordCategory *)b;
  return strcmp(x->word, y->word);
}

void fillWordList() {
    unsigned int tmp_size = 0;
    WordCategory tmp[TOTAL_WORDS];
    for (short i = 0; i < LAST_FIELD; i++) {
        for (short j = 0; j < NUM_WORDS; j++) {
            for (short k=0; k < WORD_LEN; k++) {
              if (classifier[i][j][k] != NULL 
                    && strlen(classifier[i][j][k]) 
                    && strcmp(classifier[i][j][k]," ") != 0) {
                strcpy(tmp[tmp_size].word, classifier[i][j][k]);
                tmp[tmp_size].category = 1 << i;
                tmp_size++;
              }
            }
        }
    }

    qsort(tmp,tmp_size, sizeof(WordCategory),_compareFunction);


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
