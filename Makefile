# See LICENSE file for copyright and license details.

CC   = cc
SRC  = log.c
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog

#CFLAGS  = -O2 -pipe -Wall -Werror --std=c89 -ansi -pedantic -fPIC
CFLAGS  = -O2 -pipe --std=c89 -ansi -pedantic -fPIC
LDFLAGS =

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -fPIC -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -c $<

all: ${LIBNAME:=.so} ${LIBNAME:=.a}

clean:
	rm -f *.o ${LIBNAME}.*

test-app: main.o ${OBJ}
	${CC} ${LDFLAGS} -o $@ main.o ${OBJ}
