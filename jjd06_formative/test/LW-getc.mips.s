
tests/bin/LW-getc.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <_entry>:
10000000:	3c023000 	lui	v0,0x3000
10000004:	8c420000 	lw	v0,0(v0)
10000008:	03e00008 	jr	ra
1000000c:	00000000 	nop

10000010 <getc>:
10000010:	3c023000 	lui	v0,0x3000
10000014:	8c420000 	lw	v0,0(v0)
10000018:	03e00008 	jr	ra
1000001c:	00000000 	nop
