# See LICENSE file for copyright and license details.

PREFIX = /usr/local

CC   = cc
SRC != find src -name "*.c"
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog
LIBVER  = 0.0.0-a1

CFLAGS  = -Wall -ansi --std=c89 -pedantic ${OPT} -DLIBVER=\"${LIBVER}\"

