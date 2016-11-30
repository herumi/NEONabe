/*
Domain.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/
#ifndef DOMAIN_H
 #define DOMAIN_H

#include "Structures.h"

Fp2 Y1[5], Y3[5];
Fp Y2[5];
int8_t WNAF_SK[70];
int TAM_WNAF_SK;
char  szLogThis[500];

uint32_t px4[9];
uint32_t p [9];
uint32_t mu[9];
uint32_t pi[9];
uint32_t r2[9];
uint32_t um[9];
uint32_t r [9];
uint32_t dd[9];
uint32_t sq[9];

//Q=p-1, Q=2^s*t
int S_2ST_Q;
uint32_t T_2ST_Q[9];
uint32_t T_2ST_D[9];
uint32_t Z_SQR[9];;

//BN
Fp G1_BInv[2];
Fp G1_BNor[2][2];
Fp BN_Beta;
Fp G2_BInv[4];
Fp G2_BNor[7];

#endif
