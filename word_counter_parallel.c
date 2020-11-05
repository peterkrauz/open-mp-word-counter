#include "deps.h"

struct timeval start_time, end_time;


/*
 * Sequentially iterates through block of text,
 * dismembering it into an array of lines, where each
 * array entry points to a line.
 *
 * Then, concurrently iterate through "blocks" of lines,
 * safely increment - using occurrences_mutex - the number of occurrences
 * of each word in that line.
 */
int main(int argc, char *argv[]) {
  printf("\033[1;31mOpenMP Word Counter\033[0m\n");

  pthread_mutex_t occurrences_mutex[] = {};
  char words_to_search[25][25]  = {};
  int words_occurrences[25] = {};
  int amount_of_words_to_search = 0; // One parameter is ./<exe> and the other is the number of threads
  int number_of_threads = 4;
  if (argc > 1) {
    number_of_threads = atoi(argv[1]);
    amount_of_words_to_search = argc - 2;
    for (int i = 0; i < amount_of_words_to_search; i++) {
      strcpy(words_to_search[i], argv[i + 2]);
      words_occurrences[i] = 0;
    }
    // Dynamically populate mutex array
    for (int i = 0; i < number_of_threads; i++) {
      pthread_mutex_init(&occurrences_mutex[i], NULL);
    }
  }

  printf("Using %d threads, words that'll be searched are:\n", number_of_threads);
  for (int i = 0; i < amount_of_words_to_search; i++) {
    printf("\033[1;36m %s \033[0m\n", words_to_search[i]);
  }

  // Sequentially build array of lines
  int line_count = 0;
  char lines[TEXT_SIZE][LINE_SIZE] = {};
  char * line = strtok(botd, "\n");
  while(line != NULL) {
    strcpy(lines[line_count], line);
    line = strtok(NULL, "\n");
    line_count++;
  }

  int chunk_size = line_count / number_of_threads;
  int extra_lines = line_count % number_of_threads;

  gettimeofday(&start_time, NULL);
  #pragma omp parallel for
  for (int thread_count = 0; thread_count < number_of_threads; thread_count++) {
    // Each thread should search just a chunk of the whole list of lines
    int chunk_offset = thread_count * chunk_size;
    int start_limit = 1 + chunk_offset;
    int end_limit = chunk_size + chunk_offset;

    // Initial chunk starts at 0
    if (thread_count == 0) {
      start_limit -= 1;
    }

    // Last chunk searches indices that "escaped" the integer division
    if (thread_count == number_of_threads - 1) {
      end_limit += extra_lines;
    }

    printf(
      "Thread nº%d searching occurrences from line: \n\n %s \n\n to  %s \n",
      thread_count,
      lines[start_limit],
      lines[end_limit]
    );
    for (int i = start_limit; i < end_limit; i++) {
      char * current_line = lines[i];

      // See if it contains one of the searched words
      for (int k = 0; k < amount_of_words_to_search; k++) {
        char * word_to_search = toLower(words_to_search[k]);
        char * substring_result = strstr(toLower(current_line), word_to_search);

        // Safely increment this word's occurrences
        if (substring_result != NULL) {
          pthread_mutex_lock(&occurrences_mutex[k]);
          words_occurrences[k]++;
          pthread_mutex_unlock(&occurrences_mutex[k]);
        }
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
