# See LICENSE file for copyright and license details.

LIBDIR = lib

LIBSTR_VER = 0.0.0-a1
LIBSTR     = cstr-${LIBSTR_VER}
LIBSTR_INC = -I${LIB_DIR}/${LIBSTR}/src
LIBSTR_LIB = -L${LIB_DIR}/${LIBSTR} -l:libstr.a

LIBINC = ${LIBSTR_INC}
LIBS   = ${LIBSTR_LIB}
