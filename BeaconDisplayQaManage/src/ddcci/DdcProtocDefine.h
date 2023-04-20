#ifndef DDCPROTOCDEFINE_H
#define DDCPROTOCDEFINE_H
typedef unsigned char BYTE;
typedef struct VCPFeaturePktBodyStruct
{
    BYTE vcp_opcode;
    BYTE vcp_type;
    BYTE maxhi;
    BYTE maxlow;
    BYTE valuehi;
    BYTE valuelow;
}VCPFeaturePktType;

typedef struct DDC2Bi_GetVCPFeature_ReplyCmdStruct
{

    BYTE command;
    BYTE result;
    VCPFeaturePktType a_VCPFeature;

  }DDCBi_GetVCPFeature_ReplyCmd_t;

#endif // DDCPROTOCDEFINE_H
