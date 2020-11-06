#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/time.h>
#include <ctype.h>
#include "word_entry.c"
#include "texts.h"
#define TEXT_SIZE 525
#define LINE_SIZE 90

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}
