#lwr
#34
#ChrisDeverall
#misaligned2
#
#

lui $3, 0x2000
lui $4, 0x5566
addi $4, $4, 0x7788
sw $4, 0($3)
lui $2, 0x1122
addi $2, $2, 0x3344
lwr $2, 1($3)
nop
srl $2, $2, 16

jr $0