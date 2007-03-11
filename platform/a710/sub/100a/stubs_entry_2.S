#include "stubs_asm.h"

NSTUB(kbd_pwr_on, 0xFFC18800)
NSTUB(kbd_pwr_off, 0xFFC18828)

NSTUB(VbattGet, 0xFFC1C12C)
NSTUB(GetZoomLensCurrentPosition, 0xFFE8F684)
NSTUB(GetZoomLensCurrentPoint, 0xFFE8F670)
NSTUB(GetFocusLensSubjectDistance, 0xFFEA2F3C)

NSTUB(GetSystemTime, 0xFFC04D38)
NSTUB(GetPropertyCase, 0xFFC14DEC)
NSTUB(SetPropertyCase, 0xFFC14C9C)

NSTUB(malloc, 0xFFF00AC0)
NSTUB(free, 0xFFF00ACC)

NSTUB(AllocateMemory, 0xFFC01AB0)
NSTUB(FreeMemory, 0xFFC01ABC)
NSTUB(CreatePhysicalVram, 0xFFD37D50)
NSTUB(DisplayImagePhysicalScreen, 0xFFD36FE0)
NSTUB(PhySw_testgpio, 0xFFC1889C)
NSTUB(RefreshPhysicalScreen, 0xFFD8752C)
NSTUB(isalpha, 0xFFEF4E7C)
NSTUB(isdigit, 0xFFEF4EAC)
NSTUB(islower, 0xFFEF4EDC)
NSTUB(isspace, 0xFFEF4F24)
NSTUB(isupper, 0xFFEF4F3C)
NSTUB(rand, 0xFFEF8360)
NSTUB(srand, 0xFFEF8384)

