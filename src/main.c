#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define _GNU_SOURCE
#include <getopt.h>

#define MAJOR 0
#define MINOR 0

static const char Level[] = "lmqh";

static struct option longopts[] = {
  {"help",    no_argument,       NULL, 'h'},
  {"version", no_argument,       NULL, 'v'},
  {"level",   required_argument, NULL, 'l'},
  {"Version", required_argument, NULL, 'V'},
  {0, 0, 0, 0}
};

void help(const char *);

int main(int argc, char *argv[])
{
  int opt;

  while (~(opt = getopt_long(argc, argv, "vhl:V:", longopts, NULL))) {
    switch (opt) {
    case 'v':
      printf("%s Version %1d.%02d\n", argv[0], MAJOR, MINOR);
      exit(EXIT_SUCCESS);
      /* NOTREACHED */
    case 'h':
      help(argv[0]);
      exit(EXIT_SUCCESS);
      /* NOTREACHED */
    case 'l':
    case 'V':
      printf("not implemented\n");
    case '?':
      exit(EXIT_FAILURE);
      /* NOTREACHED */
    }
  }

  return 0;
}

void help(const char *cmd)
{
  printf((
        "Usage:\n"
        "    %s [options] [string]\n"
        "\n"
        ), cmd);
  printf((
        "    -h, --help          Display this help messaage\n"
        "    -v, --version       Display version info\n"
        ));
}
