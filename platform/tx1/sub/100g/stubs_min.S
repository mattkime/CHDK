#include "stubs_asm.h"

DEF(physw_run, 0x8738)  
DEF(physw_status, 0x64E00) 
DEF(FlashParamsTable,0xFFB6AECC)
DEF(canon_menu_active,0x3474)
DEF(canon_shoot_menu_active,0x28C9)
DEF(recreview_hold, 0x2684)
DEF(zoom_busy, 0x906D0)
DEF(focus_busy, 0x8F1A0)
DEF(led_table, 0x64DC0)

// Found in PutsCameraLogEvent, right before calling the actual 'puts' function
// ROM:FF815A44   LDR     R3, =0xE8EC
// ROM:FF815A48   LDR     R0, [R3]
// ROM:FF815A4C   BL      LogPutsToBuffer
DEF(dg_cameralog_base, 0xE8EC)

