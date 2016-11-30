/*
pairing.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef PAIRING_H
 #define PAIRING_H

#include "Structures.h"

void DobLqq(Fp2 *Q, Fp *P, Fp2 *T, Fp *l, Fp *z2);
void DobLqqH(Fp2 *Q, Fp *P, Fp2 *T, Fp *l);
void AddTate(Fp2 *T, Fp *l, Fp2 *Q, Fp2 *R, Fp *P, Fp *z2);
void AddTateH(Fp2 *T, Fp *l, Fp2 *Q, Fp2 *R, Fp *P);
void RPhi(Fp2 *T, PG2 Q);
void RPhi2(Fp2 *T, PG2 Q);
void RPhi3(Fp2 *T, PG2 Q);
void LinesPrecompute(Fp12 *l, PG2 Q);
void Pairing(Fp *f, PG1 P, PG2 Q);
void SPairing(Fp *C, PG1 P, PG2 Q, Fp12 *L);
void MultiPairing(Fp *f, PG1 *P, PG2 *Q, int N);
void SMultiPairing(Fp *C, PG1 *P, PG2 *Q, Fp12 *LL, PG1 CT, PG2 L, int N);
void ExpoPrecompute(Fp12 *P1, Fp *P, int N);
void EXPONENCIACION64(Fp *C, Fp *A, Fp K);
void EXPONENCIACION_GS(Fp *C, Fp *A, Fp K);
void EXPONENCIACION_GSKNOWN(Fp *C, Fp K, Fp12 *P1, Fp12 *P2, Fp12 *P3, Fp12 *P4, int Naf);
void ExpoCombPrecompute(Fp12 *Pi, Fp *P);
void EXPONENCIACION_COMB(Fp *C, Fp12 *P, Fp K);


#endif
