/*
pairing.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "BN.h"
#include "Domain.h"

void DobLqq(Fp2 *Q, Fp *P, Fp2 *T, Fp *l, Fp *z2){
	Fp2 t0,t1,t2,t3,t4,t5,t6;
	CUAD_FP2(t0,Q[0]); //t0
	CUAD_FP2(t1,Q[1]); //t1
	CUAD_FP2(t2,t1);  //t2
	SUMA_FP2(t3, t1, Q[0]);
	CUAD_FP2(t3,t3);
	RESTA_FP2(t3, t3, t0);
	RESTA_FP2(t3, t3, t2);
	SUMA_FP2(t3, t3, t3); //t3
	SUMA_FP2(t4, t0, t0);
	SUMA_FP2(t4, t4, t0); //t4
	SUMA_FP2(t6, t4, Q[0]); //t6
	CUAD_FP2(t5,t4); //t5
	RESTA_FP2(T[0], t5, t3);
	RESTA_FP2(T[0], T[0], t3); //XT
	SUMA_FP2(T[2], Q[2], Q[1]);
	CUAD_FP2(T[2],T[2]);
	RESTA_FP2(T[2], T[2], t1);
	RESTA_FP2(T[2], T[2], z2);
	RESTA_FP2(T[1], t3, T[0]);

	MULT_FP2(T[1], T[1], t4);
	SUMA_FP2(t2, t2, t2);//2t2
	SUMA_FP2(t2, t2, t2);//4t2
	SUMA_FP2(t2, t2, t2);//8t2
	RESTA_FP2(T[1], T[1], t2);
	MULT_FP2(t3, t4, z2);
	SUMA_FP2(t4, t3, t3);
	NEGATIVO_FP2(t3,t4);
	MULE_FP2(&l[6], t3, P[0]);
	CUAD_FP2(t4,t6);
	SUMA_FP2(t1, t1, t1);
	SUMA_FP2(t1, t1, t1);
	RESTA_FP2(t6, t4, t0);
	RESTA_FP2(t6, t6, t5);
	RESTA_FP2(&l[8], t6, t1);
	MULT_FP2(t0,T[2],z2);
	SUMA_FP2(t0, t0, t0);
	MULE_FP2(l, t0, P[1]);
	CUAD_FP2(z2,T[2]);
}


void DobLqqH(Fp2 *T, Fp *l, Fp2 *Q, Fp x, Fp y){
	Fp2 A,B,C,F,G,H,J,X;
	Fp D[2],E[2];
	Mul X1[2],T1[2];
	SUMA_FP2(X, Q[1], Q[2]);
	CUAD_FP2(H, X);
	CUAD_FP2(J, Q[0]);

	MULT_FP2(A, Q[0], Q[1]);
	DIVIDE2_FP2(A,A);//A
	CUAD_FP2(B,Q[1]);//B
	CUAD_FP2(C,Q[2]);//C
	SUMA_FP2(D,C,C);
	SUMA_FP2(D,D,C);//D
	ADD256MOD(E[0], D[0], D[1]);
	SUB256MOD(E[1], D[1], D[0]);//E
	SUMA_FP2(F,E,E);
	SUMA_FP2(F,F,E);//F
	RESTA_FP2(X,B,F);

//	MULT_FP2(T[0], X, A);//X
	SUMA_FP2(G,B,F);
	DIVIDE2_FP2(G,G);//G
	CUAD_FP2L(X1,E);
	CUAD_FP2L(T1,G);
	RESTA_FP2L(T1,X1);
	RESTA_FP2L(T1,X1);
	RESTA_FP2L(T1,X1);
	REDU_FP2(T[1], T1);
	RESTA_FP2(H,H,B);
	RESTA_FP2(H,H,C);//H

	MULT_FP2_DUAL(T[2],B, H,T[0], X, A);//Z
	RESTA_FP2(&l[8],E,B);//I
	MULE_FP2(&l[0],H,y);
	MULE_FP2(&l[6],J,x);
}


void DobLqqHE(Fp2 *T, Fp *l, Fp2 *Q, Fp x, Fp y){
	Fp2 A,B,C,G,J;
	Fp D[2],E[2],H[2],F[2],X[2];
	Mul X1[2],T1[2];
	Fp_setD(D[1],0,0,0,0,0,0,0,0);
	Fp_setD(D[0],0x193C25D2,0xFFFFFFDD,0x73E9F1FF,0xFFFFFF58,0x696BFFFF,0xFFFFFE76,0xF3FFFFFF,0xFFFFFE84);
	Fp_setD(E[1],0x0BE73EAF,0x40000024,0x464A5B80,0x000000AF,0xF7B50000,0x0000019C,0xB3000000,0x0000018F);
	Fp_setD(F[0],0x016DA874,0x7FFFFF94,0xE7553AFF,0xFFFFFDF8,0x7A01FFFF,0xFFFFFB3D,0x8DFFFFFF,0xFFFFFB66);
	Fp_setD(F[1],0x23B5BC0D,0xC000006C,0xD2DF1280,0x0000020F,0xE71F0000,0x000004D6,0x19000000,0x000004AD);
	Fp_set(E[0], D[0]);
	Fp_set(E[0], D[0]);
	Fp_set(X[0], Q[1][0]);
	Fp_set(X[1], Q[1][1]);

	ADD256MOD(X[0], X[0], um);
	CUAD_FP2(H, X);
	CUAD_FP2(J, Q[0]);
	MULT_FP2(A, Q[0], Q[1]);
	DIVIDE2_FP2(A,A);//A
	CUAD_FP2(B,Q[1]);//B
	RESTA_FP2(X,B,F);
//	MULT_FP2(T[0], X, A);//X
	SUMA_FP2(G,B,F);
	DIVIDE2_FP2(G,G);//G
	CUAD_FP2L(X1,E);
	CUAD_FP2L(T1,G);
	RESTA_FP2L(T1,X1);
	RESTA_FP2L(T1,X1);
	RESTA_FP2L(T1,X1);
	REDU_FP2(T[1], T1);
	RESTA_FP2(H,H,B);
	SUB256MOD(H[0], H[0], um);
	MULT_FP2_DUAL(T[2],B, H, T[0], X, A);//Z
	RESTA_FP2(&l[8],E,B);//I
	MULE_FP2(&l[0],H,y);
	MULE_FP2(&l[6],J,x);
}

void AddTate(Fp2 *T, Fp *l, Fp2 *Q, Fp2 *R, Fp *P, Fp *z2){
	Mul Y2[2],T0[2], T1[2], T8[2], T9[2], T10[2];
	Fp2 t0,t1,t2,t3,t4,t5,t6,t7,t8,t10;
	CUAD_FP2L(Y2, Q[1]);

//	MULT_FP2(t0, Q[0], z2); //t0
	SUMA_FP2(t1, Q[1], R[2]);
	CUAD_FP2L(T1, t1);
	RESTA_FP2L(T1, Y2);
	REDU_FP2(t1,T1);
	RESTA_FP2(t1, t1, z2);
	MULT_FP2_DUAL(t1, t1, z2, t0, Q[0], z2); //t1

	RESTA_FP2(t2, t0, R[0]); //t2
	CUAD_FP2(t3, t2); //t3
	SUMA_FP2(t4, t3, t3);
	SUMA_FP2(t4, t4, t4); //t4

	MULT_FP2_DUAL(t5, t4, t2, t7, t4, R[0]); //t5

	RESTA_FP2(t6, t1, R[1]);
	RESTA_FP2(t6, t6, R[1]); //t6
	MULT_FP2L(T9, t6, Q[0]); //t9
//	MULT_FP2(t7, t4, R[0]); //t7
	CUAD_FP2(T[0], t6);
	RESTA_FP2(T[0], T[0], t5);
	RESTA_FP2(T[0], T[0], t7);
	RESTA_FP2(T[0], T[0], t7); //XT
	SUMA_FP2(T[2], R[2], t2);
	CUAD_FP2(T[2], T[2]);
	RESTA_FP2(T[2], T[2], z2);
	RESTA_FP2(T[2], T[2], t3); //ZT
	SUMA_FP2(t10, Q[1], T[2]);//t10
	RESTA_FP2(t8, t7, T[0]);
	MULT_FP2L_DUAL(T8,T0, t8, t6,R[1], t5); //t8
//	MULT_FP2L(T0, R[1], t5);
	SUMA_FP2L(T0, T0, T0);//t0
	RESTA_FP2L(T8, T0);
	REDU_FP2(T[1],T8);//YT
	CUAD_FP2L(T10, t10);
	RESTA_FP2L(T10, Y2);
	CUAD_FP2(z2, T[2]);
	SUMA_FP2L(T9, T9, T9);
	RESTA_FP2L(T9, T10);
	REDU_FP2(&l[8],T9);
	SUMA_FP2(&l[8], &l[8], z2);//t9
	MULE_FP2(t10, T[2], P[1]);
	SUMA_FP2(l, t10, t10);//t10
	NEGATIVO_FP2(t7,t6);
	MULE_FP2(t1, t7, P[0]);
	SUMA_FP2(&l[6], t1, t1);//t10
}


void AddTateA(Fp2 *T, Fp *l, Fp2 *Q, Fp2 *R, Fp *P, Fp *z2){
	Fp2 y2, t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

	CUAD_FP2(y2, Q[1]);
	MULT_FP2(t0, Q[0], z2); //t0
	SUMA_FP2(t1, Q[1], R[2]);
	CUAD_FP2(t1, t1);
	RESTA_FP2(t1, t1, y2);
	RESTA_FP2(t1, t1, z2);
	MULT_FP2(t1, t1, z2); //t1
	RESTA_FP2(t2, t0, R[0]); //t2
	CUAD_FP2(t3, t2); //t3
	SUMA_FP2(t4, t3, t3);
	SUMA_FP2(t4, t4, t4); //t4
	MULT_FP2(t5, t4, t2); //t5
	RESTA_FP2(t6, t1, R[1]);
	RESTA_FP2(t6, t6, R[1]); //t6
	MULT_FP2(t9, t6, Q[0]); //t9
	MULT_FP2(t7, t4, R[0]); //t7
	CUAD_FP2(T[0], t6);
	RESTA_FP2(T[0], T[0], t5);
	RESTA_FP2(T[0], T[0], t7);
	RESTA_FP2(T[0], T[0], t7); //XT
	SUMA_FP2(T[2], R[2], t2);
	CUAD_FP2(T[2], T[2]);
	RESTA_FP2(T[2], T[2], z2);
	RESTA_FP2(T[2], T[2], t3); //ZT
	SUMA_FP2(t10, Q[1], T[2]);//t10
	RESTA_FP2(t8, t7, T[0]);
	MULT_FP2(t8, t8, t6); //t8
	MULT_FP2(t0, R[1], t5);
	SUMA_FP2(t0, t0, t0);//t0
	RESTA_FP2(T[1], t8, t0); //YT
	CUAD_FP2(t10, t10);
	RESTA_FP2(t10, t10, y2);
	CUAD_FP2(z2, T[2]);
	RESTA_FP2(t10, t10, z2);//t10
	SUMA_FP2(t9, t9, t9);
	RESTA_FP2(&l[8], t9, t10);//t9
	MULE_FP2(t10, T[2], P[1]);
	SUMA_FP2(l, t10, t10);//t10
	NEGATIVO_FP2(t7,t6);
	MULE_FP2(t1, t7, P[0]);
	SUMA_FP2(&l[6], t1, t1);//t10
}

void AddTateH(Fp2 *T, Fp *l, Fp2 *Q, Fp2 *R, Fp x, Fp y){
	Fp2 A,B,C,D,E,F,G,H;
	Fp2 te,la,au;
	Mul I[2],T1[2],J[2],Au[2];
	MULT_FP2_DUAL(A, Q[1], R[2], B, Q[0], R[2]);
//	MULT_FP2(B, Q[0], R[2]);
	RESTA_FP2(te, R[1], A);
	RESTA_FP2(la, R[0], B);
	CUAD_FP2(C, te);
	CUAD_FP2(D, la);
	MULT_FP2_DUAL(E, D, la, F, R[2], C);
//	MULT_FP2(F, R[2], C);
	MULT_FP2(G, R[0], D);
	SUMA_FP2(H, E, F);
	RESTA_FP2(H, H, G);
	RESTA_FP2(H, H, G);
	MULT_FP2_DUAL(T[0], la, H, T[2], R[2], E);
	RESTA_FP2(au, G, H);
	//MULT_FP2(T[2], R[2], E);
	MULT_FP2L_DUAL(I,T1, R[1], E, te, au);
	//MULT_FP2L(T1, te, au);
	RESTA_FP2L(T1, I);
	REDU_FP2(T[1], T1);
	MULT_FP2L_DUAL(J,Au, Q[0], te, Q[1], la);
//	MULT_FP2L(Au, Q[1], la);
	RESTA_FP2L(J, Au);
	REDU_FP2(&l[8],J);
	MULE_FP2(&l[0],la,y);
	MULE_FP2(&l[6],te,x);
}


void RPhi(Fp2 *T, PG2 Q){
	Fp f[12],g[12];
	Fp FP[12], GP[12];
	Fpk_init(f,12);
	Fpk_init(g,12);

	Fp2_set(&f[2], Q.xyz[0]);
	Fp2_set(&g[8], Q.xyz[1]);
	Fp2_set(T[2], Q.xyz[2]);

	FROBENIUS_P(FP,f);
	FROBENIUS_P(GP,g);

	Fp2_set(T[0], &FP[2]);
	Fp2_set(T[1], &GP[8]);
}

void RPhi2(Fp2 *T, PG2 Q){
	Fp f[12],g[12];
	Fp FP[12], GP[12];
	Fpk_init(f,12);
	Fpk_init(g,12);

	Fp2_set(&f[2], Q.xyz[0]);
	Fp2_set(&g[8], Q.xyz[1]);
	Fp2_set(T[2], Q.xyz[2]);

	FROBENIUS_P2(FP,f);
	FROBENIUS_P2(GP,g);

	Fp2_set(T[0], &FP[2]);
	Fp2_set(T[1], &GP[8]);
}

void RPhi3(Fp2 *T, PG2 Q){
	Fp f[12],g[12];
	Fp FP[12], GP[12];
	Fpk_init(f,12);
	Fpk_init(g,12);

	Fp2_set(&f[2], Q.xyz[0]);
	Fp2_set(&g[8], Q.xyz[1]);
	Fp2_set(T[2], Q.xyz[2]);

	FROBENIUS_P3(FP,f);
	FROBENIUS_P3(GP,g);

	Fp2_set(T[0], &FP[2]);
	Fp2_set(T[1], &GP[8]);
}

void MultLine(Fp *l, Fp *L, Fp x, Fp y){
	Fpk_set(&l[8], &L[8], 2);
	MULE_FP2(&l[0],L,y);
	MULE_FP2(&l[6],&L[6],x);
}

void LinesPrecompute(Fp12 *l, PG2 Q){
	int i,j;
	PG2 T, Q2, Q1;
	Fp X,Y;
	for(i=0;i<70;i++)
		Fpk_init(l[i],12);
	G2P_cpy(T.xyz,Q.xyz);

	Fp_set(X,um);
	Fp_set(Y,um);

	DobLqqH(T.xyz, l[0], T.xyz, X, Y);
	AddTateH(T.xyz, l[1], Q.xyz, T.xyz, X, Y);
	j=2;
	for(i=TAM_WNAF_SK-3; i>=0; i--){
		DobLqqH(T.xyz, l[j++], T.xyz, X, Y);
		if(WNAF_SK[i]!=0){
			AddTateH(T.xyz, l[j++], Q.xyz, T.xyz, X, Y);
		}
	}
	G2Inv(T.xyz,T.xyz);
	Phi(Q1.xyz, Q);
	Phi2(Q2.xyz, Q);
	G2Inv(Q2.xyz,Q2.xyz);
	AddTateH(T.xyz, l[j++], Q1.xyz, T.xyz, X, Y);
	AddTateH(T.xyz, l[j++], Q2.xyz, T.xyz, X, Y);
}


void PairingJ(Fp *f, PG1 P, PG2 Q){
	int i;
	PG2 T, Q2, Q1;
	Fp2 Z2;
	Fp l[12];
	Fpk_init(f,12);
    Fp_set_str(f[0],"0x212BA4F27FFFFFF5A2C62EFFFFFFFFCDB939FFFFFFFFFF8A15FFFFFFFFFFFF8E");
	G2P_cpy(T.xyz,Q.xyz);
	Fp2_set(Z2, Q.xyz[2]);
	for(i=TAM_WNAF_SK-2; i>=0; i--){
		CUAD_FP12A(f,f);
		DobLqq(T.xyz, P.xyz, T.xyz, l, Z2);
		SMULT_FP12(f,f,l);
		if(WNAF_SK[i]!=0){
			AddTate(T.xyz, l, Q.xyz, T.xyz, P.xyz, Z2);
			SMULT_FP12(f,f,l);
		}
	}
	CONJUGADO_FP12A(f,f);
	G2Inv(T.xyz,T.xyz);
	Phi(Q1.xyz, Q);
	Phi2(Q2.xyz, Q);
	G2Inv(Q2.xyz,Q2.xyz);
	AddTate(T.xyz, l, Q1.xyz, T.xyz, P.xyz, Z2);
	SMULT_FP12(f,f,l);
	AddTate(T.xyz, l, Q2.xyz, T.xyz, P.xyz, Z2);
	SMULT_FP12(f,f,l);
	FINAL_EXPONENTIATION(f,f);
}

void Pairing(Fp *C, PG1 P, PG2 Q){
	int i;
	PG2 T, Q2, Q1;
	Fp X,Y,X3;
	Fp l[12],f[12];
	Fpk_init(f,12);
	G2P_cpy(T.xyz,Q.xyz);

	SUB256MOD(X, p, P.xyz[0]);
	SUB256MOD(Y, p, P.xyz[1]);
	ADD256MOD(X3, P.xyz[0], P.xyz[0]);
	ADD256MOD(X3, X3, P.xyz[0]);

	DobLqqHE(T.xyz, f, T.xyz, X3, Y);
	AddTateH(T.xyz, l, Q.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(f,f,l);

	for(i=TAM_WNAF_SK-3; i>=0; i--){
		CUAD_FP12A(f,f);
		DobLqqH(T.xyz, l, T.xyz, X3, Y);
		SMULT_FP12(f,f,l);
		if(WNAF_SK[i]!=0){
			AddTateH(T.xyz, l, Q.xyz, T.xyz, X, P.xyz[1]);
			SMULT_FP12(f,f,l);
		}
	}
	CONJUGADO_FP12A(f,f);
	G2Inv(T.xyz,T.xyz);
	Phi(Q1.xyz, Q);
	Phi2(Q2.xyz, Q);
	G2Inv(Q2.xyz,Q2.xyz);
	AddTateH(T.xyz, l, Q1.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(f,f,l);
	AddTateH(T.xyz, l, Q2.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(f,f,l);
	FINAL_EXPONENTIATION(C,f);
}

void MillerLoop(Fp *C, PG1 P, PG2 Q){
	int i;
	PG2 T, Q2, Q1;
	Fp X,Y,X3;
	Fp l[12],f[12];
	Fpk_init(f,12);
	G2P_cpy(T.xyz,Q.xyz);

	SUB256MOD(X, p, P.xyz[0]);
	SUB256MOD(Y, p, P.xyz[1]);
	ADD256MOD(X3, P.xyz[0], P.xyz[0]);
	ADD256MOD(X3, X3, P.xyz[0]);

	DobLqqHE(T.xyz, f, T.xyz, X3, Y);
	AddTateH(T.xyz, l, Q.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(f,f,l);

	for(i=TAM_WNAF_SK-3; i>=0; i--){
		CUAD_FP12A(f,f);
		DobLqqH(T.xyz, l, T.xyz, X3, Y);
		SMULT_FP12(f,f,l);
		if(WNAF_SK[i]!=0){
			AddTateH(T.xyz, l, Q.xyz, T.xyz, X, P.xyz[1]);
			SMULT_FP12(f,f,l);
		}
	}
	CONJUGADO_FP12A(f,f);
	G2Inv(T.xyz,T.xyz);
	Phi(Q1.xyz, Q);
	Phi2(Q2.xyz, Q);
	G2Inv(Q2.xyz,Q2.xyz);
	AddTateH(T.xyz, l, Q1.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(f,f,l);
	AddTateH(T.xyz, l, Q2.xyz, T.xyz, X, P.xyz[1]);
	SMULT_FP12(C,f,l);
}

void SPairing(Fp *C, PG1 P, PG2 Q, Fp12 *L){
	int i,k;
	PG2 T, Q2, Q1;
	Fp X,Y,X3;
	Fp l[12],f[12];
	Fpk_init(f,12);
	Fpk_init(l,12);
	G2P_cpy(T.xyz,Q.xyz);

	SUB256MOD(X, p, P.xyz[0]);
	SUB256MOD(Y, p, P.xyz[1]);
	ADD256MOD(X3, P.xyz[0], P.xyz[0]);
	ADD256MOD(X3, X3, P.xyz[0]);


	MultLine(f,L[0], X3, Y);
	MultLine(l,L[1], X, P.xyz[1]);
	SMULT_FP12(f,f,l);

	k=2;

	for(i=TAM_WNAF_SK-3; i>=0; i--){
		CUAD_FP12A(f,f);
		MultLine(l,L[k++], X3, Y);
		SMULT_FP12(f,f,l);
		if(WNAF_SK[i]!=0){
			MultLine(l,L[k++], X, P.xyz[1]);
			SMULT_FP12(f,f,l);
		}
	}
	CONJUGADO_FP12A(f,f);
	MultLine(l,L[k++], X, P.xyz[1]);
	SMULT_FP12(f,f,l);
	MultLine(l,L[k++], X, P.xyz[1]);
	SMULT_FP12(f,f,l);
	FINAL_EXPONENTIATION(C,f);
}


void MultiPairingJ(Fp *f, PG1 *P, PG2 *Q, int N){
	int i, j;
	PG2 T[N], Q2[N], Q1[N];
	Fp2 Z2[N];

	Fp l[12];
	Fpk_init(l,12);
	Fpk_init(f,12);
    Fp_set_str(f[0],"0x212BA4F27FFFFFF5A2C62EFFFFFFFFCDB939FFFFFFFFFF8A15FFFFFFFFFFFF8E");

    for(i=0; i<N; i++){
    	G2P_cpy(T[i].xyz,Q[i].xyz);
    	G2Inv(Q2[i].xyz,Q[i].xyz);
    	Fp2_set(Z2[i], Q[i].xyz[2]);
    }

	for(i=TAM_WNAF_SK-2; i>=0; i--){
		CUAD_FP12A(f,f);

		for(j=0; j<N; j++){
			DobLqq(T[j].xyz, P[j].xyz, T[j].xyz, l, Z2[j]);
			SMULT_FP12(f,f,l);
			if(WNAF_SK[i]<0){
				AddTate(T[j].xyz, l, Q2[j].xyz, T[j].xyz, P[j].xyz, Z2[j]);
				SMULT_FP12(f,f,l);
			}
			else if(WNAF_SK[i]>0){
				AddTate(T[j].xyz, l, Q[j].xyz, T[j].xyz, P[j].xyz, Z2[j]);
				SMULT_FP12(f,f,l);
			}
		}
	}

	for(i=0; i<N; i++){
		Phi(Q1[i].xyz, Q[i]);
		Phi2(Q2[i].xyz, Q[i]);
		G2Inv(Q2[i].xyz,Q2[i].xyz);
		AddTate(T[i].xyz, l, Q1[i].xyz, T[i].xyz, P[i].xyz, Z2[i]);
		SMULT_FP12(f,f,l);
		AddTate(T[i].xyz, l, Q2[i].xyz, T[i].xyz, P[i].xyz, Z2[i]);
		SMULT_FP12(f,f,l);
	}

	FINAL_EXPONENTIATION(f,f);
}

void MultiPairing(Fp *C, PG1 *P, PG2 *Q, int N){
	int i,j;
	PG2 T[N], Q2[N], Q1[N];
	Fp X[N],Y[N],X3[N];
	Fp l[12],f[12];
	Fpk_init(f,12);
	Fp_set(f[0],um);

	for(i=0; i<N; i++){
		G2P_cpy(T[i].xyz,Q[i].xyz);
		Phi(Q1[i].xyz, Q[i]);
		Phi2(Q2[i].xyz, Q[i]);
		G2Inv(Q2[i].xyz,Q2[i].xyz);
		SUB256MOD(X[i], p, P[i].xyz[0]);
		SUB256MOD(Y[i], p, P[i].xyz[1]);
		ADD256MOD(X3[i], P[i].xyz[0], P[i].xyz[0]);
		ADD256MOD(X3[i], X3[i], P[i].xyz[0]);
	}


	for(i=TAM_WNAF_SK-2; i>=0; i--){
		CUAD_FP12A(f,f);
		for(j=0; j<N; j++){
			DobLqqH(T[j].xyz, l, T[j].xyz, X3[j], Y[j]);
			SMULT_FP12(f,f,l);
			if(WNAF_SK[i]!=0){
				AddTateH(T[j].xyz, l, Q[j].xyz, T[j].xyz, X[j], P[j].xyz[1]);
				SMULT_FP12(f,f,l);
			}
		}
	}
	CONJUGADO_FP12A(f,f);
	for(i=0; i<N; i++){
		G2Inv(T[i].xyz,T[i].xyz);
		AddTateH(T[i].xyz, l, Q1[i].xyz, T[i].xyz, X[i], P[i].xyz[1]);
		SMULT_FP12(f,f,l);
		AddTateH(T[i].xyz, l, Q2[i].xyz, T[i].xyz, X[i], P[i].xyz[1]);
		SMULT_FP12(f,f,l);
	}
	FINAL_EXPONENTIATION(C,f);
}

void SMultiPairing(Fp *C, PG1 *P, PG2 *Q, Fp12 *LL, PG1 CT, PG2 L, int N){
	int i,j,k;
	PG2 T[N], Q2[N], Q1[N];
	Fp X[N+1],Y[N+1],X3[N+1];
	Fp l[12],f[12];
	Fpk_init(f,12);
	Fpk_init(l,12);
	Fp_set(f[0],um);

	for(i=0; i<N; i++){
		G2P_cpy(T[i].xyz,Q[i].xyz);
		Phi(Q1[i].xyz, Q[i]);
		Phi2(Q2[i].xyz, Q[i]);
		G2Inv(Q2[i].xyz,Q2[i].xyz);
		SUB256MOD(X[i], p, P[i].xyz[0]);
		SUB256MOD(Y[i], p, P[i].xyz[1]);
		ADD256MOD(X3[i], P[i].xyz[0], P[i].xyz[0]);
		ADD256MOD(X3[i], X3[i], P[i].xyz[0]);
	}
	SUB256MOD(X[i], p, CT.xyz[0]);
	SUB256MOD(Y[i], p, CT.xyz[1]);
	ADD256MOD(X3[i], CT.xyz[0], CT.xyz[0]);
	ADD256MOD(X3[i], X3[i], CT.xyz[0]);

	k=0;
	for(i=TAM_WNAF_SK-2; i>=0; i--){
		CUAD_FP12A(f,f);
		for(j=0; j<N; j++){
			DobLqqH(T[j].xyz, l, T[j].xyz, X3[j], Y[j]);
			SMULT_FP12(f,f,l);
			if(WNAF_SK[i]!=0){
				AddTateH(T[j].xyz, l, Q[j].xyz, T[j].xyz, X[j], P[j].xyz[1]);
				SMULT_FP12(f,f,l);
			}
		}

		MultLine(l, LL[k++], X3[j], Y[j]);
		SMULT_FP12(f,f,l);
		if(WNAF_SK[i]!=0){
			MultLine(l, LL[k++], X[j], CT.xyz[1]);
			SMULT_FP12(f,f,l);
		}
	}
	CONJUGADO_FP12A(f,f);
	for(i=0; i<N; i++){
		G2Inv(T[i].xyz,T[i].xyz);
		AddTateH(T[i].xyz, l, Q1[i].xyz, T[i].xyz, X[i], P[i].xyz[1]);
		SMULT_FP12(f,f,l);
		AddTateH(T[i].xyz, l, Q2[i].xyz, T[i].xyz, X[i], P[i].xyz[1]);
		SMULT_FP12(f,f,l);
	}
	MultLine(l, LL[k++],  X[i], CT.xyz[1]);
	SMULT_FP12(f,f,l);
	MultLine(l, LL[k++],  X[i], CT.xyz[1]);
	SMULT_FP12(f,f,l);

	FINAL_EXPONENTIATION(C,f);
}



void ExpoPrecompute(Fp12 *P1, Fp *P, int N){
	int i;
	Fp12 P2;
	Fpk_set(P1[1], P,12);
	CONJUGADO_FP12(P1[0], P);
	CUAD_FP12(P2, P);
	for(i=3; i<=N; i+=2){
		MULT_FP12(P1[i], P2, P1[i-2]);
		CONJUGADO_FP12(P1[i-1], P1[i]);
	}

}

void EXPONENCIACION64(Fp *C, Fp *A, Fp K){
	int i,n;
	int8_t k1[256];
	Fp12 Q;
	Fp12 P1[8];
	n=wnaf(k1,K,8);
	ExpoPrecompute(P1, A, 8);
	Fpk_set(Q,P1[k1[n-1]],12);
	for(i=n-2; i>=0; i--){
		CUAD_FP12(Q,Q);
		if(k1[i]!=0){
			if(k1[i]>0) MULT_FP12(Q,Q,P1[k1[i]]);
			else MULT_FP12(Q,Q,P1[-(k1[i]+1)]);
		}
	}
	Fpk_set(C,Q,12);
}

void EXPONENCIACION_GS(Fp *C, Fp *A, Fp K){
	int i,n1,n2,n3,n4,n;
	int8_t s[2];
	int8_t k1[70],k2[70],k3[70],k4[70];
	Fp Kd[4];
	Fp12 C1, C2, C3, C4, M, Q;
	Fp12 P1[8], P2[8], P3[8], P4[8];

	for(i=0; i<70; i++){
		k1[i]=0;
		k2[i]=0;
		k3[i]=0;
		k4[i]=0;
	}
	GSDecomposition(Kd,K,s);

	n1=wnaf(k1,Kd[0],8);
	n2=wnaf(k2,Kd[1],8);
	n3=wnaf(k3,Kd[2],8);
	n4=wnaf(k4,Kd[3],8);

	Fpk_set(C1,A,12);
	FROBENIUS_P(C2,A);
	FROBENIUS_P2(C3,A);
	FROBENIUS_P3(C4,A);

	if(s[0]<0){ CONJUGADO_FP12(M, C1); Fpk_set(C1,M,12);}
	if(s[1]>0){ CONJUGADO_FP12(M, C2); Fpk_set(C2,M,12);}
	if(s[2]>0){ CONJUGADO_FP12(M, C3); Fpk_set(C3,M,12);}
	if(s[3]>0){ CONJUGADO_FP12(M, C4); Fpk_set(C4,M,12);}

	ExpoPrecompute(P1, C1, 7);
	ExpoPrecompute(P2, C2, 7);
	ExpoPrecompute(P3, C3, 7);
	ExpoPrecompute(P4, C4, 7);

	n=n1;
	Fpk_set(Q,P1[k1[n-1]],12);
	if(n2>n){ n=n2; Fpk_set(Q,P2[k2[n-1]], 12); }
	if(n3>n){ n=n3; Fpk_set(Q,P3[k3[n-1]], 12); }
	if(n4>n){ n=n4; Fpk_set(Q,P4[k4[n-1]], 12); }
	if(n1==n){
		if(n2 == n) MULT_FP12(Q,Q,P2[k2[n-1]]);
		if(n3 == n) MULT_FP12(Q,Q,P3[k3[n-1]]);
		if(n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]]);
	}else if(n2==n){
		if(n3 == n) MULT_FP12(Q,Q,P3[k3[n-1]]);
		if(n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]]);
	}else{
		if(n3 == n && n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]]);
	}
	for(i=n-2; i>=0; i--){
		CUAD_FP12(Q,Q);
		if(k1[i]!=0){
			if(k1[i]>0) MULT_FP12(Q,Q,P1[k1[i]]);
			else MULT_FP12(Q,Q,P1[-(k1[i]+1)]);
		}
		if(k2[i]!=0){
			if(k2[i]>0) MULT_FP12(Q,Q,P2[k2[i]]);
			else MULT_FP12(Q,Q,P2[-(k2[i]+1)]);
		}
		if( k3[i]!=0){
			if(k3[i]>0) MULT_FP12(Q,Q,P3[k3[i]]);
			else MULT_FP12(Q,Q,P3[-(k3[i]+1)]);
		}
		if(k4[i]!=0){
			if(k4[i]>0) MULT_FP12(Q,Q,P4[k4[i]]);
			else MULT_FP12(Q,Q,P4[-(k4[i]+1)]);
		}
	}

	Fpk_set(C,Q,12);
}


void EXPONENCIACION_GSKNOWN(Fp *C, Fp K, Fp12 *P1, Fp12 *P2, Fp12 *P3, Fp12 *P4, int Naf){
	int i,n1,n2,n3,n4,n;
	int8_t s[2];
	int8_t k1[70],k2[70],k3[70],k4[70];
	Fp Kd[4];
	Fp12 Q;
	int m[]={0,0,0,0};
	int o[]={1,1,1,1};

	for(i=0; i<70; i++){
		k1[i]=0;
		k2[i]=0;
		k3[i]=0;
		k4[i]=0;
	}
	GSDecomposition(Kd,K,s);

	n1=wnaf(k1,Kd[0],Naf);
	n2=wnaf(k2,Kd[1],Naf);
	n3=wnaf(k3,Kd[2],Naf);
	n4=wnaf(k4,Kd[3],Naf);

	if(s[0]<0){ m[0]=1; o[0]=0; }
	if(s[1]>0){ m[1]=1; o[1]=0; }
	if(s[2]>0){ m[2]=1; o[2]=0; }
	if(s[3]>0){ m[3]=1; o[3]=0; }

	n=n1;
	Fpk_set(Q,P1[k1[n-1]-m[0]],12);
	if(n2>n){ n=n2; Fpk_set(Q,P2[k2[n-1]-m[1]], 12); }
	if(n3>n){ n=n3; Fpk_set(Q,P3[k3[n-1]-m[2]], 12); }
	if(n4>n){ n=n4; Fpk_set(Q,P4[k4[n-1]-m[3]], 12); }
	if(n1==n){
		if(n2 == n) MULT_FP12(Q,Q,P2[k2[n-1]-m[1]]);
		if(n3 == n) MULT_FP12(Q,Q,P3[k3[n-1]-m[2]]);
		if(n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]-m[3]]);
	}else if(n2==n){
		if(n3 == n) MULT_FP12(Q,Q,P3[k3[n-1]-m[2]]);
		if(n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]-m[3]]);
	}
	else{
		if(n3 == n && n4 == n) MULT_FP12(Q,Q,P4[k4[n-1]-m[3]]);
	}

	for(i=n-2; i>=0; i--){
		CUAD_FP12(Q,Q);
		if(k1[i]!=0){
			if(k1[i]>0) MULT_FP12(Q,Q,P1[k1[i]-m[0]]);
			else MULT_FP12(Q,Q,P1[abs(k1[i])-o[0]]);
		}
		if(k2[i]!=0){
			if(k2[i]>0) MULT_FP12(Q,Q,P2[k2[i]-m[1]]);
			else MULT_FP12(Q,Q,P2[abs(k2[i])-o[1]]);
		}
		if( k3[i]!=0){
			if(k3[i]>0) MULT_FP12(Q,Q,P3[k3[i]-m[2]]);
			else MULT_FP12(Q,Q,P3[abs(k3[i])-o[2]]);
		}
		if(k4[i]!=0){
			if(k4[i]>0) MULT_FP12(Q,Q,P4[k4[i]-m[3]]);
			else MULT_FP12(Q,Q,P4[abs(k4[i])-o[3]]);
		}
	}

	Fpk_set(C,Q,12);
}


void Vecget8P(Fp12 *K, Fp *P){
	int i;
	Fp12 Q;
	Fpk_set(K[0], P, 12);
	Fpk_set(Q, P, 12);
	for(i=1; i<=224; i++){
		CUAD_FP12(Q,Q);
		if(i%32==0){
			Fpk_set(K[i/32], Q, 12);
		}
	}
}

void FillVector(Fp *P, Fp12 *P8, uint8_t *val){
	int i,j;
	Fp12 A;
	for(i=0; i<8; i++){
		if(val[i]!=0){
			Fpk_set(A,P8[i],12);
			i++;
			break;
		}
	}
	for(i; i<8; i++){
		if(val[i]!=0)
			MULT_FP12(A, A, P8[i]);
	}
	Fpk_set(P,A,12);
}

void ExpoCombPrecompute(Fp12 *Pi, Fp *P){
	int i;
	Fp12 K[8];
	uint8_t valor[8];

	Vecget8P(K, P);
	for(i=1; i<256; i++){
		valor[0]=i&1;
		valor[1]=(i>>1)&1;
		valor[2]=(i>>2)&1;
		valor[3]=(i>>3)&1;
		valor[4]=(i>>4)&1;
		valor[5]=(i>>5)&1;
		valor[6]=(i>>6)&1;
		valor[7]=(i>>7)&1;
		FillVector(Pi[i], K, valor);
	}

}

void EXPONENCIACION_COMB(Fp *C, Fp12 *P, Fp K){
	uint8_t k[40];
	int i;
	int n=0;
	n=TransposeInt(k,K);
	Fp12 Q;
	Fpk_set(Q,P[k[n]], 12);
	for(i=n-1; i>=0; i--){
		CUAD_FP12(Q,Q);
		if(k[i]!=0){
			MULT_FP12(Q,Q,P[k[i]]);
		}
	}
	Fpk_set(C,Q, 12);
}
