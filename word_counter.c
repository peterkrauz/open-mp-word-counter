#include "deps.h"
#include "texts.h"


int main(int argc, char *argv[]) {
  printf("\033[1;31mWord Counter\033[0m\n");

  char words_to_search[50][50]  = {};
  int words_occurrences[50] = {};
  int amount_of_words_to_search = argc - 1;
  if (argc > 1) {
    for (int i = 0; i < amount_of_words_to_search; i++) {
      strcpy(words_to_search[i], argv[i + 1]);
      words_occurrences[i] = 0;
    }
  }

  printf("Words that'll be searched:\n");
  for (int i = 0; i < amount_of_words_to_search; i++) {
    printf("\033[1;36m %s \033[0m\n", words_to_search[i]);
  }

  // Build array of lines
  int line_count = 0;
  char lines[200][200] = {};
  char * line = strtok(the_raven, "\n");

  while(line != NULL) {
    strcpy(lines[line_count], line);
    line = strtok(NULL, "\n");
    line_count++;
  }

  // Iterate through each line
  for (int i = 0; i < line_count; i++) {
    char * current_line = lines[i];
    int has_found_occurrence = 0;

    // See if it contains one of the searched words
    for (int k = 0; k < amount_of_words_to_search; k++) {
      char * word_to_search = toLower(words_to_search[k]);
      char * substring_result = strstr(toLower(current_line), word_to_search);

      // Increment this word's occurrences
      if (substring_result != NULL) {
        words_occurrences[k]++;
        has_found_occurrence = 1;
      }
    }
  }

  printf("Searched words found:\n");
  for (int i = 0; i < amount_of_words_to_search; i++) {
    char * word_searched = words_to_search[i];
    int number_of_occurrences = words_occurrences[i];
    printf("\033[1;36m%s\033[0m found \033[1;35m%d\033[0m times\n", word_searched, number_of_occurrences);
  }
  return 0;
}
