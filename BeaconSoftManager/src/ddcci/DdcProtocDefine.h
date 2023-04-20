#ifndef DDCPROTOCDEFINE_H
#define DDCPROTOCDEFINE_H
typedef unsigned char BYTE;
#define DDC_ORDER_BRIGHT   0x10
#define DDC_ORDER_MENU_KEY 0x03
#define DDC_ORDER_SET_THREE_BRIGHT  0x07

#define DDC_ORDER_CONTROL_TURN  0xD6

#define DDC_ORDER_SET_COLOR 0x92
#define DDC_ORDER_SET_GAMMA 0x91
#define DDC_ORDER_SET_CHANNEL 0x60
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
