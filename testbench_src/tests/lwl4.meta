#lwl
#111
#ChrisDeverall
#misalignedby2
#
#

lui $3, 0x2000
lui $4, 0x3344
addi $4, $4, 0x5566
sw $4, 0($3)
addi $2, $0, 0x6fff
lwl $2, 2($3)
nop
srl $2, $2, 8
jr $0