/*
Structures.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef STRUCTURES_H
 #define STRUCTURES_H

#include<stdio.h>

typedef uint32_t Fp[9];
typedef uint32_t Mul[17];
typedef Fp Fp2[2];
typedef Fp Fp12[12];


typedef struct {
    Fp xyz[3];
} PG1;


typedef struct{
	Fp2 xyz[3];
}PG2;
#endif
