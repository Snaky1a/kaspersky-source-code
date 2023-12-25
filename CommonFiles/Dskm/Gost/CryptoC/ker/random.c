#if defined (_WIN32)
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "CrC_User.h"

//char    Pass_=0;
//DWORD   X0_, Y0_, A0_=18000, B0_=30903;
//DWORD   X1_, Y1_, A1_=23163, B1_=19215;
//DWORD   X2_, Y2_, A2_=28959, B2_=24948;
//DWORD   X3_, Y3_, A3_=19074, B3_=21723;
//DWORD   OLZ_, F_;

DWORD   A0_=18000, B0_=30903;
DWORD   A1_=23163, B1_=19215;
DWORD   A2_=28959, B2_=24948;
DWORD   A3_=19074, B3_=21723;

/*���������������������������������������������������������������������DEFINES*/
/*�����������������������������������������������������������������FORCERANDOM*/
void  CrypC_ForceRandom_(struct RND_State *State,
                         DWORD _X0, DWORD _Y0 ,
                         DWORD _X1, DWORD _Y1 ,
                         DWORD _X2, DWORD _Y2 ,
                         DWORD _X3, DWORD _Y3 ,
                         char  _Pass          )
/*  ��⠭���� ��������� ��砫쭮�� ���������� ����� 256 ��� */
/*                ���稪� ��砩��� �ᥫ                   */
/*           � ��࠭���� ⥪�饣� ����������               */
/* �室�� ��ࠬ����:                                       */
/* - �����⥫� *State �� ���⥪�� ���.                      */
/* - ����室��� ���ﭨ� ॣ���஢ Xi_, Yi_, i=0,...,3.   */
/* - ����室���� ���ﭨ� �������� Pass_.                */
/* ��室:                                                   */
/* - ����騥 ���ﭨ� ॣ���஢ Xi_, Yi_, i=0,...,3 � ����-*/
/*   ���� Pass_ ��࠭����� � ���⥪�� � �����������     */
/*   ᮤ�ন�� ᮮ⢥������� ��ࠬ��஢ ��楤���.       */
{
State->x0_   = State->X0_  ;       /* ���࠭��� ���ﭨ�.  */
State->x1_   = State->X1_  ;
State->x2_   = State->X2_  ;
State->x3_   = State->X3_  ;
State->y0_   = State->Y0_  ;
State->y1_   = State->Y1_  ;
State->y2_   = State->Y2_  ;
State->y3_   = State->Y3_  ;
State->pass_ = State->Pass_;

State->X0_   = _X0  ;              /* ��⠭����� ���ﭨ�. */
State->X1_   = _X1  ;
State->X2_   = _X2  ;
State->X3_   = _X3  ;
State->Y0_   = _Y0  ;
State->Y1_   = _Y1  ;
State->Y2_   = _Y2  ;
State->Y3_   = _Y3  ;
State->Pass_ = _Pass;
}
/*�����������������������������������������������������������������RESTRRANDOM*/
/*�����������������������������������������������������������������RESTRRANDOM*/
void  CrypC_RestrRandom_(struct RND_State *State)
/*   ����⠭������� ��࠭������ ���������� ����� 256 ���   */
/*                ���稪� ��砩��� �ᥫ                   */
/* �室�� ��ࠬ����:                                       */
/* - �����⥫� *State �� ���⥪�� ���.                      */
/* ��室:                                                   */
/* - ����⠭��������� ࠭�� ��࠭���� � ���⥪�� ����- */
/*   ��� ॣ���஢ Xi_, Yi_, i=0,...,3 � �������� Pass_.  */
{
State->X0_   = State->x0_  ;     /* ����⠭����� ���ﭨ�. */
State->X1_   = State->x1_  ;
State->X2_   = State->x2_  ;
State->X3_   = State->x3_  ;
State->Y0_   = State->y0_  ;
State->Y1_   = State->y1_  ;
State->Y2_   = State->y2_  ;
State->Y3_   = State->y3_  ;
State->Pass_ = State->pass_;
}
/*�����������������������������������������������������������������FORCERANDOM*/
/*������������������������������������������������������������������������STEP*/
void CrypC_Step_(struct RND_State *State)
{                                        /* ��� ४��७⭮�� �८�ࠧ������. */
State->X0_     = (A0_*(State->X0_ & 65535)) + (State->X0_ >> 16);
State->Y0_     = (B0_*(State->Y0_ & 65535)) + (State->Y0_ >> 16);
State->X1_     = (A1_*(State->X1_ & 65535)) + (State->X1_ >> 16);
State->Y1_     = (B1_*(State->Y1_ & 65535)) + (State->Y1_ >> 16);
State->X2_     = (A2_*(State->X2_ & 65535)) + (State->X2_ >> 16);
State->Y2_     = (B2_*(State->Y2_ & 65535)) + (State->Y2_ >> 16);
State->X3_     = (A3_*(State->X3_ & 65535)) + (State->X3_ >> 16);
State->Y3_     = (B3_*(State->Y3_ & 65535)) + (State->Y3_ >> 16);
}
/*������������������������������������������������������������������������STEP*/
/*���������������������������������������������������������������������TAKTOLZ*/
void CrypC_TaktOLZ_(struct RND_State *State)
{                                        /* ����   ࠡ��� ����� ����প�. */
State->OLZ_ = (State->OLZ_ >> 1) ^ ((
                                     State->OLZ_       ^   /* ��� 0: x**0 */
                                    (State->OLZ_ >> 1) ^   /* ��� 1: x**1 */
                                    (State->OLZ_ >> 2) ^   /* ��� 2: x**2 */
                                    (State->OLZ_ >> 3) ^   /* ��� 3: x**3 */
                                    (State->OLZ_ >> 5) ^   /* ��� 5: x**5 */
                                    (State->OLZ_ >> 7)     /* ��� 7: x**7 */
                                    ) << 31
                                   );
}
/*���������������������������������������������������������������������TAKTOLZ*/
/*������������������������������������������������������������������INITRANDOM*/
void  CrypC_InitRandom_( struct RND_State *State )
/* ������� ��砩���� ��砫쭮�� ���������� ����� 256 ��� */
/*                ���稪� ��砩��� �ᥫ                   */
{
int           i, n;
DWORD        TMP;
DWORD        X_[2], w;
DWORD        M64[2] = {0x7f3f1f0f,0x0703016a};
DWORD        P64[2] = {0xffffffff,0xffffffc5};

State->F_  = (rdtick() >> 2) & 15;                         /* ��砫쭮� ���ﭨ� F.*/
State->X0_ = (rdtick() >> 2) ^ (rdtick() << 16);           /* ��ࢨ筮� ����������. */
State->X1_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->X2_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->X3_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->Y0_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->Y1_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->Y2_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->Y3_ = (rdtick() >> 2) ^ (rdtick() << 16);
State->OLZ_= (DWORD)time(0);

for(i=0;i<64;i++)                         /* 64 ⠪� ���.               */
   CrypC_TaktOLZ_(State);
for(n=0;n<64;n++)                         /* ������뢠��� ॣ���� 0.    */
   {
   for(i=0;i<16;i++)                                CrypC_Step_(State);
   while(((State->Y0_+State->Y1_)&15) != State->F_) CrypC_Step_(State);

   TMP = (DWORD)(((BYTE *)&(State->OLZ_))[3]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[2]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[1]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[0]) ;
   State->F_  = ((rdtick() >> 3) ^        /* ����� ���祭�� F: ��砩��� */
                 (TMP      >> 4) ^        /* ���� �㬬� ���㡠�⮢ ���.  */
                  TMP          ) & 15;  
   for(i=0;i<64;i++)                      /* 64 ⠪� ���.               */
      CrypC_TaktOLZ_(State);

   if(rdtick()&4)                         /* �᫨ ��砩�� ��� == 1:    */
     {
     X_[0] = State->X0_;                  /* �६���� ����� �� 4 ᫮�. */
     X_[1] = State->Y0_;
     X_[0] ^= M64[0]; X_[1] ^= M64[1];    /* �ਡ����� ����.            */
     w = CrypC_Lshl_LC(2,M64);            /* ������᪨� ᤢ�� ��᪨...  */
     M64[1] ^= w;                         /*                        ...  */
     CrypC_Ladd_PC(2, X_, LO_, P64);      /* X_ += 0 (mod 2**64 - 59).   */
     State->X0_ = X_[0];                  /* ����� ᮤ�ন��� ॣ����.  */
     State->Y0_ = X_[1];
     }
   }
for(n=0;n<64;n++)                         /* ������뢠��� ॣ���� 1.    */
   {
   for(i=0;i<16;i++)                                CrypC_Step_(State);
   while(((State->Y0_+State->Y1_)&15) != State->F_) CrypC_Step_(State);
   
   TMP = (DWORD)(((BYTE *)&(State->OLZ_))[3]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[2]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[1]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[0]) ;
   State->F_  = ((rdtick() >> 3) ^       /* ����� ���祭�� F: ��砩��� */
                 (TMP      >> 4) ^        /* ���� �㬬� ���㡠�⮢ ���.  */
                  TMP          ) & 15;  
   for(i=0;i<64;i++)                      /* 64 ⠪� ���.               */
      CrypC_TaktOLZ_(State);

   if(rdtick()&4)                         /* �᫨ ��砩�� ��� == 1:    */
     {
     X_[0] = State->X1_;                  /* �६���� ����� �� 4 ᫮�. */
     X_[1] = State->Y1_;
     X_[0] ^= M64[0]; X_[1] ^= M64[1];    /* �ਡ����� ����.            */
     w = CrypC_Lshl_LC(2,M64);            /* ������᪨� ᤢ�� ��᪨...  */
     M64[1] ^= w;                         /*                        ...  */
     CrypC_Ladd_PC(2, X_, LO_, P64);      /* X_ += 0 (mod 2**64 - 59).   */
     State->X1_ = X_[0];                  /* ����� ᮤ�ন��� ॣ����.  */
     State->Y1_ = X_[1];
     }
   }
for(n=0;n<64;n++)                         /* ������뢠��� ॣ���� 2.    */
   {
   for(i=0;i<16;i++)                                CrypC_Step_(State);
   while(((State->Y0_+State->Y1_)&15) != State->F_) CrypC_Step_(State);
   
   TMP = (DWORD)(((BYTE *)&(State->OLZ_))[3]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[2]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[1]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[0]) ;
   State->F_  = ((rdtick() >> 3) ^        /* ����� ���祭�� F: ��砩��� */
                 (TMP      >> 4) ^        /* ���� �㬬� ���㡠�⮢ ���.  */
                  TMP          ) & 15;  
   for(i=0;i<64;i++)                      /* 64 ⠪� ���.               */
      CrypC_TaktOLZ_(State);

   if(rdtick()&4)                         /* �᫨ ��砩�� ��� == 1:    */
     {
     X_[0] = State->X2_;                  /* �६���� ����� �� 4 ᫮�. */
     X_[1] = State->Y2_;
     X_[0] ^= M64[0]; X_[1] ^= M64[1];    /* �ਡ����� ����.            */
     w = CrypC_Lshl_LC(2,M64);            /* ������᪨� ᤢ�� ��᪨...  */
     M64[1] ^= w;                         /*                        ...  */
     CrypC_Ladd_PC(2, X_, LO_, P64);      /* X_ += 0 (mod 2**64 - 59).   */
     State->X2_ = X_[0];                  /* ����� ᮤ�ন��� ॣ����.  */
     State->Y2_ = X_[1];
     }
   }
for(n=0;n<64;n++)                         /* ������뢠��� ॣ���� 3.    */
   {
   for(i=0;i<16;i++)                                CrypC_Step_(State);
   while(((State->Y0_+State->Y1_)&15) != State->F_) CrypC_Step_(State);
   
   TMP = (DWORD)(((BYTE *)&(State->OLZ_))[3]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[2]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[1]) ^
         (DWORD)(((BYTE *)&(State->OLZ_))[0]) ;
   State->F_  = ((rdtick() >> 3) ^        /* ����� ���祭�� F: ��砩��� */
                 (TMP      >> 4) ^        /* ���� �㬬� ���㡠�⮢ ���.  */
                  TMP          ) & 15;  
   for(i=0;i<64;i++)                      /* 64 ⠪� ���.               */
      CrypC_TaktOLZ_(State);

   if(rdtick()&4)                         /* �᫨ ��砩�� ��� == 1:    */
     {
     X_[0] = State->X3_;                  /* �६���� ����� �� 4 ᫮�. */
     X_[1] = State->Y3_;
     X_[0] ^= M64[0]; X_[1] ^= M64[1];    /* �ਡ����� ����.            */
     w = CrypC_Lshl_LC(2,M64);            /* ������᪨� ᤢ�� ��᪨...  */
     M64[1] ^= w;                         /*                        ...  */
     CrypC_Ladd_PC(2, X_, LO_, P64);      /* X_ += 0 (mod 2**64 - 59).   */
     State->X3_ = X_[0];                  /* ����� ᮤ�ন��� ॣ����.  */
     State->Y3_ = X_[1];
     }
   }
}
/*������������������������������������������������������������������INITRANDOM*/
/*����������������������������������������������������������������������RANDOM*/
int  CrypC_FillByRandom_( struct RND_State *State, void *Buf, long LenInBytes )
/*     ������� �ᥢ����砩���� ����� ������� �����     */
/* �室�� ��ࠬ����:                                       */
/* - �����⥫� *Buf �� ���� ��� �ᥢ����砩���� �����.  */
/* - ����� LenInBytes ���� Buf � �����.                  */
/* ��室:                                                   */
/* - � ���� *Buf ����頥��� �ᥢ����砩�� ����� �����    */
/*   LenInBytes ����.                                       */
{
DWORD        *Ptr, Tmp;

Ptr = (DWORD *)Buf;
if(!State->Pass_)                           /* ��砫쭮� ���������� Xi,Yi. */
  {
  CrypC_InitRandom_( State );
  State->Pass_ = 1;
  }
while(LenInBytes>=4)
   {
   CrypC_Step_(State);
   *Ptr    = (DWORD)((State->X0_<<16)^(State->Y0_&65535));
   *Ptr   ^= (DWORD)((State->X1_<<16)^(State->Y1_&65535));
   *Ptr   ^= (DWORD)((State->X2_<<16)^(State->Y2_&65535));
   *Ptr++ ^= (DWORD)((State->X3_<<16)^(State->Y3_&65535));
   LenInBytes -= 4;
   }
if( LenInBytes )
   {
   CrypC_Step_(State);
   Tmp     = (DWORD)((State->X0_<<16)^(State->Y0_&65535));
   Tmp    ^= (DWORD)((State->X1_<<16)^(State->Y1_&65535));
   Tmp    ^= (DWORD)((State->X2_<<16)^(State->Y2_&65535));
   Tmp    ^= (DWORD)((State->X3_<<16)^(State->Y3_&65535));
   memcpy( Ptr, &Tmp, (WORD)LenInBytes );
   }
return(0);
}
/*����������������������������������������������������������������������RANDOM*/
/*�������������������������������������������������������������������������EOF*/

#endif //_WIN32