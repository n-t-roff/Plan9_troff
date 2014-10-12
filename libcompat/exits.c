#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void
exits(char *msg) {
	if (!msg || !strlen(msg))
		exit(0);
	fprintf(stderr, "*** FATAL ERROR: %s\n", msg);
	exit(1);
}
