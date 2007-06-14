#include "../generic/wrappers.c"
#include "keyboard.h"
#include "conf.h"
#include "platform.h"

long lens_get_focus_pos()
{
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || state_kbd_script_run)?_GetFocusLensSubjectDistance():65535;
}

long lens_get_target_distance()
{
    return (kbd_is_key_pressed(KEY_SHOOT_HALF) || state_kbd_script_run)?_GetCurrentTargetDistance():65535;
}
