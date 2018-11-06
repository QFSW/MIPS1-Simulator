
tests/bin/SW-putc.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <_entry>:
10000000:	24030058 	li	v1,88
10000004:	3c023000 	lui	v0,0x3000
10000008:	ac430004 	sw	v1,4(v0)
1000000c:	03e00008 	jr	ra
10000010:	00000000 	nop

10000014 <putc>:
10000014:	3c023000 	lui	v0,0x3000
10000018:	ac440004 	sw	a0,4(v0)
1000001c:	03e00008 	jr	ra
10000020:	00000000 	nop
	...
