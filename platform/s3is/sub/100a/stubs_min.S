#include "stubs_asm.h"

DEF(physw_status, 0xF218)
DEF(physw_run, 0x1FB0)
DEF(playrec_mode, 0x6924)
DEF(led_table, 0xF4F8)
DEF(zoom_busy, 0x6C880)
DEF(focus_busy, 0x6CA04)
DEF(FlashParamsTable,0xFF991894)
DEF(canon_menu_active,0x8AEC)
DEF(canon_shoot_menu_active,0x7DA5)
DEF(recreview_hold, 0x69480)

// Found in PutsCameraLogEvent, right before calling the actual 'puts' function
// ROM:FF818124   LDR     R3, =0xE2EC
// ROM:FF818128   LDR     R0, [R3]
// ROM:FF81812C   BL      LogPutsToBuffer
DEF(dg_cameralog_base, 0xE2EC)

