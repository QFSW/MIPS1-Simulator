#bgezal
#13
#QFSW
#link-set
#

lui $31, 0x2000
addi $4, $0, 13
addi $3, $0, -2

bgezal $3 crash
nop
addi $2, $2, 1
bne $2, $4 func2
nop
jr $0
nop


crash:
lui $3, 0x2000
jr $3
nop

func2:
jr $31
nop