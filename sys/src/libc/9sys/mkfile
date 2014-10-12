LIB =		libc_9sys.a

OFILES =	sysfatal.o rerrstr.o

CPPFLAGS =	-I../../../include

all:		${LIB}

clean:
		rm -f ${OFILES} ${LIB}

install uninstall:

${LIB}:		${OFILES}
		ar cr $@ ${OFILES}
		ranlib $@

.c.o:
		${CC} -fPIC ${CFLAGS} ${CPPFLAGS} -c $<
