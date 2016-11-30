/*
arithFpk.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "arithFp.h"
#include "Domain.h"
#include <stdlib.h>
#include <stdio.h>
#define beta 1
#ifdef HAVE_NEON
#include "NEON.h"
#endif

void Fpk_print(char *name, Fp *fp, int N){
	int i;
	sprintf(szLogThis,"========%s=============", name); logC();
	for(i=0; i<N; i++){
		Fp_print(fp[i]);
	}
}

void setDomMont(Fp *C, Fp *A, int N){
	int i;
	for(i=0; i<N; i++){
		ConvertMont(C[i], A[i]);
	}
}

void setDomFp(Fp *C, Fp *A, int N){
	int i;
	for(i=0; i<N; i++){
		MULMONG1(C[i], A[i]);
	}
}

void setDomMont2(Fp2 *C, Fp2 *A, int N){
	int i;
	for(i=0; i<N; i++){
		ConvertMont(C[i][0], A[i][0]);
		ConvertMont(C[i][1], A[i][1]);
	}
}

void setDomFp2(Fp2 *C, Fp2 *A, int N){
	int i;
	for(i=0; i<N; i++){
		MULMONG1(C[i][0], A[i][0]);
		MULMONG1(C[i][1], A[i][1]);
	}
}

void initFpk(Fp *C, int N){
	int i;
	for(i=0; i<N; i++){
		Fp_init(C[i]);
	}
}

int wnaf(int8_t *ki, uint32_t *I, uint8_t w){
	int i=0;
	uint32_t K[9];
	uint8_t dob=2*w; //w=8 =>2^4=16 //w=2 2^2=4
	uint8_t get=dob-1;
	uint32_t KI[]={0,0,0,0,0,0,0,0,0};
	Fp_set(K,I);
	while(zero(K)>0){
		if(K[0]&1!=0){
			ki[i]=K[0]&get;
			if(ki[i]>w) ki[i]=-(dob-ki[i]);
			if(ki[i]<0){
				KI[0]=-ki[i];
				ADD256S(K,KI);
			}else{
				KI[0]=ki[i];
				SUB256S(K,KI);
			}
		}
		else{
			ki[i]=0;
		}
		shifR1(K,K);
		i++;
	}
	return i;
}

void BN_init(){
	Fp_set_str(Y1[0][0],"0x1B377619212E7C8CB6499B50A846953F850974924D3F77C2E17DE6C06F2A6DE9");//
	Fp_set_str(Y1[0][1],"0x09EBEE691ED1837503EAB22F57B96AC8DC178B6DB2C08850C582193F90D5922A");//
	Fp_set_str(Y1[1][0],"0x0000000000000000000000000000000000000000000000000000000000000000");//
	Fp_set_str(Y1[1][1],"0x25236482400000017080EB4000000006181800000000000CD98000000000000B");//
	Fp_set_str(Y1[2][0],"0x23DFC9D1A39F4DB8C69B87A8848AA075A7333A0E62D78CBF4B1B8EEAE58B81C5");//
	Fp_set_str(Y1[2][1],"0x23DFC9D1A39F4DB8C69B87A8848AA075A7333A0E62D78CBF4B1B8EEAE58B81C5");//
	Fp_set_str(Y1[3][0],"0x25236482400000017080EB4000000006181800000000000CD98000000000000C");//
	Fp_set_str(Y1[3][1],"0x0000000000000000000000000000000000000000000000000000000000000000");//
	Fp_set_str(Y1[4][0],"0x19F3DB6884CDCA43C2B0D5792CD135ACCB1BAEA0B017046E859975AB54B5EF9B");//
	Fp_set_str(Y1[4][1],"0x0B2F8919BB3235BDF7837806D32ECA5B9605515F4FE8FBA521668A54AB4A1078");//
	setDomMont2(Y1,Y1,5);

	Fp_set_str(Y2[0],"0x000000000000000049B36240000000024909000000000006CD80000000000008");
	Fp_set_str(Y2[1],"0x000000000000000049B36240000000024909000000000006CD80000000000007");
	Fp_set_str(Y2[2],"0x2523648240000001BA344D80000000086121000000000013A700000000000012");//-1
	Fp_set_str(Y2[3],"0x25236482400000017080EB4000000006181800000000000CD98000000000000B");
	Fp_set_str(Y2[4],"0x25236482400000017080EB4000000006181800000000000CD98000000000000C");
	setDomMont(Y2,Y2,5);

	Fp_set_str(Y3[0][0],"0x01439AB09C60B248F398C5D77B755F92B9EDC5F19D2873545BE471151A747E4E");//
	Fp_set_str(Y3[0][1],"0x23DFC9D1A39F4DB8C69B87A8848AA075A7333A0E62D78CBF4B1B8EEAE58B81C5");//
	Fp_set_str(Y3[1][0],"0x0000000000000000000000000000000000000000000000000000000000000000");//
	Fp_set_str(Y3[1][1],"0x0000000000000000000000000000000000000000000000000000000000000001");//
	Fp_set_str(Y3[2][0],"0x01439AB09C60B248F398C5D77B755F92B9EDC5F19D2873545BE471151A747E4E");//
	Fp_set_str(Y3[2][1],"0x01439AB09C60B248F398C5D77B755F92B9EDC5F19D2873545BE471151A747E4E");//
	Fp_set_str(Y3[3][0],"0x2523648240000001BA344D80000000086121000000000013A700000000000012");//-1
	Fp_set_str(Y3[3][1],"0x0000000000000000000000000000000000000000000000000000000000000000");//
	Fp_set_str(Y3[4][0],"0x23DFC9D1A39F4DB8C69B87A8848AA075A7333A0E62D78CBF4B1B8EEAE58B81C5");//
	Fp_set_str(Y3[4][1],"0x01439AB09C60B248F398C5D77B755F92B9EDC5F19D2873545BE471151A747E4E");//
	setDomMont2(Y3,Y3,5);
	int i;
	for(i=0; i<70; i++){
		WNAF_SK[i]=0;
	}
	WNAF_SK[2]=1;
	WNAF_SK[56]=1;
	WNAF_SK[57]=1;
	WNAF_SK[63]=1;
	WNAF_SK[64]=1;
	TAM_WNAF_SK=65;





	//Precomputo BN - GLV
	Fp_set_str(BN_Beta,   "0x0672A6264000001E113D4F2CA6B29BDCEC75DF6EC728463C3291039717960343");
	Fp_set_str(G1_BInv[0],"0x00000002A01FAB7E04A017B9C0EB31FF36BF3357C9C375F2F9246C37F5F8A951");
	Fp_set_str(G1_BInv[1],"0x00000000000000037937CA688A6B4904B90D84EDF5049D26699586F1D5570955");

	Fp_set_str(G1_BNor[0][0],"0x0000000000000000000000000000000061818000000000028500000000000004");
	Fp_set_str(G1_BNor[0][1],"0x0000000000000000000000000000000000000000000000008100000000000001");
	Fp_set_str(G1_BNor[1][0],"0x0000000000000000000000000000000000000000000000008100000000000001");
	Fp_set_str(G1_BNor[1][1],"0x0000000000000000000000000000000061818000000000020400000000000003");


	Fp_set_str(G2_BInv[0],"0x000000000000000000000000E00A8E7F56E007E5B09FE7FDF43BA9982D9A2C7F");
	Fp_set_str(G2_BInv[1],"0x0000000152AFF56A8054ABF9DA75DB2DA3D6885101E5FD3997D41CB1F79F52A0");//Neg
	Fp_set_str(G2_BInv[2],"0x00000000A957FAB5402A55FCED3AED96D1EB44295F40F136EE84E09BE33C9C9B");//Neg
	Fp_set_str(G2_BInv[3],"0x000000000000000000000000E00A8E7F56E007E929D7B2667EA6F29CE6A7B16D");//Neg

	Fp_set_str(G2_BNor[0],"0x0000000000000000000000000000000000000000000000004080000000000000");//t+1
	Fp_set_str(G2_BNor[1],"0x0000000000000000000000000000000000000000000000008100000000000001");//2t+1
	Fp_set_str(G2_BNor[2],"0x0000000000000000000000000000000000000000000000008100000000000002");//2t
	Fp_set_str(G2_BNor[3],"0x0000000000000000000000000000000000000000000000004080000000000002");//t-1
	Fp_set_str(G2_BNor[4],"0x0000000000000000000000000000000000000000000000004080000000000001");//t
	Fp_set_str(G2_BNor[5],"0x0000000000000000000000000000000000000000000000010200000000000002");//4t+2
	Fp_set_str(G2_BNor[6],"0x0000000000000000000000000000000000000000000000008100000000000003");//2t-1


}

//*************************************************************//
//***************       ***        *****  *********************//
//***************  ********  ****  ***    *********************//
//***************    ******        *****  *********************//
//***************  ********  ***********  *********************//
//***************  ********  *********      *******************//
//*************************************************************//

#ifdef HAVE_NEON
void MultiInverse(Fp *Inv, Fp *Ori, int N){
	int i;
	Fp C[N],U;
	Fp_set(C[0], Ori[0]);
	for(i=1; i<N; i++){
		MULMONG(C[i], C[i-1], Ori[i]);
	}
	MontInverse(U, C[N-1]);
	for(i=N-1; i>0; i--){
		MULMONGNEON(Inv[i], U, U, C[i-1], U, Ori[i]);
	}
	Fp_set(Inv[0], U);
}
#else
void MultiInverse(Fp *Inv, Fp *Ori, int N){
	int i;
	Fp C[N],U;
	Fp_set(C[0], Ori[0]);
	for(i=1; i<N; i++){
		MULMONG(C[i], C[i-1], Ori[i]);
	}

	MontInverse(U, C[N-1]);

	for(i=N-1; i>0; i--){
		MULMONG(Inv[i], U, C[i-1]);
		MULMONG(U, U, Ori[i]);
	}
	Fp_set(Inv[0], U);
}
#endif




//*************************************************************//
//***************       ***        ****      ******************//
//***************  ********  ****  ********* ******************//
//***************    ******        ****      ******************//
//***************  ********  ********** ***********************//
//***************  ********  **********      ******************//
//*************************************************************//

void Fp2_init(Fp *num){
	Fp_init(num[0]);
	Fp_init(num[1]);
}

void Fp2_set(Fp *num, Fp *a){
	Fp_set(num[0], a[0]);
	Fp_set(num[1], a[1]);
}


void Fp2_set_str(Fp *n, char *h, char *l){
	Fp_set_str(n[0], l);
	Fp_set_str(n[1], h);
}

void SUMA_FP2(Fp *C, Fp *A, Fp *B){
	ADD256MOD(C[0], A[0], B[0]);
	ADD256MOD(C[1], A[1], B[1]);
}

void SUMA_FP2L(Mul *C, Mul *A, Mul *B){
	ADD512L(C[1],A[1],B[1]);
	ADD512L(C[0],A[0],B[0]);
}

void RESTA_FP2(Fp *C, Fp *A, Fp *B){
	SUB256MOD(C[1],A[1],B[1]);
	SUB256MOD(C[0],A[0],B[0]);
}

void RESTA_FP2L(Mul *C, Mul *B){
	SUB512L(C[1],B[1]);
	SUB512L(C[0],B[0]);
}



#ifdef HAVE_NEON
void MULE_FP2(Fp *C, Fp *A, Fp b){
	MULMONGNEON(C[0],C[1], A[0], b, A[1], b);
}

void MULEI_FP2(Fp *C, Fp *A, Fp b){
	Fp aux;
	MULMONGNEON(C[1],aux, A[0], b, A[1], b);
	SUB256(C[0], p, aux);
}

void MULT_FP2(Fp *C, Fp *A, Fp *B){
	Fp S, T;
	uint32_t d1[17],d2[17];
	uint32_t d0[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ADD256(S, A[0], A[1]);
	ADD256(T, B[0], B[1]);
	MUL256(d0,S,T);
	MUL256NEON(d1,d2,A[0], B[0], A[1], B[1]);
	SUB512(d0, d1);
	SUB512(d0, d2);
	SUB512L(d1,d2);
	MOD512NEON(C[1], C[0], d0, d1);
}

void MULT_FP2_DUAL(Fp *C1, Fp *A1, Fp *B1, Fp *C2, Fp *A2, Fp *B2){
	Fp S1, T1, S2, T2;
	uint32_t d0[17],d1[17],d2[17],e0[17],e1[17],e2[17];

	ADD256(S1, A1[0], A1[1]);
	ADD256(T1, B1[0], B1[1]);
	ADD256(S2, A2[0], A2[1]);
	ADD256(T2, B2[0], B2[1]);

	MUL256NEON(d0,e0,S1,T1,S2,T2);
	MUL256NEON(d1,d2,A1[0], B1[0], A1[1], B1[1]);
	MUL256NEON(e1,e2,A2[0], B2[0], A2[1], B2[1]);

	SUB512(d0, d1);
	SUB512(d0, d2);
	SUB512L(d1,d2);

	SUB512(e0, e1);
	SUB512(e0, e2);
	SUB512L(e1,e2);

	MOD512NEON(C1[1], C1[0], d0, d1);
	MOD512NEON(C2[1], C2[0], e0, e1);

}


void MULT_FP2L(Mul *C, Fp *A, Fp *B){
	Fp S, T;
	uint32_t d1[17],d2[17];
	uint32_t d0[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ADD256(S, A[0], A[1]);
	ADD256(T, B[0], B[1]);
	MUL256(d0,S,T);
	MUL256NEON(d1,d2,A[0], B[0], A[1], B[1]);
	SUB512(d0, d1);
	SUB512A(C[1], d0, d2);
	SUB512LE(C[0],d1, d2);
}

void MULT_FP2L_DUAL(Mul *C1, Mul *C2, Fp *A1, Fp *B1, Fp *A2, Fp *B2){
	Fp S1, T1, S2, T2;
	uint32_t d0[17],d1[17],d2[17],e0[17],e1[17],e2[17];

	ADD256(S1, A1[0], A1[1]);
	ADD256(T1, B1[0], B1[1]);
	ADD256(S2, A2[0], A2[1]);
	ADD256(T2, B2[0], B2[1]);
	MUL256NEON(d0,e0,S1,T1,S2,T2);

	MUL256NEON(d1,d2,A1[0], B1[0], A1[1], B1[1]);
	MUL256NEON(e1,e2,A2[0], B2[0], A2[1], B2[1]);

	SUB512(d0, d1);
	SUB512A(C1[1], d0, d2);
	SUB512LE(C1[0],d1, d2);

	SUB512(e0, e1);
	SUB512A(C2[1], e0, e2);
	SUB512LE(C2[0],e1, e2);

}


void SMULT_FP2(Fp *C, Fp *A, Fp *B){
	Fp S, T;
	MULMONGNEON(S,T, A[0], B[0], A[1], B[1]);
	ADD256MOD(C[1],S,T);
	SUB256MOD(C[0],S,T);
}

void REDU_FP2(Fp *C, Mul *A){
	MOD512NEON(C[0], C[1], A[0], A[1]);
}

void CUAD_FP2(Fp *C, Fp *A){
    Fp T, T2, T3;
	SUB256MOD(T, A[0], A[1]); //A0-A1
	ADD256MOD(T2, A[1], A[0]); //A0-beta*A1
	ADD256MOD(T3, A[1], A[1]); //2A1
	MULMONGNEON(C[1], C[0], T3, A[0], T, T2);  //2A1A0 == C[1]
}

void CUAD_FP2L(Mul *C, Fp *A){
    Fp T, T2, T3;
	SUB256MOD(T, A[0], A[1]); //A0-A1
	ADD256MOD(T2, A[1], A[0]); //A0-beta*A1
	ADD256(T3, A[1], A[1]); //2A1
	MUL256NEON(C[1], C[0], T3, A[0], T, T2);  //2A1A0 == C[1]
}

void INVERT_FP2(Fp *C, Fp *A){
	Fp aux, t0, t1;
	Mul r0, r1;
	MUL256NEON(r0,r1, A[0], A[0], A[1], A[1]); //a0*a0
	ADD512L(r0, r0, r1); //a0*a0-beta*a1*a1
	MOD512(t0, r0);
	MontInverse(t1, t0);
	MULMONGNEON(C[0], aux, A[0], t1, A[1], t1); //a0*t1, a1*t1
	SUB256(C[1], p, aux); //-a1*t1
}
#else
void MULE_FP2(Fp *C, Fp *A, Fp b){
	MULMONG(C[0], A[0], b);
	MULMONG(C[1], A[1], b);
}

void MULEI_FP2(Fp *C, Fp *A, Fp b){
	Fp aux;
	MULMONG(C[1], A[0], b);
	MULMONG(aux, A[1], b);
	SUB256(C[0], p, aux);
}

void MULT_FP2(Fp *C, Fp *A, Fp *B){
	Fp S, T;
	uint32_t d0[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t d1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t d2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ADD256(S, A[0], A[1]);
	ADD256(T, B[0], B[1]);
	MUL256(d0,S,T);
	MUL256(d1,A[0],B[0]);
	MUL256(d2,A[1],B[1]);
	SUB512(d0, d1);
	SUB512(d0, d2);
	MOD512(C[1], d0);
	SUB512L(d1,d2);
	MOD512(C[0], d1);
}

void MULT_FP2_DUAL(Fp *C1, Fp *A1, Fp *B1, Fp *C2, Fp *A2, Fp *B2){
	MULT_FP2(C1, A1, B1);
	MULT_FP2(C2, A2, B2);
}


void MULT_FP2L(Mul *C, Fp *A, Fp *B){
	Fp S, T;
	uint32_t d0[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t d1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t d2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ADD256(S, A[0], A[1]);
	ADD256(T, B[0], B[1]);
	MUL256(d0,S,T);
	MUL256(d1,A[0],B[0]);
	MUL256(d2,A[1],B[1]);
	SUB512(d0, d1);
	SUB512A(C[1], d0, d2);
	SUB512LE(C[0],d1, d2);
}

void MULT_FP2L_DUAL(Mul *C1, Mul *C2, Fp *A1, Fp *B1, Fp *A2, Fp *B2){
	MULT_FP2L(C1, A1, B1);
	MULT_FP2L(C2, A2, B2);
}

void SMULT_FP2(Fp *C, Fp *A, Fp *B){
	Fp S, T;
	MULMONG(S, A[0], B[0]);
	MULMONG(T, A[1], B[1]);
	ADD256MOD(C[1],S,T);
	SUB256MOD(C[0],S,T);
}


void REDU_FP2(Fp *C, Mul *A){
	MOD512(C[0], A[0]);
	MOD512(C[1], A[1]);
}

void CUAD_FP2(Fp *C, Fp *A){
    Fp T, T2, T3;
	SUB256MOD(T, A[0], A[1]); //A0-A1
	ADD256MOD(T2, A[1], A[0]); //A0-beta*A1

	ADD256MOD(T3, A[1], A[1]); //2A1
	MULMONG(C[1], T3, A[0]);  //2A1A0 == C[1]
	MULMONG(C[0], T, T2);  //(A0-A1)*(A0+A1)
}

void CUAD_FP2L(Mul *C, Fp *A){
    Fp T, T2, T3;
	SUB256MOD(T, A[0], A[1]); //A0-A1
	ADD256MOD(T2, A[1], A[0]); //A0-beta*A1
	ADD256(T3, A[1], A[1]); //2A1
	MUL256(C[1], T3, A[0]);  //2A1A0 == C[1]
	MUL256(C[0], T, T2);  //(A0-A1)*(A0+A1)
}


void INVERT_FP2(Fp *C, Fp *A){
	Fp aux, t0, t1;
	Mul r0, r1;
	MUL256(r0, A[0], A[0]); //a0*a0
	MUL256(r1, A[1], A[1]); //a1*a1
	ADD512L(r0, r0, r1); //a0*a0-beta*a1*a1
	MOD512(t0, r0);
	MontInverse(t1, t0);
	MULMONG(C[0], A[0], t1); //a0*t1
	MULMONG(aux, A[1], t1); //a1*t1
	SUB256(C[1], p, aux); //-a1*t1*/
}

#endif

void MULU_FP2(Fp *C, Fp *A){
	SUB256MOD(C[0], A[0], A[1]);
	ADD256MOD(C[1], A[0], A[1]);
}

void MULUINV_FP2(Fp *C, Fp *A){
	Fp aux;
	SUB256MOD(C[1], A[0], A[1]);
	SUB256MOD(C[2], A[0], A[1]);
}

void MULU_FP2L(Mul *C, Mul *A){
	SUB512LE(C[0], A[0], A[1]);
	ADD512L(C[1], A[0], A[1]);
}

void CONJUGADO_FP2(Fp *C, Fp *A){
	Fp_set(C[0],A[0]);
	SUB256(C[1],p,A[1]);
}

void NEGATIVO_FP2(Fp *C, Fp *A){
	SUB256(C[0],p,A[0]);
	SUB256(C[1],p,A[1]);
}

void DIVIDE2_FP2(Fp *C, Fp *A){
	DIVIDE2(C[0], A[0]);
	DIVIDE2(C[1], A[1]);
}

void MULTIINVERSE_FP2(Fp2 *Inv, Fp2 *Ori, int N){
	int i;
	Fp2 C[N],U;
	Fp2_set(C[0], Ori[0]);
	for(i=1; i<N; i++){
		MULT_FP2(C[i], C[i-1], Ori[i]);
	}
	INVERT_FP2(U, C[N-1]);
	for(i=N-1; i>0; i--){
		MULT_FP2(Inv[i], U, C[i-1]);
		MULT_FP2(U, U, Ori[i]);
	}
	Fp2_set(Inv[0], U);
}



//*************************************************************//
//***************       ***        *****  ****  ***************//
//***************  ********  ****  *****  ****  ***************//
//***************    ******        *****        ***************//
//***************  ********  *****************  ***************//
//***************  ********  *****************  ***************//
//*************************************************************//

void CUAD_FP4B(Fp *C1, Fp *C2,Fp *A1, Fp *A2){
	Fp t0[2],t1[2], aux[2];
	SUMA_FP2(aux, A1,A2);
	CUAD_FP2(t0, A1);//elevadas al cuadrado
	CUAD_FP2(t1, A2);
	MULU_FP2(C1, t1); //t1*epsilon
	SUMA_FP2(C1, C1,t0);
	CUAD_FP2(C2, aux);
	RESTA_FP2(C2,C2,t0);
	RESTA_FP2(C2,C2,t1);
}

void CUAD_FP4(Fp *C1, Fp *C2,Fp *A1, Fp *A2){
	Fp aux[2];
	Mul t0[2],t1[2],c1[2], c2[2];
	SUMA_FP2(aux, A1,A2);
	CUAD_FP2L(t0, A1);//elevadas al cuadrado
	CUAD_FP2L(t1, A2);
	MULU_FP2L(c1, t1); //t1*epsilon
	SUMA_FP2L(c1, c1,t0);
	REDU_FP2(C1,c1);
	CUAD_FP2L(c2, aux);
	RESTA_FP2L(c2,t0);
	RESTA_FP2L(c2,t1);
	REDU_FP2(C2,c2);
}

void CUAD_FP4A(Fp *C1, Fp *C2,Fp *A1, Fp *A2){
	Fp t0[2],t1[2], aux[2];
	MULU_FP2(aux, A2);
	SUMA_FP2(t0, A1,A2);
	SUMA_FP2(t1, A1,aux);
#ifdef HAVE_NEON
	MULT_FP2_DUAL(C2, A1, A2, C1, t1, t0);
#else
	MULT_FP2(C2, A1, A2);
	MULT_FP2(C1, t1, t0);
#endif
	MULU_FP2(aux, C2);
	RESTA_FP2(C1,C1,C2);
	RESTA_FP2(C1,C1,aux);
	SUMA_FP2(C2,C2,C2);
}

//*************************************************************//
//***************       ***        *****        ***************//
//***************  ********  ****  *****  *********************//
//***************    ******        *****        ***************//
//***************  ********  ***********  ****  ***************//
//***************  ********  ***********        ***************//
//*************************************************************//

void SUMA_FP6(Fp *C,Fp *A,Fp *B){
	SUMA_FP2(C, A, B);
	SUMA_FP2(&C[2], &A[2],&B[2]);
	SUMA_FP2(&C[4], &A[4],&B[4]);
}

void SUMA_FP6L(Mul *C,Mul *A,Mul *B){
	SUMA_FP2L(C, A, B);
	SUMA_FP2L(&C[2], &A[2],&B[2]);
	SUMA_FP2L(&C[4], &A[4],&B[4]);
}

void RESTA_FP6(Fp *C,Fp *A,Fp *B){
	RESTA_FP2(&C[0], &A[0],&B[0]);
	RESTA_FP2(&C[2], &A[2],&B[2]);
	RESTA_FP2(&C[4], &A[4],&B[4]);
}

void RESTA_FP6L(Mul *C,Mul *B){
	SUB512L(C[0],B[0]);
	SUB512L(C[1],B[1]);
	SUB512L(C[2],B[2]);
	SUB512L(C[3],B[3]);
	SUB512L(C[4],B[4]);
	SUB512L(C[5],B[5]);
}


void MULGAMA_FP6(Fp *C, Fp *A){
	MULU_FP2(&C[0], &A[4]);
	Fp_set(C[2],A[0]);
	Fp_set(C[3],A[1]);
	Fp_set(C[4],A[2]);
	Fp_set(C[5],A[3]);
}

void MULGAMA_FP6L(Mul *C, Mul *A){
	MULU_FP2L(&C[0], &A[4]);
	Mul_set(C[2],A[0]);
	Mul_set(C[3],A[1]);
	Mul_set(C[4],A[2]);
	Mul_set(C[5],A[3]);
}

#ifdef HAVE_NEON

void MULT_FP6(Fp *C, Fp *A, Fp *B){
	Mul r0[2], r1[2], r2[2], Au[2],Bu[2],Cu[2];
	Fp S0[2],S1[2];

	//C0
	SUMA_FP2(S0,&A[2],&A[4]);
	SUMA_FP2(S1,&B[2],&B[4]);
	MULT_FP2L_DUAL(Au,r1, S1,S0, &A[2], &B[2]);


	//C1
	SUMA_FP2(S0,&A[0],&A[2]);
	SUMA_FP2(S1,&B[0],&B[2]);
	RESTA_FP2L(Au,r1);
	MULT_FP2L_DUAL(Bu,r2, S1,S0, &A[4], &B[4]);
	RESTA_FP2L(Au,r2);
	MULU_FP2L(Cu, Au);

	//C2
	SUMA_FP2(S0,&A[0],&A[4]);
	SUMA_FP2(S1,&B[0],&B[4]);
	MULT_FP2L_DUAL(Au,r0,S1,S0, &A[0], &B[0]);
	SUMA_FP2L(Cu,Cu,r0);
	REDU_FP2(&C[0],Cu);

	RESTA_FP2L(Bu,r0);
	RESTA_FP2L(Bu,r1);
	MULU_FP2L(Cu, r2);
	SUMA_FP2L(Cu,Cu,Bu);
	REDU_FP2(&C[2],Cu);

	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r2);
	SUMA_FP2L(Cu,Au,r1);
	REDU_FP2(&C[4],Cu);
}

void MULT_FP6L(Mul *C, Fp *A, Fp *B){
	Mul r0[2], r1[2], r2[2], Au[2],Bu[2],Cu[2];
	Fp S0[2],S1[2];

	//C0
	SUMA_FP2(S0,&A[2],&A[4]);
	SUMA_FP2(S1,&B[2],&B[4]);
	MULT_FP2L_DUAL(Au,r1, S1,S0, &A[2], &B[2]);


	//C1
	SUMA_FP2(S0,&A[0],&A[2]);
	SUMA_FP2(S1,&B[0],&B[2]);
	RESTA_FP2L(Au,r1);
	MULT_FP2L_DUAL(Bu,r2, S1,S0, &A[4], &B[4]);
	RESTA_FP2L(Au,r2);
	MULU_FP2L(C, Au);

	//C2
	SUMA_FP2(S0,&A[0],&A[4]);
	SUMA_FP2(S1,&B[0],&B[4]);
	MULT_FP2L_DUAL(Au,r0,S1,S0, &A[0], &B[0]);
	SUMA_FP2L(C,C,r0);

	RESTA_FP2L(Bu,r0);
	RESTA_FP2L(Bu,r1);
	MULU_FP2L(Cu, r2);
	SUMA_FP2L(&C[2],Cu,Bu);

	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r2);
	SUMA_FP2L(&C[4],Au,r1);
}

void MULT_FP6_b0(Fp *C, Fp *A, Fp *b0){
	MULT_FP2_DUAL(&C[0],&A[0],b0, &C[2],&A[2],b0);
	MULT_FP2(&C[4],&A[4],b0);
}

void MULT_FP6_b0L(Mul *C, Fp *A, Fp *b0){
	MULT_FP2L_DUAL(&C[0],&C[2],&A[0],b0,&A[2],b0);
	MULT_FP2L(&C[4],&A[4],b0);
}

void MULT_FP6_b0_b1(Fp *C, Fp *A, Fp *b0, Fp *b1){
	Fp t0[2],t1[2],S1[2],S2[2];
	SUMA_FP2(S1,&A[2],&A[4]);

	MULT_FP2_DUAL(S2,S1,b1,t1,&A[2],b1);
	RESTA_FP2(S1,S2,t1);
	MULU_FP2(&C[0], S1);
	SUMA_FP2(S1,&A[0],&A[2]);
	SUMA_FP2(S2,b0,b1);
	MULT_FP2_DUAL(t0,&A[0],b0,&C[2],S1,S2);
	SUMA_FP2(&C[0],&C[0],t0);

	RESTA_FP2(&C[2],&C[2],t0);
	RESTA_FP2(&C[2],&C[2],t1);
	MULT_FP2(&C[4],&A[4],b0);
	SUMA_FP2(&C[4],&C[4],t1);
}

void MULT_FP6_b0_b1L(Mul *C, Fp *A, Fp *b0, Fp *b1){
	Fp s1[2],s2[2];
	Mul t0[2],t1[2],S1[2];

	MULT_FP2L_DUAL(t0,t1,&A[0],b0,&A[2],b1);
	SUMA_FP2(s1,&A[2],&A[4]);
	MULT_FP2L(S1,s1,b1);
	RESTA_FP2L(S1,t1);
	MULU_FP2L(C, S1);
	SUMA_FP2L(C,C,t0);

	SUMA_FP2(s1,&A[0],&A[2]);
	SUMA_FP2(s2,b0,b1);
	MULT_FP2L_DUAL(&C[2],&C[4],s1,s2,&A[4],b0);
	RESTA_FP2L(&C[2],t0);
	RESTA_FP2L(&C[2],t1);
	SUMA_FP2L(&C[4],&C[4],t1);
}

void CUAD_FP6(Fp *C, Fp *A){
	Fp c3[2],c4[2],c5[2], aux[2];

	MULT_FP2_DUAL(c4,&A[0],&A[2],c5,&A[2],&A[4]);

	SUMA_FP2(c4,c4,c4);

	CUAD_FP2(c3, &A[4]);
	MULU_FP2(&C[2], c3);
	SUMA_FP2(&C[2],&C[2],c4);
	RESTA_FP2(&C[4],c4,c3);

	CUAD_FP2(c3, &A[0]);
	RESTA_FP2(c4,&A[0],&A[2]);
	SUMA_FP2(c4,c4,&A[4]);

	SUMA_FP2(c5,c5,c5);
	CUAD_FP2(aux, c4);
	MULU_FP2(&C[0], c5);
	SUMA_FP2(&C[0],&C[0],c3);
	SUMA_FP2(&C[4],&C[4],aux);
	SUMA_FP2(&C[4],&C[4],c5);
	RESTA_FP2(&C[4],&C[4],c3);
}

void CUAD_FP6L(Mul *C, Fp *A){
	Mul c3[2],c4[2],c5[2], aux[2];
	Fp C4[2];
	MULT_FP2L_DUAL(c4,c5,&A[0],&A[2],&A[2],&A[4]);

	SUMA_FP2L(&C[4],c4,c4);
	CUAD_FP2L(c3, &A[4]);
	MULU_FP2L(&C[2], c3);
	SUMA_FP2L(&C[2],&C[2],&C[4]);
	RESTA_FP2L(&C[4],c3);

	CUAD_FP2L(c3, &A[0]);
	RESTA_FP2(C4,&A[0],&A[2]);
	SUMA_FP2(C4,C4,&A[4]);
	SUMA_FP2L(c5,c5,c5);
	CUAD_FP2L(aux, C4);
	MULU_FP2L(&C[0], c5);
	SUMA_FP2L(&C[0],&C[0],c3);
	SUMA_FP2L(&C[4],&C[4],aux);
	SUMA_FP2L(&C[4],&C[4],c5);
	RESTA_FP2L(&C[4],c3);
}

void INVERSO_FP6(Fp *C, Fp *A){
	Mul t0[2],t1[2],t2[2],t3[2],t4[2];
	Mul C0[2], C1[2], C2[2];
	Fp c0[2], c1[2], c2[2], c3[2],c4[2];

	CUAD_FP2L(t0,&A[0]);
	CUAD_FP2L(C2,&A[2]);
	CUAD_FP2L(t2,&A[4]);

	MULT_FP2L_DUAL(t3,t1,&A[0],&A[2],&A[4],&A[2]);
	MULU_FP2L(C0, t1);
	RESTA_FP2L(t0,C0);//C0
	MULU_FP2L(C1, t2);
	RESTA_FP2L(C1,t3);
	REDU_FP2(c0,t0);
	REDU_FP2(c1,C1);

	MULT_FP2L_DUAL(t4,t1,&A[0],&A[4],&A[4],c1);//Redu c1
	RESTA_FP2L(C2,t4);//C2
	REDU_FP2(c2,C2);
	MULU_FP2L(t2,t1);

	MULT_FP2L_DUAL(t3,t1,&A[0],c0,&A[2],c2);//Redu c0
	SUMA_FP2L(t3,t3,t2);
	MULU_FP2L(t2,t1);
	SUMA_FP2L(t3,t3,t2);//redu t6
	REDU_FP2(c3,t3);
	INVERT_FP2(c4, c3);

	MULT_FP2_DUAL(&C[0],c0,c4,&C[2],c1,c4);
	MULT_FP2(&C[4],c2,c4);
}


#else
void MULT_FP6(Fp *C, Fp *A, Fp *B){
	Mul r0[2], r1[2], r2[2], Au[2],Cu[2];
	Fp S0[2],S1[2];

	MULT_FP2L(r0, &A[0], &B[0]);
	MULT_FP2L(r1, &A[2], &B[2]);
	MULT_FP2L(r2, &A[4], &B[4]);

	//C0
	SUMA_FP2(S0,&A[2],&A[4]);
	SUMA_FP2(S1,&B[2],&B[4]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r1);
	RESTA_FP2L(Au,r2);
	MULU_FP2L(Cu, Au);
	SUMA_FP2L(Cu,Cu,r0);
	REDU_FP2(&C[0],Cu);

	//C1
	SUMA_FP2(S0,&A[0],&A[2]);
	SUMA_FP2(S1,&B[0],&B[2]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r1);
	MULU_FP2L(Cu, r2);
	SUMA_FP2L(Cu,Cu,Au);
	REDU_FP2(&C[2],Cu);

	//C2
	SUMA_FP2(S0,&A[0],&A[4]);
	SUMA_FP2(S1,&B[0],&B[4]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r2);
	SUMA_FP2L(Cu,Au,r1);
	REDU_FP2(&C[4],Cu);
}

void MULT_FP6L(Mul *C, Fp *A, Fp *B){
	Mul r0[2], r1[2], r2[2], Au[2],Cu[2];
	Fp S0[2],S1[2];

	MULT_FP2L(r0, &A[0], &B[0]);
	MULT_FP2L(r1, &A[2], &B[2]);
	MULT_FP2L(r2, &A[4], &B[4]);

	//C0
	SUMA_FP2(S0,&A[2],&A[4]);
	SUMA_FP2(S1,&B[2],&B[4]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r1);
	RESTA_FP2L(Au,r2);
	MULU_FP2L(Cu, Au);
	SUMA_FP2L(C,Cu,r0);

	//C1
	SUMA_FP2(S0,&A[0],&A[2]);
	SUMA_FP2(S1,&B[0],&B[2]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r1);
	MULU_FP2L(Cu, r2);
	SUMA_FP2L(&C[2],Cu,Au);

	//C2
	SUMA_FP2(S0,&A[0],&A[4]);
	SUMA_FP2(S1,&B[0],&B[4]);
	MULT_FP2L(Au,S1,S0);
	RESTA_FP2L(Au,r0);
	RESTA_FP2L(Au,r2);
	SUMA_FP2L(&C[4],Au,r1);
}

void MULT_FP6_b0(Fp *C, Fp *A, Fp *b0){

	MULT_FP2(&C[0],&A[0],b0);
	MULT_FP2(&C[2],&A[2],b0);
	MULT_FP2(&C[4],&A[4],b0);
}


void MULT_FP6_b0L(Mul *C, Fp *A, Fp *b0){
	MULT_FP2L(&C[0],&A[0],b0);
	MULT_FP2L(&C[2],&A[2],b0);
	MULT_FP2L(&C[4],&A[4],b0);
}

void MULT_FP6_b0_b1(Fp *C, Fp *A, Fp *b0, Fp *b1){
	Fp t0[2],t1[2],S1[2],S2[2];
	MULT_FP2(t0,&A[0],b0);
	MULT_FP2(t1,&A[2],b1);
	SUMA_FP2(S1,&A[2],&A[4]);
	MULT_FP2(S2,S1,b1);
	RESTA_FP2(S1,S2,t1);
	MULU_FP2(&C[0], S1);
	SUMA_FP2(&C[0],&C[0],t0);
	SUMA_FP2(S1,&A[0],&A[2]);
	SUMA_FP2(S2,b0,b1);
	MULT_FP2(&C[2],S1,S2);
	RESTA_FP2(&C[2],&C[2],t0);
	RESTA_FP2(&C[2],&C[2],t1);
	MULT_FP2(&C[4],&A[4],b0);
	SUMA_FP2(&C[4],&C[4],t1);
}

void MULT_FP6_b0_b1L(Mul *C, Fp *A, Fp *b0, Fp *b1){
	Fp s1[2],s2[2];
	Mul t0[2],t1[2],S1[2];

	MULT_FP2L(t0,&A[0],b0);
	MULT_FP2L(t1,&A[2],b1);
	SUMA_FP2(s1,&A[2],&A[4]);
	MULT_FP2L(S1,s1,b1);
	RESTA_FP2L(S1,t1);
	MULU_FP2L(C, S1);
	SUMA_FP2L(C,C,t0);

	SUMA_FP2(s1,&A[0],&A[2]);
	SUMA_FP2(s2,b0,b1);
	MULT_FP2L(&C[2],s1,s2);
	RESTA_FP2L(&C[2],t0);
	RESTA_FP2L(&C[2],t1);

	MULT_FP2L(&C[4],&A[4],b0);
	SUMA_FP2L(&C[4],&C[4],t1);
}

void CUAD_FP6(Fp *C, Fp *A){
	Fp c3[2],c4[2],c5[2], aux[2];
	MULT_FP2(c4,&A[0],&A[2]);
	SUMA_FP2(c4,c4,c4);
	CUAD_FP2(c5, &A[4]);
	MULU_FP2(&C[2], c5);
	SUMA_FP2(&C[2],&C[2],c4);
	RESTA_FP2(&C[4],c4,c5);
	CUAD_FP2(c3, &A[0]);
	RESTA_FP2(c4,&A[0],&A[2]);
	SUMA_FP2(c4,c4,&A[4]);
	MULT_FP2(c5,&A[2],&A[4]);
	SUMA_FP2(c5,c5,c5);
	CUAD_FP2(aux, c4);
	MULU_FP2(&C[0], c5);
	SUMA_FP2(&C[0],&C[0],c3);
	SUMA_FP2(&C[4],&C[4],aux);
	SUMA_FP2(&C[4],&C[4],c5);
	RESTA_FP2(&C[4],&C[4],c3);
}
void CUAD_FP6L(Mul *C, Fp *A){
	Mul c3[2],c4[2],c5[2], aux[2];
	Fp C4[2];
	MULT_FP2L(c4,&A[0],&A[2]);
	SUMA_FP2L(&C[4],c4,c4);
	CUAD_FP2L(c5, &A[4]);
	MULU_FP2L(&C[2], c5);
	SUMA_FP2L(&C[2],&C[2],&C[4]);
	RESTA_FP2L(&C[4],c5);

	CUAD_FP2L(c3, &A[0]);
	RESTA_FP2(C4,&A[0],&A[2]);
	SUMA_FP2(C4,C4,&A[4]);
	MULT_FP2L(c5,&A[2],&A[4]);
	SUMA_FP2L(c5,c5,c5);
	CUAD_FP2L(aux, C4);
	MULU_FP2L(&C[0], c5);
	SUMA_FP2L(&C[0],&C[0],c3);
	SUMA_FP2L(&C[4],&C[4],aux);
	SUMA_FP2L(&C[4],&C[4],c5);
	RESTA_FP2L(&C[4],c3);
}

void INVERSO_FP6(Fp *C, Fp *A){
	Mul t0[2],t1[2],t2[2],t3[2],t4[2];
	Mul C0[2], C1[2], C2[2];
	Fp c0[2], c1[2], c2[2], c3[2],c4[2];

	CUAD_FP2L(t0,&A[0]);
	CUAD_FP2L(C2,&A[2]);
	CUAD_FP2L(t2,&A[4]);
	MULT_FP2L(t3,&A[0],&A[2]);
	MULT_FP2L(t4,&A[0],&A[4]);
	MULT_FP2L(t1,&A[4],&A[2]);
	MULU_FP2L(C0, t1);
	RESTA_FP2L(t0,C0);//C0

	MULU_FP2L(C1, t2);
	RESTA_FP2L(C1,t3);
	RESTA_FP2L(C2,t4);//C2

	REDU_FP2(c0,t0);
	REDU_FP2(c1,C1);
	REDU_FP2(c2,C2);

	MULT_FP2L(t3,&A[0],c0);//Redu c0
	MULT_FP2L(t1,&A[4],c1);//Redu c1
	MULU_FP2L(t2,t1);
	SUMA_FP2L(t3,t3,t2);
	MULT_FP2L(t1,&A[2],c2);//redu c2
	MULU_FP2L(t2,t1);
	SUMA_FP2L(t3,t3,t2);//redu t6

	REDU_FP2(c3,t3);
	INVERT_FP2(c4, c3);
	MULT_FP2(&C[0],c0,c4);
	MULT_FP2(&C[2],c1,c4);
	MULT_FP2(&C[4],c2,c4);
}

#endif


void REDU_FP6(Fp *C, Mul *A){
	REDU_FP2(C,A);
	REDU_FP2(&C[2],&A[2]);
	REDU_FP2(&C[4],&A[4]);
}




//*************************************************************//
//***************       ***        *****  *****        ********//
//***************  ********  ****  ***    ***********  ********//
//***************    ******        *****  *****        ********//
//***************  ********  ***********  *****  **************//
//***************  ********  *********      ***        ********//
//*************************************************************//

void SUMA_FP12(Fp *C,Fp *A,Fp *B){
	SUMA_FP6(&C[0], &A[0],&B[0]);
	SUMA_FP6(&C[6], &A[6],&B[6]);
}

void RESTA_FP12(Fp *C,Fp *A,Fp *B){
	RESTA_FP6(&C[0], &A[0],&B[0]);
	RESTA_FP6(&C[6], &A[6],&B[6]);
}

void MULT_FP12(Fp *C, Fp *A, Fp *B){
	Mul r0[6],r1[6],Cu[6],Cg[6];
	Fp t0[6],t1[6], S1[6], S2[6];
	SUMA_FP6(S1, &A[0], &A[6]);
	SUMA_FP6(S2, &B[0], &B[6]);

	MULT_FP6L(Cu, S1,S2);
	MULT_FP6L(r0, &A[0],&B[0]);
	MULT_FP6L(r1, &A[6],&B[6]);
	RESTA_FP6L(Cu,r1);
	RESTA_FP6L(Cu,r0);
	REDU_FP6(&C[6],Cu);

	MULGAMA_FP6L(Cu, r1);
	SUMA_FP6L(Cu, Cu, r0);
	REDU_FP6(&C[0],Cu);

}


void SMULT_FP12(Fp *C, Fp *A, Fp *B){
	Mul r0[6],r1[6],Cu[6];
	Fp  t2[6], aux[6];

	SUMA_FP6(aux, &A[0], &A[6]);
	MULT_FP6_b0L(r0, &A[0], B);
	MULT_FP6_b0_b1L(r1, &A[6], &B[6],&B[8]);
	MULGAMA_FP6L(Cu, r1);
	SUMA_FP6L(Cu, Cu, r0);
	REDU_FP6(&C[0],Cu);

	SUMA_FP2(&t2[0],B,&B[6]);
	MULT_FP6_b0_b1L(Cu, aux, &t2[0],&B[8]);
	RESTA_FP6L(Cu,r0);
	RESTA_FP6L(Cu,r1);
	REDU_FP6(&C[6],Cu);
}

void SMULT_FP12A(Fp *C, Fp *A, Fp *B){
	Fp t0[6],t1[6], t2[6], aux[6];
	SUMA_FP6(aux, &A[0], &A[6]);

	MULT_FP6_b0(t0, &A[0], B);
	MULT_FP6_b0_b1(t1, &A[6], &B[6],&B[8]);
	MULGAMA_FP6(&C[0], t1);
	SUMA_FP6(&C[0], &C[0], t0);

	SUMA_FP2(&t2[0],B,&B[6]);
	MULT_FP6_b0_b1(&C[6], aux, &t2[0],&B[8]);
	RESTA_FP6(&C[6], &C[6],t0);
	RESTA_FP6(&C[6], &C[6],t1);
}

void MULT_FP12_b0(Fp *C, Fp *A, Fp b0){
	MULE_FP2(C,A, b0);
	MULE_FP2(&C[2],&A[2], b0);
	MULE_FP2(&C[4],&A[4], b0);
	MULE_FP2(&C[6],&A[6], b0);
	MULE_FP2(&C[8],&A[8], b0);
	MULE_FP2(&C[10],&A[10], b0);
}

void MULT_FP12_b0b1(Fp *C, Fp *A, Fp *b0, Fp *b1){
	Fp t0[6],t1[6], t2[6], aux[6];
	SUMA_FP6(aux, &A[0], &A[6]);

	MULT_FP6_b0(t0, &A[0], b0);
	MULT_FP6_b0_b1(t1, &A[6], &b1[0],&b1[2]);
	MULGAMA_FP6(&C[0], t1);
	SUMA_FP6(&C[0], &C[0], t0);

	SUMA_FP2(&t2[0],b0,&b1[0]);
	Fp_set(t2[2],b1[2]);
	Fp_set(t2[3],b1[3]);
	MULT_FP6_b0_b1(&C[6], aux, &t2[0],&t2[2]);
	RESTA_FP6(&C[6], &C[6],t0);
	RESTA_FP6(&C[6], &C[6],t1);
}

void CUAD_FP12A(Fp *C,Fp *A){
	Fp c0[6],c2[6],c3[6];
	RESTA_FP6(c0,&A[0], &A[6]);
	MULGAMA_FP6(c2, &A[6]);
	RESTA_FP6(c3,&A[0],c2);
	MULT_FP6(c2,&A[0], &A[6]);
	MULT_FP6(&C[0], c0,c3);
	SUMA_FP6(&C[0], &C[0],c2);
	SUMA_FP6(&C[6], c2,c2);
	MULGAMA_FP6(c0, c2);
	SUMA_FP6(&C[0], &C[0],c0);
}

void SCOM_FP12(Fp *C, Fp *A){
	Fp t0[4],t1[4],aux[2],C0[4], C1[4];
	CUAD_FP4(t0,&t1[2], &A[6], &A[4]);
	CUAD_FP4(&t0[2],aux, &A[2], &A[10]);
	MULU_FP2(t1,aux);

	SUMA_FP2(C0, t0, t0);
	SUMA_FP2(C0, C0, t0);
	SUMA_FP2(aux, &A[2], &A[2]);
	RESTA_FP2(&C[2],C0, aux);
	SUMA_FP2(&C0[2], &t0[2], &t0[2]);
	SUMA_FP2(&C0[2], &C0[2], &t0[2]);
	SUMA_FP2(aux, &A[4], &A[4]);
	RESTA_FP2(&C[4], &C0[2], aux);

	SUMA_FP2(C1, t1, t1);
	SUMA_FP2(C1, C1, t1);
	SUMA_FP2(C1, C1, &A[6]);
	SUMA_FP2(&C[6], &A[6], C1);
	SUMA_FP2(&C1[2], &t1[2], &t1[2]);
	SUMA_FP2(&C1[2], &C1[2], &t1[2]);
	SUMA_FP2(&C1[2], &C1[2], &A[10]);
	SUMA_FP2(&C[10], &A[10], &C1[2]);
}

void SDEC_FP12(Fp *C,Fp *A){
	int i;
	Fp t0[2],t1[2],t2[2],aux[2];
	for(i=0; i<12; i++)
		Fp_set(C[i], A[i]);

	if(zero(A[6])>0||zero(A[7])>0){
		CUAD_FP2(aux, &A[10]);
		MULU_FP2(t0, aux);
		CUAD_FP2(t1, &A[2]);
		SUMA_FP2(aux, t1, t1);
		SUMA_FP2(t1, t1, aux);
		SUMA_FP2(t0, t0, t1);
		SUMA_FP2(aux, &A[4], &A[4]);
		RESTA_FP2(t0, t0, aux);
		SUMA_FP2(t1, &A[6], &A[6]);
		SUMA_FP2(aux, t1, t1);
		INVERT_FP2(t1, aux);
		MULT_FP2(&C[8], t0, t1);
		CUAD_FP2(t0, &C[8]);
		SUMA_FP2(t0, t0, t0);
		MULT_FP2(t1, &A[6], &A[10]);
		MULT_FP2(t2, &A[4], &A[2]);
		SUMA_FP2(t0, t0, t1);
		SUMA_FP2(aux, t2, t2);
		SUMA_FP2(t2, t2, aux);
		RESTA_FP2(t0,t0, t2);
		MULU_FP2(C, t0);

	}else{
		MULT_FP2(t0, &A[2], &A[10]);
		SUMA_FP2(t0, t0, t0);
		INVERT_FP2(t1, &A[4]);
		MULT_FP2(&C[8], t0, t1);

		CUAD_FP2(t0, &A[8]);
		SUMA_FP2(t0, t0, t0);
		MULT_FP2(t2, &A[4], &A[2]);
		SUMA_FP2(aux, t2, t2);
		SUMA_FP2(t2, t2, aux);
		RESTA_FP2(t0,t0, t2);
		MULU_FP2(C, t0);
	}
	ADD256S(C[0],um);

}


void SDEC_A0_FP12(Fp *A){
	Fp t0[2],t1[2],t2[2],aux[2];
	CUAD_FP2(t0, &A[8]);
	SUMA_FP2(t0, t0, t0);
	if(zero(A[6])>0||zero(A[7])>0){
		MULT_FP2(t1, &A[6], &A[10]);
		SUMA_FP2(t0, t0, t1);
	}
	MULT_FP2(t2, &A[4], &A[2]);
	SUMA_FP2(aux, t2, t2);
	SUMA_FP2(t2, t2, aux);
	RESTA_FP2(t0,t0, t2);
	MULU_FP2(A, t0);
	ADD256S(A[0],um);

}

void SDEC_A1_FP12(Fp *A, Fp *inv){
	Fp t0[2],t1[2],t2[2],aux[2];
	if(zero(A[6])>0||zero(A[7])>0){
		CUAD_FP2(aux, &A[10]);
		MULU_FP2(t0, aux);
		CUAD_FP2(t1, &A[2]);
		SUMA_FP2(aux, t1, t1);
		SUMA_FP2(t1, t1, aux);
		SUMA_FP2(t0, t0, t1);
		SUMA_FP2(aux, &A[4], &A[4]);
		RESTA_FP2(&A[8], t0, aux);
		SUMA_FP2(t1, &A[6], &A[6]);
		SUMA_FP2(inv, t1, t1);

	}else{
		MULT_FP2(t0, &A[2], &A[10]);
		SUMA_FP2(&A[8], t0, t0);
		Fp_set(inv[0], A[4]);
		Fp_set(inv[1], A[5]);
	}
}

//Esto se puede hacer variable con Montgomery y una estructura 12
void SDEC3_FP12(Fp *A, Fp *B, Fp *C){
	Fp t0[2],t1[2],t2[2], aux[2];
	Fp inv[2], r0[2], r1[2];

	SDEC_A1_FP12(A, t0);
	SDEC_A1_FP12(B, t1);
	SDEC_A1_FP12(C, t2);

	MULT_FP2(r0, t1, t2); //b*c 	(1M)
	MULT_FP2(aux, r0, t0);	//a*b*c (1M)
	INVERT_FP2(inv, aux);

	MULT_FP2(aux, r0, inv); //=1/a 	(1M)
	MULT_FP2(&A[8], &A[8], aux);

	MULT_FP2(r1, t0, inv); //=1/bc	(1M)
	MULT_FP2(aux, r1, t2); //=1/b	(1M)
	MULT_FP2(&B[8], &B[8], aux);

	MULT_FP2(aux, r1, t1); //=1/c	(1M)
	MULT_FP2(&C[8], &C[8], aux);

	SDEC_A0_FP12(A);
	SDEC_A0_FP12(B);
	SDEC_A0_FP12(C);
}

void SDEC2_FP12(Fp *A, Fp *B){
	Fp t0[2],t1[2], aux[2];
	Fp inv[2], r0[2];

	SDEC_A1_FP12(A, t0);
	SDEC_A1_FP12(B, t1);

	MULT_FP2(r0, t1, t0); //a*b 	(1M)
	INVERT_FP2(inv, r0);

	MULT_FP2(aux, t1, inv); //=1/a 	(1M)
	MULT_FP2(&A[8], &A[8], aux);

	MULT_FP2(aux, t0, inv); //=1/b	(1M)
	MULT_FP2(&B[8], &B[8], aux);

	SDEC_A0_FP12(A);
	SDEC_A0_FP12(B);
}



void CUAD_FP12(Fp *C,Fp *A){
	Fp t0[6],t1[6],aux[2],C0[6], C1[6];
	CUAD_FP4(t0,&t1[2],A, &A[8]);
	CUAD_FP4(&t0[2],&t1[4], &A[6], &A[4]);
	CUAD_FP4(&t0[4],aux, &A[2], &A[10]);
	MULU_FP2(t1,aux);

	RESTA_FP2(C0, t0, A);
	SUMA_FP2(C0, C0, C0);
	SUMA_FP2(C, C0, t0);

	RESTA_FP2(&C0[2], &t0[2], &A[2]);
	SUMA_FP2(&C0[2], &C0[2], &C0[2]);
	SUMA_FP2(&C[2], &C0[2], &t0[2]);

	RESTA_FP2(&C0[4], &t0[4], &A[4]);
	SUMA_FP2(&C0[4], &C0[4], &C0[4]);
	SUMA_FP2(&C[4], &C0[4], &t0[4]);

	SUMA_FP2(C1, t1, &A[6]);
	SUMA_FP2(C1, C1, C1);
	SUMA_FP2(&C[6], t1, C1);

	SUMA_FP2(&C1[2], &t1[2], &A[8]);
	SUMA_FP2(&C1[2], &C1[2], &C1[2]);
	SUMA_FP2(&C[8], &t1[2], &C1[2]);

	SUMA_FP2(&C1[4], &t1[4], &A[10]);
	SUMA_FP2(&C1[4], &C1[4], &C1[4]);
	SUMA_FP2(&C[10], &t1[4], &C1[4]);

}

void INVERSO_FP12(Fp *C,Fp *A){
	Mul t0[6],t1[6], aux2[6];
	Fp r0[6], r1[6], aux[6];
	CUAD_FP6L(t0, &A[0]);
	CUAD_FP6L(t1, &A[6]);
	MULGAMA_FP6L(aux2, t1);
	RESTA_FP6L(t0,aux2);
	REDU_FP6(r0,t0);
	INVERSO_FP6(r1, r0);
	MULT_FP6(&C[0], &A[0],r1);
	MULT_FP6(aux, &A[6],r1);
	SUB256(C[6],p,aux[0]);
	SUB256(C[7],p,aux[1]);
	SUB256(C[8],p,aux[2]);
	SUB256(C[9],p,aux[3]);
	SUB256(C[10],p,aux[4]);
	SUB256(C[11],p,aux[5]);
}


void CONJUGADO_FP12(Fp *C, Fp *A){//*Tener cuidado
	Fp_set(C[0],A[0]);
	Fp_set(C[1],A[1]);
	Fp_set(C[2],A[2]);
	Fp_set(C[3],A[3]);
	Fp_set(C[4],A[4]);
	Fp_set(C[5],A[5]);
	SUB256(C[6], p, A[6]);
	SUB256(C[7], p, A[7]);
	SUB256(C[8], p, A[8]);
	SUB256(C[9], p, A[9]);
	SUB256(C[10], p, A[10]);
	SUB256(C[11], p, A[11]);
}

void CONJUGADO_FP12A(Fp *C, Fp *A){
	Fp D[6];
	Fp_set(D[0],A[6]);
	Fp_set(D[1],A[7]);
	Fp_set(D[2],A[8]);
	Fp_set(D[3],A[9]);
	Fp_set(D[4],A[10]);
	Fp_set(D[5],A[11]);
	Fp_set(C[0],A[0]);
	Fp_set(C[1],A[1]);
	Fp_set(C[2],A[2]);
	Fp_set(C[3],A[3]);
	Fp_set(C[4],A[4]);
	Fp_set(C[5],A[5]);
	SUB256(C[6], p, D[0]);
	SUB256(C[7], p, D[1]);
	SUB256(C[8], p, D[2]);
	SUB256(C[9], p, D[3]);
	SUB256(C[10], p, D[4]);
	SUB256(C[11], p, D[5]);
}


void FROBENIUS_P(Fp *C,Fp *A){
	Fp t2[2],t3[2],t4[2],t5[2],t6[2];
	CONJUGADO_FP2(&C[0], &A[0]);//Cuidado
	CONJUGADO_FP2(t2, &A[6]);
	CONJUGADO_FP2(t3, &A[2]);
	CONJUGADO_FP2(t4, &A[8]);
	CONJUGADO_FP2(t5, &A[4]);
	CONJUGADO_FP2(t6, &A[10]);

	MULT_FP2(&C[6], t2, Y1[0]);
	MULEI_FP2(&C[2], t3, Y1[1][1]);
	SMULT_FP2(&C[8], t4, Y1[2]);
	MULE_FP2(&C[4], t5, Y1[3][0]);
	MULT_FP2(&C[10], t6,Y1[4]);
}



void FROBENIUS_P2(Fp *C,Fp *A){
	Fp_set(C[0],A[0]);
	Fp_set(C[1],A[1]);
	MULE_FP2(&C[6], &A[6], Y2[0]);
	MULE_FP2(&C[2], &A[2], Y2[1]);
	NEGATIVO_FP2(&C[8], &A[8]);
	MULE_FP2(&C[4], &A[4], Y2[3]);
	MULE_FP2(&C[10],&A[10],Y2[4]);
}

void FROBENIUS_P3(Fp *C,Fp *A){
	Fp t2[2],t3[2],t4[2],t5[2],t6[2];

	Fp_set(C[3],A[2]);
	Fp_set(C[2],A[3]);

	CONJUGADO_FP2(&C[0], &A[0]); //cuidado
	CONJUGADO_FP2(t2, &A[6]);
	CONJUGADO_FP2(t4, &A[8]);
	CONJUGADO_FP2(t5, &A[4]);
	CONJUGADO_FP2(t6, &A[10]);
	MULT_FP2(&C[6], t2, Y3[0]);

	SMULT_FP2(&C[8], t4, Y3[2]);
	NEGATIVO_FP2(&C[4], t5);
	MULT_FP2(&C[10],t6, Y3[4]);
}

void EXPONENCIAR_FP12(Fp *C,Fp *A, int *e, int L){
	int i, j;
	Fp cA[12];
	CONJUGADO_FP12(cA, A);
	for(i=0; i<12; i++){
		Fp_set(C[i],A[i]);
	}
	for(i=L-2; i>=0; i--){
		CUAD_FP12(C,C);
		if(e[i]!=0){
			if(e[i]>0){
				MULT_FP12(C,C,A);
			}
			else{
				MULT_FP12(C,C,cA);
			}
		}
	}
}

void SEXPONENCIAR_FP12(Fp *C,Fp *A, int *e, int L){
	int i, j, k;
	Fp cA[12];
	Fp P[2][12];
	for(i=0; i<12; i++){
		Fp_set(C[i],A[i]);
	}
	j=0;
	for(i=1; i<L; i++){
		SCOM_FP12(C,C);
		if(e[i]!=0){
			for(k=0; k<12; k++){
				Fp_set(P[j][k],C[k]);
			}
			j++;
		}
	}
	SDEC2_FP12(C,P[0]);
	MULT_FP12(C,C,P[0]);
	MULT_FP12(cA,A,C);
	CONJUGADO_FP12(C, cA);
}


void FINAL_EXPONENTIATIONA(Fp *C,Fp *A){
	int i;
	int t[63];
	Fp F1[12], F2[12], F[12], FT1[12], FT2[12], FT3[12], FP1[12], FP2[12], FP3[12];
	Fp Y[7][12], T0[12], T1[12], AUX[12], AUX2[12];
	for(i=0; i<63; i++)	t[i]=0;
	t[62]=0;
	t[54]=-1;
	t[44]=1;
	CONJUGADO_FP12(F1,A);
	INVERSO_FP12(F2, A);
	MULT_FP12(AUX, F1, F2);
	FROBENIUS_P2(FP2, AUX);
	MULT_FP12(F, FP2, AUX);

	SEXPONENCIAR_FP12(FT1, F, t, 63);
	SEXPONENCIAR_FP12(FT2, FT1, t, 63);
	SEXPONENCIAR_FP12(FT3, FT2, t, 63);

	FROBENIUS_P (FP1, F);
	FROBENIUS_P2(FP2, F);
	FROBENIUS_P3(FP3, F);
	MULT_FP12(AUX, FP1, FP2);
	MULT_FP12(Y[0], AUX, FP3);
	CONJUGADO_FP12(Y[1],F);
	FROBENIUS_P2(Y[2], FT2);
	FROBENIUS_P (AUX, FT1);
	CONJUGADO_FP12(Y[3],AUX);
	FROBENIUS_P (Y[4], FT2);
	MULT_FP12 (AUX,Y[4], FT1);
	CONJUGADO_FP12(Y[4],AUX);
	CONJUGADO_FP12(Y[5],FT2);
	FROBENIUS_P (Y[6], FT3);
	MULT_FP12 (AUX,Y[6], FT3);
	CONJUGADO_FP12(Y[6],AUX);
	CUAD_FP12(T0, Y[6]);
	MULT_FP12 (AUX,T0, Y[4]);
	MULT_FP12 (T0,AUX, Y[5]);
	MULT_FP12 (AUX,Y[3], Y[5]);
	MULT_FP12 (T1,AUX, T0);
	MULT_FP12 (AUX2,T0, Y[2]);
	CUAD_FP12(AUX, T1);
	MULT_FP12 (T1,AUX, AUX2);
	CUAD_FP12(AUX, T1);
	MULT_FP12 (T0,AUX, Y[1]);
	MULT_FP12 (T1,AUX, Y[0]);
	CUAD_FP12(AUX, T0);
	MULT_FP12 (C,T1, AUX);
}

void FINAL_EXPONENTIATION(Fp *C,Fp *A){
	int i;
	int t[63];
	Fp F1[12], F2[12], F[12], FP[12], FP2[12], FP3[12];
	Fp FT[12], F2T[12], F2TI[12], F3T[12], F6T[12], F6T2[12], F6T3[12], F12T3[12];
	Fp a[12], b[12], g[12], AUX[12], TMP[12];
	for(i=0; i<63; i++)	t[i]=0;
	t[62]=1;
	t[55]=1;
	t[0]=1;
	CONJUGADO_FP12(F1,A);
	INVERSO_FP12(F2, A);
	MULT_FP12(AUX, F1, F2);
	FROBENIUS_P2(FP2, AUX);
	MULT_FP12(F, FP2, AUX);
	SEXPONENCIAR_FP12(FT, F, t, 63);
	CUAD_FP12(F2T, FT);
	MULT_FP12(F3T, F2T, FT);
	CUAD_FP12(F6T, F3T);
	SEXPONENCIAR_FP12(F6T2, F6T, t, 63);
	SEXPONENCIAR_FP12(F6T3, F6T2, t, 63);
	CUAD_FP12(F12T3, F6T3);
	MULT_FP12(AUX, F12T3, F6T2);
	MULT_FP12(a, AUX, F6T);
	CONJUGADO_FP12(F2TI,F2T);
	MULT_FP12(b, F2TI, a);
	MULT_FP12(AUX, a, F6T2);
	MULT_FP12(g, AUX, F);
	FROBENIUS_P (FP, b);
	MULT_FP12(AUX, g, FP);
	FROBENIUS_P2(FP2, a);
	MULT_FP12(g, FP2, AUX);
	CONJUGADO_FP12(AUX,F);
	MULT_FP12(TMP, b, AUX);
	FROBENIUS_P3(FP3, TMP);
	MULT_FP12(C, g, FP3);
}

void Comprobacion(Fp *C,Fp *A){
	int i;
	int t[63];
	Fp FT[12], F2T[12], F3T[12], F6T[12], F6T2[12], F6T3[12], F12T3[12];
	Fp AUX[12];
	for(i=0; i<63; i++)	t[i]=0;
	t[62]=1;
	t[54]=-1;
	t[44]=1;
	EXPONENCIAR_FP12(FT, A, t, 63);
	CUAD_FP12(F2T, FT);
	MULT_FP12(F3T, F2T, FT);
	CUAD_FP12(F6T, F3T);
	EXPONENCIAR_FP12(F6T2, F6T, t, 63);
	EXPONENCIAR_FP12(F6T3, F6T2, t, 63);
	CUAD_FP12(F12T3, F6T3);
	MULT_FP12(AUX, F12T3, F6T2);
	MULT_FP12(C, AUX, F2T);
}

int comparaFpk(Fp *A, Fp *B, int n){
	int i,m=0;
	for(i=0;i<n; i++){
		m+=abs(comparativo(A[i], B[i],8));
	}
	if(m==0) return 0;
	else return 1;
}


void Fpk_init(Fp *num, int n){
	int i;
	for(i=0; i<n; i++)
		Fp_init(num[i]);
}

void Fpk_rand(Fp *n, int N){
	int i;
	for(i=0; i<N; i++){
		Fp_setD(n[i], rand()&0x1FFFFFFF,rand(),rand(),rand(),rand(),rand(),rand(),rand());
	}
}

void Fpk_set(Fp *C, Fp *A, int N){
	int i;
	for(i=0; i<N; i++){
		Fp_set(C[i], A[i]);
	}
}
