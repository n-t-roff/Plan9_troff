/* tf.c: save and restore fill mode around table */
# include "t.h"

void
savefill(void)
{
			/* remembers various things: fill mode, vs, ps in mac 35 (SF) */
	Bprint(&(tabout.Biobufhdr), ".de %d\n", SF);
	Bprint(&(tabout.Biobufhdr), ".ps \\n(.s\n");
	Bprint(&(tabout.Biobufhdr), ".vs \\n(.vu\n");
	Bprint(&(tabout.Biobufhdr), ".in \\n(.iu\n");
	Bprint(&(tabout.Biobufhdr), ".if \\n(.u .fi\n");
	Bprint(&(tabout.Biobufhdr), ".if \\n(.j .ad\n");
	Bprint(&(tabout.Biobufhdr), ".if \\n(.j=0 .na\n");
	Bprint(&(tabout.Biobufhdr), "..\n");
	Bprint(&(tabout.Biobufhdr), ".nf\n");
	/* set obx offset if useful */
	Bprint(&(tabout.Biobufhdr), ".nr #~ 0\n");
	Bprint(&(tabout.Biobufhdr), ".if \\n(.T .if n .nr #~ 0.6n\n");
}


void
rstofill(void)
{
	Bprint(&(tabout.Biobufhdr), ".%d\n", SF);
}


void
endoff(void)
{
	int	i;

	for (i = 0; i < MAXHEAD; i++)
		if (linestop[i])
			Bprint(&(tabout.Biobufhdr), ".nr #%c 0\n", linestop[i] + 'a' - 1);
	for (i = 0; i < texct; i++)
		Bprint(&(tabout.Biobufhdr), ".rm %c+\n", texstr[i]);
	Bprint(&(tabout.Biobufhdr), "%s\n", last);
}


void
ifdivert(void)
{
	Bprint(&(tabout.Biobufhdr), ".ds #d .d\n");
	Bprint(&(tabout.Biobufhdr), ".if \\(ts\\n(.z\\(ts\\(ts .ds #d nl\n");
}


void
saveline(void)
{
	Bprint(&(tabout.Biobufhdr), ".if \\n+(b.=1 .nr d. \\n(.c-\\n(c.-1\n");
	linstart = iline;
}


void
restline(void)
{
	Bprint(&(tabout.Biobufhdr), ".if \\n-(b.=0 .nr c. \\n(.c-\\n(d.-%d\n", iline - linstart);
	linstart = 0;
}


void
cleanfc(void)
{
	Bprint(&(tabout.Biobufhdr), ".fc\n");
}


