#include "stubs_asm.h"

DEF(physw_status, 0x01061c)
DEF(physw_run, 0x1ca4)
DEF(FlashParamsTable,0xFFE7D1B4)
DEF(zoom_busy, 0x9DC0)  //0x9DAC + 0x14
DEF(focus_busy, 0x9D50) //  0x9CB8
DEF(canon_menu_active,0xB55C)
DEF(canon_shoot_menu_active,0xAE15)   // 0xAE14+1
DEF(recreview_hold, 0xABE8) // 0xAB38+0xB0

// Found in PutsCameraLog, right before calling the actual 'puts' function
// ROM:FFC57ECC   LDR     R5, =0x5880
// ROM:FFC57F30   LDR     R0, [R5,#8]
// ROM:FFC57F34   ADD     R1, SP, #0x50+var_4C
// ROM:FFC57F38   BL      sub_FFC1B0CC
DEF(dg_cameralog_base, 0x5888)

