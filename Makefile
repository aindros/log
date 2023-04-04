# See LICENSE file for copyright and license details.

include config.mk



dist: static shared

static:
	@make OPT='-O2 -pipe -Werror' ${LIBNAME:=.a}
	rm -f ${OBJ}

shared:
	@make OPT='-O2 -pipe -Werror -fPIC' ${LIBNAME:=.so}
	rm -f ${OBJ}

debug:
	@make OPT=-g all

${LIBNAME:=.so}: ${OBJ}
	${CC} ${LDFLAGS} -shared ${OBJ} -o $@

${LIBNAME:=.a}: ${OBJ}
	ar rcs $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJ} ${LIBNAME}.* *.core
	cd test && make clean

tests: dist
	cd test && make clean tests

install: dist
	cp src/log.h ${PREFIX}/include/log.h
	cp ${LIBNAME:=.so} ${PREFIX}/lib/${LIBNAME:=.so}
	cp ${LIBNAME:=.a} ${PREFIX}/lib/${LIBNAME:=.a}
	cp log.pc ${PKG_CONFIG_PATH}/log.pc

uninstall:
	rm -f ${PREFIX}/include/log.h
	rm -f ${PREFIX}/lib/${LIBNAME:=.so}
	rm -f ${PREFIX}/lib/${LIBNAME:=.a}
	rm -f ${PKG_CONFIG_PATH}/log.pc
