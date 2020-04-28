#include <unistd.h>

void exec() {
   char *name[2];

   name[0] = "/bin/sh";
   name[1] = NULL;
   execve(name[0], name, NULL);

   _exit(0);
}

void main() {
	exec();
}