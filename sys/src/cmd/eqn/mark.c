#include "e.h"
#include "y.tab.h"
extern YYSTYPE yyval;

void mark(int p1)
{
	markline = 1;
	printf(".ds %d \\k(09\\*(%d\n", p1, p1);
	yyval.token = p1;
	dprintf(".\tmark %d\n", p1);
}

void lineup(int p1)
{
	markline = 2;
	if (p1 == 0) {
		yyval.token = salloc();
		printf(".ds %d \\h'|\\n(09u'\n", yyval.token);
	}
	dprintf(".\tlineup %d\n", p1);
}
