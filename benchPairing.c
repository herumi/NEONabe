/*
benchPairing.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "bench.h"
#include "pairing.h"
#include <stdlib.h>
#define TAM 6
char  szLogThis[500];

void bench_FP2(){
	int i,j;
	Fp A[2],B[2],C[2];

	BENCH_BEGIN("Add", 500){
		Fpk_rand(A,2);
		Fpk_rand(B,2);
		Fpk_rand(C,2);
		BENCH_ADD(SUMA_FP2(C,A,B), 500);
	}
	BENCH_END(500, 500);

	BENCH_BEGIN("Sub", 500){
		Fpk_rand(A,2);
		Fpk_rand(B,2);
		Fpk_rand(C,2);
		BENCH_ADD(RESTA_FP2(C,A,B), 500);
	}
	BENCH_END(500, 500);

	BENCH_BEGIN("MULT", 500){
		Fpk_rand(A,2);
		Fpk_rand(B,2);
		Fpk_rand(C,2);
		BENCH_ADD(MULT_FP2(C,A,B), 500);
	}
	BENCH_END(500, 500);

	BENCH_BEGIN("SQR", 500){
		Fpk_rand(A,2);
		Fpk_rand(C,2);
		BENCH_ADD(CUAD_FP2(C,A), 500);
	}
	BENCH_END(500, 500);

	BENCH_BEGIN("INV", 500){
		Fpk_rand(A,2);
		Fpk_rand(C,2);
		BENCH_ADD(INVERT_FP2(C,A), 500);
	}
	BENCH_END(500, 500);

}




void bench_Pairing(){
	int i,j;
	Fp A, A1;
	Fp C[12],B[12];
	BN_init();

    PG1 P, kP;
    G1P_set(P.xyz,
    		"0x2523648240000001BA344D80000000086121000000000013A700000000000012",
    		"0x0000000000000000000000000000000000000000000000000000000000000001");
    setDomMont(P.xyz,P.xyz,3);

    PG2 Q, kQ;
    G2P_set(Q.xyz,
    		"0x061A10BB519EB62FEB8D8C7E8C61EDB6A4648BBB4898BF0D91EE4224C803FB2B",
    		"0x0516AAF9BA737833310AA78C5982AA5B1F4D746BAE3784B70D8C34C1E7D54CF3",
    		"0x021897A06BAF93439A90E096698C822329BD0AE6BDBE09BD19F0E07891CD2B9A",
    		"0x0EBB2B0E7C8B15268F6D4456F5F38D37B09006FFD739C9578A2D1AEC6B3ACE9B");
    setDomMont2(Q.xyz,Q.xyz,3);

	PG1 Pi[256];
	PG2 Qi[256];

	G1CombPrecompute(Pi, P);
	G2CombPrecompute(Qi, Q);

	BENCH_BEGIN("Miller Loop", 10){
		Fp_rand(A);
		Fp_rand(A1);
		G1combMult(kP.xyz, Pi, A);
		G1J2A(kP.xyz, kP.xyz);
		G2combMult(kQ.xyz, Qi, A1);
		G2J2A(kQ.xyz, kQ.xyz);
		BENCH_ADD(MillerLoop(C,kP,kQ), 10);
	}
	BENCH_END(10, 10);


	BENCH_BEGIN("Final Exponentiation", 10){
		Fpk_rand(B,12);
		BENCH_ADD(FINAL_EXPONENTIATION(C,B), 10);
	}
	BENCH_END(10, 10);


	BENCH_BEGIN("Pairing", 10){
		Fp_rand(A);
		Fp_rand(A1);
		G1combMult(kP.xyz, Pi, A);
		G1J2A(kP.xyz, kP.xyz);
		G2combMult(kQ.xyz, Qi, A1);
		G2J2A(kQ.xyz, kQ.xyz);
		BENCH_ADD(Pairing(C,kP,kQ), 10);
	}
	BENCH_END(10, 10);

}


void bench_SM(){
	int i, j;
	PG1 P, kP;
	Fp A, B[12],C[12];

	BN_init();

	G1P_set(P.xyz,
			"0x2523648240000001BA344D80000000086121000000000013A700000000000012",
			"0x0000000000000000000000000000000000000000000000000000000000000001");
	setDomMont(P.xyz,P.xyz,3);

	PG2 Q, kQ;
	G2P_set(Q.xyz,
			"0x061A10BB519EB62FEB8D8C7E8C61EDB6A4648BBB4898BF0D91EE4224C803FB2B",
			"0x0516AAF9BA737833310AA78C5982AA5B1F4D746BAE3784B70D8C34C1E7D54CF3",
			"0x021897A06BAF93439A90E096698C822329BD0AE6BDBE09BD19F0E07891CD2B9A",
			"0x0EBB2B0E7C8B15268F6D4456F5F38D37B09006FFD739C9578A2D1AEC6B3ACE9B");
	setDomMont2(Q.xyz,Q.xyz,3);

	PG1 Pi[256];
	PG2 Qi[256];

	G1CombPrecompute(Pi, P);
	G2CombPrecompute(Qi, Q);

	BENCH_BEGIN("S.M. G1: w-NAF method", 100){
		Fp_setD(A,0,0,0,0,0,0,rand(),rand());
		BENCH_ADD(G1scalarMult(kP.xyz, P, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("S.M. G1: GLV Method", 100){
		Fp_rand(A);
		BENCH_ADD(G1GLVMult(kP.xyz, P, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("S.M. G1: Comb Method", 100){
		Fp_rand(A);
		BENCH_ADD(G1combMult(kP.xyz, Pi, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("S.M. G2: w-NAF method", 100){
		Fp_setD(A,0,0,0,0,0,0,rand(),rand());
		BENCH_ADD(G2scalarMult(kQ.xyz, Q, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("S.M. G2: GS Method", 100){
		Fp_rand(A);
		BENCH_ADD(G2GLVMult(kQ.xyz, Q, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("S.M. G2: Comb Method", 100){
		Fp_rand(A);
		BENCH_ADD(G2combMult(kQ.xyz, Qi, A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("Exp. GT: w-NAF method", 100){
		Fp_setD(A,0,0,0,0,0,0,rand(),rand());
		Fpk_rand(B,12);
		BENCH_ADD(EXPONENCIACION64(C,B,A), 100);
	}
	BENCH_END(100, 100);

	BENCH_BEGIN("Exp. GT: GS Method", 100){
		Fp_rand(A);
		Fpk_rand(B,12);
		BENCH_ADD(EXPONENCIACION_GS(C,B,A), 100);
	}
	BENCH_END(100, 100);

	Fp12 Vi[256];

	BENCH_BEGIN("Exp. GT: Comb Method", 100){
		Fp_rand(A);
		Fpk_rand(B,12);
		ExpoCombPrecompute(Vi,B);
		BENCH_ADD(EXPONENCIACION_COMB(C,Vi,A), 100);
	}
	BENCH_END(100, 100);

}

void bench_ABE(){
	int i, j;

	BN_init();

    //Setup
	Fp A,C[12];
    PG1 P, MSK, H[TAM];
    PG2 Q;
	G1P_set(P.xyz,
			"0x2523648240000001BA344D80000000086121000000000013A700000000000012",
			"0x0000000000000000000000000000000000000000000000000000000000000001");
	setDomMont(P.xyz,P.xyz,3);
	G2P_set(Q.xyz,
			"0x061A10BB519EB62FEB8D8C7E8C61EDB6A4648BBB4898BF0D91EE4224C803FB2B",
			"0x0516AAF9BA737833310AA78C5982AA5B1F4D746BAE3784B70D8C34C1E7D54CF3",
			"0x021897A06BAF93439A90E096698C822329BD0AE6BDBE09BD19F0E07891CD2B9A",
			"0x0EBB2B0E7C8B15268F6D4456F5F38D37B09006FFD739C9578A2D1AEC6B3ACE9B");
	setDomMont2(Q.xyz,Q.xyz,3);

	Fp_rand(A);
	G1GLVMult(MSK.xyz, P, A);
	G1J2A(MSK.xyz, MSK.xyz);

	for(i=0; i<TAM; i++){
		G1P_cpy(H[i].xyz, P.xyz);
	}
	Fp12 E[256];
	Pairing(C,P,Q);


	//Precomputo
	PG1 Pi[256];
	G1CombPrecompute(Pi, P);
	PG2 Qi[256],lQ[2];
	G2CombPrecompute(Qi, Q);
	Fp12 l[70];
	LinesPrecompute(l,Q);
	ExpoCombPrecompute(E,C);

	//keyGen
	PG1 K;
	PG1 Kx[TAM];
	PG2 L;
	KeyGen(K.xyz, L.xyz, Kx, P, MSK, Q, H, TAM);

	BENCH_BEGIN("Key Gen", 100){
		BENCH_ADD(KeyGen(K.xyz, L.xyz, Kx, P, MSK, Q, H, TAM), 100);
	}
	BENCH_END(100, 100);


	//delegate
	PG1 K2;
	PG1 Kx2[TAM];
	PG2 L2;
	Delegate(K2.xyz, L2.xyz, Kx2, K.xyz, L.xyz, Kx, P, Q, H, TAM);
	BENCH_BEGIN("Delegate", 100){
		BENCH_ADD(Delegate(K2.xyz, L2.xyz, Kx2, K.xyz, L.xyz, Kx, P, Q, H, TAM), 100);
	}
	BENCH_END(100, 100);

	//encrypt
	PG2 CP, Di[TAM];
	PG1 Ci[TAM];
	Fp B,M,S;
	Encrypt(C, S, M, E, CP.xyz, Qi, Ci, Di, Pi, H, B, TAM);
	BENCH_BEGIN("Encryption", 100){
		Fp_rand(B);
		Fp_rand(M);
		Fp_rand(S);
		BENCH_ADD(Encrypt(C, S, M, E, CP.xyz, Qi, Ci, Di, Pi, H, B, TAM), 100);
	}
	BENCH_END(100, 100);

	//decrypt
	Fp Omega[TAM];
	int Sign[TAM];
	Fp delta;
	Fp_setD(delta,0,0,0,0,0,0,0,1);
	for(i=0; i<TAM; i++){
		Fp_setD(Omega[i],0,0,0,0,0,0,0,rand());
		if(i%2==0) Sign[i]=1;
		else Sign[i]=-1;
	}

	//Decrypt
	Fp D[12];
	BENCH_BEGIN("Decrypt Delta=1", 100){
		BENCH_ADD(Decrypt(D,C,Ci,Kx, Omega, Sign, TAM, K, L, l, Di, CP, delta), 100);
	}
	BENCH_END(100, 100);


	BENCH_BEGIN("Decrypt Delta>1",100){
		Fp_rand(delta);
		BENCH_ADD(Decrypt(D,C,Ci,Kx, Omega, Sign, TAM, K, L, l, Di, CP, delta), 100);
	}
	BENCH_END(8, 8);

}


void bench_Graph(){
	int i, j;

	BN_init();

    //Setup
	Fp A,C[12];
    PG1 P, MSK, H[50];
    PG2 Q;
	G1P_set(P.xyz,
			"0x2523648240000001BA344D80000000086121000000000013A700000000000012",
			"0x0000000000000000000000000000000000000000000000000000000000000001");
	setDomMont(P.xyz,P.xyz,3);
	G2P_set(Q.xyz,
			"0x061A10BB519EB62FEB8D8C7E8C61EDB6A4648BBB4898BF0D91EE4224C803FB2B",
			"0x0516AAF9BA737833310AA78C5982AA5B1F4D746BAE3784B70D8C34C1E7D54CF3",
			"0x021897A06BAF93439A90E096698C822329BD0AE6BDBE09BD19F0E07891CD2B9A",
			"0x0EBB2B0E7C8B15268F6D4456F5F38D37B09006FFD739C9578A2D1AEC6B3ACE9B");
	setDomMont2(Q.xyz,Q.xyz,3);

	Fp_rand(A);
	G1GLVMult(MSK.xyz, P, A);
	G1J2A(MSK.xyz, MSK.xyz);

	for(i=0; i<50; i++){
		G1P_cpy(H[i].xyz, P.xyz);
	}
	Fp12 E[256];
	Pairing(C,P,Q);


	//Precomputo
	PG1 Pi[256];
	G1CombPrecompute(Pi, P);
	PG2 Qi[256],lQ[2];
	G2CombPrecompute(Qi, Q);
	Fp12 l[70];
	LinesPrecompute(l,Q);
	ExpoCombPrecompute(E,C);

	//keyGen
	PG1 K;
	PG1 Kx[50];
	PG2 L;

	int size;
	sprintf(szLogThis, "Key Gen");logC();
	for(size=10; size<=50; size+=10){
		BENCH_BEGIN("", 10){
			BENCH_ADD(KeyGen(K.xyz, L.xyz, Kx, P, MSK, Q, H, size), 10);
		}
		BENCH_END(10, 10);
	}

	//delegate
	PG1 K2;
	PG1 Kx2[50];
	PG2 L2;
	sprintf(szLogThis, "Delegate");logC();
	for(size=10; size<=50; size+=10){
		BENCH_BEGIN("", 10){
			BENCH_ADD(Delegate(K2.xyz, L2.xyz, Kx2, K.xyz, L.xyz, Kx, P, Q, H, size), 10);
		}
		BENCH_END(10, 10);
	}

	//encrypt
	PG2 CP, Di[50];
	PG1 Ci[50];
	Fp B,M,S;

	sprintf(szLogThis, "Encrypt");logC();
	for(size=10; size<=50; size+=10){
		BENCH_BEGIN("", 10){
			Fp_rand(B);
			Fp_rand(M);
			Fp_rand(S);
			BENCH_ADD(Encrypt(C, S, M, E, CP.xyz, Qi, Ci, Di, Pi, H, B, size), 10);
		}
		BENCH_END(10, 10);
	}
	//decrypt
	Fp Omega[50];
	int Sign[50];
	Fp delta;
	Fp_setD(delta,0,0,0,0,0,0,0,1);
	for(i=0; i<50; i++){
		Fp_setD(Omega[i],0,0,0,0,0,0,0,rand());
		if(i%2==0) Sign[i]=1;
		else Sign[i]=-1;
	}


	//Decrypt
	 sprintf(szLogThis, "Decrypt Delta=1");logC();
	Fp D[12];
	for(size=10; size<=50; size+=10){
		BENCH_BEGIN("D", 10){
			BENCH_ADD(Decrypt(D,C,Ci,Kx, Omega, Sign, size, K, L, l, Di, CP, delta), 10);
		}
		BENCH_END(10, 10);
	}

	 sprintf(szLogThis, "Decrypt Delta>1");logC();
	for(size=10; size<=50; size+=10){
		BENCH_BEGIN("D", 10){
			Fp_rand(delta);
			BENCH_ADD(Decrypt(D,C,Ci,Kx, Omega, Sign, size, K, L, l, Di, CP, delta), 10);
		}
		BENCH_END(10, 10);
	}

}
