/*
arithFp.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef ARITHFP_H
 #define ARITHFP_H
#include<stdio.h>
#include "Structures.h"

#define DEBUG_TAG "debug_tag"
char  szLogThis[500];


void logC();
void Fp_print(uint32_t *A);
void Fp_printN(uint32_t *A, int n);
int comparativo(uint32_t *A, uint32_t *B, int tam);
void ADD256(uint32_t *res, uint32_t *A, uint32_t *B);
void SUB256(uint32_t *res, uint32_t *A, uint32_t *B);
void ADD256MOD(uint32_t *res, uint32_t *A, uint32_t *B);
void SUB256MOD(uint32_t *res, uint32_t *A, uint32_t *B);
void sumRed(uint32_t *T, uint32_t *X);
uint32_t zero(uint32_t *A);
void MUL256N(uint32_t *T, uint32_t *A, uint32_t *B, int N);
void MUL256(uint32_t *T, uint32_t *A, uint32_t *B);
void MULE(uint32_t *T, uint32_t *B, uint32_t A);
void MULE512(uint32_t *T, uint32_t *B, uint32_t A);
void shifR1(uint32_t *T, uint32_t *A);
void shifR3(uint32_t *T, uint32_t *A);
void shifL1(uint32_t *T, uint32_t *A);

void REDBARRET(uint32_t *T, uint32_t *X);
void ConvertMont(uint32_t *T, uint32_t *A);
void MULMONG(uint32_t *t, uint32_t *A, uint32_t *B);
void MULMONG1(uint32_t *T, uint32_t *A);
void MOD512(uint32_t *T, uint32_t *t);
void MULMONGS(uint32_t *T, uint32_t *A, uint32_t *B);
void SADD256(uint32_t *res, uint32_t *A, uint32_t *B);
void SSUB256(uint32_t *res, uint32_t *A, uint32_t *B);
void inverso(uint32_t *Ai, uint32_t *A, uint32_t *B);
int partialMontInv(uint32_t *A, uint32_t *B, uint32_t *X);
void MontInverse(uint32_t *X, uint32_t *A);
void DIVIDE2(uint32_t *C, uint32_t *A);
void Fp_init(uint32_t *num);
void Fp_set(uint32_t *num, uint32_t *a);
void Fp_setD(uint32_t *num, uint32_t a7,uint32_t a6,uint32_t a5,uint32_t a4,uint32_t a3,uint32_t a2,uint32_t a1,uint32_t a0);
void Fp_set_str(uint32_t *n, char *s);
void Fp_rand(uint32_t *n);
void Fp_randL(uint32_t *n, uint32_t *l);
int binary16Integer(uint8_t *bin, uint32_t *k);
int TransposeInt(uint8_t *bin, uint32_t *k);
void EXPO(uint32_t *T, uint32_t *A, uint32_t *k);
int SQRROOT(uint32_t *T, uint32_t *A);
#endif
