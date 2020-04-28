
CFLAGS=-g -m32													# debug, 32bit code for simplicity, static link
CFLAGS+=-fno-pie -mpreferred-stack-boundary=2 -fno-builtin		# produce simpler assembly, not important
LDFLAGS=-static -m32											# static link, 32bit

CFLAGS  += -fno-stack-protector		# no canaries, important!
LDFLAGS += -zexecstack				# allow executable stack, important!

target: target.o
test: test.o
shellcode: shellcode.o
shellcodeasm: shellcodeasm.o
shellcodetest: shellcodetest.o
exploit1: exploit1.o
exploit2: exploit2.o

clean:
	rm -f *.o target test shellcode shellcodeasm shellcodetest exploit1 exploit2

# remember to disable address space layout randomization (ASLR)
disable_aslr:
	echo 0 > /proc/sys/kernel/randomize_va_space
