#include "polynom.h"

int main(void)
{
  polynom f, g;

  InitPolynom(&f);
  InitPolynom(&g);
  
  SetPolynom(&f, 9, 236, 128, 46, 220, 41, 69, 205, 65, 32);
  SetAlphaPolynom(&g, 18, 136, 163, 243, 39, 150, 99, 24, 147, 214, 206, 123, 239, 43, 78, 206, 139, 43, 0);
  PrintPolynom(&f);

  ShiftPolynom(&f, 17);
  PrintPolynom(&f);

  PrintAlphaPolynom(&g);
  
  ModAlphaPolynom(&f, &g);
  PrintPolynom(&f);

  ClearPolynom(&f);
  ClearPolynom(&g);

  return 0;
}

