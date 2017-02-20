CC = gcc
LD = gcc
NASM = nasm

CFLAGS = -m32 -c -o kc.o
LFLAGS = -m32 -elf_i386 -T link.ld
NASMFLAGS = -f elf32 -o kasm.o

PROG = kernel

OBJS = kasm.o $(PROG).o kc.o


default: $(PROG)

$(PROG): $(OBJS)
		$(LD) $(LFLAGS) $(OBJS)  -o $(PROG)

kasm.o: link.ld
		$(NASM) $(NASMFLAGS) kernel.asm

$(PROG).o: $(PROG).asm
		$(NASM) $(NASMFLAGS) $(PROG).asm

kc.o: kernel.c
		$(CC) $(CFLAGS) kernel.c

clean:
		rm -rf *.o *~

real_clean:
		rm -rf *.o $(PROG) *~