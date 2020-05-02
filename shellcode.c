#include <unistd.h>

void exec() {
   char *argv[2];

   argv[0] = "/bin/sh";
   argv[1] = NULL;
   execve(argv[0], argv, NULL);

   _exit(0);
}

void main() {
	exec();
}