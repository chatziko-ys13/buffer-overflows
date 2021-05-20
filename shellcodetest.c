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

void overwrite_return_address(void* address) {
	// hackish way of getting a pointer to the return address (4 bytes below the arg)
	void** ret_addr = (void**)((void*)&address - 4);
	*ret_addr = address;
}

// run the shellcode directly changing the return address
void direct() {
	char buffer[sizeof(shellcode)];		// large enough buffer
	memcpy(buffer, shellcode, sizeof(shellcode));

	overwrite_return_address(buffer);
}

// run the shellcode via overflow
char payload[128];
void overflow() {
	char buffer[96];	// the target buffer

	// prepare the payload
	//
	// the payload is filled with the address of the buffer, to overwrite the return address
	for (int i = 0; i < sizeof(payload)/4; i++)
		((long*)payload)[i] = (long)buffer;

	// and the shellcode in the beginning
	for (int i = 0; i < strlen(shellcode); i++)
		payload[i] = shellcode[i];

	payload[sizeof(payload)-1] = 0;

	// the actual overflow attack
	strcpy(buffer, payload);
}

