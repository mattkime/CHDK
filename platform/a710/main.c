#include "../generic/main.c"

long get_vbatt_min()
{
    return 2300;
}

long get_vbatt_max()
{
    return 2550;
}

const int dof_tbl[] = {5800, 6420, 7060, 7700, 8340, 9950, 11550, 13160, 14750, 17150, 19570, 22760, 26750, 30750, 34800};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);

static struct {
	int hackmode;
	int canonmode;
} modemap[] = {
    { MODE_AUTO,               6  },
    { MODE_P,                  1  },
    { MODE_TV,                 3  },
    { MODE_AV,                 2  },
    { MODE_M,                  0  },
    { MODE_PORTRAIT,           9  },
    { MODE_NIGHT,              8  },
    { MODE_LANDSCAPE,          7  },
    { MODE_VIDEO,              18 },
    { MODE_STITCH,             5  },
    { MODE_MY_COLORS,          4  },
    { MODE_SCN_WATER,          13 },
    { MODE_SCN_NIGHT,          15 },
    { MODE_SCN_CHILD,          16 },
    { MODE_SCN_PARTY,          14 },
    { MODE_SCN_GRASS,          10 },
    { MODE_SCN_SNOW,           11 },
    { MODE_SCN_BEACH,          12 },
    { MODE_SCN_FIREWORK,       17 }
};
#define MODESCNT (sizeof(modemap)/sizeof(modemap[0]))

int mode_get() {
    int mode, i, t=0xFF;

    mode  = (physw_status[2] & 0x00002000)?MODE_REC:MODE_PLAY;
    mode |= (physw_status[2] & 0x00008000)?0:MODE_SCREEN_OPENED;
    mode |= (physw_status[2] & 0x00004000)?0:MODE_SCREEN_ROTATED;
    
    _GetPropertyCase(0, &t, 4);
    for (i=0; i<MODESCNT; ++i) {
	if (modemap[i].canonmode == t) {
	    return (mode | (modemap[i].hackmode & MODE_SHOOTING_MASK));
	}
    }
    return (mode);
}
