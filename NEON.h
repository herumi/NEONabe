/*
NEON.h
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#ifndef NEON_H
 #define NEON_H

void MUL256NEON(uint32_t *T, uint32_t *T2, uint32_t *A, uint32_t *B, uint32_t *A1, uint32_t *B1);
void MUL256NEONIT(uint32_t *T, uint32_t *T2, uint32_t *A, uint32_t *B, uint32_t *A1, uint32_t *B1, int it);
void MOD512NEON(uint32_t *T,uint32_t *T2, uint32_t *t, uint32_t *t2);
void MULMONGNEON(uint32_t *T, uint32_t *T2, uint32_t *A, uint32_t *B, uint32_t *A1, uint32_t *B1);
void MULMONGNEON2(uint32_t *T1, uint32_t *T2, uint32_t *A, uint32_t *B, uint32_t *A1, uint32_t *B1);

#endif
