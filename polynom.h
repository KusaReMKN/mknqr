#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include <stddef.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "alpha.h"

// 多項式のデフォルト最大次元
extern size_t DIMENSION;

// 多項式型
typedef struct _polynom_t {
  size_t dim;
  int *coeff;
} polynom;

// 多項式の初期化
int InitPolynom(polynom *);
int InitPolynom2(polynom *, size_t);

// 多項式の解放
int ClearPolynom(polynom *);

// 多項式のセット
int SetPolynom(polynom *, size_t, ...);
int SetPolynom2(polynom *, size_t, int *);

// 多項式のコピー
int CopyPolynom(polynom *, polynom *);

// 多項式の加減算
int AddPolynom(polynom *, polynom *);
int SubPolynom(polynom *, polynom *);

// 多項式の XOR
int XorPolynom(polynom *, polynom *);

// 多項式の k 倍
int xPolynom(polynom *, int);

// 最高次数
size_t MaxDimension(polynom *);

// 多項式の x^n 倍
int ShiftPolynom(polynom *, size_t);

// 多項式の表示
int PrintPolynom(polynom *);

// 多項式同士の掛け算
int MulPolynom(polynom *, polynom *);

// 多項式同士の剰余
int ModPolynom(polynom *, polynom *);

// α多項式の最高次数
size_t MaxDimensionAlpha(polynom *);

// 全部の項に足す
int xAlphaPolynom(polynom *, int);

// α多項式からの変換
int Alpha2Polynom(polynom *);

// 多項式をα多項式で割ったあまり
int ModAlphaPolynom(polynom *, polynom *);

// x^n 倍
int ShiftAlphaPolynom(polynom *, size_t);

// 多項式のセット
int SetAlphaPolynom(polynom *, size_t, ...);
int SetAlphaPolynom2(polynom *, size_t, int *);

// α式の表示
int PrintAlphaPolynom(polynom *);

#endif /* __POLYNOM_H__ */
