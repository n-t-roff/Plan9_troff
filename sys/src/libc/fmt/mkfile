LIB =		libc_fmt.a

OFILES =	dofmt.o dorfmt.o errfmt.o fltfmt.o fmt.o fmtfd.o fmtlock.o \
		fmtprint.o fmtquote.o fmtrune.o fmtstr.o fmtvprint.o \
		fprint.o print.o runefmtstr.o runeseprint.o runesmprint.o \
		runesnprint.o runesprint.o runevseprint.o runevsmprint.o \
		runevsnprint.o seprint.o smprint.o snprint.o sprint.o \
		vfprint.o vseprint.o vsmprint.o vsnprint.o

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
