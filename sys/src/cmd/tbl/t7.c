/* t7.c: control to write table entries */
# include "t.h"
# define realsplit ((ct=='a'||ct=='n') && table[ldata][c].rcol)

void
runout(void)
{
	int	i;

	if (boxflg || allflg || dboxflg) 
		need();
	if (ctrflg) {
		Bprint(&(tabout.Biobufhdr), ".nr #I \\n(.i\n");
		Bprint(&(tabout.Biobufhdr), ".in +(\\n(.lu-\\n(TWu-\\n(.iu)/2u\n");
	}
	Bprint(&(tabout.Biobufhdr), ".fc %c %c\n", F1, F2);
	Bprint(&(tabout.Biobufhdr), ".nr #T 0-1\n");
	deftail();
	for (i = 0; i < nlin; i++)
		putline(i, i);
	if (leftover)
		yetmore();
	Bprint(&(tabout.Biobufhdr), ".fc\n");
	Bprint(&(tabout.Biobufhdr), ".nr T. 1\n");
	Bprint(&(tabout.Biobufhdr), ".T# 1\n");
	if (ctrflg)
		Bprint(&(tabout.Biobufhdr), ".in \\n(#Iu\n");
}


void
runtabs(int lform, int ldata)
{
	int	c, ct, vforml, lf;

	Bprint(&(tabout.Biobufhdr), ".ta ");
	for (c = 0; c < ncol; c++) {
		vforml = lform;
		for (lf = prev(lform); lf >= 0 && vspen(table[lf][c].col); lf = prev(lf))
			vforml = lf;
		if (fspan(vforml, c))
			continue;
		switch (ct = ctype(vforml, c)) {
		case 'n':
		case 'a':
			if (table[ldata][c].rcol)
				if (lused[c]) /*Zero field width*/
					Bprint(&(tabout.Biobufhdr), "\\n(%2su ", reg(c, CMID));
		case 'c':
		case 'l':
		case 'r':
			if (realsplit ? rused[c] : (used[c] + lused[c]))
				Bprint(&(tabout.Biobufhdr), "\\n(%2su ", reg(c, CRIGHT));
			continue;
		case 's':
			if (lspan(lform, c))
				Bprint(&(tabout.Biobufhdr), "\\n(%2su ", reg(c, CRIGHT));
			continue;
		}
	}
	Bprint(&(tabout.Biobufhdr), "\n");
}


int
ifline(char *s)
{
	if (!point(s)) 
		return(0);
	if (s[0] == '\\') 
		s++;
	if (s[1] ) 
		return(0);
	if (s[0] == '_') 
		return('-');
	if (s[0] == '=') 
		return('=');
	return(0);
}


void
need(void)
{
	int	texlin, horlin, i;

	for (texlin = horlin = i = 0; i < nlin; i++) {
		if (fullbot[i] != 0)
			horlin++;
		else if (instead[i] != 0)
			continue;
		else
			texlin++;
	}
	Bprint(&(tabout.Biobufhdr), ".ne %dv+%dp\n", texlin, 2 * horlin);
}


void
deftail(void)
{
	int	i, c, lf, lwid;

	for (i = 0; i < MAXHEAD; i++)
		if (linestop[i])
			Bprint(&(tabout.Biobufhdr), ".nr #%c 0-1\n", linestop[i] + 'a' - 1);
	Bprint(&(tabout.Biobufhdr), ".nr #a 0-1\n");
	Bprint(&(tabout.Biobufhdr), ".eo\n");
	Bprint(&(tabout.Biobufhdr), ".de T#\n");
	Bprint(&(tabout.Biobufhdr), ".nr 35 1m\n");
	Bprint(&(tabout.Biobufhdr), ".ds #d .d\n");
	Bprint(&(tabout.Biobufhdr), ".if \\(ts\\n(.z\\(ts\\(ts .ds #d nl\n");
	Bprint(&(tabout.Biobufhdr), ".mk ##\n");
	Bprint(&(tabout.Biobufhdr), ".nr ## -1v\n");
	Bprint(&(tabout.Biobufhdr), ".ls 1\n");
	for (i = 0; i < MAXHEAD; i++)
		if (linestop[i])
			Bprint(&(tabout.Biobufhdr), ".if \\n(#T>=0 .nr #%c \\n(#T\n",
			     linestop[i] + 'a' - 1);
	if (boxflg || allflg || dboxflg) /* bottom of table line */
		if (fullbot[nlin-1] == 0) {
			if (!pr1403)
				Bprint(&(tabout.Biobufhdr), ".if \\n(T. .vs \\n(.vu-\\n(.sp\n");
			Bprint(&(tabout.Biobufhdr), ".if \\n(T. ");
			drawline(nlin, 0, ncol, dboxflg ? '=' : '-', 1, 0);
			Bprint(&(tabout.Biobufhdr), "\n.if \\n(T. .vs\n");
			/* T. is really an argument to a macro but because of 
		   eqn we don't dare pass it as an argument and reference by $1 */
		}
	for (c = 0; c < ncol; c++) {
		if ((lf = left(nlin - 1, c, &lwid)) >= 0) {
			Bprint(&(tabout.Biobufhdr), ".if \\n(#%c>=0 .sp -1\n", linestop[lf] + 'a' - 1);
			Bprint(&(tabout.Biobufhdr), ".if \\n(#%c>=0 ", linestop[lf] + 'a' - 1);
			tohcol(c);
			drawvert(lf, nlin - 1, c, lwid);
			Bprint(&(tabout.Biobufhdr), "\\h'|\\n(TWu'\n");
		}
	}
	if (boxflg || allflg || dboxflg) /* right hand line */ {
		Bprint(&(tabout.Biobufhdr), ".if \\n(#a>=0 .sp -1\n");
		Bprint(&(tabout.Biobufhdr), ".if \\n(#a>=0 \\h'|\\n(TWu'");
		drawvert (0, nlin - 1, ncol, dboxflg ? 2 : 1);
		Bprint(&(tabout.Biobufhdr), "\n");
	}
	Bprint(&(tabout.Biobufhdr), ".ls\n");
	Bprint(&(tabout.Biobufhdr), "..\n");
	Bprint(&(tabout.Biobufhdr), ".ec\n");
}


