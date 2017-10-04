#include<stdio.h>
#include <errno.h>
int
main(int argc, char *argv[])
{
fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
errno = ENOENT;
perror(argv[1]);
exit(0);
}