#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int
create(char *pathname, int flags, ulong mode) {
	open(pathname, flags | O_CREAT, mode);
}
