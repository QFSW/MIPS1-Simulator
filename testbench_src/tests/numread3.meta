#function
#126
#QFSW
#in=126
#126
#

jal readnum
nop
addi $2, $3, 0
jr $0


#output = $3, temp = $4, $5, $6, $7
readnum:
addi $3, $0, 0
lui $4, 0x3000
addi $5, $0, 10

read:
lw $6, 0($4)
nop
slti $7, $6, 31
bgtz $7 read-end
nop

addi $2, $2, 1
mult $3, $5
mflo $3
add $3, $3, $6
addi $3, $3, -48
j read
nop

read-end:
jr $31
nop

