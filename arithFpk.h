/*
arithFpk.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef ARITHFPK_H
 #define ARITHFPK_H

#include "Structures.h"
#define beta 5


void Fpk_print(char *name, Fp *fp, int N);
void setDomMont(Fp *C, Fp *A, int N);
void setDomFp(Fp *C, Fp *A, int N);
void setDomMont2(Fp2 *C, Fp2 *A, int N);
void setDomFp2(Fp2 *C, Fp2 *A, int N);
void initFpk(Fp *C, int N);
int wnaf(int8_t *ki, uint32_t *I, uint8_t w);
void BN_init();
void MultiInverse(Fp *Inv, Fp *Ori, int N);
void Fp2_init(Fp *num);
void Fp2_set(Fp *num, Fp *a);
void Fp2_set_str(Fp *n, char *h, char *l);
void SUMA_FP2(Fp *C, Fp *A, Fp *B);
void RESTA_FP2(Fp *C, Fp *A, Fp *B);
void MULE_FP2(Fp *C, Fp *A, Fp b);
void MULT_FP2(Fp *C, Fp *A, Fp *B);
void CUAD_FP2(Fp *C, Fp *A);
void INVERT_FP2(Fp *C, Fp *A);
void MULT_FP2A(Fp *C, Fp *A, Fp *B);
void MULU_FP2(Fp *C, Fp *A);
void CONJUGADO_FP2(Fp *C, Fp *A);
void NEGATIVO_FP2(Fp *C, Fp *A);
void DIVIDE2_FP2(Fp *C, Fp *A);
void MULTIINVERSE_FP2(Fp2 *Inv, Fp2 *Ori, int N);

void CUAD_FP4(Fp *C1, Fp *C2,Fp *A1, Fp *A2);
void CUAD_FP4A(Fp *C1, Fp *C2,Fp *A1, Fp *A2);

void SUMA_FP6(Fp *C,Fp *A,Fp *B);
void RESTA_FP6(Fp *C,Fp *A,Fp *B);
void MULGAMA_FP6(Fp *C, Fp *A);
void MULT_FP6(Fp *C, Fp *A, Fp *B);
void MULT_FP6_b0(Fp *C, Fp *A, Fp *b0);
void MULT_FP6_b0_b1(Fp *C, Fp *A, Fp *b0, Fp *b1);
void CUAD_FP6(Fp *C, Fp *A);
void INVERSO_FP6(Fp *C, Fp *A);

void SUMA_FP12(Fp *C,Fp *A,Fp *B);
void RESTA_FP12(Fp *C,Fp *A,Fp *B);
void MULT_FP12(Fp *C, Fp *A, Fp *B);
void SMULT_FP12(Fp *C, Fp *A, Fp *B);
void MULT_FP12_b0(Fp *C, Fp *A, Fp b0);
void MULT_FP12_b0b1(Fp *C, Fp *A, Fp *b0, Fp *b1);
void CUAD_FP12A(Fp *C,Fp *A);
void SCOM_FP12(Fp *C, Fp *A);
void SDEC_FP12(Fp *C,Fp *A);
void SDEC_A0_FP12(Fp *A);
void SDEC_A1_FP12(Fp *A, Fp *inv);
void SDEC3_FP12(Fp *A, Fp *B, Fp *C);
void CUAD_FP12(Fp *C,Fp *A);
void INVERSO_FP12(Fp *C,Fp *A);
void CONJUGADO_FP12(Fp *C, Fp *A);

void FROBENIUS_P(Fp *C,Fp *A);
void FROBENIUS_P2(Fp *C,Fp *A);
void FROBENIUS_P3(Fp *C,Fp *A);

void EXPONENCIAR_FP12(Fp *C,Fp *A, int *e, int L);
void SEXPONENCIAR_FP12(Fp *C,Fp *A, int *e, int L);
void FINAL_EXPONENTIATIONA(Fp *C,Fp *A);
void FINAL_EXPONENTIATION(Fp *C,Fp *A);

void Comprobacion(Fp *C,Fp *A);
int comparaFpk(Fp *A, Fp *B, int n);
void Fpk_init(Fp *num, int n);
void Fpk_rand(Fp *n, int N);
void Fpk_set(Fp *C, Fp *A, int N);

#endif
