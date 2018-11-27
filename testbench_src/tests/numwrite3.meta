#function
#0
#QFSW
#in=666
#
#666

#SP = $10
lui $10, 0x2000

addi $3, $0, 666
jal writenum
nop
addi $2, $3, 0
jr $0


#input = $3, temp = $4, $5, $6, $7
writenum:
lui $4, 0x3000
addi $5, $0, 10
addi $7, $0, 0

push-stack:
div $3, $5
mflo $3
mfhi $6
sw $6, 0($10)
addi $10, $10, 4
addi $7, $7, 1
bne $3, $0 push-stack
nop

print:
addi $10, $10, -4
lw $6, 0($10)
addi $7, $7, -1
addi $6, $6, 48
sw $6, 4($4)
bgtz $7 print
nop


jr $31
nop

