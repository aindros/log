# See LICENSE file for copyright and license details.

PREFIX = /usr/local

CC   = cc
SRC != find src -name "*.c"
OBJ  = ${SRC:.c=.o}

LIBNAME = liblog
LIBVER  = 0.0.0-a1

CFLAGS != scripts/cflags.sh
CFLAGS += -Wall -ansi --std=c89 -pedantic ${OPT} -DLIBVER=\"${LIBVER}\"

PKG_CONFIG_PATH != pkg-config --variable pc_path pkg-config | sed -E "s|.*(${PREFIX}[^:]*)[:].*|\1|g"
