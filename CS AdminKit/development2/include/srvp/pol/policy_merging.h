#ifndef __KL_POLICY_MERGING_H__
#define __KL_POLICY_MERGING_H__

typedef enum
{
    KLPOL_MT_NONE   = 0,
    KLPOL_MT_LOCKED = 1,
    KLPOL_MT_ALL    = 3
}KLPOL_MERGING_TYPE;

#define KLPOL_MERGE_POLICY  L".KLPOL_SEC_MERGE_POLICY"
#define KLPOL_PP_MERGING_TYPE   L"KLPOL_MERGING_TYPE"

#endif //__KL_POLICY_MERGING_H__