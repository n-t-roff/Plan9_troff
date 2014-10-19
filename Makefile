TEMPDIR =	/var/tmp
DWBHOME =	/usr/local/p9roff
BINDIR =	bin
LIBDIR =	lib
TMACDIR =	${LIBDIR}/tmac
FONTDIR =	${LIBDIR}/troff/font
NTERMDIR =	${LIBDIR}/troff/term
POSTDIR =	${LIBDIR}/postscript
MAN1DIR =	man/man1
MAN5DIR =	man/man5
TEXHYPHENS =	/usr/share/texmf/tex/generic/hyphen/hyphen.tex
ALTHYPHENS =	${TMACDIR}/hyphen.tex
PROGRAMNAME =	troff, Plan 9 edition
#CFLAGS =	-g
LDFLAGS =	-s

EXPMACS =	TMACDIR=${TMACDIR} FONTDIR=${FONTDIR} NTERMDIR=${NTERMDIR} \
		TEXHYPHENS=${TEXHYPHENS} ALTHYPHENS=${ALTHYPHENS} \
		DWBHOME=${DWBHOME} BINDIR=${BINDIR} LIBDIR=${LIBDIR} \
		"CFLAGS=${CFLAGS}" "LDFLAGS=${LDFLAGS}" POSTDIR=${POSTDIR} \
		TEMPDIR=${TEMPDIR} MAN1DIR=$(MAN1DIR) MAN5DIR=$(MAN5DIR) \
		"PROGRAMNAME=$(PROGRAMNAME)"

SUBDIRS =	libcompat sys

all clean install uninstall:
		@for i in ${SUBDIRS}; do \
			(cd $$i; make -f mkfile ${EXPMACS} $@) || exit; \
		done
		@if [ "$@" = "uninstall" -a -d ${DWBHOME} ]; then \
			find ${DWBHOME} -depth -type d -exec rmdir {} \
			    \;; \
		fi
