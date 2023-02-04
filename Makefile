# See LICENSE file for copyright and license details.

include libs.config.mk

CC   = cc
SRC != find src -name "*.c"
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog

CFLAGS  = -Wall -ansi --std=c89 -pedantic ${OPT} ${LIBINC}
LDFLAGS = ${LIBS}

dist: static shared

# ar -rc libaz.a libabc.a libxyz.a
static: libs
	@make OPT='-O2 -pipe -Werror' ${LIBNAME:=.a}
	rm -f ${OBJ}

shared: libs
	@make OPT='-O2 -pipe -Werror -fPIC' ${LIBNAME:=.so}
	rm -f ${OBJ}

debug:
	@make OPT=-g all

all: ${LIBNAME:=.so} ${LIBNAME:=.a}

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJ} ${LIBNAME}.* *.core
	cd test && make clean

tests: all
	cd test && make clean tests

include libs.target.mk
