#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define _GNU_SOURCE
#include <getopt.h>

#define MAJOR 0
#define MINOR 0

static struct option longopts[] = {
  {"help",    no_argument, NULL, 'h'},
  {"version", no_argument, NULL, 'v'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
  int opt;

  while (~(opt = getopt_long(argc, argv, "vh", longopts, NULL))) {
    switch (opt) {
    case 'v':
      printf("%s Version %1d.%02d\n", argv[0], MAJOR, MINOR);
      exit(EXIT_SUCCESS);
      /* NOTREACHED */
    case 'h':
      printf("Usage:\n    %s [options] [string]\n\n", argv[0]);
      printf("    -h, --help\t\tshow list of command-line options\n");
      printf("    -v, --version\t\tshow version\n");
      exit(EXIT_SUCCESS);
      /* NOTREACHED */
    case '?':
      exit(EXIT_FAILURE);
      /* NOTREACHED */
    }
  }

  return 0;
}
