#lhu
#1
#QFSW
#EOF-offset
#tests/sample3.txt
#

addi $5, $0, -1
addi $4, $0, 26
lui $3, 0x3000

read:
lhu $2, 0($3)
nop
add $2, $2, $3
addi $4, $4, -1
bgez $4, read
nop

addi $2, $2, 1
srl $2, $2, 16
jr $0
