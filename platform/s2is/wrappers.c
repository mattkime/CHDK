#include "../generic/wrappers.c"
#include "keyboard.h"
#include "platform.h"

long lens_get_focus_pos()
{
    static long v=65535;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF))?v=_GetFocusLensSubjectDistance():v;
}

long lens_get_target_distance()
{
    static long v=65535;
    return (kbd_is_key_pressed(KEY_SHOOT_HALF))?v=_GetCurrentTargetDistance():v;
}
