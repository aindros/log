# See LICENSE file for copyright and license details.

include libs.config.mk

CC   = cc
SRC != find src -name "*.c"
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog
LIBVER  = 0.0.0-a1

CFLAGS  = -Wall -ansi --std=c89 -pedantic ${OPT} ${LIBINC} -DLIBVER=\"${LIBVER}\"
LDFLAGS = ${LIBS}

dist: static shared

static: libs
	@make OPT='-O2 -pipe -Werror' ${LIBNAME:=.a}
	rm -f ${OBJ}

shared: libs
	@make OPT='-O2 -pipe -Werror -fPIC' ${LIBNAME:=.so}
	rm -f ${OBJ}

debug:
	@make OPT=-g all

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
#	ar rcs $@ ${OBJ}
	mkdir build
	cd build && ar -x ../${LIBSTR_PATH}
	ar rcs $@ ${OBJ} build/*
	rm -rf build

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJ} ${LIBNAME}.* *.core
	rm -rf build
	cd test && make clean

tests: dist
	cd test && make clean tests

include libs.target.mk
