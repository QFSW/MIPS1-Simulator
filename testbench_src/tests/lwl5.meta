#lwl
#102
#ChrisDeverall
#misalignedby3
#
#

lui $3, 0x2000
lui $4, 0x3344
addi $4, $4, 0x5566
sw $4, 0($3)
addi $2, $0, 0x1122
lwl $2, 3($3)
nop
srl $2, $2, 24
jr $0