#include "polynom.h"

int main(void)
{
  polynom f;

  InitPolynom(&f);
  SetPolynom(&f, 3, 3, 2, 1);
  PrintPolynom(&f);
  ShiftPolynom(&f, 4);
  PrintPolynom(&f);
  xPolynom(&f, 3);
  PrintPolynom(&f);
  ClearPolynom(&f);
  return 0;
}

