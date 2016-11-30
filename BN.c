/*
BN.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "arithFpk.h"
#include "Domain.h"


//********************************************************//
//********************        ********  ******************//
//********************  ************    ******************//
//********************  **    ********  ******************//
//********************  ****  ********  ******************//
//********************        ******      ****************//
//********************************************************//


void G1P_print(PG1 P, char *t){
	Fpk_print(t, P.xyz, 3);
}

void G1P_set(Fp *C, char *X, char *Y){
	Fp_set_str(C[0], X);
	Fp_set_str(C[1], Y);
	Fp_setD(C[2],0,0,0,0,0,0,0,1);
}

void G1P_cpy(Fp *C, Fp *A){
	Fp_set(C[0],A[0]);
	Fp_set(C[1],A[1]);
	Fp_set(C[2],A[2]);
}

void G1Inv(Fp *C, Fp *A){
	Fp aux;
	Fp_set(aux,A[1]);
	SUB256MOD(C[1],p,aux);
	Fp_set(C[0],A[0]);
	Fp_set(C[2],A[2]);
}

void G1AddAff(Fp *C, Fp *A, Fp *B){
	Fp t1, t2, t3;
	SUB256MOD(t1,B[0],A[0]);
	MontInverse(t1,t1);
	SUB256MOD(t2,B[1],A[1]);
	MULMONG(t2, t2, t1);
	MULMONG(t3, t2, t2);
	SUB256MOD(t3,t3, B[0]);
	SUB256MOD(t3,t3, A[0]);
	SUB256MOD(t1, A[0],t3);
	MULMONG(t1, t1, t2);
	SUB256MOD(t1, t1,A[1]);
	Fp_set(C[0],t3);
	Fp_set(C[1],t1);
	Fp_set(C[2],A[2]);
}


void G1DobAff(Fp *C, Fp *A){
	Fp t1, t2, t3;
	MULMONG(t1,A[0], A[0]);
	ADD256MOD(t2,t1,t1);
	ADD256MOD(t2,t2,t1);
	ADD256MOD(t1,A[1],A[1]);
	MontInverse(t1,t1);
	MULMONG(t2,t2, t1);
	MULMONG(t3, t2, t2);
	SUB256MOD(t3,t3, A[0]);
	SUB256MOD(t3,t3, A[0]);
	SUB256MOD(t1, A[0],t3);
	MULMONG(t1, t1, t2);
	SUB256MOD(t1, t1,A[1]);
	Fp_set(C[0],t3);
	Fp_set(C[1],t1);
	Fp_set(C[2],A[2]);
}


#ifdef HAVE_NEON
void G1DoubJ(Fp *C, Fp *A){
	Fp t0,t1,t2,t3,t4;
	Fp_init(t4);
	MULMONGNEON(C[2],t1, A[1], A[2],A[0], A[0]);
	ADD256MOD(C[2],C[2],C[2]);//z3
//	MULE(t4, t1, 3); //t4
	ADD256MOD(t4, t1, t1);
	ADD256MOD(t4, t4, t1);//t4

	MULMONGNEON(t1,t0, A[1], A[1], t4, t4);
	ADD256MOD(t1,t1,t1);//t1

	MULMONGNEON(t2, t3, A[0], t1, t1, t1);
	ADD256MOD(t2,t2,t2);//t2
	ADD256MOD(t3,t3,t3);//t3

	SUB256MOD(C[0],t0,t2);
	SUB256MOD(C[0],C[0],t2);//x3
	SUB256MOD(t2,t2,C[0]);
	MULMONG(C[1], t4, t2);
	SUB256MOD(C[1],C[1],t3);//y3
}

void G1AddMix(Fp *C, Fp *A, Fp *B){
	Fp t1,t2,t3,t4,t5,t6,t7,t8,t9;
	MULMONG(t1,A[2], A[2]);

	MULMONGNEON(t2, t3, t1, A[2], t1, B[0]);
	SUB256MOD(t5,t3,A[0]);
	MULMONGNEON(t4,t7, B[1], t2, t5, t5);
	SUB256MOD(t6,t4,A[1]);

	MULMONGNEON(t8, t9, t7, t5, A[0], t7);

	MULMONGNEON(C[0], C[2], t6, t6, A[2], t5);
	SUB256MOD(C[0],C[0],t8);
	SUB256MOD(C[0],C[0],t9);
	SUB256MOD(C[0],C[0],t9);
	SUB256MOD(t9,t9,C[0]);

	MULMONGNEON(t8, C[1], t8, A[1], t9, t6);
	SUB256MOD(C[1],C[1],t8);

}

void G1J2A(Fp *C, Fp *A){
	Fp t1,t2,t3;
	if(zero(A[2])==0){
		Fp_set(C[0], A[0]);
		Fp_set(C[1], A[1]);
		Fp_set(C[2], A[2]);
		return;
	}
	MULMONG(t1,A[2], A[2]);
	MULMONGNEON(t2, C[1], t1, A[2], A[1], t1);
	MULMONGNEON(t3, C[0], t1, t2, A[0], t2);
	MontInverse(t3, t3);
	MULMONGNEON(C[0], C[1], C[0], t3, C[1], t3);
	Fp_set(C[2], um);
}


void G1Decomposition(Fp *D, Fp A, int8_t *S){
	int i;
	uint32_t b1[]={0,0,0,0,0,0,0,0,0};
	uint32_t b2[]={0,0,0,0,0,0,0,0,0};
	uint32_t res1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	MUL256NEON(res1, res2, G1_BInv[0],A, G1_BInv[1],A);
	b1[0]=res1[11];
	for(i=12; i<16; i++){
		b1[i-11]=res1[i];
		b2[i-12]=res2[i];
	}
	MUL256NEON(A1,A2,G1_BNor[0][0],b1,G1_BNor[0][1],b2);
	MUL256NEON(B1,B2,G1_BNor[1][0],b1,G1_BNor[1][1],b2);


	ADD256(A1,A1,A2);
	SUB256(D[0], A, A1);

	if(comparativo(B1, B2, 8)>-1){
		SUB256(D[1], B1, B2);
		S[1]=-1;
	}
	else{
		SUB256(D[1], B2, B1);
		S[1]=1;
	}

}

void G1Multinormalizacion(PG1 *P,int N, int flag){
	int i;
	Fp Ori[N],Inv[N], aux;
	for(i=0; i<N; i++){
		Fp_set(Ori[i], P[i].xyz[2]);
	}
	MultiInverse(Inv, Ori, N);
	for(i=0; i<N; i++){
		MULMONGNEON(aux, P[i].xyz[1], Inv[i], Inv[i],P[i].xyz[1], Inv[i]);
		MULMONGNEON(P[i].xyz[0], P[i].xyz[1], P[i].xyz[0], aux,P[i].xyz[1], aux);
		Fp_set(P[i].xyz[2], um);
	}
	if(flag==1){
		for(i=0; i<N; i++){
			 setDomFp(P[i].xyz, P[i].xyz,3);
		}
	}
}
#else
void G1DoubJ(Fp *C, Fp *A){
	Fp t1,t2,t3,t4;
	Fp_init(t4);
	MULMONG(C[2],A[1], A[2]);
	ADD256MOD(C[2],C[2],C[2]);//z3
	MULMONG(t1, A[0], A[0]);

	//	MULE(t4, t1, 3); //t4
	ADD256MOD(t4, t1, t1);
	ADD256MOD(t4, t4, t1);//t4

	MULMONG(t1, A[1], A[1]);
	ADD256MOD(t1,t1,t1);//t1
	MULMONG(t2, A[0], t1);
	ADD256MOD(t2,t2,t2);//t2
	MULMONG(t3, t1, t1);
	ADD256MOD(t3,t3,t3);//t3
	MULMONG(C[0], t4, t4);
	SUB256MOD(C[0],C[0],t2);
	SUB256MOD(C[0],C[0],t2);//x3
	SUB256MOD(t2,t2,C[0]);
	MULMONG(C[1], t4, t2);
	SUB256MOD(C[1],C[1],t3);//y3
}

void G1AddMix(Fp *C, Fp *A, Fp *B){
	Fp t1,t2,t3,t4,t5,t6,t7,t8,t9;
	MULMONG(t1,A[2], A[2]);
	MULMONG(t2,t1, A[2]);
	MULMONG(t3,t1, B[0]);
	MULMONG(t4,B[1], t2);
	SUB256MOD(t5,t3,A[0]);
	SUB256MOD(t6,t4,A[1]);
	MULMONG(t7,t5,t5);
	MULMONG(t8,t7,t5);
	MULMONG(t9,A[0],t7);
	MULMONG(C[0],t6,t6);
	SUB256MOD(C[0],C[0],t8);
	SUB256MOD(C[0],C[0],t9);
	SUB256MOD(C[0],C[0],t9);
	SUB256MOD(t9,t9,C[0]);
	MULMONG(t8,t8,A[1]);
	MULMONG(C[1],t9,t6);
	SUB256MOD(C[1],C[1],t8);
	MULMONG(C[2],A[2],t5);
}

void G1J2A(Fp *C, Fp *A){
	Fp t1,t2,t3;
	if(zero(A[2])==0){
		Fp_set(C[0], A[0]);
		Fp_set(C[1], A[1]);
		Fp_set(C[2], A[2]);
		return;
	}
	MULMONG(t1,A[2], A[2]);
	MULMONG(t2,t1, A[2]);
	MULMONG(t3,t1, t2);
	MontInverse(t3, t3);
	MULMONG(C[0],A[0], t2);
	MULMONG(C[0],C[0], t3);
	MULMONG(C[1],A[1], t1);
	MULMONG(C[1],C[1], t3);
	Fp_set(C[2], um);
}


void G1Decomposition(Fp *D, Fp A, int8_t *S){//Pasar a NEON
	int i;
	uint32_t b1[]={0,0,0,0,0,0,0,0,0};
	uint32_t b2[]={0,0,0,0,0,0,0,0,0};
	uint32_t res1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	MUL256(res1,G1_BInv[0],A);
	MUL256(res2,G1_BInv[1],A);
	b1[0]=res1[11];
	for(i=12; i<16; i++){
		b1[i-11]=res1[i];
		b2[i-12]=res2[i];
	}
	MUL256N(A1,G1_BNor[0][0],b1,4);
	MUL256N(A2,G1_BNor[0][1],b2,2);
	MUL256N(B1,G1_BNor[1][0],b1,2);
	MUL256N(B2,G1_BNor[1][1],b2,4);
	ADD256(A1,A1,A2);
	SUB256(D[0], A, A1);


	if(comparativo(B1, B2, 8)>-1){
		SUB256(D[1], B1, B2);
		S[1]=-1;
	}
	else{
		SUB256(D[1], B2, B1);
		S[1]=1;
	}

}

void G1Multinormalizacion(PG1 *P,int N, int flag){
	int i;
	Fp Ori[N],Inv[N], aux;
	for(i=0; i<N; i++){
		Fp_set(Ori[i], P[i].xyz[2]);
	}
	MultiInverse(Inv, Ori, N);
	for(i=0; i<N; i++){
		MULMONG(aux, Inv[i], Inv[i]);
		MULMONG(P[i].xyz[0], P[i].xyz[0], aux);
		MULMONG(P[i].xyz[1], P[i].xyz[1], aux);
		MULMONG(P[i].xyz[1], P[i].xyz[1], Inv[i]);
		Fp_set(P[i].xyz[2], um);
	}
	if(flag==1){
		for(i=0; i<N; i++){
			 setDomFp(P[i].xyz, P[i].xyz,3);
		}
	}
}
#endif

void G1normalize(Fp *C, int flag){
	if(flag==1) G1J2A(C,C);
    setDomFp(C, C,2);
    Fp_set_str(C[2], "0x0000000000000000000000000000000000000000000000000000000000000001");
}

void G1Precompute(PG1 *Pi, PG1 P, int n){
	int i;
	PG1 P2;
	G1P_cpy(Pi[1].xyz,P.xyz);
	G1Inv(Pi[0].xyz,P.xyz);
	G1DoubJ(P2.xyz, P.xyz);
	for(i=3; i<=n; i+=2){
		G1AddMix(Pi[i].xyz, P2.xyz, Pi[i-2].xyz);
		G1J2A(Pi[i].xyz,Pi[i].xyz);
		G1Inv(Pi[i-1].xyz,Pi[i].xyz);
	}
}

void G1GLVPrecompute(PG1 *P1, PG1 *H1, PG1 P, PG1 H){
	PG1 P2, H2;
	Fp Inv[2], Ori[2], aux;
	G1P_cpy(P1[1].xyz,P.xyz);
	G1Inv(P1[0].xyz,P.xyz);
	G1P_cpy(H1[1].xyz,H.xyz);
	G1Inv(H1[0].xyz,H.xyz);
	G1DoubJ(P2.xyz, P.xyz);
	G1DoubJ(H2.xyz, H.xyz);
	G1AddMix(P2.xyz, P2.xyz, P.xyz);
	G1AddMix(H2.xyz, H2.xyz, H.xyz);

	Fp_set(Ori[0], P2.xyz[2]);
	Fp_set(Ori[1], H2.xyz[2]);

	MultiInverse(Inv, Ori, 2);

#ifdef HAVE_NEON
	MULMONGNEON(aux, P1[3].xyz[1], Inv[0], Inv[0], P2.xyz[1], Inv[0]);
	MULMONGNEON(P1[3].xyz[0],P1[3].xyz[1], P2.xyz[0], aux, P1[3].xyz[1], aux);

	MULMONGNEON(aux, H1[3].xyz[1], Inv[1], Inv[1], H2.xyz[1], Inv[1]);
	MULMONGNEON(H1[3].xyz[0],H1[3].xyz[1], H2.xyz[0], aux, H1[3].xyz[1], aux);
#else
	MULMONG(aux, Inv[0], Inv[0]);
	MULMONG(P1[3].xyz[0], P2.xyz[0], aux);
	MULMONG(P1[3].xyz[1], P2.xyz[1], aux);
	MULMONG(P1[3].xyz[1], P1[3].xyz[1], Inv[0]);

	MULMONG(aux, Inv[1], Inv[1]);
	MULMONG(H1[3].xyz[0], H2.xyz[0], aux);
	MULMONG(H1[3].xyz[1], H2.xyz[1], aux);
	MULMONG(H1[3].xyz[1], H1[3].xyz[1], Inv[1]);
#endif
	Fp_set(P1[3].xyz[2], P.xyz[2]);
	Fp_set(H1[3].xyz[2], H.xyz[2]);

	G1Inv(P1[2].xyz,P1[3].xyz);
	G1Inv(H1[2].xyz,H1[3].xyz);

}

//Metodo Normal
void G1scalarMult(Fp *kP, PG1 P, Fp K){
	int i,n;
	int8_t ki[260];
	int8_t aux;
	n=wnaf(ki,K,4);
	PG1 Pi[8],  Q;
	G1Precompute(Pi,P,3);

	G1P_cpy(Q.xyz,Pi[ki[n-1]].xyz);
	for(i=n-2; i>=0; i--){
		G1DoubJ(Q.xyz,Q.xyz);
		if(ki[i]!=0){
			if(ki[i]>0){
				G1AddMix(Q.xyz,Q.xyz,Pi[ki[i]].xyz);
			}
			else{
				G1AddMix(Q.xyz,Q.xyz,Pi[-(ki[i]+1)].xyz);
			}
		}
	}
	G1P_cpy(kP,Q.xyz);
}

void G1GLVMult(Fp *kP, PG1 P, Fp K){
	int i,n1,n2;
	int8_t s[2];
	int8_t k1[130],k2[130];
	Fp Kd[2];
	PG1 P1[4],P2[4];
	PG1 H;
	PG1 Q, Q2;

	G1P_cpy(H.xyz,P.xyz);
	MULMONG(H.xyz[0], P.xyz[0], BN_Beta);

	G1Decomposition(Kd,K,s);
	if(s[1]<0) G1Inv(H.xyz, H.xyz);

	n1=wnaf(k1,Kd[0],4);
	n2=wnaf(k2,Kd[1],4);

	G1GLVPrecompute(P1,P2, P, H);

	G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);
	G1P_cpy(Q2.xyz,P2[k2[n2-1]].xyz);

	if(n1>=n2){
		G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);
		for(i=n1-2; i>=n2-1; i--){
			G1DoubJ(Q.xyz,Q.xyz);
			if(k1[i]!=0){
				if(k1[i]>0){
					G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
				}
			}
		}
		G1AddMix(Q.xyz,Q.xyz,P2[k2[n2-1]].xyz);
	}
	else{
		G1P_cpy(Q.xyz,P2[k2[n2-1]].xyz);
		for(i=n2-2; i>=n1-1; i--){
			G1DoubJ(Q.xyz,Q.xyz);
			if(k2[i]!=0){
				if(k2[i]>0){
					G1AddMix(Q.xyz,Q.xyz,P2[k2[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P2[-(k2[i]+1)].xyz);
				}
			}
		}
		G1AddMix(Q.xyz,Q.xyz,P1[k1[n1-1]].xyz);

	}

	for(i; i>=0; i--){
		G1DoubJ(Q.xyz,Q.xyz);
		if(k1[i]!=0){
			if(k1[i]>0){
				G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
			}
			else{
				G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
			}
		}
		if(k2[i]!=0){
			if(k2[i]>0){
				G1AddMix(Q.xyz,Q.xyz,P2[k2[i]].xyz);
			}
			else{
				G1AddMix(Q.xyz,Q.xyz,P2[-(k2[i]+1)].xyz);
			}
		}
	}
	G1P_cpy(kP,Q.xyz);
}


void G1GLVMultKnown(Fp *kP, Fp K, PG1 *P1, PG1 *P2, int Naf){ //Precomputo
	int i,n1,n2;
	int8_t s[2];
	int8_t k1[130],k2[130];
	Fp Kd[2];
	PG1 Q;

	G1Decomposition(Kd,K,s);

	n1=wnaf(k1,Kd[0],Naf);
	n2=wnaf(k2,Kd[1],Naf);


	if(s[1]>-1){

		G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);

		if(n1>=n2){
			G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);
			for(i=n1-2; i>=n2-1; i--){
				G1DoubJ(Q.xyz,Q.xyz);
				if(k1[i]!=0){
					if(k1[i]>0){
						G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
					}
					else{
						G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
					}
				}
			}
			G1AddMix(Q.xyz,Q.xyz,P2[k2[n2-1]].xyz);
		}
		else{
			G1P_cpy(Q.xyz,P2[k2[n2-1]].xyz);
			for(i=n2-2; i>=n1-1; i--){
				G1DoubJ(Q.xyz,Q.xyz);
				if(k2[i]!=0){
					if(k2[i]>0){
						G1AddMix(Q.xyz,Q.xyz,P2[k2[i]].xyz);
					}
					else{
						G1AddMix(Q.xyz,Q.xyz,P2[-(k2[i]+1)].xyz);
					}
				}
			}
			G1AddMix(Q.xyz,Q.xyz,P1[k1[n1-1]].xyz);
		}
		for(i; i>=0; i--){
			G1DoubJ(Q.xyz,Q.xyz);
			if(k1[i]!=0){
				if(k1[i]>0){
					G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
				}
			}
			if(k2[i]!=0){
				if(k2[i]>0){
					G1AddMix(Q.xyz,Q.xyz,P2[k2[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P2[-(k2[i]+1)].xyz);
				}
			}
		}
	}
	else{

//////////////////////SI S NEGATIVO ///////////////////////////
		G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);

		if(n1>=n2){
			G1P_cpy(Q.xyz,P1[k1[n1-1]].xyz);
			for(i=n1-2; i>=n2-1; i--){
				G1DoubJ(Q.xyz,Q.xyz);
				if(k1[i]!=0){
					if(k1[i]>0){
						G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
					}
					else{
						G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
					}
				}
			}
			G1AddMix(Q.xyz,Q.xyz,P2[k2[n2-1]-1].xyz);
		}
		else{
			G1P_cpy(Q.xyz,P2[k2[n2-1]-1].xyz);
			for(i=n2-2; i>=n1-1; i--){
				G1DoubJ(Q.xyz,Q.xyz);
				if(k2[i]!=0){
					if(k2[i]<0){
						G1AddMix(Q.xyz,Q.xyz,P2[-k2[i]].xyz);
					}
					else{
						G1AddMix(Q.xyz,Q.xyz,P2[k2[i]-1].xyz);
					}
				}
			}
			G1AddMix(Q.xyz,Q.xyz,P1[k1[n1-1]].xyz);
		}

		for(i; i>=0; i--){
			G1DoubJ(Q.xyz,Q.xyz);
			if(k1[i]!=0){
				if(k1[i]>0){
					G1AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
				}
			}
			if(k2[i]!=0){
				if(k2[i]<0){
					G1AddMix(Q.xyz,Q.xyz,P2[-k2[i]].xyz);
				}
				else{
					G1AddMix(Q.xyz,Q.xyz,P2[k2[i]-1].xyz);
				}
			}
		}


	}


	G1P_cpy(kP,Q.xyz);
}

void G1MapToPoint(Fp *P, Fp X){
	int n;
	Fp X1, X2, X3, C5;
	Fp_set_str(C5,"0x1D33E562BFFFFFE98B58107FFFFFFF931152FFFFFFFFFF0084FFFFFFFFFFFF09");
	Fp_set(P[2], um);
	do{
		Fp_set(P[0], X);
		MULMONG(X2, X, X);
		MULMONG(X3, X2, X);
		ADD256MOD(X3, X3, C5);
		n=SQRROOT(P[1],X3);
		ADD256MOD(X, X, um);
	}while(n==-1);

}

void G1get8P(PG1 *K, PG1 P){
	int i;
	PG1 Q;
	G1P_cpy(K[0].xyz,P.xyz);
	G1P_cpy(Q.xyz,P.xyz);
	for(i=1; i<=224; i++){
		G1DoubJ(Q.xyz,Q.xyz);
		if(i%32==0){
			G1J2A(K[i/32].xyz,Q.xyz);
		}
	}
}

void G1FillPoint(Fp *P, PG1 *P8, uint8_t *val){
	int i,j;
	PG1 A;
	for(i=0; i<8; i++){
		if(val[i]!=0){
			G1P_cpy(A.xyz,P8[i].xyz);
			i++;
			break;
		}
	}
	for(i; i<8; i++){
		if(val[i]!=0)
			G1AddMix(A.xyz, A.xyz, P8[i].xyz);
	}
	G1J2A(P,A.xyz);
}

void G1CombPrecompute(PG1 *Pi, PG1 P){
	int i;
	PG1 K[8];
	uint8_t valor[8];

	G1get8P(K, P);
	for(i=1; i<256; i++){
		valor[0]=i&1;
		valor[1]=(i>>1)&1;
		valor[2]=(i>>2)&1;
		valor[3]=(i>>3)&1;
		valor[4]=(i>>4)&1;
		valor[5]=(i>>5)&1;
		valor[6]=(i>>6)&1;
		valor[7]=(i>>7)&1;
		G1FillPoint(Pi[i].xyz, K, valor);

	}

}

void G1combMult(Fp *kP, PG1 *P, Fp K){
	uint8_t k[40];
	int i;
	int n=0;
	n=TransposeInt(k,K);
	PG1 Q;

	G1P_cpy(Q.xyz,P[k[n]].xyz);

	for(i=n-1; i>=0; i--){
		G1DoubJ(Q.xyz,Q.xyz);
		if(k[i]!=0){
			G1AddMix(Q.xyz,Q.xyz,P[k[i]].xyz);
		}
	}

	G1P_cpy(kP,Q.xyz);
}

//********************************************************//
//********************        ****      ******************//
//********************  *************** ******************//
//********************  **    ****      ******************//
//********************  ****  **** ***********************//
//********************        ****      ******************//
//********************************************************//

void G2P_print(PG2 p, char *t){
	int i;
	sprintf(szLogThis,"========%s=============", t); logC();
	for(i=0; i<3; i++){
		Fp_print(p.xyz[i][0]);
		Fp_print(p.xyz[i][1]);
	}
}


void G2P_set(Fp2 *C, char *X1,char *X2, char *Y1,char *Y2){
	Fp2_set_str(C[0], X2, X1);
	Fp2_set_str(C[1], Y2, Y1);
	Fp2_init(C[2]);
	C[2][0][0]=1;
}

void G2P_cpy(Fp2 *C, Fp2 *A){
	Fp2_set(C[0],A[0]);
	Fp2_set(C[1],A[1]);
	Fp2_set(C[2],A[2]);
}

void G2Inv(Fp2 *C, Fp2 *A){
	Fp2 aux;
	Fp2_set(aux,A[1]);
	SUB256MOD(C[1][0],p,aux[0]);
	SUB256MOD(C[1][1],p,aux[1]);
	Fp2_set(C[0],A[0]);
	Fp2_set(C[2],A[2]);
}

void Phi(Fp2 *T, PG2 Q){
	Fp f[2],g[2];
	CONJUGADO_FP2(f, Q.xyz[0]);
	CONJUGADO_FP2(g, Q.xyz[1]);
	MULEI_FP2(T[0], f, Y1[1][1]);
	SMULT_FP2(T[1], g, Y1[2]);
	Fp2_set(T[2], Q.xyz[2]);
}

void Phi2(Fp2 *T, PG2 Q){
	MULE_FP2(T[0], Q.xyz[0], Y2[1]);
	MULE_FP2(T[1], Q.xyz[1], Y2[2]);
	Fp2_set(T[2], Q.xyz[2]);
}

void Phi3(Fp2 *T, PG2 Q){
	Fp f[2],g[2];
	Fp_set(T[0][0],Q.xyz[0][1]);
	Fp_set(T[0][1],Q.xyz[0][0]);
	CONJUGADO_FP2(g, Q.xyz[1]);
	MULT_FP2(T[1], g, Y3[2]);
	Fp2_set(T[2], Q.xyz[2]);
}

void G2AddAff(Fp2 *C, Fp2 *A, Fp2 *B){
	Fp2 t1, t2, t3;
	RESTA_FP2(t1, B[0], A[0]);
	INVERT_FP2(t1,t1);
	RESTA_FP2(t2, B[1], A[1]);
	MULT_FP2(t2, t2, t1);
	MULT_FP2(t3, t2, t2);
	RESTA_FP2(t3,t3, B[0]);
	RESTA_FP2(t3,t3, A[0]);
	RESTA_FP2(t1, A[0],t3);
	MULT_FP2(t1, t1, t2);
	RESTA_FP2(t1, t1,A[1]);
	Fp2_set(C[0],t3);
	Fp2_set(C[1],t1);
	Fp2_set(C[2],A[2]);
}


void G2DobAff(Fp2 *C, Fp2 *A){
	Fp2 t1, t2, t3;
	CUAD_FP2(t1,A[0]);
	SUMA_FP2(t2,t1,t1);
	SUMA_FP2(t2,t2,t1);
	SUMA_FP2(t1,A[1],A[1]);
	INVERT_FP2(t1,t1);
	MULT_FP2(t2,t2, t1);
	CUAD_FP2(t3, t2);
	RESTA_FP2(t3,t3, A[0]);
	RESTA_FP2(t3,t3, A[0]);
	RESTA_FP2(t1, A[0],t3);
	MULT_FP2(t1, t1, t2);
	RESTA_FP2(t1, t1,A[1]);
	Fp2_set(C[0],t3);
	Fp2_set(C[1],t1);
	Fp2_set(C[2],A[2]);
}

void G2DoubJ(Fp2 *C, Fp2 *A){
	Fp2 t1,t2,t3,t4;


	CUAD_FP2(t1, A[0]);
	SUMA_FP2(t4,t1,t1);
	SUMA_FP2(t4,t4,t1); //t4
	CUAD_FP2(t1, A[1]);
	SUMA_FP2(t1,t1,t1);//t1

	MULT_FP2_DUAL(t2, A[0], t1,C[2], A[1], A[2]);
	SUMA_FP2(C[2],C[2],C[2]); //z3

	SUMA_FP2(t2,t2,t2);//t2
	CUAD_FP2(t3, t1);
	SUMA_FP2(t3,t3,t3);//t3
	CUAD_FP2(C[0], t4);
	RESTA_FP2(C[0],C[0],t2);
	RESTA_FP2(C[0],C[0],t2); //x3
	RESTA_FP2(t2,t2,C[0]);
	MULT_FP2(C[1], t4, t2);
	RESTA_FP2(C[1],C[1],t3);//y3
}

void G2AddMix(Fp2 *C, Fp2 *A, Fp2 *B){
	Fp2 t1,t2,t3,t4,t5,t6,t7,t8,t9;
	CUAD_FP2(t1,A[2]);
	MULT_FP2_DUAL(t2,t1, A[2],t3,t1, B[0]);
	RESTA_FP2(t5,t3,A[0]);
	CUAD_FP2(t7,t5);
	MULT_FP2_DUAL(t4,B[1], t2,t8,t7,t5);
	RESTA_FP2(t6,t4,A[1]);
	CUAD_FP2(t1,t6);
	RESTA_FP2(t1,t1,t8);

	MULT_FP2_DUAL(t9,A[0],t7, t8,t8,A[1]);
	RESTA_FP2(t1,t1,t9);
	RESTA_FP2(C[0],t1,t9);
	RESTA_FP2(t9,t9,C[0]);

	MULT_FP2_DUAL(C[1],t9,t6,C[2],A[2],t5);
	RESTA_FP2(C[1],C[1],t8);
}

void G2J2A(Fp2 *C, Fp2 *A){
	Fp2 t1,t2,t3;
	if((zero(A[2][0])==0)&&(zero(A[2][1])==0)){
		Fp2_set(C[0], A[0]);
		Fp2_set(C[1], A[1]);
		Fp2_set(C[2], A[2]);
		return;
	}
    CUAD_FP2(t1,A[2]);
	MULT_FP2_DUAL(t2,t1, A[2], C[1],A[1], t1);
	MULT_FP2_DUAL(t3,t1, t2,C[0],A[0], t2);
	INVERT_FP2(t3, t3);
	MULT_FP2_DUAL(C[0],C[0], t3, C[1],C[1], t3);
	Fp2_set_str(C[2],
			"0x0000000000000000000000000000000000000000000000000000000000000000" ,
			"0x212ba4f27ffffff5a2c62effffffffcdb939ffffffffff8a15ffffffffffff8e");
}

void G2H2A(Fp2 *C, Fp2 *A){
	Fp2 t1,t2,t3;
	if((zero(A[2][0])==0)&&(zero(A[2][1])==0)){
		Fp2_set(C[0], A[0]);
		Fp2_set(C[1], A[1]);
		Fp2_set(C[2], A[2]);
		return;
	}
	INVERT_FP2(t1, A[2]);
	MULT_FP2_DUAL(C[0],A[0], t1, C[1],A[1], t1);
	Fp2_set_str(C[2],
			"0x0000000000000000000000000000000000000000000000000000000000000000" ,
			"0x212ba4f27ffffff5a2c62effffffffcdb939ffffffffff8a15ffffffffffff8e");
}

void G2normalize(Fp2 *C, int flag){
	if(flag==1) G2J2A(C,C);
	setDomFp2(C,C,3);
}

void G2Precompute(PG2 *Pi, PG2 P, int n){
	int i;
	PG2 P2;
	G2P_cpy(Pi[1].xyz,P.xyz);
	G2Inv(Pi[0].xyz,P.xyz);
	G2DoubJ(P2.xyz,P.xyz);
	for(i=3; i<=n; i+=2){
		G2AddMix(Pi[i].xyz, P2.xyz, Pi[i-2].xyz);
		G2J2A(Pi[i].xyz,Pi[i].xyz);
		G2Inv(Pi[i-1].xyz,Pi[i].xyz);
	}
}


void G2GLVPrecompute(PG2 *P1, PG2 *Q1, PG2 *R1, PG2 *S1, PG2 P, PG2 Q, PG2 R, PG2 S){
	int i;
	PG2 P2, Q2, R2, S2;
	Fp2 Ori[4], Inv[4], A;
	G2P_cpy(P1[1].xyz,P.xyz);
	G2P_cpy(Q1[1].xyz,Q.xyz);
	G2P_cpy(R1[1].xyz,R.xyz);
	G2P_cpy(S1[1].xyz,S.xyz);
	G2Inv(P1[0].xyz,P.xyz);
	G2Inv(Q1[0].xyz,Q.xyz);
	G2Inv(R1[0].xyz,R.xyz);
	G2Inv(S1[0].xyz,S.xyz);
	G2DoubJ(P2.xyz,P.xyz);
	G2DoubJ(Q2.xyz,Q.xyz);
	G2DoubJ(R2.xyz,R.xyz);
	G2DoubJ(S2.xyz,S.xyz);
	G2AddMix(P2.xyz, P2.xyz, P.xyz);
	G2AddMix(Q2.xyz, Q2.xyz, Q.xyz);
	G2AddMix(R2.xyz, R2.xyz, R.xyz);
	G2AddMix(S2.xyz, S2.xyz, S.xyz);
	Fp2_set(Ori[0], P2.xyz[2]);
	Fp2_set(Ori[1], Q2.xyz[2]);
	Fp2_set(Ori[2], R2.xyz[2]);
	Fp2_set(Ori[3], S2.xyz[2]);
	Fp2_set(P1[3].xyz[2], P.xyz[2]);
	Fp2_set(Q1[3].xyz[2], Q.xyz[2]);
	Fp2_set(R1[3].xyz[2], R.xyz[2]);
	Fp2_set(S1[3].xyz[2], S.xyz[2]);
	MULTIINVERSE_FP2(Inv,Ori, 4);

	CUAD_FP2(A, Inv[0]);
	MULT_FP2_DUAL(P1[3].xyz[0], P2.xyz[0], A, P1[3].xyz[1], P2.xyz[1], A);

	CUAD_FP2(A, Inv[1]);
	MULT_FP2_DUAL(P1[3].xyz[1], P1[3].xyz[1], Inv[0], Q1[3].xyz[1], Q2.xyz[1], A);
	MULT_FP2_DUAL(Q1[3].xyz[0], Q2.xyz[0], A, Q1[3].xyz[1], Q1[3].xyz[1], Inv[1]);

	CUAD_FP2(A, Inv[2]);
	MULT_FP2_DUAL(R1[3].xyz[0], R2.xyz[0], A, R1[3].xyz[1], R2.xyz[1], A);

	CUAD_FP2(A, Inv[3]);
	MULT_FP2_DUAL(R1[3].xyz[1], R1[3].xyz[1], Inv[2], S1[3].xyz[1], S2.xyz[1], A);
	MULT_FP2_DUAL(S1[3].xyz[0], S2.xyz[0], A, S1[3].xyz[1], S1[3].xyz[1], Inv[3]);

	G2Inv(P1[2].xyz,P1[3].xyz);
	G2Inv(Q1[2].xyz,Q1[3].xyz);
	G2Inv(R1[2].xyz,R1[3].xyz);
	G2Inv(S1[2].xyz,S1[3].xyz);

}

void G2scalarMult(Fp2 *kP, PG2 P, Fp K){
	int i,n;
	int8_t ki[260];
	int8_t aux;
	n=wnaf(ki,K,4);
	PG2 Pi[8], P2, Q;
	G2Precompute(Pi, P, 3);
	G2P_cpy(Q.xyz,Pi[ki[n-1]].xyz);
	for(i=n-2; i>=0; i--){
		G2DoubJ(Q.xyz,Q.xyz);
		if(ki[i]!=0){
			if(ki[i]>0){
				G2AddMix(Q.xyz,Q.xyz,Pi[ki[i]].xyz);
			}
			else{
				G2AddMix(Q.xyz,Q.xyz,Pi[-(ki[i]+1)].xyz);
			}
		}
	}
	G2P_cpy(kP,Q.xyz);
}

#ifdef HAVE_NEON
void GSDecomposition(Fp *D, Fp A, int8_t *sig){
	int i;
	uint32_t b1[]={0,0,0,0,0,0,0,0,0};
	uint32_t b2[]={0,0,0,0,0,0,0,0,0};
	uint32_t b3[]={0,0,0,0,0,0,0,0,0};
	uint32_t b4[]={0,0,0,0,0,0,0,0,0};
	uint32_t res1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t A1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t B1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t C1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t D1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	MUL256NEON(res1, res2, G2_BInv[0], A, G2_BInv[1], A);
	MUL256NEON(res3, res4, G2_BInv[2], A, G2_BInv[3], A);

	for(i=9; i<16; i++){
		b1[i-9]=res1[i];
		b2[i-9]=res2[i];
		b3[i-9]=res3[i];
		b4[i-9]=res4[i];
	}

	MUL256NEONIT(A1, A2, G2_BNor[0], b1, G2_BNor[1], b2, 2);
	MUL256NEONIT(A3, A4, G2_BNor[2], b3, G2_BNor[3], b4, 2);

	MUL256NEONIT(B1, B2, G2_BNor[4], b1, G2_BNor[4], b2, 2);
	MUL256NEONIT(B3, B4, G2_BNor[1], b3, G2_BNor[5], b4, 3);

	MUL256NEONIT(C1, C2, G2_BNor[4], b1, G2_BNor[0], b2, 2);
	MUL256NEONIT(C3, C4, G2_BNor[1], b3, G2_BNor[6], b4, 2);

	MUL256NEONIT(D1, D2, G2_BNor[2], b1, G2_BNor[4], b2, 2);
	MUL256NEONIT(D3, D4, G2_BNor[1], b3, G2_BNor[3], b4, 2);

	ADD256(A2,A2,A3);
	ADD256(A2,A2,A4);
	SUB256(A2,A2,A1);

	if(comparativo(A, A2, 8)>-1){
		sig[0]=1;
		SUB256(D[0], A, A2);
	}else{
		sig[0]=-1;
		SUB256(D[0], A2, A);
	}


	ADD256(B1,B1,B2);
	ADD256(B3,B3,B4);

	if(comparativo(B3, B1, 8)>-1){
		sig[1]=1;
		SUB256(D[1], B3, B1);
	}else{
		sig[1]=-1;
		SUB256(D[1], B1, B3);
	}

	ADD256(C1,C1,C2);
	ADD256(C1,C1,C4);

	if(comparativo(C1, C3, 8)>-1){
		sig[2]=-1;
		SUB256(D[2], C1, C3);
	}else{
		sig[2]=1;
		SUB256(D[2], C3, C1);
	}

	ADD256(D1,D1,D3);
	ADD256(D1,D1,D4);

	if(comparativo(D2, D1, 8)>-1){
		sig[3]=-1;
		SUB256(D[3], D2, D1);
	}else{
		sig[3]=1;
		SUB256(D[3], D1, D2);
	}
}
#else
void GSDecomposition(Fp *D, Fp A, int8_t *sig){
	int i;
	uint32_t b1[]={0,0,0,0,0,0,0,0,0};
	uint32_t b2[]={0,0,0,0,0,0,0,0,0};
	uint32_t b3[]={0,0,0,0,0,0,0,0,0};
	uint32_t b4[]={0,0,0,0,0,0,0,0,0};
	uint32_t res1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t res4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t A1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t A4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t B1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t B4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t C1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t C4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	uint32_t D1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t D4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	MUL256N(res1, G2_BInv[0], A, 8);
	MUL256N(res2, G2_BInv[1], A, 8);
	MUL256N(res3, G2_BInv[2], A, 8);
	MUL256N(res4, G2_BInv[3], A, 8);

	for(i=9; i<16; i++){
		b1[i-9]=res1[i];
		b2[i-9]=res2[i];
		b3[i-9]=res3[i];
		b4[i-9]=res4[i];
	}

	MUL256N(A1, G2_BNor[0], b1, 2);
	MUL256N(A2, G2_BNor[1], b2, 2);
	MUL256N(A3, G2_BNor[2], b3, 2);
	MUL256N(A4, G2_BNor[3], b4, 2);

	MUL256N(B1, G2_BNor[4], b1, 2);
	MUL256N(B2, G2_BNor[4], b2, 2);
	MUL256N(B3, G2_BNor[1], b3, 2);
	MUL256N(B4, G2_BNor[5], b4, 3);

	MUL256N(C1, G2_BNor[4], b1, 2);
	MUL256N(C2, G2_BNor[0], b2, 2);
	MUL256N(C3, G2_BNor[1], b3, 2);
	MUL256N(C4, G2_BNor[6], b4, 2);

	MUL256N(D1, G2_BNor[2], b1, 2);
	MUL256N(D2, G2_BNor[4], b2, 2);
	MUL256N(D3, G2_BNor[1], b3, 2);
	MUL256N(D4, G2_BNor[3], b4, 2);

	ADD256(A2,A2,A3);
	ADD256(A2,A2,A4);
	SUB256(A2,A2,A1);

	if(comparativo(A, A2, 8)>-1){
		sig[0]=1;
		SUB256(D[0], A, A2);
	}else{
		sig[0]=-1;
		SUB256(D[0], A2, A);
	}


	ADD256(B1,B1,B2);
	ADD256(B3,B3,B4);

	if(comparativo(B3, B1, 8)>-1){
		sig[1]=1;
		SUB256(D[1], B3, B1);
	}else{
		sig[1]=-1;
		SUB256(D[1], B1, B3);
	}

	ADD256(C1,C1,C2);
	ADD256(C1,C1,C4);

	if(comparativo(C1, C3, 8)>-1){
		sig[2]=-1;
		SUB256(D[2], C1, C3);
	}else{
		sig[2]=1;
		SUB256(D[2], C3, C1);
	}

	ADD256(D1,D1,D3);
	ADD256(D1,D1,D4);

	if(comparativo(D2, D1, 8)>-1){
		sig[3]=-1;
		SUB256(D[3], D2, D1);
	}else{
		sig[3]=1;
		SUB256(D[3], D1, D2);
	}
}
#endif

void G2GLVMult(Fp2 *kP, PG2 P, Fp K){
	int i,n1,n2,n3,n4,n;
	int8_t s[4];
	int8_t k1[70],k2[70],k3[70],k4[70];
	Fp Kd[4];
	PG2 P1[4],P2[4],P3[4],P4[4];
	PG2 H0,H1,H2,H3;
	PG2 Q;
	for(i=0; i<70; i++){
		k1[i]=0;
		k2[i]=0;
		k3[i]=0;
		k4[i]=0;
	}
	GSDecomposition(Kd,K,s);
	G2P_cpy(H0.xyz,P.xyz);

	Phi (H1.xyz,P);
	Phi2(H2.xyz,P);
	Phi3(H3.xyz,P);


	if(s[0]<0) G2Inv(H0.xyz, P.xyz);
	if(s[1]>0) G2Inv(H1.xyz, H1.xyz);
	if(s[2]>0) G2Inv(H2.xyz, H2.xyz);
	if(s[3]>0) G2Inv(H3.xyz, H3.xyz);

	G2GLVPrecompute(P1,P2,P3,P4,H0,H1,H2,H3);

	n1=wnaf(k1,Kd[0],4);
	n2=wnaf(k2,Kd[1],4);
	n3=wnaf(k3,Kd[2],4);
	n4=wnaf(k4,Kd[3],4);

	n=n1;
	G2P_cpy(Q.xyz,P1[k1[n-1]].xyz);
	if(n2>n){ n=n2; G2P_cpy(Q.xyz,P2[k2[n-1]].xyz); }
	if(n3>n){ n=n3; G2P_cpy(Q.xyz,P3[k3[n-1]].xyz); }
	if(n4>n){ n=n4; G2P_cpy(Q.xyz,P4[k4[n-1]].xyz); }

	if(n1==n){
		if(n2 == n) G2AddMix(Q.xyz,Q.xyz,P2[k2[n-1]].xyz);
		if(n3 == n) G2AddMix(Q.xyz,Q.xyz,P3[k3[n-1]].xyz);
		if(n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]].xyz);
	}else if(n2==n){
		if(n3 == n) G2AddMix(Q.xyz,Q.xyz,P3[k3[n-1]].xyz);
		if(n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]].xyz);
	}else{
		if(n3 == n && n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]].xyz);
	}

	for(i=n-2; i>=0; i--){
		G2DoubJ(Q.xyz,Q.xyz);
		if(k1[i]!=0){
			if(k1[i]>0) G2AddMix(Q.xyz,Q.xyz,P1[k1[i]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P1[-(k1[i]+1)].xyz);
		}
		if(k2[i]!=0){
			if(k2[i]>0) G2AddMix(Q.xyz,Q.xyz,P2[k2[i]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P2[-(k2[i]+1)].xyz);
		}
		if( k3[i]!=0){
			if(k3[i]>0) G2AddMix(Q.xyz,Q.xyz,P3[k3[i]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P3[-(k3[i]+1)].xyz);
		}
		if(k4[i]!=0){
			if(k4[i]>0) G2AddMix(Q.xyz,Q.xyz,P4[k4[i]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P4[-(k4[i]+1)].xyz);
		}
	}
	G2P_cpy(kP,Q.xyz);
}


void G2GLVMultKnown(Fp2 *kP, Fp K, PG2 *P1, PG2 *P2, PG2 *P3, PG2 *P4, int Naf){
	int i,n1,n2,n3,n4,n;
	int m[]={0,0,0,0};
	int o[]={1,1,1,1};
	int8_t s[4];
	int8_t k1[70],k2[70],k3[70],k4[70];
	Fp Kd[4];
	PG2 Q;
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
	G2P_cpy(Q.xyz,P1[k1[n-1]-m[0]].xyz);
	if(n2>n){ n=n2; G2P_cpy(Q.xyz,P2[k2[n-1]-m[1]].xyz); }
	if(n3>n){ n=n3; G2P_cpy(Q.xyz,P3[k3[n-1]-m[2]].xyz); }
	if(n4>n){ n=n4; G2P_cpy(Q.xyz,P4[k4[n-1]-m[3]].xyz); }
	if(n1==n){
		if(n2 == n) G2AddMix(Q.xyz,Q.xyz,P2[k2[n-1]-m[1]].xyz);
		if(n3 == n) G2AddMix(Q.xyz,Q.xyz,P3[k3[n-1]-m[2]].xyz);
		if(n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]-m[3]].xyz);
	}else if(n2==n){
		if(n3 == n) G2AddMix(Q.xyz,Q.xyz,P3[k3[n-1]-m[2]].xyz);
		if(n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]-m[3]].xyz);
	}else{
		if(n3 == n && n4 == n) G2AddMix(Q.xyz,Q.xyz,P4[k4[n-1]-m[3]].xyz);
	}

	for(i=n-2; i>=0; i--){
		G2DoubJ(Q.xyz,Q.xyz);
		if(k1[i]!=0){
			if(k1[i]>0) G2AddMix(Q.xyz,Q.xyz,P1[k1[i]-m[0]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P1[abs(k1[i])-o[0]].xyz);
		}
		if(k2[i]!=0){
			if(k2[i]>0) G2AddMix(Q.xyz,Q.xyz,P2[k2[i]-m[1]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P2[abs(k2[i])-o[1]].xyz);
		}
		if( k3[i]!=0){
			if(k3[i]>0) G2AddMix(Q.xyz,Q.xyz,P3[k3[i]-m[2]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P3[abs(k3[i])-o[2]].xyz);
		}
		if(k4[i]!=0){
			if(k4[i]>0) G2AddMix(Q.xyz,Q.xyz,P4[k4[i]-m[3]].xyz);
			else G2AddMix(Q.xyz,Q.xyz,P4[abs(k4[i])-o[3]].xyz);
		}
	}
	G2P_cpy(kP,Q.xyz);
}

void G2Multinormalizacion(PG2 *P,int N, int flag){
	int i;
	Fp2 Ori[N],Inv[N], aux;
	for(i=0; i<N; i++){
		Fp2_set(Ori[i], P[i].xyz[2]);
	}

	MULTIINVERSE_FP2(Inv, Ori, N);
	for(i=0; i<N; i++){
		MULT_FP2(aux, Inv[i], Inv[i]);
		MULT_FP2(P[i].xyz[0], P[i].xyz[0], aux);
		MULT_FP2(P[i].xyz[1], P[i].xyz[1], aux);
		MULT_FP2(P[i].xyz[1], P[i].xyz[1], Inv[i]);
		Fp2_set_str(P[i].xyz[2],
					"0x0000000000000000000000000000000000000000000000000000000000000000" ,
					"0x08172eda56cca85f0b6bfc4fb10d8ddaaf7c37563ee98269ed3d8cb0cb582f66");
	}
	if(flag==1){
		for(i=0; i<N; i++){
			 setDomFp2(P[i].xyz, P[i].xyz,3);
		}
	}
}


void G2get8P(PG2 *K, PG2 P){
	int i;
	PG2 Q;
	G2P_cpy(K[0].xyz,P.xyz);
	G2P_cpy(Q.xyz,P.xyz);
	for(i=1; i<=224; i++){
		G2DoubJ(Q.xyz,Q.xyz);
		if(i%32==0){
			G2J2A(K[i/32].xyz,Q.xyz);
		}
	}
}

void G2FillPoint(Fp2 *P, PG2 *P8, uint8_t *val){
	int i,j;
	PG2 A;
	for(i=0; i<8; i++){
		if(val[i]!=0){
			G2P_cpy(A.xyz,P8[i].xyz);
			i++;
			break;
		}
	}
	for(i; i<8; i++){
		if(val[i]!=0)
			G2AddMix(A.xyz, A.xyz, P8[i].xyz);
	}
	G2J2A(P,A.xyz);
}

void G2CombPrecompute(PG2 *Pi, PG2 P){
	int i;
	PG2 K[8];
	uint8_t valor[8];

	G2get8P(K, P);
	for(i=1; i<256; i++){
		valor[0]=i&1;
		valor[1]=(i>>1)&1;
		valor[2]=(i>>2)&1;
		valor[3]=(i>>3)&1;
		valor[4]=(i>>4)&1;
		valor[5]=(i>>5)&1;
		valor[6]=(i>>6)&1;
		valor[7]=(i>>7)&1;
		G2FillPoint(Pi[i].xyz, K, valor);
	}

}

void G2combMult(Fp2 *kP, PG2 *P, Fp K){
	uint8_t k[40];
	int i;
	int n=0;
	n=TransposeInt(k,K);
	PG2 Q;
	G2P_cpy(Q.xyz,P[k[n]].xyz);
	for(i=n-1; i>=0; i--){
		G2DoubJ(Q.xyz,Q.xyz);
		if(k[i]!=0){
			G2AddMix(Q.xyz,Q.xyz,P[k[i]].xyz);
		}
	}
	G2P_cpy(kP,Q.xyz);
}

int G2compare(Fp2 *K, Fp2 *L){
	int i=0;
	if(comparaFpk(K[0],L[0],2)==0)i++;
	if(comparaFpk(K[1],L[1],2)==0)i++;

	if(i==2) return 0;
	return 1;
}
