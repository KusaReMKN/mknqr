# 各種マクロ (再)定義
CC = gcc
CFLAGS = -Wall
OBJS = main.o polynom.o alpha.o
VPATH = src
PROGRAM = mknqr
DEPEND = depend.inc
SHELL = /bin/sh

# プライマリターゲット
.PHONY: all
all: depend ${PROGRAM}

# プログラム生成
${PROGRAM}: ${OBJS}
	${CC} -o $@ ${OBJS}

# 不要ファイル削除
.PHONY: clean
clean:
	${RM} ${OBJS} ${PROGRAM} ${DEPEND}

# 依存関係記述
.PHONY: depend
depend: ${OBJS:.o=.c}
	-@ ${RM} ${DEPEND}
	-@ for i in $^; do cpp -MM $$i | sed "s/\ [_a-zA-Z0-9]+\.c//g" >> ${DEPEND}; done

# 依存関係をインクルード
-include ${DEPEND}
