#include "polynom.h"

int main(void)
{
  polynom f, g;

  InitPolynom(&f);
  InitPolynom(&g);
  
  SetPolynom(&f, 4, 0, 1, 0, 1);
  SetPolynom(&g, 11, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1);
  PrintPolynom(&f);

  ShiftPolynom(&f, 10);
  PrintPolynom(&f);

  PrintPolynom(&g);
  
  ModPolynom(&f, &g);
  PrintPolynom(&f);

  ClearPolynom(&f);
  ClearPolynom(&g);

  return 0;
}

