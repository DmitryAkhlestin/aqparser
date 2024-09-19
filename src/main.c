#define _GNU_SOURCE
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "adjacent.h"
#include "log.h"

extern int map[NUMBER_LETTERS];

static void help(void)
{
  print_out(
    "Usage: aqparser [OPTION]...\n"
    "Analyzes a dictionary of English words and determines how many\n"
    "of them can be typed on an English QWERTY keyboard by moving\n"
    "only on adjacent keys.\n"
    "You can press the same key twice in a row.\n\n"
    "-h       Print this help\n"
    "-f path  Path to the file with the word dictionary");
}

static int aq_parser(const char *pathname)
{
  FILE *fp;
  size_t buffer_len;
  ssize_t rb;
  char *line;
  int passed_lines;

  if (pathname == NULL) {
    return EINVAL;
  }

  fp = fopen(pathname, "r");
  if (fp == NULL) {
    return errno;
  }

  line = NULL;
  //buffer_len = 0;
  passed_lines = 0;

  while ((rb = getline(&line, &buffer_len, fp)) != EOF) {
    if (line[rb - 1] == '\n') {
      line[rb - 1] = '\000';
    }
    
    /*we should not count empty string*/
    if (rb == 1)
      continue;

    if (is_word_correct(line)) {
      ++passed_lines;
      print_out("passed: %s", line);
    } else {
      print_out("not passed: %s", line);
    }
  }

  fclose(fp);

  if (line != NULL) {
    free(line);
  }

  if (passed_lines > 0) {
    print_out("Passed number: %d", passed_lines);
  } else {
    print_out("All words are not passed");
  }

  return 0;
}

int main(int argc, char **argv)
{
  char *pathname;
  int result;
  int c;

  pathname = NULL;

  while ((c = getopt(argc, argv, "f:h")) != EOF) {
    switch(c) {
      case 'f':
        pathname = optarg;
        break;
      case 'h':
        help();
        return 0;
      default:
        print_err("Use -h to get help");
        return EINVAL;
    }
  }

  if (pathname == NULL) {
    print_err("Option -f is required. Use -h to get help");
    return 0;
  }
  result = initialize_maps();
  result = aq_parser(pathname);
  if (result != 0) {
    print_err("%s", strerror(result));
    return result;
  }

  return 0;
}
