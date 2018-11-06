
tests/bin/ADD-wrap.mips.elf:     file format elf32-tradbigmips


Disassembly of section .text:

10000000 <_entry>:
10000000:	3c027fff 	lui	v0,0x7fff
10000004:	3442ffff 	ori	v0,v0,0xffff
10000008:	3c037fff 	lui	v1,0x7fff
1000000c:	3463ffff 	ori	v1,v1,0xffff
10000010:	00631020 	add	v0,v1,v1
10000014:	03e00008 	jr	ra
10000018:	00000000 	nop
1000001c:	00000000 	nop
