# See LICENSE file for copyright and license details.

CC   = cc
SRC != find * -name '*.c'
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog

CFLAGS  = -O2 -pipe -Wall -Werror --std=c89 -ansi
LDFLAGS =

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -c $<

all: ${LIBNAME:=.so} ${LIBNAME:=.a}

clean:
	rm -f *.o ${LIBNAME}.*
