#include <sys/types.h>
#include <unistd.h>
typedef long long vlong;
vlong seek(int fd, vlong offset, int whence) {
	return lseek(fd, offset, whence);
}
