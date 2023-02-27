# See LICENSE file for copyright and license details.

CC   = cc
SRC != find * -name '*.c'
OBJ  = ${SRC:.c=.o}

CFLAGS  = -Wall --std=c99 -pedantic\
	-I../src/
LDFLAGS = -L../ -l:liblog.a

tests: test-app
	./test-app

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

test-app: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ}

clean:
	rm -f test-app ${OBJ} *.core
