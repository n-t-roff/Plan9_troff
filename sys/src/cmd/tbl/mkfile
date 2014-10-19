_BINDIR =	${DWBHOME}/${BINDIR}
_LIBDIR =	${DWBHOME}/${LIBDIR}
PKGROOT =	../../../..

TARG =		tbl

OFILES =	t8.o t4.o t6.o tu.o t5.o t7.o tv.o tg.o t3.o tb.o tt.o t9.o \
		t1.o tf.o tc.o ti.o tm.o t0.o tr.o te.o ts.o t2.o

CPPFLAGS =	-I${PKGROOT}/sys/include

_LDFLAGS =	-L${PKGROOT}/libcompat      -lcompat \
		-L${PKGROOT}/sys/src/libc   -lc_p9   \
		-L${PKGROOT}/sys/src/libbio -lbio    \
		-L${_LIBDIR} -Wl,-rpath,${_LIBDIR}

all:		${TARG}

clean:
		rm -f ${OFILES} ${TARG}

install:
		@[ -d ${_BINDIR} ] || mkdir -p ${_BINDIR}
		install ${TARG} ${_BINDIR}/

uninstall:
		rm -f ${_BINDIR}/${TARG}
		@rmdir ${_BINDIR} 2> /dev/null || true

${TARG}:	${OFILES}
		${CC} -o $@ ${OFILES} ${_LDFLAGS}
