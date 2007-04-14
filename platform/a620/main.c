#include "../generic/main.c"

long get_vbatt_min()
{
    return 4550;
}

long get_vbatt_max()
{
    return 5150;
}

const int dof_tbl[] = {7300, 8460, 9565, 10835, 12565, 14926, 17342, 21709, 29200};
const int dof_tbl_size = sizeof(dof_tbl)/sizeof(dof_tbl[0]);
