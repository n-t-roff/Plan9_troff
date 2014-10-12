#include <string.h>
#include <errno.h>
typedef unsigned int uint;
int
errstr(char *buf, uint buflen) {
	strerror_r(errno, buf, buflen);
}
