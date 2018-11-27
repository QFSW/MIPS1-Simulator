#stack
#120
#QFSW
#5!
#
#

#$10 is the SP
lui $10, 0x2000

#uses factorial
addiu $6, $0, 5
jal factorial
nop
addiu $2, $5, 0
jr $0





#$5 is output, $6 is input
factorial:
#stack op
sw $31, 0($10)
addiu $10, $10, 4

#case detection
bne $6, $0 fac-mul

fac-base:
addiu $5, $0, 1
j fac-return
nop

fac-mul:
sw $6, 0($10)
addiu $10, $10, 4

addiu $6, $6, -1
jal factorial
nop

addiu $10, $10, -4
lw $6, 0($10)
nop

multu $5, $6
mflo $5

fac-return:
addiu $10, $10, -4
lw $31, 0($10)

nop
jr $31
nop
