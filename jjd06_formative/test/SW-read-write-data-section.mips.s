
tests/bin/SW-read-write-data-section.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <_entry>:
10000000:	3c022000 	lui	v0,0x2000
10000004:	24030005 	li	v1,5
10000008:	ac430000 	sw	v1,0(v0)
1000000c:	8c420000 	lw	v0,0(v0)
10000010:	03e00008 	jr	ra
10000014:	00000000 	nop
	...
