#include "stubs_asm.h"

DEF(physw_status, 0x54648)
DEF(physw_run, 0x7E10)

DEF(zoom_busy, 0x7E12C)
DEF(focus_busy, 0x7D860)

DEF(FlashParamsTable,0xFFEE84EC)
DEF(canon_menu_active,0x2F38)
DEF(canon_shoot_menu_active,0x27B1)
DEF(recreview_hold, 0x2584)

// Found in PutsCameraLogEvent, right before calling the actual 'puts' function
// ROM:FFC059BC   LDR     R3, =0xD9CC
// ROM:FFC059C0   LDR     R0, [R3]
// ROM:FFC059C4   BL      LogPutsToBuffer
DEF(dg_cameralog_base, 0xD9CC)

