#include "qr.h"

int CheckMode(const char *str, int mode)
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

  switch (mode) {
  case 0:
    /* FALLTHROUGH */
  case MODE_NUMBER:
    if (!regexec(&number, str, 0, NULL, 0)) {
      ret = MODE_NUMBER;
      break;
    }
    /* FALLTHROUGH */
  case MODE_ALNUM:
    if (!regexec(&alnum, str, 0, NULL, 0)) {
      ret = MODE_ALNUM;
      break;
    }
    /* FALLTHROUGH */
  case MODE_8BIT:
    ret = MODE_8BIT;
    break;
  default:
    break;
  }

  regfree(&alnum);
QUIT_1:
  regfree(&number);
QUIT_2:
  return ret;
}

int InitQRData(qrdata *p)
{
  const qrdata zero = { 0, NULL, 0, NULL };
  memcpy(p, &zero, sizeof(qrdata));

  return 0;
}

int ClearQRData(qrdata *p)
{
  free(p->buf);
  InitQRData(p);

  return 0;
}
