# See LICENSE file for copyright and license details.

CC   = cc
SRC  = log.c
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog

CFLAGS  = -O2 -pipe -Wall -Werror --std=c89 -ansi -pedantic
LDFLAGS =

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -fPIC -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -fPIC -c $<

all: ${LIBNAME:=.so} ${LIBNAME:=.a}

clean:
	rm -f *.o ${LIBNAME}.*


# Targets for testing application
main.o:
	${CC} ${CFLAGS} -c $<

test-app: main.o ${OBJ}
	${CC} ${LDFLAGS} -o $@ main.o ${OBJ}
