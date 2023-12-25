#include "signport.h"


#ifdef _DEBUG
int errno;
#endif

#include <memory.h>
#include <Sign/ct_funcs.h>
#include <Sign/ct_supp.h>
#include <Sign/sign_lib.h>
#include <Stuff/text2bin.h>
#include <Avp_defs.h>

extern char kl_ok[256];

extern CT_PTR (CTAPI *ptrAMemAlloc)( CT_ULONG );
extern void   (CTAPI *ptrAMemFree)( CT_PTR );


/*
      if ( notaries ) {
        memset( &notaries[local_count], 0, sizeof(notaries[local_count]) );
        notaries[local_count].guid = *(GUID*)tmp;
        memcpy( &notaries[local_count].r, tmp+sizeof(GUID),              NOTARY_LEN_R );
        memcpy( &notaries[local_count].s, tmp+sizeof(GUID)+NOTARY_LEN_R, NOTARY_LEN_S );
      }

typedef struct t_Notary {
  GUID      guid;
  CT_UCHAR  r[CT_N_LEN_MAXRS];
  CT_UCHAR  s[CT_N_LEN_MAXRS];
} Notary;


*/

static int free_not( void* not, int ret ) {
  if ( not )
    ptrAMemFree( not );
  return ret;
}


// ---
int sign_check_buffer( void* buffer, int buff_len, int* out_len, int kasp_key, void* keys[], int key_count, int all_of ) {
  
  int i;
  int found_one_of;
  CTN_Notary* not = 0;
  CTN_Hash    hash;
  int sign_count = MAX_NOT_COUNT;
  void* notaries[MAX_NOT_COUNT];
  char  conv_buffer[ NOTARY_VALUE_BIN_LEN+2 ];

  s_mset( notaries, 0, sizeof(notaries) );

  MY_TRY {

    int j, res, local_len;

    if ( !buff_len )
      return free_not( not, SIGN_BAD_PARAMETERS );

    if ( keys && !key_count )
      return free_not( not, SIGN_BAD_PARAMETERS );

    if ( !keys && !kasp_key )
      return free_not( not, SIGN_BAD_PARAMETERS );

    if ( !out_len )
      out_len = &local_len;

    res = sign_collect_notaries( buffer, buff_len, notaries, &sign_count, out_len );
    if ( SIGN_OK != res ) 
      return free_not( not, res );

    if ( !sign_count )
      return free_not( not, SIGN_NOTARY_NOT_FOUND );

    not = (CTN_Notary*)ptrAMemAlloc( sizeof(CTN_Notary) );
    if ( !not )
      return free_not( not, SIGN_NOT_ENOUGH_MEMORY );

    CTN_NotInitVariables( not );

    sign_hash_buffer( &not->Hash, buffer, *out_len );
    s_mcpy( &hash, &not->Hash, sizeof(hash) );

    found_one_of = 0;
    kasp_key = !!kasp_key;
    for( i=0; i<key_count + kasp_key; i++ ) {
      void* key;
      if ( kasp_key && i==0 )
        key = kl_ok;
      else 
        key = keys[i-kasp_key];
      //void* key = (i<key_count) ? keys[i] : kl_ok;

      if ( !key ) 
        return free_not( not, SIGN_BAD_PARAMETERS );

      CTN_NotInitVariables( not );
      s_mcpy( &not->Hash, &hash, sizeof(hash) );
      res = sign_load_open_key( not, key, 0 );

      if ( res == SIGN_OK ) {
        int found_all_of = 0;

        res = CT_ERR_BAD_FILE;
        for( j=0; j<sign_count; j++ ) {
          char* p = ((char*)notaries[j]) + NOTARY_TXT_BEG;
          if ( !s_mcmp(not->Public.UserName,p,STR_GUID_TXT_LEN) ) {
            found_one_of = 1;
            found_all_of = 1;
            s_mset( not->RS.r, 0, CT_N_LEN_MAXRS );
            s_mset( not->RS.s, 0, CT_N_LEN_MAXRS );
            TextToBin( p + STR_GUID_TXT_LEN, NOTARY_VALUE_TXT_LEN, conv_buffer, NOTARY_VALUE_BIN_LEN+2 );
            s_mcpy( not->RS.r, conv_buffer,              NOTARY_LEN_R );
            s_mcpy( not->RS.s, conv_buffer+NOTARY_LEN_R, NOTARY_LEN_S );
            res = CTN_LANSNot( not );
            break;
          }
        }
        if ( all_of ) {
          if ( res != CT_ERR_OK ) {
            if ( found_all_of )
              return free_not( not, SIGN_NOT_MATCH );
            else
              return free_not( not, SIGN_NOTARY_NOT_FOUND );
          }
        }
        else if ( res == CT_ERR_OK )
          return free_not( not, SIGN_OK );
      }
      else
        return res/*SIGN_BAD_PARAMETERS*/;
    }
    if ( all_of )
      return free_not( not, SIGN_OK );
    else {
      if ( found_one_of )
        return free_not( not, SIGN_NOT_MATCH );
      else
        return free_not( not, SIGN_NOTARY_NOT_FOUND );
    }
  }
  MY_EXCEPT
}


