#lb
#0
#QFSW
#EOF-offset
#tests/sample2.txt
#

addi $5, $0, -1
addi $4, $0, 8
lui $3, 0x3000

read:
lb $2, 0($3)
nop
add $2, $2, $3
addi $4, $4, -1
bgez $4, read
nop

addi $2, $2, 1
jr $0
