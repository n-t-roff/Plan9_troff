#include "e.h"
#include "y.tab.h"
extern YYSTYPE yyval;

extern int Funnyps;
extern double Funnyht, Funnybase;

void funny(int n)
{
	char *f = 0;

	yyval.token = salloc();
	switch (n) {
	case SUM:
		f = lookup(deftbl, "sum_def")->cval; break;
	case UNION:
		f = lookup(deftbl, "union_def")->cval; break;
	case INTER:	/* intersection */
		f = lookup(deftbl, "inter_def")->cval; break;
	case PROD:
		f = lookup(deftbl, "prod_def")->cval; break;
	default:
		ERROR "funny type %d in funny", n FATAL;
	}
	printf(".ds %d %s\n", yyval.token, f);
	eht[yyval.token] = EM(1.0, ps+Funnyps) - EM(Funnyht, ps);
	ebase[yyval.token] = EM(Funnybase, ps);
	dprintf(".\tS%d <- %s; h=%g b=%g\n", 
		yyval.token, f, eht[yyval.token], ebase[yyval.token]);
	lfont[yyval.token] = rfont[yyval.token] = ROM;
}
