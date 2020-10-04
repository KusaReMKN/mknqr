#ifndef __QR_H__
#define __QR_H__

#include <stddef.h>
#include <string.h>
#include <malloc.h>

#include <sys/types.h>
#include <regex.h>

#define MODE_NUMBER 0x01
#define MODE_ALNUM  0x02
#define MODE_8BIT   0x04
#define MODE_KANJI  0x08
#define MODE_ECI    0x07

typedef struct _qrdata_t {
  size_t bitlen;
  unsigned char *buf;
  size_t buflen;
  struct _qrdata_t *next;
} qrdata;

int CheckMode(const char *, int);

int InitQRData(qrdata *);
int ClearQRData(qrdata *);

#endif /* __QR_H__ */
