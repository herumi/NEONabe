/*
Funciones.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "pairing.h"

uint32_t r [9];

void KeyGen(Fp *K, Fp2 *L, PG1 *Kx, PG1 PK, PG1 MSK, PG2 G2, PG1 *H, int tam){

	int i;
	Fp t;
    Fp_randL(t,r);
    G1GLVMult(K, PK, t);
    G1AddMix(K, K, MSK.xyz);
    G1normalize(K, 1);

    G2GLVMult(L, G2, t);
    G2normalize(L, 1);

    for(i=0; i<tam; i++){
        G1GLVMult(Kx[i].xyz, H[i], t);
    }
    G1Multinormalizacion(Kx, tam, 1);
}


void Encrypt(Fp *C, Fp S, Fp M, Fp12 *E, Fp2 *CP, PG2 *Q1,
		PG1 *Ci, PG2 *Di, PG1 *K1, PG1 *H, Fp *lambda, int n){

	int i;
	PG1 A;
	Fp Ri;

	ConvertMont(M, M);

	EXPONENCIACION_COMB(C,E,S);
    MULT_FP12_b0(C, C, M);
    setDomFp(C, C, 12);

    G2combMult(CP, Q1, S);
    G2normalize(CP, 1);



    for(i=0; i<n; i++){
    	Fp_randL(Ri,r);
    	G1combMult(Ci[i].xyz, K1, lambda[i]);
    	G1GLVMult(A.xyz, H[i], Ri);
    	G1J2A(A.xyz, A.xyz);
    	G1Inv(A.xyz, A.xyz);
    	G1AddMix(Ci[i].xyz, Ci[i].xyz, A.xyz);
    	G2combMult(Di[i].xyz, Q1, Ri);
    }

    G1Multinormalizacion(Ci, n, 1);
    G2Multinormalizacion(Di, n, 1);
}


void Decrypt(Fp *PT,Fp *C,PG1 *Ci, PG1 *Ki, Fp *Omega, int *Sign, int n, PG1 K, PG2 L, Fp12 *l,PG2 *Di, PG2 CP, Fp delta){
	int x=0;
	int i;
	PG1 CT;
	Fp uno ={1,0,0,0,0,0,0,0,0};
	Fp B1[12],B2[12],E1[12],E2[12];

	for(i=0; i<n; i++){
		if(Sign[i] !=0){
			if(Sign[i]<0){
				G1Inv(Ci[x].xyz, Ci[x].xyz);
				G1Inv(Ki[x].xyz, Ki[x].xyz);
			}
			G1scalarMult(Ci[x].xyz, Ci[x], Omega[i]);
			G1scalarMult(Ki[x].xyz, Ki[x], Omega[i]);
			x++;
		}
	}

	G1Multinormalizacion(Ci, x, 0);
	G1Multinormalizacion(Ki, x, 0);

	G1P_cpy(CT.xyz, Ci[0].xyz);

	for(i=1; i<x; i++){
		G1AddMix(CT.xyz, CT.xyz, Ci[i].xyz);
	}
	G1J2A(CT.xyz, CT.xyz);

	SMultiPairing(E1, Ki, Di, l,  CT, L, x);
	Pairing(B1, K, CP); //Bien

	if(comparativo(uno,delta,8)!=0){
		EXPONENCIACION_GS(E2,E1,delta);
	}
	CONJUGADO_FP12(B2, B1);
	MULT_FP12(E1, E2, B2);

	MULT_FP12(PT, C, E1);

	setDomFp(PT, PT, 1);

}


void Delegate(Fp *K2, Fp2 *L2, PG1 *Kx2, Fp *K1, Fp2 *L1, PG1 *Kx1, PG1 PK, PG2 G2, PG1 *H, int tam){
	int i;
	Fp t;
    Fp_randL(t,r);
    G1GLVMult(K2, PK, t);
    G1AddMix(K2, K2, K1);
    G1normalize(K2, 1);
    G2GLVMult(L2, G2, t);
    G2AddMix(L2, L2, L1);
    G2normalize(L2, 1);

    for(i=0; i<tam; i++){
        G1GLVMult(Kx2[i].xyz, H[i], t);
        G1AddMix(Kx2[i].xyz, Kx2[i].xyz, Kx1[i].xyz);
    }
    G1Multinormalizacion(Kx2, tam, 1);
}
