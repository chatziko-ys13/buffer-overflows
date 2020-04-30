#include <string.h>
#include <stdio.h>

// put the shellcode here in binary form: "\xAA\xBB..."
char shellcode[] = "";

void direct();
void overflow();

void main() {
	direct();
	// overflow();
}

// run the shellcode by directly changing the return address
void direct() {
	long *ret;
	ret = (long *)&ret + 2;		// hackish way of getting a pointer to the return address
	(*ret) = (long)shellcode;	// set the return address to our code!
}

// run the shellcode via overflow
char large_string[128];
void overflow() {
	char buffer[96];	// the target buffer

	// the large string is filled with the address of the buffer, which will be written at the return address
	for (int i = 0; i < sizeof(large_string)/4; i++)
		((long*)large_string)[i] = (long)buffer;

	for (int i = 0; i < strlen(shellcode); i++)
		large_string[i] = shellcode[i];

	large_string[sizeof(large_string)-1] = 0;

	strcpy(buffer, large_string);
}

