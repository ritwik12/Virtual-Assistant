#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_CLASSIFIERS 100
#define MAX_WORD_LEN 50
#define LAST_FIELD 10  // Adjust this as needed

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} Classifier;

int main() {
    char example[1000]; // Replace with your input
    int word = 0;

    // Splitting the input string into words
    Classifier split; // Using a dynamic array for words
    split.count = 0;
    
    for (int iter_char = 0; example[iter_char] != '\0'; iter_char++) {
        example[iter_char] = tolower(example[iter_char]);
        if (example[iter_char] == ' ') {
            if (word > 0) {
                split.words[word][split.count] = '\0';
                split.count = 0;
                word++;
            }
        } else {
            split.words[word][split.count++] = example[iter_char];
        }
    }
    if (split.count > 0) {
        split.words[word][split.count] = '\0';
        word++;
    }

    // Assuming classifiers are already loaded into a suitable data structure
    Classifier classifier[LAST_FIELD][MAX_CLASSIFIERS];
    // ...

    // Classification Scoring
    int scores[LAST_FIELD] = {0};
    for (int class = 0; class < LAST_FIELD; class++) {
        for (int iter_input = 0; iter_input < word; iter_input++) {
            for (int iter_classifier = 0; iter_classifier < MAX_CLASSIFIERS; iter_classifier++) {
                for (int iter_classifier_w = 0; iter_classifier_w < classifier[class][iter_classifier].count; iter_classifier_w++) {
                    if (strcmp(classifier[class][iter_classifier].words[iter_classifier_w], split.words[iter_input]) == 0) {
                        scores[class]++;
                    }
                }
            }
        }
    }

    // Finding Highest Classifier Score
    int maxScore = -1;
    int maxScoreIndex = -1;
    for (int class = 0; class < LAST_FIELD; class++) {
        if (scores[class] > maxScore) {
            maxScore = scores[class];
            maxScoreIndex = class;
        }
    }

    // Print the result
    if (maxScoreIndex != -1) {
        printf("Result: %s\n", catagories_str[maxScoreIndex]); // Replace with the correct array
    }

    return 0;
}
