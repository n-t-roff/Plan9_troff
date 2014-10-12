#include "e.h"
#include "y.tab.h"
extern YYSTYPE yyval;

void sqrt9(int p2)
{
	static int af = 0;
	int nps;	/* point size for radical */
	double radscale = 0.95;

	if (ttype == DEVPOST)
		radscale = 1.05;
	nps = ps * radscale * eht[p2] / EM(1.0,ps) + 0.99;	/* kludgy */
	nps = max(EFFPS(nps), ps);
	yyval.token = p2;
	if (ttype == DEVCAT || ttype == DEVAPS)
		eht[yyval.token] = EM(1.2, nps);
	else if (ttype == DEVPOST)
		eht[yyval.token] = EM(1.15, nps);
	else		/* DEV202, DEVPOST */
		eht[yyval.token] = EM(1.15, nps);
	dprintf(".\tS%d <- sqrt S%d;b=%g, h=%g, nps=%d\n", 
		yyval.token, p2, ebase[yyval.token], eht[yyval.token], nps);
	printf(".as %d \\|\n", yyval.token);
	nrwid(p2, ps, p2);
	if (af++ == 0)
		printf(".af 10 01\n");	/* make it two digits when it prints */
	printf(".nr 10 %.3fu*\\n(.su/10\n", 9.2*eht[p2]);	/* this nonsense */
			/* guesses point size corresponding to height of stuff */
	printf(".ds %d \\v'%gm'\\s(\\n(10", yyval.token, REL(ebase[p2],ps));
	if (ttype == DEVCAT || ttype == DEVAPS)
		printf("\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'", p2);
	else		/* DEV202, DEVPOST so far */
		printf("\\(sr\\l'\\n(%du\\(rn'", p2);
	printf("\\s0\\v'%gm'\\h'-\\n(%du'\\^\\*(%d\n", REL(-ebase[p2],ps), p2, p2);
	lfont[yyval.token] = rfont[yyval.token] = ROM;
}
