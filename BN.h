/*
BN.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef BN_H
 #define BN_H

#include "Structures.h"

void G1P_print(PG1 p, char *t);
void G1P_set(Fp *C, char *X, char *Y);
void G1P_cpy(Fp *C, Fp *A);
void G1Inv(Fp *C, Fp *A);
void G1AddAff(Fp *C, Fp *A, Fp *B);
void G1DobAff(Fp *C, Fp *A);

void G1DoubJ(Fp *C, Fp *A);
void G1AddMix(Fp *C, Fp *A, Fp *B);
void G1J2A(Fp *C, Fp *A);
void G1Decomposition(Fp *D, Fp A, int8_t *S);
void G1Multinormalizacion(PG1 *P,int N, int flag);
void G1normalize(Fp *C, int flag);
void G1Precompute(PG1 *Pi, PG1 P, int n);
void G1GLVPrecompute(PG1 *P1, PG1 *H1, PG1 P, PG1 H);
void G1scalarMult(Fp *kP, PG1 P, Fp K);
void G1GLVMult(Fp *kP, PG1 P, Fp K);
void G1GLVMultKnown(Fp *kP, Fp K, PG1 *P1, PG1 *P2, int Naf);
void G1MapToPoint(Fp *P, Fp X);
void G1CombPrecompute(PG1 *Pi, PG1 P);
void G1combMult(Fp *kP, PG1 *P, Fp K);

void G2P_print(PG2 p, char *t);
void G2P_set(Fp2 *C, char *X1,char *X2, char *Y1,char *Y2);
void G2P_cpy(Fp2 *C, Fp2 *A);
void G2Inv(Fp2 *C, Fp2 *A);
void Phi(Fp2 *T, PG2 Q);
void Phi2(Fp2 *T, PG2 Q);
void Phi3(Fp2 *T, PG2 Q);
void G2AddAff(Fp2 *C, Fp2 *A, Fp2 *B);
void G2DobAff(Fp2 *C, Fp2 *A);
void G2DoubJ(Fp2 *C, Fp2 *A);
void G2AddMix(Fp2 *C, Fp2 *A, Fp2 *B);
void G2J2A(Fp2 *C, Fp2 *A);
void G2H2A(Fp2 *C, Fp2 *A);
void G2normalize(Fp2 *C, int flag);
void G2Precompute(PG2 *Pi, PG2 P, int n);
void G2GLVPrecompute(PG2 *P1, PG2 *Q1, PG2 *R1, PG2 *S1, PG2 P, PG2 Q, PG2 R, PG2 S);
void G2scalarMult(Fp2 *kP, PG2 P, Fp K);
void GSDecomposition(Fp *D, Fp A, int8_t *sig);
void G2GLVMult(Fp2 *kP, PG2 P, Fp K);
void G2GLVMultKnown(Fp2 *kP, Fp K, PG2 *P1, PG2 *P2, PG2 *P3, PG2 *P4, int Naf);
void G2Multinormalizacion(PG2 *P,int N, int flag);
void G2CombPrecompute(PG2 *Pi, PG2 P);
void G2combMult(Fp2 *kP, PG2 *P, Fp K);

#endif
