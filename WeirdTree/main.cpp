#define _POSIX_C_SOURCE  200809L
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
int
main (void) {
int i;
char c;
for ( c='a'; c<='z'; c++)
{
char name [] = {c, '.', 'd', 'a', 't', 0};
int fd = creat(name, S_IRWXU ^ S_IXUSR);
for ( i=1; i<=10; i++) {
dprintf(fd, "kontrolnya zapys ¹ %d v faile %s\n" , i, name);
}
close (fd);
}
return 0;
}
