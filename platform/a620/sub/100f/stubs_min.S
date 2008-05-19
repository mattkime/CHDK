#include "stubs_asm.h"

DEF(physw_status, 0x11540)
DEF(physw_run, 0x1fa4)
DEF(zoom_busy, 0x801C4)
DEF(focus_busy, 0x80574)
DEF(FlashParamsTable,0xFFD4C4E8)
DEF(canon_menu_active,0x8DC4)
DEF(canon_shoot_menu_active,0x8221)
DEF(recreview_hold, 0x7D574)

// Found in PutsCameraLog, right before calling the actual 'puts' function
// ROM:FFC07C90   LDR     R3, =0x1048C
// ROM:FFC07C94   LDR     R0, [R3]
// ROM:FFC07C98   BL      LogPutsToBuffer
DEF(dg_cameralog_base, 0x1048C)

