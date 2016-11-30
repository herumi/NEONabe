/*
assembly.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef ASSEMBLY_H
 #define ASSEMBLY_H
#include <stdint.h>

/*********************************
              SUMAS
 ********************************/

#define ADD_32(r1, i1) \
asm volatile(                         \
"add   %0, %1 \n\t"            \
: "+r"(r1) \
: "r"(i1));

#define ADD_32L(c, r1, i1 ) \
asm volatile(                         \
"adds   %0, %2 \n\t"            \
"movcs  %1, #1 \n\t"            \
: "+r"(r1),"+r"(c) \
: "r"(i1));

#define ADD_32C(c1, r1, i1) \
asm volatile(                         \
"adds   %0, #4294967295 \n\t"            \
"adcs   %1, %2 \n\t"            \
: "+r"(c1),"+r"(r1) \
: "r"(i1));

#define ADD_64(r, i ) \
asm volatile(                         \
"adds   %0, %2 \n\t"            \
"adcs   %1, %3 \n\t"            \
: "+r"(r[0]),"+r"(r[1]) \
: "r"(i[0]), "r"(i[1]));

#define ADD_64L(c, r1, r2, i1, i2 ) \
asm volatile(                         \
"adds   %0, %3 \n\t"            \
"adcs   %1, %4 \n\t"            \
"movcs  %2, #1 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(c) \
: "r"(i1), "r"(i2));

#define ADD_64HL(r1, r2, i1 ) \
asm volatile(                         \
"adds   %0, %2 \n\t"            \
"adcs   %1, #0 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(i1));

#define ADD_64C(c1, r1, r2, i1, i2 ) \
asm volatile(                         \
"adds   %0, #4294967295 \n\t"            \
"adcs   %1, %3 \n\t"            \
"adcs   %2, %4 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(r2) \
: "r"(i1), "r"(i2));

#define ADD_64CL(c1, c2, r1, r2, i1, i2 ) \
asm volatile(                         \
"adds   %0, #4294967295 \n\t"            \
"adcs   %1, %4 \n\t"            \
"adcs   %2, %5 \n\t"            \
"movcs  %3, #1 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(r2),"+r"(c2) \
: "r"(i1), "r"(i2));


#define ADD_64CL2(c1, r1, r2, i1, i2 ) \
asm volatile(                         \
"adds   %0, #4294967295 \n\t"            \
"adcs   %1, %3 \n\t"            \
"adcs   %2, %4 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(r2) \
: "r"(i1), "r"(i2));

#define ADD_96(r, i ) \
asm volatile (                         \
"adds   %0, %3 \n\t"            \
"adcs   %1, %4 \n\t"            \
"adcs   %2, %5 \n\t"            \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]) \
: "r"(i[0]), "r"(i[1]),"r"(i[2]));

#define ADD_128L(c, r1, r2, r3, r4, i1, i2, i3, i4 ) \
asm volatile (                         \
"adds   %0, %5 \n\t"            \
"adcs   %1, %6 \n\t"            \
"adcs   %2, %7 \n\t"            \
"adcs   %3, %8 \n\t"            \
"movcs  %4, #1 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4),"+r"(c) \
: "r"(i1), "r"(i2),"r"(i3), "r"(i4));

#define ADD_128CL(c, r1, r2, r3, r4, i1, i2, i3, i4 ) \
asm volatile (                         \
"adds   %0, %5 \n\t"            \
"adcs   %1, %6 \n\t"            \
"adcs   %2, %7 \n\t"            \
"adcs   %3, %8 \n\t"            \
"adcs   %4, #0 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4),"+r"(c) \
: "r"(i1), "r"(i2),"r"(i3), "r"(i4));

#define ADD_96L(r1, r2, r3, r4, i1, i2, i3 ) \
asm volatile (                         \
"adds   %0, %4 \n\t"            \
"adcs   %1, %5 \n\t"            \
"adcs   %2, %6 \n\t"            \
"adcs   %3, #0 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4) \
: "r"(i1), "r"(i2),"r"(i3));

/*********************************
              RESTAS
 ********************************/
#define SUB_32(r1, i1 )\
asm volatile(                      \
"sub   %0, %1 \n\t"            \
: "+r"(r1) \
: "r"(i1));

#define SUB_32C(c1, r1, i1 )\
asm volatile(                      \
"subs   %0, #1 \n\t"            \
"sbcs   %1, %2 \n\t"            \
: "+r"(c1),"+r"(r1) \
: "r"(i1));

#define SUB_32CL(c1, c2, r1, i1 )\
asm volatile(                      \
"subs   %0, #1 \n\t"            \
"sbcs   %1, %3 \n\t"            \
"sbcs   %2, #0 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(c2) \
: "r"(i1));

#define SUB_64(r,i ) \
asm volatile(                         \
"subs   %0, %2 \n\t"            \
"sbcs   %1, %3 \n\t"            \
: "+r"(r[0]),"+r"(r[1]) \
: "r"(i[0]), "r"(i[1]));

#define SUB_64L(c, r1, r2, i1, i2 ) \
asm volatile(                         \
"subs   %0, %3 \n\t"            \
"sbcs   %1, %4 \n\t"            \
"sbcs   %2, #0 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(c) \
: "r"(i1), "r"(i2));

#define SUB_64C(c1, r1, r2, i1, i2 ) \
asm volatile(                      \
"subs   %0, #1 \n\t"            \
"sbcs   %1, %3 \n\t"            \
"sbcs   %2, %4 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(r2) \
: "r"(i1), "r"(i2));

#define SUB_64CL(c1, c2, r1, r2, i1, i2 ) \
asm volatile(                      \
"subs   %0, #1 \n\t"            \
"sbcs   %1, %4 \n\t"            \
"sbcs   %2, %5 \n\t"            \
"sbcs   %3, #0 \n\t"            \
: "+r"(c1),"+r"(r1),"+r"(r2),"+r"(c2) \
: "r"(i1), "r"(i2));

#define SUB_96(r, i ) \
asm volatile (                         \
"subs   %0, %3 \n\t"            \
"sbcs   %1, %4 \n\t"            \
"sbcs   %2, %5 \n\t"            \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]) \
: "r"(i[0]), "r"(i[1]),"r"(i[2]));

#define SUB_128(r, i ) \
asm volatile (                         \
"subs   %0, %4 \n\t"            \
"sbcs   %1, %5 \n\t"            \
"sbcs   %2, %6 \n\t"            \
"sbcs   %3, %7 \n\t"            \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]) \
: "r"(i[0]), "r"(i[1]),"r"(i[2]), "r"(i[3]));

#define SUB_128L(c, r1, r2, r3, r4, i1, i2, i3, i4 ) \
asm volatile(                         \
"subs   %0, %5 \n\t"            \
"sbcs   %1, %6 \n\t"            \
"sbcs   %2, %7 \n\t"            \
"sbcs   %3, %8 \n\t"            \
"sbcs   %4, #0 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4),"+r"(c) \
: "r"(i1), "r"(i2),"r"(i3), "r"(i4));



/*********************************
         MULTIPLICACION
 ********************************/
#define MUL32(r1, r2, i1, i2 ) \
asm(                         \
"umull   %0,%1,%2,%3 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(i1),"r"(i2));

#define MUL32S(r1, i1, i2 ) \
asm(                         \
"mul   %0,%1,%2 \n\t"            \
: "+r"(r1) \
: "r"(i1),"r"(i2));

#define MUL32A1(r1, r2, i1, i2, a1, s){\
asm(                         \
"umull  %0,%1,%2,%3 \n\t"            \
: "+r"(s),"+r"(r2) \
: "r"(i1),"r"(i2)); \
asm(                         \
"adds    %0, %2, %3 \n\t"            \
"adcs    %1, #0 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(s),"r"(a1)); }


#define MUL32A2(r1, r2, i1, i2, a1, a2, s) \
asm(                         \
"umull   %0,%1,%2,%3 \n\t"            \
: "+r"(s),"+r"(r2) \
: "r"(i1),"r"(i2)); \
asm(                         \
"adds    %0, %2, %3 \n\t"            \
"adcs    %1, #0 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(s), "r"(a1));\
asm(                         \
"adds    %0, %2 \n\t"            \
"adcs    %1, #0 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(a2));

/*
#define MUL32A1(r1, r2, i1, i2, o1) \
asm(                         \
"umull   %0,%1,%2,%3 \n\t"            \
"adds    %0, %4 \n\t"            \
"adcs    %1, #0 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(i1),"r"(i2),"r"(o1));
*/



/*********************************
            SHIFTS
 ********************************/

#define LSL1(r1,i1)\
asm(		\
"lsl %0, %1, #1 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSL2_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1])\
: );

#define LSL3_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2])	\
: );

#define LSL4_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
"lsl %3, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3])\
: );

#define LSL5_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
"lsl %3, #1 \n\t" \
"lsl %4, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4])	\
: );

#define LSL6_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
"lsl %3, #1 \n\t" \
"lsl %4, #1 \n\t" \
"lsl %5, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5])\
: );

#define LSL7_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
"lsl %3, #1 \n\t" \
"lsl %4, #1 \n\t" \
"lsl %5, #1 \n\t" \
"lsl %6, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6])	\
: );

#define LSL8_1(r)\
asm(		\
"lsl %0, #1 \n\t" \
"lsl %1, #1 \n\t" \
"lsl %2, #1 \n\t" \
"lsl %3, #1 \n\t" \
"lsl %4, #1 \n\t" \
"lsl %5, #1 \n\t" \
"lsl %6, #1 \n\t" \
"lsl %7, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6]),"+r"(r[7]) 			\
: );

#define LSL29(r1,i1)\
asm (		\
"lsl %0, %1, #29 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSL31(r1,i1)\
asm (		\
"lsl %0, %1, #31 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSL2_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1])	\
: );

#define LSL3_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
"lsl %2, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2])\
: );

#define LSL4_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
"lsl %2, #31 \n\t" \
"lsl %3, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3])	\
: );

#define LSL5_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
"lsl %2, #31 \n\t" \
"lsl %3, #31 \n\t" \
"lsl %4, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4])\
: );

#define LSL6_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
"lsl %2, #31 \n\t" \
"lsl %3, #31 \n\t" \
"lsl %4, #31 \n\t" \
"lsl %5, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5])	\
: );

#define LSL7_31(r)\
asm(		\
"lsl %0, #31 \n\t" \
"lsl %1, #31 \n\t" \
"lsl %2, #31 \n\t" \
"lsl %3, #31 \n\t" \
"lsl %4, #31 \n\t" \
"lsl %5, #31 \n\t" \
"lsl %6, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6])\
: );


#define LSR1(r1,i1)\
asm (		\
"lsr %0, %1, #1 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSR2_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1])	\
: );

#define LSR3_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2])	\
: );

#define LSR4_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
"lsr %3, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3])	\
: );

#define LSR5_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
"lsr %3, #1 \n\t" \
"lsr %4, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4])	\
: );

#define LSR6_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
"lsr %3, #1 \n\t" \
"lsr %4, #1 \n\t" \
"lsr %5, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5])	\
: );

#define LSR7_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
"lsr %3, #1 \n\t" \
"lsr %4, #1 \n\t" \
"lsr %5, #1 \n\t" \
"lsr %6, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6])	\
: );

#define LSR8_1(r)\
asm(		\
"lsr %0, #1 \n\t" \
"lsr %1, #1 \n\t" \
"lsr %2, #1 \n\t" \
"lsr %3, #1 \n\t" \
"lsr %4, #1 \n\t" \
"lsr %5, #1 \n\t" \
"lsr %6, #1 \n\t" \
"lsr %7, #1 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6]),"+r"(r[7]) 			\
: );

#define LSR3(r1,i1)\
asm (		\
"lsr %0, %1, #3 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSR31(r1,i1)\
asm (		\
"lsr %0, %1, #31 \n\t" \
: "+r"(r1) 			\
: "r"(i1));

#define LSR2_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1])	\
: );

#define LSR3_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
"lsr %2, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2])\
: );

#define LSR4_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
"lsr %2, #31 \n\t" \
"lsr %3, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3])	\
: );

#define LSR5_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
"lsr %2, #31 \n\t" \
"lsr %3, #31 \n\t" \
"lsr %4, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4])\
: );

#define LSR6_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
"lsr %2, #31 \n\t" \
"lsr %3, #31 \n\t" \
"lsr %4, #31 \n\t" \
"lsr %5, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5])	\
: );

#define LSR7_31(r)\
asm(		\
"lsr %0, #31 \n\t" \
"lsr %1, #31 \n\t" \
"lsr %2, #31 \n\t" \
"lsr %3, #31 \n\t" \
"lsr %4, #31 \n\t" \
"lsr %5, #31 \n\t" \
"lsr %6, #31 \n\t" \
: "+r"(r[0]),"+r"(r[1]),"+r"(r[2]),"+r"(r[3]),"+r"(r[4]),"+r"(r[5]),"+r"(r[6])\
: );

/*********************************
              XOR
 ********************************/
#define XOR_32(r1, i1 ) \
asm volatile (                         \
"eor   %0, %1 \n\t"            \
: "+r"(r1) \
: "r"(i1));

#define XOR_64(r1, r2, i1, i2 ) \
asm volatile (                         \
"eor   %0, %2 \n\t"            \
"eor   %1, %3 \n\t"            \
: "+r"(r1),"+r"(r2) \
: "r"(i1), "r"(i2));

#define XOR_96(r1, r2, r3, i1, i2, i3 ) \
asm volatile (                         \
"eor   %0, %3 \n\t"            \
"eor   %1, %4 \n\t"            \
"eor   %2, %5 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3) \
: "r"(i1), "r"(i2),"r"(i3));

#define XOR_128(r1, r2, r3, r4, i1, i2, i3, i4 ) \
asm volatile (                         \
"eor   %0, %4 \n\t"            \
"eor   %1, %5 \n\t"            \
"eor   %2, %6 \n\t"            \
"eor   %3, %7 \n\t"            \
: "+r"(r1),"+r"(r2),"+r"(r3),"+r"(r4) \
: "r"(i1), "r"(i2),"r"(i3), "r"(i4));

/*********************************
    AUXILIARES -SUMAS INVERSO
 ********************************/
void ADD_160(uint32_t *res, uint32_t *B){
	uint32_t c1=0;
	ADD_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	ADD_32C(c1,res[4], B[4]);
}

void ADD_192(uint32_t *res, uint32_t *B){
	uint32_t c1=0;
	ADD_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	ADD_64C(c1, res[4], res[5], B[4], B[5]);
}

void ADD_224(uint32_t *res, uint32_t *B){
	uint32_t c1=0, c2=0;
	ADD_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	ADD_64CL(c1, c2,res[4], res[5], B[4], B[5]);
	ADD_32C(c2,res[6], B[6]);
}

void ADD_256(uint32_t *res, uint32_t *B){
	uint32_t c1=0, c2=0;
	ADD_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	ADD_64CL(c1, c2,res[4], res[5], B[4], B[5]);
	ADD_64C(c2, res[6], res[7], B[6], B[7]);
}

/*********************************
    AUXILIARES -RESTAS INVERSO
 ********************************/
void SUB_160(uint32_t *res, uint32_t *B){
	uint32_t c1=1;
	SUB_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	SUB_32C(c1,res[4], B[4]);
}

void SUB_192(uint32_t *res, uint32_t *B){
	uint32_t c1=1;
	SUB_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	SUB_64C(c1, res[4], res[5], B[4], B[5]);
}

void SUB_224(uint32_t *res, uint32_t *B){
	uint32_t c1=1, c2=1;
	SUB_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	SUB_64CL(c1, c2,res[4], res[5], B[4], B[5]);
	SUB_32C(c2,res[6], B[6]);
}

void SUB_256(uint32_t *res, uint32_t *B){
	uint32_t c1=1, c2=1;
	SUB_128L(c1,res[0],res[1],res[2], res[3], B[0],B[1],B[2],B[3]);
	SUB_64CL(c1, c2,res[4], res[5], B[4], B[5]);
	SUB_64C(c2, res[6], res[7], B[6], B[7]);
}

/*********************************
    AUXILIARES -SHIFTS INVERSO
 ********************************/

void shifR1_64(uint32_t *A){
	uint32_t t;
	LSL31(t,A[1]);
	LSR2_1(A);
	XOR_32(A[0],t);
}

void shifR1_96(uint32_t *A){
	uint32_t t[]={A[1],A[2]};
	LSR3_1(A);
	LSL2_31(t);
	XOR_64(A[0],A[1],t[0],t[1]);
}

void shifR1_128(uint32_t *A){
	uint32_t t[]={A[1],A[2],A[3]};
	LSR4_1(A);
	LSL3_31(t);
	XOR_96(A[0],A[1],A[2],t[0],t[1],t[2]);
}

void shifR1_160(uint32_t *A){
	uint32_t t[]={A[1],A[2],A[3],A[4]};
	LSR5_1(A);
	LSL4_31(t);
	XOR_128(A[0],A[1],A[2],A[3],t[0],t[1],t[2],t[3]);
}

void shifR1_192(uint32_t *A){
	uint32_t t[]={A[1],A[2],A[3],A[4],A[5]};
	LSR6_1(A);
	LSL5_31(t);
	XOR_128(A[0],A[1],A[2],A[3],t[0],t[1],t[2],t[3]);
	XOR_32(A[4],t[4]);
}

void shifR1_224(uint32_t *A){
	uint32_t t[]={A[1],A[2],A[3],A[4],A[5],A[6]};
	LSR7_1(A);
	LSL6_31(t);
	XOR_128(A[0],A[1],A[2],A[3],t[0],t[1],t[2],t[3]);
	XOR_64(A[4],A[5],t[4],t[5]);
}

void shifR1_256(uint32_t *A){
	uint32_t t[]={A[1],A[2],A[3],A[4],A[5],A[6],A[7]};
	LSR8_1(A);
	LSL7_31(t);
	XOR_128(A[0],A[1],A[2],A[3],t[0],t[1],t[2],t[3]);
	XOR_96(A[4],A[5],A[6],t[4],t[5],t[6]);
}

void shifL1_64(uint32_t *A){
	uint32_t t;
	LSR31(t,A[0]);
	LSL2_1(A);
	XOR_32(A[1],t);
}

void shifL1_96(uint32_t *A){
	uint32_t t[]={A[0],A[1]};
	LSL3_1(A);
	LSR2_31(t);
	XOR_64(A[1],A[2],t[0],t[1]);
}

void shifL1_128(uint32_t *A){
	uint32_t t[]={A[0],A[1],A[2]};
	LSL4_1(A);
	LSR3_31(t);
	XOR_96(A[1],A[2],A[3],t[0],t[1],t[2]);
}

void shifL1_160(uint32_t *A){
	uint32_t t[]={A[0],A[1],A[2],A[3]};
	LSL5_1(A);
	LSR4_31(t);
	XOR_128(A[1],A[2],A[3],A[4],t[0],t[1],t[2],t[3]);
}

void shifL1_192(uint32_t *A){
	uint32_t t[]={A[0],A[1],A[2],A[3],A[4]};
	LSL6_1(A);
	LSR5_31(t);
	XOR_128(A[1],A[2],A[3],A[4],t[0],t[1],t[2],t[3]);
	XOR_32(A[5],t[4]);
}

void shifL1_224(uint32_t *A){
	uint32_t t[]={A[0],A[1],A[2],A[3],A[4],A[5]};
	LSL7_1(A);
	LSR6_31(t);
	XOR_128(A[1],A[2],A[3],A[4],t[0],t[1],t[2],t[3]);
	XOR_64(A[5],A[6],t[4],t[5]);
}

void shifL1_256(uint32_t *A){
	uint32_t t[]={A[0],A[1],A[2],A[3],A[4],A[5],A[6]};
	LSL8_1(A);
	LSR7_31(t);
	XOR_128(A[1],A[2],A[3],A[4],t[0],t[1],t[2],t[3]);
	XOR_96(A[5],A[6],A[7],t[4],t[5],t[6]);
}

#endif
