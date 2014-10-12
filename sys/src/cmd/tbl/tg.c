/* tg.c: process included text blocks */
# include "t.h"

int
gettext9(char *sp, int ilin, int icol, char *fn, char *sz)
{
					/* get a section of text */
	char	line[4096];
	int	oname, startline;
	char	*vs;

	startline = iline;
	if (texname == 0) 
		error("Too many text block diversions");
	if (textflg == 0) {
		Bprint(&(tabout.Biobufhdr), ".nr %d \\n(.lu\n", SL); /* remember old line length */
		textflg = 1;
	}
	Bprint(&(tabout.Biobufhdr), ".eo\n");
	Bprint(&(tabout.Biobufhdr), ".am %s\n", reg(icol, CRIGHT));
	Bprint(&(tabout.Biobufhdr), ".br\n");
	Bprint(&(tabout.Biobufhdr), ".di %c+\n", texname);
	rstofill();
	if (fn && *fn) 
		Bprint(&(tabout.Biobufhdr), ".nr %d \\n(.f\n.ft %s\n", S1, fn);
	Bprint(&(tabout.Biobufhdr), ".ft \\n(.f\n"); /* protect font */
	vs = vsize[icol][stynum[ilin]];
	if ((sz && *sz) || (vs && *vs)) {
		Bprint(&(tabout.Biobufhdr), ".nr %d \\n(.v\n", S9);
		if (vs == 0 || *vs == 0) 
			vs = "\\n(.s+2";
		if (sz && *sz)
			Bprint(&(tabout.Biobufhdr), ".ps %s\n", sz);
		Bprint(&(tabout.Biobufhdr), ".vs %s\n", vs);
		Bprint(&(tabout.Biobufhdr), ".if \\n(%du>\\n(.vu .sp \\n(%du-\\n(.vu\n", S9, S9);
	}
	if (cll[icol][0])
		Bprint(&(tabout.Biobufhdr), ".ll %sn\n", cll[icol]);
	else
		Bprint(&(tabout.Biobufhdr), ".ll \\n(%du*%du/%du\n", SL, ctspan(ilin, icol), ncol + 1);
	Bprint(&(tabout.Biobufhdr), ".if \\n(.l<\\n(%2s .ll \\n(%2su\n", reg(icol, CRIGHT),
	     reg(icol, CRIGHT));
	if (ctype(ilin, icol) == 'a')
		Bprint(&(tabout.Biobufhdr), ".ll -2n\n");
	Bprint(&(tabout.Biobufhdr), ".in 0\n");
	for (;;) {
		if (gets1(line, sizeof(line)) == nil) {
			iline = startline;
			error("missing closing T}");
		}
		if (line[0] == 'T' && line[1] == '}' && line[2] == tab) 
			break;
		if (match("T}", line)) 
			break;
		Bprint(&(tabout.Biobufhdr), "%s\n", line);
	}
	if (fn && *fn) 
		Bprint(&(tabout.Biobufhdr), ".ft \\n(%d\n", S1);
	if (sz && *sz) 
		Bprint(&(tabout.Biobufhdr), ".br\n.ps\n.vs\n");
	Bprint(&(tabout.Biobufhdr), ".br\n");
	Bprint(&(tabout.Biobufhdr), ".di\n");
	Bprint(&(tabout.Biobufhdr), ".nr %c| \\n(dn\n", texname);
	Bprint(&(tabout.Biobufhdr), ".nr %c- \\n(dl\n", texname);
	Bprint(&(tabout.Biobufhdr), "..\n");
	Bprint(&(tabout.Biobufhdr), ".ec \\\n");
	/* copy remainder of line */
	if (line[2])
		tcopy (sp, line + 3);
	else
		*sp = 0;
	oname = texname;
	texname = texstr[++texct];
	return(oname);
}


void
untext(void)
{
	rstofill();
	Bprint(&(tabout.Biobufhdr), ".nf\n");
	Bprint(&(tabout.Biobufhdr), ".ll \\n(%du\n", SL);
}


