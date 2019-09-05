
/* 
 * File:   analysis.c
 *
 * Created on April 10, 2018, 9:56 AM
 */

/*
 * split incoming strings to individual words array
 * change uppercase letters in string to lowercase for convenience
 */


int word = 0, character = 0;
for (int i = 0; i < strlen(example); i++) {
    example[i] = tolower(example[i]);
    if (example[i] == ' ') {
        if (example[i + 1] != ' ') {
            split[word][character] = '\0';
            character = 0;
            word++;
        }
        continue;
    } else {
        split[word][character++] = example[i];
    }
}

split[word][character] = '\0';

/*
 * classify string - compare input with all classifiers
 */
int classification_score = 0;
for (int class = 0 ; class < LAST_FIELD ; class++) {
	for (int v = 0; v <= word; v++) {
		for (int b = 0; b < NUM_WORDS; b++) {

			for (int c = 0; c < WORD_LEN; c++) {
				if ((classifier[class][b][c]) && (strcmp(classifier[class][b][c], split[v]) == 0)) {
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
for (int class = 0; class < LAST_FIELD; class++) {
	if (scores[class] > score) {
		score = scores[class];
		strcpy(result, catagories_str[class]);
	}
}
