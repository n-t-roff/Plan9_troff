#include <u.h>
#include <libc.h>

void
sysfatal(char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	vfprint(2, fmt, arg);
	va_end(arg);
}
