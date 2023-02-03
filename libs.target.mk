# See LICENSE file for copyright and license details.

clean-libs:
	rm -rf ${LIBDIR}

libs: ${LIBDIR} ${LIBDIR}/${LIBSTR}

${LIBDIR}:
	@mkdir -p $@

${LIBDIR}/${LIBSTR}:
	fetch -o - https://git.alessandroiezzi.it/libs/c/cstr.git/snapshot/${LIBSTR}.tar.gz | tar xzf - -C ${LIBDIR}
	cd $@ && make
