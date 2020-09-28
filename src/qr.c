#include "qr.h"

int GetMode(const char *str)
{
  regex_t number, alnum;
  const char *numptn = "^[0-9]*$",
             *alnptn = "^[0-9A-Z $%*+-./:]*$";
  int ret = -1;

  if (regcomp(&number, numptn, REG_EXTENDED | REG_NOSUB | REG_NEWLINE)) {
    goto QUIT_2;
  }
  if (regcomp(&alnum, alnptn, REG_EXTENDED | REG_NOSUB | REG_NEWLINE)) {
    goto QUIT_1;
  }

  if (!regexec(&number, str, 0, NULL, 0)) {
    ret = MODE_NUMBER;
  }
  else if (!regexec(&alnum, str, 0, NULL, 0)) {
    ret = MODE_ALNUM;
  }
  else {
    ret = MODE_8BIT;
  }

  regfree(&alnum);
QUIT_1:
  regfree(&number);
QUIT_2:
  return ret;
}
