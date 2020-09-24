#include "polynom.h"

size_t DIMENSION = 4096;

int InitPolynom(polynom *pp)
{
  return InitPolynom2(pp, DIMENSION);
}

int InitPolynom2(polynom *pp, size_t len)
{
  polynom tmp = { 0, NULL };

  tmp.dim = len;
  tmp.coeff = (int *)calloc(tmp.dim, sizeof(int));
  if (tmp.coeff) {
    *pp = tmp;
    return 0;
  }
  return -1;
}

int ClearPolynom(polynom *pp)
{
  pp->dim = 0;
  free(pp->coeff);
  pp->coeff = NULL;
  return 0;
}

int SetPolynom(polynom *pp, size_t len, ...)
{
  va_list ap;
  
  if (pp->dim < len) { return -1; }

  memset(pp->coeff, 0, pp->dim * sizeof(int));

  va_start(ap, len);
  for (size_t l = 0; l < len; l++) {
    pp->coeff[l] = va_arg(ap, int);
  }
  va_end(ap);

  return 0;
}

int SetPolynom2(polynom *pp, size_t len, int *v)
{
  if (pp->dim < len) { return -1; }

  memset(pp->coeff, 0, pp->dim * sizeof(int));

  for (size_t l = 0; l < len; l++) {
    pp->coeff[l] = v[l];
  }

  return 0;
}

int CopyPolynom(polynom *dest, polynom *src)
{
  return SetPolynom2(dest, src->dim, src->coeff);
}

int AddPolynom(polynom *dest, polynom *src)
{
  if (dest->dim < src->dim) { return -1; }

  for (size_t l = 0; l < src->dim; l++) {
    dest->coeff[l] += src->coeff[l];
  }

  return 0;
}

int SubPolynom(polynom *dest, polynom *src)
{
  if (dest->dim < src->dim) { return -1; }

  for (size_t l = 0; l < src->dim; l++) {
    dest->coeff[l] -= src->coeff[l];
  }

  return 0;
}

int XorPolynom(polynom *dest, polynom *src)
{
  if (dest->dim < src->dim) { return -1; }

  for (size_t l = 0; l < src->dim; l++) {
    dest->coeff[l] ^= src->coeff[l];
  }

  return 0;
}

int xPolynom(polynom *pp, int k)
{
  for (size_t l = 0; l < pp->dim; l++) {
    pp->coeff[l] *= k;
  }

  return 0;
}

size_t MaxDimension(polynom *pp)
{
  size_t max = 0;

  for (size_t l = 0; l < pp->dim; l++) {
    if (pp->coeff[l]) {
      max = l;
    }
  }

  return max;
}

int ShiftPolynom(polynom *pp, size_t n)
{
  polynom tmp;

  if (pp->dim < MaxDimension(pp) + n) { return -1; }

  InitPolynom2(&tmp, pp->dim);
  SetPolynom(&tmp, 0);
  for (size_t l = 0; l < MaxDimension(pp) + 1; l++) {
    tmp.coeff[l+n] = pp->coeff[l];
  }
  CopyPolynom(pp, &tmp);
  ClearPolynom(&tmp);

  return 0;
}

int PrintPolynom(polynom *pp)
{
  for (size_t l = MaxDimension(pp) + 1; l > 0; l--) {
    if (pp->coeff[l-1]) {
      printf("%+dx^%u ", pp->coeff[l-1], l-1);
    }
  }
  putchar('\n');

  return 0;
}

int MulPolynom(polynom *dest, polynom *src)
{
  polynom res, tmp;

  if (dest->dim < MaxDimension(dest) + MaxDimension(src)) { return -1; }

  InitPolynom2(&res, dest->dim);
  InitPolynom2(&tmp, dest->dim);
  SetPolynom(&res, 0);
  CopyPolynom(&tmp, dest);

  for (size_t l = 0; l < MaxDimension(src) + 1; l++) {
    if (!src->coeff[l]) { continue; }

    CopyPolynom(&tmp, dest);
    ShiftPolynom(&tmp, l);
    xPolynom(&tmp, src->coeff[l]);
    AddPolynom(&res, &tmp);
  }

  CopyPolynom(dest, &res);

  ClearPolynom(&tmp);
  ClearPolynom(&res);

  return 0;
}

int ModPolynom(polynom *dest, polynom *src)
{
  polynom tmp;

  if (MaxDimension(src) == 0u && src->coeff[0] == 0) { return -1; }

  InitPolynom2(&tmp, dest->dim);
  while (MaxDimension(src) <= MaxDimension(dest)) {
    CopyPolynom(&tmp, src);
    ShiftPolynom(&tmp, MaxDimension(dest) - MaxDimension(src));
    xPolynom(&tmp, dest->coeff[MaxDimension(dest)] / src->coeff[MaxDimension(src)]);
    SubPolynom(dest, &tmp);
  }
  ClearPolynom(&tmp);

  return 0;
}

size_t MaxDimensionAlpha(polynom *pp)
{
  size_t max = 0;

  for (size_t l = 0; l < pp->dim; l++) {
    if (~pp->coeff[l]) {
      max = l;
    }
  }

  return max;
}

int xAlphaPolynom(polynom *pp, int k)
{
  for (size_t l = 0; l < MaxDimensionAlpha(pp) + 1; l++) {
    pp->coeff[l] += k;
  }

  return 0;
}

int Alpha2Polynom(polynom *pp)
{
  for (size_t l = 0; l < pp->dim; l++) {
    pp->coeff[l] = alpha2int(pp->coeff[l]);
  }
  return 0;
}

int ShiftAlphaPolynom(polynom *pp, size_t n)
{
  polynom tmp;

  if (pp->dim < MaxDimensionAlpha(pp) + n) { return -1; }

  InitPolynom2(&tmp, pp->dim);
  SetAlphaPolynom(&tmp, 0);
  for (size_t l = 0; l < MaxDimensionAlpha(pp) + 1; l++) {
    tmp.coeff[l+n] = pp->coeff[l];
  }
  CopyPolynom(pp, &tmp);
  ClearPolynom(&tmp);

  return 0;
}

int ModAlphaPolynom(polynom *dest, polynom *src)
{
  polynom tmp;

  if (MaxDimensionAlpha(src) == 0 && src->coeff[0] == ~0) { return -1; }

  InitPolynom2(&tmp, dest->dim);
  while (MaxDimensionAlpha(src) <= MaxDimension(dest)) {
    CopyPolynom(&tmp, src);
    xAlphaPolynom(&tmp, int2alpha(dest->coeff[MaxDimension(dest)]) - src->coeff[(MaxDimensionAlpha(src))]);
    ShiftAlphaPolynom(&tmp, MaxDimension(dest) - MaxDimensionAlpha(src));
    Alpha2Polynom(&tmp);
    XorPolynom(dest, &tmp);
  }
  ClearPolynom(&tmp);

  return 0;
}

int SetAlphaPolynom(polynom *pp, size_t len, ...)
{
  va_list ap;
  
  if (pp->dim < len) { return -1; }

  memset(pp->coeff, ~0, pp->dim * sizeof(int));

  va_start(ap, len);
  for (size_t l = 0; l < len; l++) {
    pp->coeff[l] = va_arg(ap, int);
  }
  va_end(ap);

  return 0;
}

int SetAlphaPolynom2(polynom *pp, size_t len, int *v)
{
  if (pp->dim < len) { return -1; }

  memset(pp->coeff, ~0, pp->dim * sizeof(int));

  for (size_t l = 0; l < len; l++) {
    pp->coeff[l] = v[l];
  }

  return 0;
}

int PrintAlphaPolynom(polynom *pp)
{
  for (size_t l = MaxDimension(pp) + 1; l > 0; l--) {
    if (~pp->coeff[l-1]) {
      printf("+α^%dx^%u ", pp->coeff[l-1], l-1);
    }
  }
  putchar('\n');

  return 0;
}
