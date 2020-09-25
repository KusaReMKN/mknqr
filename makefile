
CC = gcc
OBJ = main.o polynom.o alpha.o
VPATH = src
PROGRAM = mknqr


all : ${PROGRAM}



${PROGRAM} : ${OBJ}
	${CC} -o $@ ${OBJ}



polynom.o : polynom.h

alpha.o : alpha.h



.PHONY : clean

clean :
	${RM} ${OBJ} ${PROGRAM}

