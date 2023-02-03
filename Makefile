# See LICENSE file for copyright and license details.

include libs.mk

CC   = cc
SRC != find src -name "*.c"
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog

CFLAGS  = -Wall -ansi --std=c89 -pedantic ${OPT}
LDFLAGS =


dist:
	@make OPT='-O2 -pipe -Werror' all

debug:
	@make OPT=-g all

all: ${LIBNAME:=.so} ${LIBNAME:=.a}

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -fPIC -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -fPIC -c $< -o $@

clean:
	rm -f ${OBJ} ${LIBNAME}.* *.core
	cd test && make clean

tests: all
	cd test && make clean tests
