/*
Funciones.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef FUNCIONES_H
 #define FUNCIONES_H

#include "arith/Structures.h"

void KeyGen(Fp *K, Fp2 *L, PG1 *Kx, PG1 PK, PG1 MSK, PG2 G2, PG1 *H, int tam);
void Encrypt(Fp *C, Fp S, Fp M, Fp12 *E, Fp2 *CP, PG2 *Q1, PG1 *Ci, PG2 *Di, PG1 *K1, PG1 *H, Fp *lambda, int n);
void Decrypt(Fp *PT,Fp *C,PG1 *Ci, PG1 *Ki, Fp *Omega, int *Sign, int n, PG1 K, PG2 L, Fp12 *l,PG2 *Di, PG2 CP, Fp delta);
void Delegate(Fp *K2, Fp2 *L2, PG1 *Kx2, Fp *K1, Fp2 *L1, PG1 *Kx1, PG1 PK, PG2 G2, PG1 *H, int tam);

#endif
