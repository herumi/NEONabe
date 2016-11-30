/*
arithFp_asm.s
CINVESTAV-IPN
A.H.Sánchez, A. Faz
Public domain.
*/

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Constants:
@     ZERO   = 0          , (128-bit)
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.text
	.align 3
ZERO:
	.word 0
	.word 0
	.word 0
	.word 0
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Set an element to zero.
@ Usage:
@    void SETZERO(uint32_t *A);
@ Operation:
@    A = 0
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	SETZERO
	.type	SETZERO, %function
SETZERO:
	VEOR q0,q0
	VEOR q1,q1
	VSTM r0, {q0,q1}
	bx	lr
	.size	SETZERO, .-SETZERO


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Copy two elements in Fp
@ Usage:
@    void COPY(Fp B, Fp A);
@ Operation:
@    B = A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	COPY
	.type	COPY, %function
COPY:
	VLDM r1, {q0,q1}
	VSTM r0, {q0,q1}
	bx	lr
	.size	COPY, .-COPY

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Eight word or (256-bit) addition
@ Usage:
@    void ADD256(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B + A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	ADD256S
	.type	ADD256S, %function
ADD256S:
	push {r4-r9}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADDS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADCS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADC  r5,r9
	STM r0!, {r2-r5}

	pop {r4-r9}
	bx	lr
	.size	ADD256S, .-ADD256S


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Eight word or (256-bit) addition
@ Usage:
@    void ADD256C(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B + A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	ADD256C
	.type	ADD256C, %function
ADD256C:
	push {r4-r10}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADDS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r6}
	LDM r1!, {r7-r10}
	ADCS r2,r7
	ADCS r3,r8
	ADCS r4,r9
	ADCS r5,r10
	ADC  r6,#0
	STM r0!, {r2-r6}

	pop {r4-r10}
	bx	lr
	.size	ADD256C, .-ADD256C



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Eight word or (256-bit) substraction
@ Usage:
@    void SUB256S(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B - A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	SUB256S
	.type	SUB256S, %function
SUB256S:
	push {r4-r9}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SUBS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBC  r5,r9
	STM r0!, {r2-r5}

	pop {r4-r9}
	bx	lr
	.size	SUB256S, .-SUB256S



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Eight word or (256-bit) substraction
@ Usage:
@    void SUB256C(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B - A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	SUB256C
	.type	SUB256C, %function
SUB256C:
	push {r4-r10}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SUBS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r6}
	LDM r1!, {r7-r10}
	SBCS r2,r7
	SBCS r3,r8
	SBCS r4,r9
	SBCS r5,r10
	SBC	 r6, #0
	STM r0!, {r2-r6}

	pop {r4-r10}
	bx	lr
	.size	SUB256C, .-SUB256C


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 16 word or (512-bit) addition
@ Usage:
@    void ADD512(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B + A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	ADD512
	.type	ADD512, %function
ADD512:
	push {r4-r9}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADDS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADCS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADCS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADCS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADC  r5,r9
	STM r0!, {r2-r5}

	pop {r4-r9}
	bx	lr
	.size	ADD512, .-ADD512


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 16 word or (512-bit) substraction
@ Usage:
@    void SUB512(uint32_t *B, uint32_t *A)
@ Operation:
@    B = B - A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	SUB512
	.type	SUB512, %function
SUB512:
	push {r4-r9}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SUBS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBC  r5,r9
	STM r0!, {r2-r5}

	pop {r4-r9}
	bx	lr
	.size	SUB512, .-SUB512


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 16 word or (512-bit) substraction
@ Usage:
@    void SUB512C(uint32_t *B, uint32_t *A)
@ Operation:
@    B = (sign)B - A
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	SUB512C
	.type	SUB512C, %function
SUB512C:
	push {r4-r10}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SUBS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	SBCS r2,r6
	SBCS r3,r7
	SBCS r4,r8
	SBCS r5,r9
	STM r0!, {r2-r5}

	LDM r0, {r2-r6}
	LDM r1!, {r7-r10}
	SBCS r2,r7
	SBCS r3,r8
	SBCS r4,r9
	SBCS r5,r10
	SBC	 r6, #0
	STM r0!, {r2-r6}

	pop {r4-r10}
	bx	lr
	.size	SUB512C, .-SUB512C



.align	2
	.global	MUL128DUAL
	.type	MUL128DUAL, %function
MUL128DUAL:
	VLDM r2, {q0,q1}
	VZIP.32 q0,q1
	VLDM r3, {q2,q3}
	VZIP.32 q2,q3

	VMOV.I64 q15,#0x00000000ffffffff

	VMULL.U32 q6, d0, d4
	VMULL.U32 q7, d1, d4
	VSRA.U64 q7,  q6, #32
	VMULL.U32 q8, d2, d4
	VSRA.U64 q8,  q7, #32
	VAND.I64 q7,  q15
	VMULL.U32 q9, d3, d4
	VSRA.U64 q9,  q8, #32
	VAND.I64 q8,  q15
	VSHR.U64 q10, q9, #32
	VAND.I64 q9,  q15

	VMLAL.U32 q7,  d0, d5
	VMLAL.U32 q8,  d1, d5
	VSRA.U64 q8,  q7,  #32
	VMLAL.U32 q9,  d2, d5
	VSRA.U64 q9,  q8,  #32
	VAND.I64 q8,  q15
	VMLAL.U32 q10, d3, d5
	VSRA.U64 q10, q9,  #32
	VAND.I64 q9,  q15
	VSHR.U64 q11, q10, #32
	VAND.I64 q10, q15

	VMLAL.U32 q8,  d0, d6
	VMLAL.U32 q9,  d1, d6
	VSRA.U64 q9,  q8,  #32
	VMLAL.U32 q10, d2, d6
	VSRA.U64 q10, q9,  #32
	VAND.I64 q9,  q15
	VMLAL.U32 q11, d3, d6
	VSRA.U64 q11, q10, #32
	VAND.I64 q10, q15
	VSHR.U64 q12, q11, #32
	VAND.I64 q11, q15

	VMLAL.U32 q9,  d0, d7
	VMLAL.U32 q10, d1, d7
	VSRA.U64 q10, q9,  #32
	VMLAL.U32 q11, d2, d7
	VSRA.U64 q11, q10, #32
	VMLAL.U32 q12, d3, d7

	VSRA.U64 q12, q11, #32
	VSHR.U64 q13, q12, #32

	VMOVN.I64 d0, q6
	VMOVN.I64 d4, q7
	VMOVN.I64 d1, q8
	VMOVN.I64 d5, q9
	VMOVN.I64 d2, q10
	VMOVN.I64 d6, q11
	VMOVN.I64 d3, q12
	VMOVN.I64 d7, q13

	VUZP.32 d0, d4
	VUZP.32 d1, d5
	VUZP.32 d2, d6
	VUZP.32 d3, d7


	VSTM r0, {q0,q1} @ store d0
	VSTM r1, {q2,q3} @ store d1

	bx	lr
	.size	MUL128DUAL, .-MUL128DUAL



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Four word or (128-bit) addition
@ Usage:
@    void ADD_128(C, A, B);
@ Operation:
@    C = A + B
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	ADD_128
	.type	ADD_128, %function
ADD_128:
	push {r4-r9}

	LDM r0, {r2-r5}
	LDM r1!, {r6-r9}
	ADDS r2,r6
	ADCS r3,r7
	ADCS r4,r8
	ADC  r5,r9
	STM r0!, {r2-r5}

	pop {r4-r9}
	bx	lr
	.size	ADD_128, .-ADD_128


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Four word or (128-bit) addition
@ Usage:
@    void ADD_128C(C, B);
@ Operation:
@    C = C + B
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	.align	2
	.global	ADD_128C
	.type	ADD_128C, %function
ADD_128C:
	push {r4-r10}

	LDM r0, {r2-r6}
	LDM r1!, {r7-r10}
	ADDS r2,r7
	ADCS r3,r8
	ADCS r4,r9
	ADCS r5,r10
	ADC  r6,#0
	STM r0!, {r2-r6}

	pop {r4-r10}
	bx	lr
	.size	ADD_128C, .-ADD_128C

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Three Four word or (128-bit) multiplication.
@ Usage:
@  void MUL128_32(C,A,b);
@
@ Operation:
@  C = A*b
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	.align	2
	.global	MUL128_32
	.type	MUL128_32, %function
MUL128_32:
	push {r4-r11}

	LDM r1!, {r8-r11}

	EOR r5,r5
	EOR r6,r6
	EOR r7,r7

	UMULL r3,r4, r8,  r2 @a0b0
	UMLAL r4,r5, r9,  r2 @a0b1
	UMLAL r5,r6, r10, r2 @a0b2
	UMLAL r6,r7, r11, r2 @a0b3

	STM r0!, {r3-r7}

	pop {r4-r11}
	bx	lr
	.size	MUL128_32, .-MUL128_32



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Three Four word or (128-bit) multiplication.
@ Usage:
@  void MUL128_32ADD(C,A,b);
@
@ Operation:
@  C = A*b+C
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	.align	2
	.global	MUL128_32ADD
	.type	MUL128_32ADD, %function
MUL128_32ADD:
	push {r4-r12}

	LDM r1!, {r8-r11}

	EOR r5,r5
	EOR r6,r6
	EOR r7,r7

	UMULL r3,r4, r8,  r2 @a0b0
	UMLAL r4,r5, r9,  r2 @a0b1
	UMLAL r5,r6, r10, r2 @a0b2
	UMLAL r6,r7, r11, r2 @a0b3

	LDM r0, {r8-r12}
	ADDS r8,r3
	ADCS r9,r4
	ADCS r10,r5
	ADCS r11,r6
	ADC  r12,r7
	STM r0!, {r8-r12}

	pop {r4-r12}
	bx	lr
	.size	MUL128_32ADD, .-MUL128_32ADD

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Three Four word or (256-bit) multiplication.
@ Usage:
@  void MUL256_32ADD(C,A,b);
@
@ Operation:
@  C = A*b+C
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	.align	2
	.global	MUL256_32ADD
	.type	MUL256_32ADD, %function
MUL256_32ADD:
	push {r4-r11}

	LDM r1!, {r8-r11}

	EOR r5,r5
	EOR r6,r6
	EOR r7,r7

	UMULL r3,r4, r8,  r2 @a0b0
	UMLAL r4,r5, r9,  r2 @a0b1
	UMLAL r5,r6, r10, r2 @a0b2
	UMLAL r6,r7, r11, r2 @a0b3

	LDM r0, {r8-r11}
	ADDS r8,r3
	ADCS r9,r4
	ADCS r10,r5
	ADCS r11,r6
	STM r0!, {r8-r11}

	LDM r1!, {r8-r11}

	EOR r3,r3
	EOR r4,r4
	EOR r5,r5
	EOR r6,r6

	UMLAL r7,r4, r8,  r2 @a0b0
	UMLAL r4,r5, r9,  r2 @a0b1
	UMLAL r5,r6, r10, r2 @a0b2
	UMLAL r6,r3, r11, r2 @a0b3

	LDM r0, {r8-r11}
	ADCS r8,r7
	ADCS r9,r4
	ADCS r10,r5
	ADCS r11,r6
	STM r0!, {r8-r11}

	LDM r0, {r8-r10}
	ADCS r8,r3
	ADCS r9,#0
	ADCS r0,#0
	STM r0!, {r8-r10}

	pop {r4-r11}
	bx	lr
	.size	MUL256_32ADD, .-MUL256_32ADD


	.align	2
	.global	UNZIP
	.type	UNZIP, %function
UNZIP:
	push {r4-r5}

	VLDM r0, {q8-q15}

	VUZP.32 d16,d17
	VUZP.32 d18,d19
	VUZP.32 d20,d21
	VUZP.32 d22,d23
	VUZP.32 d24,d25
	VUZP.32 d26,d27
	VUZP.32 d28,d29
	VUZP.32 d30,d31

	VST1.64 {d16}, [r0]!
	VST1.64 {d18}, [r0]!
	VST1.64 {d20}, [r0]!
	VST1.64 {d22}, [r0]!
	VST1.64 {d24}, [r0]!
	VST1.64 {d26}, [r0]!
	VST1.64 {d28}, [r0]!
	VST1.64 {d30}, [r0]!

	VST1.64 {d17}, [r0]!
	VST1.64 {d19}, [r0]!
	VST1.64 {d21}, [r0]!
	VST1.64 {d23}, [r0]!
	VST1.64 {d25}, [r0]!
	VST1.64 {d27}, [r0]!
	VST1.64 {d29}, [r0]!
	VST1.64 {d31}, [r0]!

	pop {r4-r5}
	bx	lr
	.size	UNZIP, .-UNZIP


	.align	2
	.global	MULNEON
	.type	MULNEON, %function
MULNEON:
	push {r4-r5}

	VLDM r2, {q0-q3}
	VZIP.32 q0,q2
	VZIP.32 q1,q3

	VLDM r3!, {d28,d29}
	VMOV.I64 q15,#0x00000000ffffffff

	VMULL.U32 	q6, d0, d28 @ a0*b0, c0*d0
	VMULL.U32 	q7, d1, d28 @ a1*b0, c1*d0
	VSRA.U64 	q7, q6, #32
	VMULL.U32 	q8, d4, d28 @ a2*b0, c2*d0
	VSRA.U64 	q8, q7, #32
	VMULL.U32 	q9, d5, d28 @ a3*b0, c3*d0
	VSRA.U64 	q9, q8, #32
	VMULL.U32 	q10,d2, d28 @ a4*b0, c4*d0
	VSRA.U64 	q10,q9, #32
	VMULL.U32 	q11,d3, d28 @ a5*b0, c5*d0
	VSRA.U64 	q11,q10, #32
	VMULL.U32 	q12,d6, d28 @ a6*b0, c6*d0
	VSRA.U64 	q12,q11, #32
	VMULL.U32 	q13,d7, d28 @ a7*b0, c7*d0
	VSRA.U64 	q13,q12, #32

	VMOVN.I64 d12, q6
	vst1.32  {d12}, [r0]!

@segunda
	VSHR.U64 q6,  q13, #32
	VAND.I64 q7,  q15
	VAND.I64 q8,  q15
	VAND.I64 q9,  q15
	VAND.I64 q10,  q15
	VAND.I64 q11,  q15
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15

	VMLAL.U32 	q7, d0, d29 @ a0*b1, c0*d1
	VMLAL.U32 	q8, d1, d29 @ a1*b1, c1*d1
	VSRA.U64 	q8, q7, #32
	VMLAL.U32 	q9, d4, d29 @ a2*b1, c2*d1
	VSRA.U64 	q9, q8, #32
	VMLAL.U32 	q10,d5, d29 @ a3*b1, c3*d1
	VSRA.U64 	q10,q9, #32
	VMLAL.U32 	q11,d2, d29 @ a4*b1, c4*d1
	VSRA.U64 	q11,q10, #32
	VMLAL.U32 	q12,d3, d29 @ a5*b1, c5*d1
	VSRA.U64 	q12,q11, #32
	VMLAL.U32 	q13,d6, d29 @ a6*b1, c6*d1
	VSRA.U64 	q13,q12, #32
	VMLAL.U32 	q6,d7, d29 @ a7*b1, c7*d1
	VSRA.U64 	q6,q13, #32


	VMOVN.I64 d14, q7
	vst1.32  {d14}, [r0]!
	VLDM r3!, {d28,d29}
	VSHR.U64 q7,  q6, #32

@Tercera
	VAND.I64 q8,  q15
	VAND.I64 q9,  q15
	VAND.I64 q10,  q15
	VAND.I64 q11,  q15
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15

	VMLAL.U32 	q8, d0, d28 @ a0*b1, c0*d1
	VMLAL.U32 	q9, d1, d28 @ a1*b1, c1*d1
	VSRA.U64 	q9, q8, #32
	VMLAL.U32 	q10, d4, d28 @ a2*b1, c2*d1
	VSRA.U64 	q10, q9, #32
	VMLAL.U32 	q11,d5, d28 @ a3*b1, c3*d1
	VSRA.U64 	q11,q10, #32
	VMLAL.U32 	q12,d2, d28 @ a4*b1, c4*d1
	VSRA.U64 	q12,q11, #32
	VMLAL.U32 	q13,d3, d28 @ a5*b1, c5*d1
	VSRA.U64 	q13,q12, #32
	VMLAL.U32 	q6,d6, d28 @ a6*b1, c6*d1
	VSRA.U64 	q6,q13, #32
	VMLAL.U32 	q7,d7, d28 @ a7*b1, c7*d1
	VSRA.U64 	q7,q6, #32

	VMOVN.I64 d16, q8
	vst1.32  {d16}, [r0]!

@Cuarta
	VSHR.U64 q8,  q7, #32
	VAND.I64 q9,  q15
	VAND.I64 q10,  q15
	VAND.I64 q11,  q15
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15
	VAND.I64 q7,  q15

	VMLAL.U32 	q9, d0, d29 @ a0*b1, c0*d1
	VMLAL.U32 	q10, d1, d29 @ a1*b1, c1*d1
	VSRA.U64 	q10, q9, #32
	VMLAL.U32 	q11, d4, d29 @ a2*b1, c2*d1
	VSRA.U64 	q11, q10, #32
	VMLAL.U32 	q12,d5, d29 @ a3*b1, c3*d1
	VSRA.U64 	q12,q11, #32
	VMLAL.U32 	q13,d2, d29 @ a4*b1, c4*d1
	VSRA.U64 	q13,q12, #32
	VMLAL.U32 	q6,d3, d29 @ a5*b1, c5*d1
	VSRA.U64 	q6,q13, #32
	VMLAL.U32 	q7,d6, d29 @ a6*b1, c6*d1
	VSRA.U64 	q7,q6, #32
	VMLAL.U32 	q8,d7, d29 @ a7*b1, c7*d1
	VSRA.U64 	q8,q7, #32

	VMOVN.I64 d18, q9
	vst1.32  {d18}, [r0]!
	VLDM r3!, {d28,d29}

@Quinta
	VSHR.U64 q9,  q8, #32
	VAND.I64 q10,  q15
	VAND.I64 q11,  q15
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15
	VAND.I64 q7,  q15
	VAND.I64 q8,  q15

	VMLAL.U32 	q10, d0, d28 @ a0*b1, c0*d1
	VMLAL.U32 	q11, d1, d28 @ a1*b1, c1*d1
	VSRA.U64 	q11, q10, #32
	VMLAL.U32 	q12, d4, d28 @ a2*b1, c2*d1
	VSRA.U64 	q12, q11, #32
	VMLAL.U32 	q13,d5, d28 @ a3*b1, c3*d1
	VSRA.U64 	q13,q12, #32
	VMLAL.U32 	q6,d2, d28 @ a4*b1, c4*d1
	VSRA.U64 	q6,q13, #32
	VMLAL.U32 	q7,d3, d28 @ a5*b1, c5*d1
	VSRA.U64 	q7,q6, #32
	VMLAL.U32 	q8,d6, d28 @ a6*b1, c6*d1
	VSRA.U64 	q8,q7, #32
	VMLAL.U32 	q9,d7, d28 @ a7*b1, c7*d1
	VSRA.U64 	q9,q8, #32

	VMOVN.I64 d20, q10
	vst1.32  {d20}, [r0]!


@Sexta
	VSHR.U64 q10,  q9, #32
	VAND.I64 q11,  q15
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15
	VAND.I64 q7,  q15
	VAND.I64 q8,  q15
	VAND.I64 q9,  q15

	VMLAL.U32 	q11, d0, d29 @ a0*b1, c0*d1
	VMLAL.U32 	q12, d1, d29 @ a1*b1, c1*d1
	VSRA.U64 	q12, q11, #32
	VMLAL.U32 	q13, d4, d29 @ a2*b1, c2*d1
	VSRA.U64 	q13, q12, #32
	VMLAL.U32 	q6,d5, d29 @ a3*b1, c3*d1
	VSRA.U64 	q6,q13, #32
	VMLAL.U32 	q7,d2, d29 @ a4*b1, c4*d1
	VSRA.U64 	q7,q6, #32
	VMLAL.U32 	q8,d3, d29 @ a5*b1, c5*d1
	VSRA.U64 	q8,q7, #32
	VMLAL.U32 	q9,d6, d29 @ a6*b1, c6*d1
	VSRA.U64 	q9,q8, #32
	VMLAL.U32 	q10,d7, d29 @ a7*b1, c7*d1
	VSRA.U64 	q10,q9, #32

	VMOVN.I64 d22, q11
	vst1.32  {d22}, [r0]!
	VLDM r3!, {d28,d29}


@Septima
	VSHR.U64 q11,  q10, #32
	VAND.I64 q12,  q15
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15
	VAND.I64 q7,  q15
	VAND.I64 q8,  q15
	VAND.I64 q9,  q15
	VAND.I64 q10,  q15

	VMLAL.U32 	q12, d0, d28 @ a0*b1, c0*d1
	VMLAL.U32 	q13, d1, d28 @ a1*b1, c1*d1
	VSRA.U64 	q13, q12, #32
	VMLAL.U32 	q6, d4, d28 @ a2*b1, c2*d1
	VSRA.U64 	q6, q13, #32
	VMLAL.U32 	q7,d5, d28 @ a3*b1, c3*d1
	VSRA.U64 	q7,q6, #32
	VMLAL.U32 	q8,d2, d28 @ a4*b1, c4*d1
	VSRA.U64 	q8,q7, #32
	VMLAL.U32 	q9,d3, d28 @ a5*b1, c5*d1
	VSRA.U64 	q9,q8, #32
	VMLAL.U32 	q10,d6, d28 @ a6*b1, c6*d1
	VSRA.U64 	q10,q9, #32
	VMLAL.U32 	q11,d7, d28 @ a7*b1, c7*d1
	VSRA.U64 	q11,q10, #32

	VMOVN.I64 d24, q12
	vst1.32  {d24}, [r0]!


@Octava
	VSHR.U64 q12,  q11, #32
	VAND.I64 q13,  q15
	VAND.I64 q6,  q15
	VAND.I64 q7,  q15
	VAND.I64 q8,  q15
	VAND.I64 q9,  q15
	VAND.I64 q10,  q15
	VAND.I64 q11,  q15

	VMLAL.U32 	q13, d0, d29 @ a0*b1, c0*d1
	VMLAL.U32 	q6, d1, d29 @ a1*b1, c1*d1
	VSRA.U64 	q6, q13, #32
	VMLAL.U32 	q7, d4, d29 @ a2*b1, c2*d1
	VSRA.U64 	q7, q6, #32
	VMLAL.U32 	q8,d5, d29 @ a3*b1, c3*d1
	VSRA.U64 	q8,q7, #32
	VMLAL.U32 	q9,d2, d29 @ a4*b1, c4*d1
	VSRA.U64 	q9,q8, #32
	VMLAL.U32 	q10,d3, d29 @ a5*b1, c5*d1
	VSRA.U64 	q10,q9, #32
	VMLAL.U32 	q11,d6, d29 @ a6*b1, c6*d1
	VSRA.U64 	q11,q10, #32
	VMLAL.U32 	q12,d7, d29 @ a7*b1, c7*d1
	VSRA.U64 	q12,q11, #32

	VMOVN.I64 d26, q13
	vst1.32  {d26}, [r0]!
	VSHR.U64 q13,  q12, #32


	VMOVN.I64 d0, q6
	VMOVN.I64 d1, q7
	VMOVN.I64 d2, q8
	VMOVN.I64 d3, q9
	VMOVN.I64 d4, q10
	VMOVN.I64 d5, q11
	VMOVN.I64 d6, q12
	VMOVN.I64 d7, q13

	VSTM r0, {q0-q3}


	pop {r4-r5}
	bx	lr
	.size	MULNEON, .-MULNEON
