
/* 
 * File:   analysis.c
 *
 * Created on April 10, 2018, 9:56 AM
 */

/*
 * split incoming strings to individual words array
 * change uppercase letters in string to lowercase for convenience
 */


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

/*
 * classify string - compare input with all classifiers
 * class - iterator for classes, i.e. google, weather etc.
 * iter_input - iterates over words in the input string
 * iter_classifier - iterates over the classifier arrays in each class
 * iter_classifier_w - iterates over all words in a single classifier array
 */
int classification_score = 0;
for (size_t class = 0 ; class < LAST_FIELD ; class++) {
	for (size_t iter_input = 0; iter_input <= word; iter_input++) {
		for (size_t iter_classifier = 0; iter_classifier < NUM_WORDS; iter_classifier++) {
			for (size_t iter_classifier_w = 0; iter_classifier_w < WORD_LEN; iter_classifier_w++) {
				if ((classifier[class][iter_classifier][iter_classifier_w]) &&
						(strcmp(classifier[class][iter_classifier][iter_classifier_w], split[iter_input]) == 0)) {
					classification_score++;
				}
			}
		}
	}
	scores[class] = classification_score;
	classification_score = 0;
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
