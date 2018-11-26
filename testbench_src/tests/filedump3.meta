#lb
#-1
#QFSW
#EOF
#tests/sample3.txt
#200IQ play universe brain

addi $5, $0, -1
addi $4, $0, 26
lui $3, 0x3000

read:
lb $2, 3($3)
nop
beq $2, $5 writeskp
nop

write:
sw $2, 4($3)

writeskp:
addi $4, $4, -1
bgez $4, read
nop

jr $0
