/*
Domain.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include "Structures.h"

Fp2 Y1[5], Y3[5];
Fp Y2[5];
int8_t WNAF_SK[70];
int TAM_WNAF_SK;
char  szLogThis[500];


uint32_t px4[]={0x0000004C,0x9C000000,0x0000004E,0x84840000,0x00000021,0xE8D13600,0x00000006,0x948D9209,0};
uint32_t p []={0x00000013,0xA7000000,0x00000013,0x61210000,0x00000008,0xBA344D80,0x40000001,0x25236482,0};
uint32_t pi[]={0xD79435E5,0x08435E50,0x1104F6C8,0x6E371BA8,0xC45B843C,0x92022379,0xBA60808C,0xB65373CC,0};
uint32_t r []={0x0000000D,0xA1000000,0x00000010,0xFF9F8000,0x00000007,0xBA344D80,0x40000001,0x25236482,0};
uint32_t mu[]={0x4C735A91,0x5A5F8D22,0x3B56F610,0x24046450,0x7BB36C39,0x7FCEDBA3,0x93AF3394,0xE4A64840,6,0};
uint32_t r2[]={0x5370473D,0xB3E88674,0x8C1CC3F1,0x55EFBF6E,0x7F86954F,0x281E3A1B,0xF6403A3D,0x1B0A32FD,0};
uint32_t um[]={0xFFFFFF8E,0x15FFFFFF,0xFFFFFF8A,0xB939FFFF,0xFFFFFFCD,0xA2C62EFF,0x7FFFFFF5,0x212BA4F2,0};
uint32_t dd[]={0x0000000A,0xD3800000,0x00000009,0x30908000,0x00000004,0xDD1A26C0,0x20000000,0x1291B241,0};
uint32_t sq[]={0x00000005,0xE9C00000,0x00000004,0x18484000,0x00000002,0x6E8D1360,0x90000000,0x0948D920,0};


//SquareRoot Cambiar
//Q=p-1, Q=2^s*t
int S_2ST_Q=45;
uint32_t T_2ST_Q[]={0x000BF403,0xFA00C000,0x120BE811,0xD4C43728,0x7DF273B0,0xD824EA08,0x00011B87,0,0};
uint32_t T_2ST_D[]={0x0005FA01,0xFD006000,0x0905F408,0x6A621B94,0x3EF939D8,0xEC127504,0x00008DC3,0,0};
uint32_t Z_SQR[]={0x73417B06,0x968DEBE4,0x778FC4FC,0xE571C1F9,0xA0399908,0x3D9F9615,0xCCA1ACA4,0x8D3305,0};


//BN
Fp G1_BInv[2];
Fp G1_BNor[2][2];
Fp BN_Beta;
Fp G2_BInv[4];
Fp G2_BNor[7];

