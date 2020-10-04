多項式演算関数群
================

多項式型
--------

多項式を表す型として `polynom` 型を利用する。
`polynom` 型は以下のように宣言されている。

    typedef struct _polynom_t {
      size_t  dim;    // 多項式の表現可能な次元数
      int    *coeff;  // 多項式の各係数が格納されている配列へのポインタ
    } polynom;


多項式の初期化・解放
--------------------

多項式は使用する前に初期化されなければならない。
多項式を初期化するもっとも簡単な方法は `InitPolynom` 関数を利用することである。

    int InitPolynom(polynom *pp);

`InitPolynom` 関数には初期化する多項式へのポインタ `pp` を渡す。
`InitPolynom` 関数は、多項式が表現可能な次元数に広域変数 `DIMENSION`
の値を利用する。
初期化に成功すると `0` を、失敗すると `-1` を返す。

多項式が表現可能な次元数を指定しながら多項式を初期化するには `InitPolynom2`
 関数を利用する。

    int InitPolynom2(polynom *pp, size_t len);

`InitPolynom2` 関数は多項式の表現可能な次元数を `len` に設定すること以外は
`InitPolynom` 関数と同様である。
`InitPolynom(pp)` は `InitPolynom2(pp, DIMENSION)` と全く同じである。

使用の終了した多項式はなるべく早く解放されなければならない。
多項式を解放するには `ClearPolynom` 関数を利用する。

    int ClearPolynom(polynom *pp);

`ClearPolynom` 関数には解放する多項式へのポインタ `pp` を渡す。
`ClearPolynom` 関数は常に `0` を返す。
初期化されていない多項式を `ClearPolynom` 関数に渡したときの動作は不定である。


多項式のセット・コピー
----------------------

多項式の係数を設定する方法の一つは `SetPolynom` 関数を利用することである。

    int SetPolynom(polynom *pp, size_t len, ...);

`SetPolynom` 関数には係数を設定する多項式へのポインタ `pp`
と係数を設定する次元数 `len`、それに続いて各係数の値を `int`
で昇べきの順で渡す。
係数の設定に成功すると `0` を、失敗すると `-1` を返す。
失敗の主な理由は多項式の表現可能な次元数が足りないことである。
`len` の値を 0 で渡すことですべての係数を 0 に設定することができる。

例えば、 $ f(x) = 3x^2 -5x +2 $ を表現するには以下のように実行する。

    polynom f;
    InitPolynom(f);
    SetPolynom(&f, (size_t) 3, 2, -5, 3);

多項式の係数を設定するもう一つの方法は `SetPolynom2` 関数を利用することである。

    int SetPolynom2(polynom *pp, size_t len, int *v);

`SetPolynom2` 関数は係数のリストを可変引数の代わりに配列で渡すこと以外は
`SetPolynom` 関数と同様である。

多項式をコピーするには `CopyPolynom` 関数を利用する。

    int CopyPolynom(polynom *dest, polynom *src);

`CopyPolynom(pp1, pp2)` は `SetPolynom2(pp1, pp2->dim, pp2->coeff)`
と全く同じである。


多項式の加減算
--------------

多項式の加算をするには `AddPolynom` 関数を利用する。

    int AddPolynom(polynom *dest, polynom *src);

`AddPolynom` 関数には多項式へのポインタ `dest` と `src` を渡す。
`AddPolynom` 関数は成功すると `0` を、失敗すると `-1` を返す。
多項式 `dest` は多項式 `dest` と多項式 `src` を足し合わせたものに上書きされる。

多項式の減算をするには `SubPolynom` 関数を利用する。

    int SubPolynom(polynom *dest, polynom *src);

`SubPolynom` 関数は減算を行うこと以外は `AddPolynom` 関数と同様である。


多項式の排他的論理和
--------------------

多項式の各係数ごとの排他的論理和を計算するには `XorPolynom` 関数を利用する。

    int XorPolynom(polynom *dest, polynom *src);

`XorPolynom` 関数は排他的論理和を計算すること以外は `AddPolynom`
関数と同様である。


多項式の整数倍
--------------

多項式を整数倍するには `xPolynom` 関数を利用する。

    int xPolynom(polynom *pp, int k);

`xPolynom` 関数には多項式へのポインタ `pp` と係数 `k` を渡す。
`xPolynom` 関数は常に `0` を返す。


多項式の最大次元数
------------------

多項式の最大次元数を求めるには `MaxDimension` 関数を利用する。

    size_t MaxDimension(polynom *pp);

`MaxDimension` 関数には多項式へのポインタ `pp` を渡す。
`MaxDimension` 関数は渡された多項式の最大次元数を返す。
渡された多項式の値が 0 の場合は `0` を返す (定数式 0x^0 とみなす)。


多項式の x^n 倍
---------------

多項式を x^n 倍するには `ShiftPolynom` 関数を利用する。

    int ShiftPolynom(polynom *pp, size_t n);

`ShiftPolynom` 関数には多項式へのポインタ `pp` と x の指数 `n` を渡す。
`ShiftPolynom` 関数は成功すると `0` を、失敗すると `-1` を返す。


多項式の乗算
------------

多項式同士を乗算するには `MulPolynom` 関数を利用する。

    int MulPolynom(polynom *dest, polynom *src);

`MulPolynom` 関数には多項式へのポインタ `dest` と `src` を渡す。
`MulPolynom` 関数は成功すると `0` を、失敗すると `-1` を返す。
係数のオーバーフローに注意すること。


多項式の剰余
------------

多項式の剰余を計算するには `ModPolynom` 関数を利用する。

    int ModPolynom(polynom *dest, polynom *src);

`ModPolynom` 関数には多項式へのポインタ `dest` と `src` を渡す。
`ModPolynom` 関数は成功すると `0` を、失敗すると `-1` を返す。
失敗の主な理由は `src` の値が 0 であることである。


多項式の表示
------------

多項式を標準出力に表示するには `PrintPolynom` 関数を利用する。

    int PrintPolynom(polynom *pp);

`PrintPolynom` 関数には多項式へのポインタ `pp` を渡す。
`PrintPolynom` 関数は常に `0` を返す。
多項式は降べきの順に、係数が 0 でないもののみが表示され、改行される
(多項式のすべての係数が 0 の場合は単に改行される)。


α のべき乗表示
--------------

リード・ソロモン符号などで利用する α のべき乗表記に対応した演算関数もある。
これらの関数は係数を α
のべき乗表記として扱う以外は対応する通常の多項式演算関数と同様である。

    size_t MaxDimensionAlpha(polynom *pp);
    int xAlphaPolynom(polynom *pp, int k);
    int ShiftAlphaPolynom(polynom *pp, size_t n);
    int ModPolynom(polynom *dest, polynom *src);
    int SetAlphaPolynom(polynom *pp, size_t len, ...);
    int SetAlphaPolynom2(polynom *pp, size_t len, int *v);
    int PrintAlphaPolynom(polynom *pp);

α のべき乗表記から通常の多項式に変換するには `Alpha2Polynom` 関数を利用する。

    int Alpha2Polynom(polynom *pp);

`Alpha2Polynom` 関数には多項式へのポインタ `pp` を渡す。
`Alpha2Polynom` 関数は常に `0` を返す。
