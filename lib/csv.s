/ C register save and restore -- version 7/75

.globl	csv
.globl	cret

/ function:
/     JSR R5, csv
/         R5=>Stack
/         PC=>R5 (return address)
/         JMP csv
/ Next:

csv:
	mov	r5,r0       / address of Next
	mov	sp,r5       / frame pointer = start of new stack frame
	mov	r4,-(sp)    / push working registers into new stack frame
	mov	r3,-(sp)
	mov	r2,-(sp)
	jsr	pc,(r0)		/ stack pc - never used

/ lmul accesses parameters as 10(r5),8(r5),6(r5),4(r5)
/ 2(r5) is the old PC pushed by JSR PC,fuction
/ 0(r5) is the old R5 pushed bu JSR R5,csv

cret:
	mov	r5,r2       / r2 = frame pointer
	mov	-(r2),r4    / restore working registers
	mov	-(r2),r3
	mov	-(r2),r2
	mov	r5,sp       / discard stack frame
	mov	(sp)+,r5    / restore old frame pointer (pushed by JSR R5, csv)
	rts	pc          / return from JSR PC,function
