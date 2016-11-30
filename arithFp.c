/*
arithFp.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include <stdio.h>
#ifdef IS_ANDROID
#include <android/log.h>
#define DEBUG_TAG "debug_tag"
#endif

#include <stdlib.h>
#include "assembly.h"
#include "Domain.h"

char  szLogThis[500];

void logC(){
#ifdef IS_ANDROID
__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "LC: [%s]", szLogThis);
#else
	printf("LC: [%s]", szLogThis);
#endif
}


void Fp_print(uint32_t *A){

	 sprintf(szLogThis,"%08x%08x%08x%08x%08x%08x%08x%08x", A[7], A[6], A[5],A[4],A[3], A[2], A[1],A[0]); logC();
}

void Fp_printN(uint32_t *A, int n){
	int i, N=n*8;
	for(i=0; i<N; i+=8){
	 sprintf(szLogThis,"%08x%08x%08x%08x%08x%08x%08x%08x", A[i+7], A[i+6], A[i+5],A[i+4],A[i+3], A[i+2], A[i+1],A[i+0]); logC();
	}
}

#define alg16 __attribute__ ((aligned(16)))


int comparativo(uint32_t *A, uint32_t *B, int tam){
	int i;
	for(i=tam-1; i>=0; i--){
		if(A[i]<B[i]) return -1;
		if(A[i]>B[i]) return 1;
	}
	return 0;
}


void ADD256(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	ADD256S(res, B);
}


void SUB256(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	SUB256S(res, B);
}

void ADD512L(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	COPY(&res[8],&A[8]);
	ADD512(res,B);
	if(res[15]>p[7]){
		SUB256S(&res[8],p);
	}
}

void ADD256MOD(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	ADD256S(res, B);
	if(res[7]<p[7]) return;
	SUB256S(res,p);
}


void SUB256MOD(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	res[8]=1;
	SUB256C(res,B);
	if(res[8]==1){
		return;
	}
	ADD256S(res,p);
}


void SUB512A(uint32_t *res, uint32_t *A, uint32_t *B){
	uint32_t c1=1, c2=1;
	COPY(res,A);
	COPY(&res[8],&A[8]);
	SUB512(res,B);
}

void SUB512L(uint32_t *res, uint32_t *B){
	res[16]=1;
	SUB512C(res,B);
	if(res[16]==0){
		ADD256S(&res[8],p);
	}
}

void SUB512LE(uint32_t *res, uint32_t *A, uint32_t *B){
	COPY(res,A);
	COPY(&res[8],&A[8]);
	res[16]=1;
	SUB512C(res,B);
	if(res[16]==0){
		ADD256S(&res[8],p);
	}
}


uint32_t zero(uint32_t *A){
	if(A[0]==0&&A[1]==0&&A[2]==0&&A[3]==0&&A[4]==0&&A[5]==0&&A[6]==0&&A[7]==0)
		return 0;
	return 1;
}

void MUL256N(uint32_t *T, uint32_t *A, uint32_t *B, int N){
	int i;
	uint32_t C,C1,S,s;
	for(i=0; i<N; i++){
		if(A[i]>0){
		C=0;
		MUL32A1(T[i],C,A[i],B[0],T[i],S);
		MUL32A1(S,C1,A[i],B[1],C,s);
		ADD_64HL(T[i+1], C1, S);
		MUL32A1(S,C,A[i],B[2],C1,s);
		ADD_64HL(T[i+2], C, S);
		MUL32A1(S,C1,A[i],B[3],C,s);
		ADD_64HL(T[i+3], C1, S);
		MUL32A1(S,C,A[i],B[4],C1,s);
		ADD_64HL(T[i+4], C, S);
		MUL32A1(S,C1,A[i],B[5],C,s);
		ADD_64HL(T[i+5], C1, S);
		MUL32A1(S,C,A[i],B[6],C1,s);
		ADD_64HL(T[i+6], C, S);
		MUL32A1(S,C1,A[i],B[7],C,s);
		ADD_64HL(T[i+7], C1, S);
		T[i+8]=C1;
		}
	}
}

void MUL256(uint32_t *T, uint32_t *A, uint32_t *B){
	uint32_t s,C0,C1,S0,S1,c1,c2,c3=0;
	uint32_t C[]={A[0],A[1],A[2],A[3],0};
	uint32_t D[]={B[0],B[1],B[2],B[3],0};
	uint32_t R[]={0,0,0,0,0,0,0,0,0};

	ADD_128C(C,&A[4]);
	ADD_128C(D,&B[4]);

#ifdef HAVE_NEON
	MUL128DUAL(T,&T[8],A,B);
#else
	MUL128_32(T,B, A[0]);
	MUL128_32ADD(&T[1],B, A[1]);
	MUL128_32ADD(&T[2],B, A[2]);
	MUL128_32ADD(&T[3],B, A[3]);

	MUL128_32(&T[8],&B[4], A[4]);
	MUL128_32ADD(&T[9],&B[4], A[5]);
	MUL128_32ADD(&T[10],&B[4], A[6]);
	MUL128_32ADD(&T[11],&B[4], A[7]);
#endif

	//MEDIA
	MUL128_32(R,C, D[0]);
	MUL128_32ADD(&R[1],C, D[1]);
	MUL128_32ADD(&R[2],C, D[2]);
	MUL128_32ADD(&R[3],C, D[3]);

	if(C[4]!=0){
		ADD_128C(&R[4],D);
	}
	if(D[4]!=0){
		ADD_128C(&R[4],C);
	}
	if(C[4]!=0&&D[4]!=0)R[8]++;
	SUB256C(R,T);
	SUB256C(R,&T[8]);

	ADD256C(&T[4],R);
	T[12]=T[12];
}


void shifL1(uint32_t *T, uint32_t *A){
	uint32_t t[7];
	LSR31(t[0],A[0]);
	LSR31(t[1],A[1]);
	LSR31(t[2],A[2]);
	LSR31(t[3],A[3]);
	LSR31(t[4],A[4]);
	LSR31(t[5],A[5]);
	LSR31(t[6],A[6]);

	LSL1(T[0],A[0]);
	LSL1(T[1],A[1]);
	LSL1(T[2],A[2]);
	LSL1(T[3],A[3]);
	LSL1(T[4],A[4]);
	LSL1(T[5],A[5]);
	LSL1(T[6],A[6]);
	LSL1(T[7],A[7]);

	T[1]=t[0]|T[1];
	T[2]=t[1]|T[2];
	T[3]=t[2]|T[3];
	T[4]=t[3]|T[4];
	T[5]=t[4]|T[5];
	T[6]=t[5]|T[6];
	T[7]=t[6]|T[7];
}

void shifR1(uint32_t *T, uint32_t *A){
	uint32_t t[7];

	LSL31(t[0],A[1]);
	LSL31(t[1],A[2]);
	LSL31(t[2],A[3]);
	LSL31(t[3],A[4]);
	LSL31(t[4],A[5]);
	LSL31(t[5],A[6]);
	LSL31(t[6],A[7]);

	LSR1(T[0],A[0]);
	LSR1(T[1],A[1]);
	LSR1(T[2],A[2]);
	LSR1(T[3],A[3]);
	LSR1(T[4],A[4]);
	LSR1(T[5],A[5]);
	LSR1(T[6],A[6]);
	LSR1(T[7],A[7]);

	T[0]=t[0]|T[0];
	T[1]=t[1]|T[1];
	T[2]=t[2]|T[2];
	T[3]=t[3]|T[3];
	T[4]=t[4]|T[4];
	T[5]=t[5]|T[5];
	T[6]=t[6]|T[6];

	T[8]=A[8];
	if(A[8]==0)return;
	if((A[8]&1)!=0) T[7]|0x80000000;
	T[8]=A[8]>>1;
}
void shifR3(uint32_t *T, uint32_t *A){
	uint32_t t[7];

	LSL29(t[0],A[1]);
	LSL29(t[1],A[2]);
	LSL29(t[2],A[3]);
	LSL29(t[3],A[4]);
	LSL29(t[4],A[5]);
	LSL29(t[5],A[6]);
	LSL29(t[6],A[7]);

	LSR3(T[0],A[0]);
	LSR3(T[1],A[1]);
	LSR3(T[2],A[2]);
	LSR3(T[3],A[3]);
	LSR3(T[4],A[4]);
	LSR3(T[5],A[5]);
	LSR3(T[6],A[6]);
	LSR3(T[7],A[7]);

	T[0]=t[0]|T[0];
	T[1]=t[1]|T[1];
	T[2]=t[2]|T[2];
	T[3]=t[3]|T[3];
	T[4]=t[4]|T[4];
	T[5]=t[5]|T[5];
	T[6]=t[6]|T[6];

	T[8]=A[8];
	if(A[8]==0)return;
	if((A[8]&1)!=0) T[7]|0x80000000;
	T[8]=A[8]>>3;
}


void REDBARRET(uint32_t *T, uint32_t *X){
	int i, flag=1;
	uint32_t tmp[16];
	uint32_t tmp2[16];
	uint32_t Mxmu[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t Q[9], R1[9], R2[9];
	uint32_t QP[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t c,aux[4];
	uint32_t Xh[]={X[7], X[8], X[9], X[10], X[11], X[12], X[13], X[14],X[15],0};

	//MULTIPLICACION 9X9
	MUL256N(Mxmu, Xh, mu, 9);

	aux[0]=Mxmu[16];
	aux[1]=Mxmu[17];
	MUL256N(&Mxmu[8], &mu[8], Xh, 1);
	aux[2]=Mxmu[16];
	aux[3]=Mxmu[17];

	MUL32(Mxmu[16], Mxmu[17], X[15],mu[8]);
	ADD_64L(c,Mxmu[16], Mxmu[17], aux[0], aux[1] );
	ADD_64L(c,Mxmu[16], Mxmu[17], aux[2], aux[3] );

   for(i=0; i<=8; i++){
	   Q[i]=Mxmu[9+i];
   }

  MUL256N(QP, Q, p, 9);

  for(i=0; i<=8; i++){
	   R1[i]=QP[i];
	   T[i]=X[i];
  }

  uint32_t c1=1, c2=1;
  SUB_64L(c1, T[0], T[1], R1[0], R1[1]);
  SUB_64CL(c1, c2, T[2], T[3],R1[2], R1[3]);
  c1=1;
  SUB_64CL(c2, c1,T[4], T[5], R1[4], R1[5]);
  c2=1;
  SUB_64CL(c1, c2,T[6], T[7], R1[6], R1[7]);
  c1=1;
  SUB_32CL(c2,c1, T[8], R1[8]);

  while(flag==1){
	  if(T[8]>0){
		  c1=SUB256S(T,p);
		  if(c1==1) T[8]=0;
	  }
	  else{
		  if(comparativo(T,p,8)>=0){
			  SUB256S(T,p);
		  }
		  else{
			  flag=0;
		  }
	  }
  }

}

void ConvertMont(uint32_t *T, uint32_t *A){
	uint32_t ap[]={0,0,0,0,0,0,0,0,A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],0};
	REDBARRET(T,ap);
}


void MULMONGS(uint32_t *t, uint32_t *A, uint32_t *B){
	int i;
	uint32_t C,C1,S,m;
	uint32_t T[]={0,0,0,0,0,0,0,0,0,0};
	for(i=0; i<8; i++){
		if(A[i]>0){
			MUL32A1(T[0],C,A[i],B[0],T[0],S);
			MUL32A2(T[1],C1,A[i],B[1],T[1],C,S);
			MUL32A2(T[2],C,A[i],B[2],T[2],C1,S);
			MUL32A2(T[3],C1,A[i],B[3],T[3],C,S);
			MUL32A2(T[4],C,A[i],B[4],T[4],C1,S);
			MUL32A2(T[5],C1,A[i],B[5],T[5],C,S);
			MUL32A2(T[6],C,A[i],B[6],T[6],C1,S);
			MUL32A2(T[7],C1,A[i],B[7],T[7],C,S);
			C=0;
			ADD_64HL(T[8], C, C1);
		}

		MUL32S(m, T[0], pi[0]);
		MUL32A1(S,C1,p[0],m,T[0],S);
		MUL32A2(T[0],C,m,p[1],C1,T[1],S);
		MUL32A2(T[1],C1,m,p[2],C,T[2],S);
		MUL32A2(T[2],C,m,p[3],C1,T[3],S);
		MUL32A2(T[3],C1,m,p[4],C,T[4],S);
		MUL32A2(T[4],C,m,p[5],C1,T[5],S);
		MUL32A2(T[5],C1,m,p[6],C,T[6],S);
		MUL32A2(T[6],C,m,p[7],C1,T[7],S);
		C1=0;
		ADD_64HL(C, C1, T[8]);
		T[7]=C;
		T[8]=C1;
	}
	t[0]=T[0];
	t[1]=T[1];
	t[2]=T[2];
	t[3]=T[3];
	t[4]=T[4];
	t[5]=T[5];
	t[6]=T[6];
	t[7]=T[7];
	while(t[7]>p[7]){
			SUB256S(t,p);
	}
}


void MULMONG1(uint32_t *T, uint32_t *A){
	int i,j;
	uint32_t C,C1,S,m;
	uint32_t c1=0,c2=1;
	uint32_t t[]={A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],0,0,0,0,0,0,0,0};
	for(i=0; i<8; i++){
		C=0;
		MUL32S(m, t[i], pi[0]);
		if(m>0){
		MUL32(S,C,m,p[0]);
		ADD_64HL(t[i], C, S);

		MUL32(S,C1,m,p[1]);
		ADD_64HL(S, C1, C);
		ADD_64HL(t[i+1], C1, S);

		MUL32(S,C,m,p[2]);
		ADD_64HL(S, C, C1);
		ADD_64HL(t[i+2], C, S);

		MUL32(S,C1,m,p[3]);
		ADD_64HL(S, C1, C);
		ADD_64HL(t[i+3], C1, S);

		MUL32(S,C,m,p[4]);
		ADD_64HL(S, C, C1);
		ADD_64HL(t[i+4], C, S);

		MUL32(S,C1,m,p[5]);
		ADD_64HL(S, C1, C);
		ADD_64HL(t[i+5], C1, S);

		MUL32(S,C,m,p[6]);
		ADD_64HL(S, C, C1);
		ADD_64HL(t[i+6], C, S);

		MUL32(S,C1,m,p[7]);
		ADD_64HL(S, C1, C);
		ADD_64HL(t[i+7], C1, S);

		j=8;c1=0;
		ADD_32L(c1,t[i+j],C1);
		while(c1!=0){
			c1=0; j++;
			ADD_32L(c1,t[i+j],C1);
		}
		}
	}
	COPY(T,&t[8]);

	while(comparativo(T,p,8)>=0){
		SUB256S(T,p);
	}

}


void MOD512(uint32_t *T, uint32_t *t){
	int i,j;
	uint32_t m;
	for(i=0; i<8; i++){
		MUL32S(m, t[i], pi[0]);
		MUL256_32ADD(&t[i],p,m);
	}
	COPY(T,&t[8]);

	if(T[7]>p[7])
		SUB256S(T,p);
}
#ifdef HAVE_NEON
void MULMONG(uint32_t *T, uint32_t *A, uint32_t *B){
	uint32_t t[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	MUL256(t,B, A);
	MOD512(T,t);
}
#else
void MULMONG(uint32_t *t, uint32_t *A, uint32_t *B){
	int i;
	uint32_t C,C1,S,m;
	uint32_t T[]={0,0,0,0,0,0,0,0,0,0};
	for(i=0; i<8; i++){
		if(A[i]>0){
			MUL32A1(T[0],C,A[i],B[0],T[0],S);
			MUL32A2(T[1],C1,A[i],B[1],T[1],C,S);
			MUL32A2(T[2],C,A[i],B[2],T[2],C1,S);
			MUL32A2(T[3],C1,A[i],B[3],T[3],C,S);
			MUL32A2(T[4],C,A[i],B[4],T[4],C1,S);
			MUL32A2(T[5],C1,A[i],B[5],T[5],C,S);
			MUL32A2(T[6],C,A[i],B[6],T[6],C1,S);
			MUL32A2(T[7],C1,A[i],B[7],T[7],C,S);
			C=0;
			ADD_64HL(T[8], C, C1);
		}

		MUL32S(m, T[0], pi[0]);
		MUL32A1(S,C1,p[0],m,T[0],S);
		MUL32A2(T[0],C,m,p[1],C1,T[1],S);
		MUL32A2(T[1],C1,m,p[2],C,T[2],S);
		MUL32A2(T[2],C,m,p[3],C1,T[3],S);
		MUL32A2(T[3],C1,m,p[4],C,T[4],S);
		MUL32A2(T[4],C,m,p[5],C1,T[5],S);
		MUL32A2(T[5],C1,m,p[6],C,T[6],S);
		MUL32A2(T[6],C,m,p[7],C1,T[7],S);
		C1=0;
		ADD_64HL(C, C1, T[8]);
		T[7]=C;
		T[8]=C1;
	}
	t[0]=T[0];
	t[1]=T[1];
	t[2]=T[2];
	t[3]=T[3];
	t[4]=T[4];
	t[5]=T[5];
	t[6]=T[6];
	t[7]=T[7];
	while(t[7]>p[7]){
			SUB256S(t,p);
	}
}
#endif

int partialMontInv(uint32_t *A, uint32_t *B, uint32_t *X){
	int i;
	uint32_t u[]={A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],0};
	uint32_t v[]={B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7],0};
	uint32_t x1[]={1,0,0,0,0,0,0,0,0};
	uint32_t x2[]={0,0,0,0,0,0,0,0,0};
	int k=0;
	if(zero(A)==0) return k;
	while(v[7]>0&&x1[0]<0x7FFFFFFF&&x2[0]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_256(v);
			LSL1(x1[0],x1[0]);
		}
		else if((u[0]&1)==0){
			shifR1_256(u);
			LSL1(x2[0],x2[0]);
		}
		else if(comparativo(v,u,8)>=0){
			SUB256S(v,u);
			shifR1_256(v);
			ADD_32(x2[0],x1[0]);
			LSL1(x1[0],x1[0]);
		}else{
			SUB256S(u,v);
			shifR1_256(u);
			ADD_32(x1[0],x2[0]);
			LSL1(x2[0],x2[0]);
		}
		k++;
	}
	while(v[7]>0||u[7]>0){
		if((v[0]&1)==0){
			shifR1_256(v);
			shifL1_64(x1);
		}
		else if((u[0]&1)==0){
			shifR1_256(u);
			shifL1_64(x2);
		}
		else if(comparativo(v,u,8)>=0){
			SUB256S(v,u);
			shifR1_256(v);
			ADD_64(x2,x1);
			shifL1_64(x1);
		}else{
			SUB256S(u,v);
			shifR1_256(u);
			ADD_64(x1,x2);
			shifL1_64(x2);
		}
		k++;
	}
	while(v[6]>0&&x1[1]<0x7FFFFFFF&&x2[1]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_224(v);
			shifL1_64(x1);
		}
		else if((u[0]&1)==0){
			shifR1_224(u);
			shifL1_64(x2);
		}
		else if(comparativo(v,u,7)>=0){
			SUB_224(v,u);
			shifR1_224(v);
			ADD_64(x2,x1);
			shifL1_64(x1);
		}else{
			SUB_224(u,v);
			shifR1_224(u);
			ADD_64(x1,x2);
			shifL1_64(x2);
		}
		k++;
	}
	while(v[6]>0||u[6]>0){
		if((v[0]&1)==0){
			shifR1_224(v);
			shifL1_96(x1);
		}
		else if((u[0]&1)==0){
			shifR1_224(u);
			shifL1_96(x2);
		}
		else if(comparativo(v,u,7)>=0){
			SUB_224(v,u);
			shifR1_224(v);
			ADD_96(x2,x1);
			shifL1_96(x1);
		}else{
			SUB_224(u,v);
			shifR1_224(u);
			ADD_96(x1,x2);
			shifL1_96(x2);
		}
		k++;
	}
	while(v[5]>0&&x1[2]<0x7FFFFFFF&&x2[2]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_192(v);
			shifL1_96(x1);
		}
		else if((u[0]&1)==0){
			shifR1_192(u);
			shifL1_96(x2);
		}
		else if(comparativo(v,u,6)>=0){
			SUB_192(v,u);
			shifR1_192(v);
			ADD_96(x2,x1);
			shifL1_96(x1);
		}else{
			SUB_192(u,v);
			shifR1_192(u);
			ADD_96(x1,x2);
			shifL1_96(x2);
		}
		k++;
	}
	while(v[5]>0||u[5]>0){
		if((v[0]&1)==0){
			shifR1_192(v);
			shifL1_128(x1);
		}
		else if((u[0]&1)==0){
			shifR1_192(u);
			shifL1_128(x2);
		}
		else if(comparativo(v,u,6)>=0){
			SUB_192(v,u);
			shifR1_192(v);
			ADD_128(x2,x1);
			shifL1_128(x1);
		}else{
			SUB_192(u,v);
			shifR1_192(u);
			ADD_128(x1,x2);
			shifL1_128(x2);
		}
		k++;
	}

	while(v[4]>0&&x1[3]<0x7FFFFFFF&&x2[3]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_160(v);
			shifL1_128(x1);
		}
		else if((u[0]&1)==0){
			shifR1_160(u);
			shifL1_128(x2);
		}
		else if(comparativo(v,u,5)>=0){
			SUB_160(v,u);
			shifR1_160(v);
			ADD_128(x2,x1);
			shifL1_128(x1);
		}else{
			SUB_160(u,v);
			shifR1_160(u);
			ADD_128(x1,x2);
			shifL1_128(x2);
		}
		k++;
	}
	while(v[4]>0||u[4]>0){
		if((v[0]&1)==0){
			shifR1_160(v);
			shifL1_160(x1);
		}
		else if((u[0]&1)==0){
			shifR1_160(u);
			shifL1_160(x2);
		}
		else if(comparativo(v,u,5)>=0){
			SUB_160(v,u);
			shifR1_160(v);
			ADD_160(x2,x1);
			shifL1_160(x1);
		}else{
			SUB_160(u,v);
			shifR1_160(u);
			ADD_160(x1,x2);
			shifL1_160(x2);
		}
		k++;
	}
	while(v[3]>0&&x1[4]<0x7FFFFFFF&&x2[4]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_128(v);
			shifL1_160(x1);
		}
		else if((u[0]&1)==0){
			shifR1_128(u);
			shifL1_160(x2);
		}
		else if(comparativo(v,u,4)>=0){
			SUB_128(v,u);
			shifR1_128(v);
			ADD_160(x2,x1);
			shifL1_160(x1);
		}else{
			SUB_128(u,v);
			shifR1_128(u);
			ADD_160(x1,x2);
			shifL1_160(x2);
		}
		k++;
	}
	while(v[3]>0||u[3]>0){
		if((v[0]&1)==0){
			shifR1_128(v);
			shifL1_192(x1);
		}
		else if((u[0]&1)==0){
			shifR1_128(u);
			shifL1_192(x2);
		}
		else if(comparativo(v,u,4)>=0){
			SUB_128(v,u);
			shifR1_128(v);
			ADD_192(x2,x1);
			shifL1_192(x1);
		}else{
			SUB_128(u,v);
			shifR1_128(u);
			ADD_192(x1,x2);
			shifL1_192(x2);
		}
		k++;
	}
	while(v[2]>0&&x1[5]<0x7FFFFFFF&&x2[5]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_96(v);
			shifL1_192(x1);
		}
		else if((u[0]&1)==0){
			shifR1_96(u);
			shifL1_192(x2);
		}
		else if(comparativo(v,u,3)>=0){
			SUB_96(v,u);
			shifR1_96(v);
			ADD_192(x2,x1);
			shifL1_192(x1);
		}else{
			SUB_96(u,v);
			shifR1_96(u);
			ADD_192(x1,x2);
			shifL1_192(x2);
		}
		k++;
	}
	while(v[2]>0||u[2]>0){
		if((v[0]&1)==0){
			shifR1_96(v);
			shifL1_224(x1);
		}
		else if((u[0]&1)==0){
			shifR1_96(u);
			shifL1_224(x2);
		}
		else if(comparativo(v,u,3)>=0){
			SUB_96(v,u);
			shifR1_96(v);
			ADD_224(x2,x1);
			shifL1_224(x1);
		}else{
			SUB_96(u,v);
			shifR1_96(u);
			ADD_224(x1,x2);
			shifL1_224(x2);
		}
		k++;
	}
	while((v[1]>0||u[1]>0)&&x1[6]<0x7FFFFFFF&&x2[6]<0x7FFFFFFF){
		if((v[0]&1)==0){
			shifR1_64(v);
			shifL1_224(x1);
		}
		else if((u[0]&1)==0){
			shifR1_64(u);
			shifL1_224(x2);
		}
		else if(comparativo(v,u,8)>=0){
			SUB_64(v,u);
			shifR1_64(v);
			ADD_224(x2,x1);
			shifL1_224(x1);
		}else{
			SUB_64(u,v);
			shifR1_64(u);
			ADD_224(x1,x2);
			shifL1_224(x2);
		}
		k++;
	}
	while(v[1]>0||u[1]>0){
		if((v[0]&1)==0){
			shifR1_64(v);
			shifL1_256(x1);
		}
		else if((u[0]&1)==0){
			shifR1_64(u);
			shifL1_256(x2);
		}
		else if(comparativo(v,u,2)>=0){
			SUB_64(v,u);
			shifR1_64(v);
			ADD256S(x2,x1);
			shifL1_256(x1);
		}else{
			SUB_64(u,v);
			shifR1_64(u);
			ADD256S(x1,x2);
			shifL1_256(x2);
		}
		k++;
	}
	while(v[0]>0){
		if((v[0]&1)==0){
			LSR1(v[0],v[0]);
			shifL1_256(x1);
		}
		else if((u[0]&1)==0){
			LSR1(u[0],u[0]);
			shifL1_256(x2);
		}
		else if(v[0]>=u[0]){
			v[0]-=u[0];
			LSR1(v[0],v[0]);
			ADD256S(x2,x1);
			shifL1_256(x1);
		}else{
			u[0]-=v[0];
			LSR1(u[0],u[0]);
			ADD256S(x1,x2);
			shifL1_256(x2);
		}
		k++;
	}
	if(u[0]!=1) return -1;
	if(comparativo(x1,B,8)>=0){
		SUB256S(x1,B);
	}
	COPY(X,x1);

	return k;
}

void MontInverse(uint32_t *X, uint32_t *A){
	int k=0,i=0,aux;
	uint32_t DOS[]={0,0,0,0,0,0,0,0,0};

	k=partialMontInv(A,p,X);
	if(k==256){
		MULMONG(X,X,r2);
		return;
	}

	if(k<256){
		MULMONG(X,X,r2);
		k=k+256;
	}
	MULMONG(X,X,r2);
	aux=512-k;
	if(aux>0){
		i=aux/32;
		aux=aux-32*i;
		if(aux%32==0){
			DOS[i]=1;
		}
		else{
			DOS[i]=1<<aux;
		}
		MULMONG(X,X,DOS);
	}
	else{
		MULMONG1(X,X);
	}
}


void DIVIDE2(uint32_t *C, uint32_t *A){
	if(A[0]&1==1){
		shifR1(C,A);
		ADD256S(C,dd);
	}
	else{
		shifR1(C,A);
	}
}


void Fp_init(uint32_t *num){
	num[0]=0;
	num[1]=0;
	num[2]=0;
	num[3]=0;
	num[4]=0;
	num[5]=0;
	num[6]=0;
	num[7]=0;
	num[8]=0;
}

void Fp_set(uint32_t *num, uint32_t *a){
#ifdef HAVE_NEON
	COPY(num,a);
#else
	num[0]=a[0];
	num[1]=a[1];
	num[2]=a[2];
	num[3]=a[3];
	num[4]=a[4];
	num[5]=a[5];
	num[6]=a[6];
	num[7]=a[7];
#endif
}

void Fp_setD(uint32_t *num, uint32_t a7,uint32_t a6,uint32_t a5,uint32_t a4,uint32_t a3,uint32_t a2,uint32_t a1,uint32_t a0){
	num[0]=a0;
	num[1]=a1;
	num[2]=a2;
	num[3]=a3;
	num[4]=a4;
	num[5]=a5;
	num[6]=a6;
	num[7]=a7;
	num[8]=0;
}

void Fp_set_str(uint32_t *n, char *s){
	sscanf(s, "0x%08x%08x%08x%08x%08x%08x%08x%08x",&n[7],&n[6],&n[5],&n[4],&n[3],&n[2],&n[1],&n[0]);
	n[8]=0;
}

void Fp_rand(uint32_t *n){
	Fp_setD(n, rand()&0x3FFFFFFF,rand(),rand(),rand(),rand(),rand(),rand(),rand());
}

void Fp_randL(uint32_t *n, uint32_t *l){
	Fp_setD(n, rand()&0x3FFFFFFF,rand(),rand(),rand(),rand(),rand(),rand(),rand());
	if(comparativo(n,l,8)>=0){
		SUB256S(n,l);
	}
}

void Mul_set(uint32_t *num, uint32_t *a){
	COPY(num,a);
	COPY(&num[8],&a[8]);
}

int binary16Integer(uint8_t *bin, uint32_t *k){
	int i,j, ind=0;
	uint32_t aux;
	for(i=0; i<8; i++){
		for(j=0; j<8; j++){
			aux=k[i]>>j*4;
			bin[ind+j]=aux&0xF;
		}
		ind+=8;
	}
	//Encuentra el primer bit>0
	for(i=ind-1; i>=0; i--){
		if(bin[i]>0) break;
	}
	return i;
}

int TransposeInt(uint8_t *bin, uint32_t *k){
	int i;
	uint8_t v;
	uint32_t aux[9];

	for(i=0; i<8; i++){
		aux[i]=k[i];
	}
	for(i=0; i<32; i++){
		v=0;
		v+=aux[0]&1;
		v+=(aux[1]&1)<<1;
		v+=(aux[2]&1)<<2;
		v+=(aux[3]&1)<<3;
		v+=(aux[4]&1)<<4;
		v+=(aux[5]&1)<<5;
		v+=(aux[6]&1)<<6;
		v+=(aux[7]&1)<<7;
		bin[i]=v;
		aux[0]=aux[0]>>1;
		aux[1]=aux[1]>>1;
		aux[2]=aux[2]>>1;
		aux[3]=aux[3]>>1;
		aux[4]=aux[4]>>1;
		aux[5]=aux[5]>>1;
		aux[6]=aux[6]>>1;
		aux[7]=aux[7]>>1;
	}

	for(i=31; i>=0; i--){
		if(bin[i]!=0) return i;
	}

	return 0;
}


void EXPO(uint32_t *T, uint32_t *A, uint32_t *k){
	int i,n;
	uint8_t s[64];
	Fp t[16];

//Realizo el precomputo d=4
	Fp_setD(t[0],0,0,0,0,0,0,0,1);
	Fp_set(t[1], A);
	MULMONG(t[2], A, A);
	MULMONG(t[3], t[2], A);
	MULMONG(t[4], t[3], A);
	MULMONG(t[5], t[4], A);
	MULMONG(t[6], t[5], A);
	MULMONG(t[7], t[6], A);
	MULMONG(t[8], t[7], A);
	MULMONG(t[9], t[8], A);
	MULMONG(t[10], t[9], A);
	MULMONG(t[11], t[10], A);
	MULMONG(t[12], t[11], A);
	MULMONG(t[13], t[12], A);
	MULMONG(t[14], t[13], A);
	MULMONG(t[15], t[14], A);

	n=binary16Integer(s,k);
	Fp_set(T, t[s[n]]);

	for(i=n-1; i>=0; i--){
		MULMONG(T,T,T);
		MULMONG(T,T,T);
		MULMONG(T,T,T);
		MULMONG(T,T,T);
		if(s[i]>0){
			MULMONG(T,T,t[s[i]]);
		}
	}

}
int SQRROOT(uint32_t *T, uint32_t *A){
	Fp C;
	EXPO(T, A, sq);
	MULMONG(C,T,T);
	if(comparativo(C, A, 8)==0) return 1;
	return -1;
}


//Falta Probar
int SQRROOT_14(uint32_t *T, uint32_t *A){
	Fp C0, Z, W, A0, X, B;
	int i,v,m,aux, tmp=0;
	Fp_set(Z, Z_SQR);
	EXPO(W, A, T_2ST_D);
	MULMONG(X,W,A);
	MULMONG(B,X,W);
	Fp_set(A0,B);
	for(i=0; i<S_2ST_Q-1; i++){
		MULMONG(A0,A0,A0);
	}
	SUB256MOD(C0, p, A0);
	if(comparativo(C0, um, 8)==0) return -1;
	v=S_2ST_Q;
	while(comparativo(B, um, 8)!=0){
		m=1; tmp++;
		MULMONG(C0, B, B);
		while(comparativo(C0, um, 8)!=0){
			MULMONG(C0, C0, C0);
			m++;
		}
		aux=v-m-1;
		if(aux>0){
			MULMONG(W,Z,Z);
			for(i=0; i<aux-1; i++){
				MULMONG(W,W,W);
			}
		}
		else{
			Fp_set(W, Z);
		}
		MULMONG(Z,W,W);
		MULMONG(X,X,W);
		MULMONG(B,B,Z);
		v=m;
	}
	Fp_set(T,X);
	return tmp;
}

