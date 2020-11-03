#include "deps.h"

struct timeval start_time, end_time;


int main(int argc, char *argv[]) {
  printf("\033[1;31mWord Counter\033[0m\n");

  char words_to_search[25][25]  = {};
  int words_occurrences[25] = {};
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
  char * line = strtok(botd, "\n");
  while(line != NULL) {
    strcpy(lines[line_count], line);
    line = strtok(NULL, "\n");
    line_count++;
  }

  gettimeofday(&start_time, NULL);
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
  gettimeofday(&end_time, NULL);
  double seconds_spent = end_time.tv_sec - start_time.tv_sec;
  double milliseconds_spent =  (end_time.tv_usec - start_time.tv_usec)/1000000.0;
  double time_spent = seconds_spent + milliseconds_spent;
  printf("Time spent searching: %f\n", time_spent);

  printf("Searched words found:\n");
  for (int i = 0; i < amount_of_words_to_search; i++) {
    char * word_searched = words_to_search[i];
    int number_of_occurrences = words_occurrences[i];
    printf("\033[1;36m%s\033[0m found \033[1;35m%d\033[0m times\n", word_searched, number_of_occurrences);
  }
  return 0;
}
