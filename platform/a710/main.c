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
