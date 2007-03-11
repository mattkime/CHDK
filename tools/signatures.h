
static FuncSig func_sig_AllocateMemory[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   3, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   8, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{  11, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  16, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  17, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  18, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ADFDA
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a01043, 0xfdffffff }, // mov:6:0xE3A01043
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007D5
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_Close[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DD0
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   4, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00024D
	{   6, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  10, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EC2
	{  12, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000282
	{  15, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  16, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFB8
	{  21, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCF
	{  23, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_close[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb95c, 0xfdffffff }, // ldr:4:0xE59FB95C
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   5, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   7, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{   8, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   9, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  10, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  11, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000321
	{  13, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  14, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  15, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  17, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  18, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  19, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  20, 0xe1a0f00b, 0xfdffffff }, // mov:6:0xE1A0F00B
	{  21, 0xe08dd00c, 0xfdffffff }, // add:6:0xE28DD00C
	{  22, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_CreateTaskStrict[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe59dc00c, 0xfdffffff }, // ldr:4:0xE59DC00C
	{   3, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBA0
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   6, 0xe1540005, 0xfdffffff }, // cmp:7:0xE3540005
	{   7, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{   8, 0xe1a01019, 0xfdffffff }, // mov:6:0xE3A01019
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC5BA
	{  11, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  12, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF639
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  19, 0xe1540005, 0xfdffffff }, // cmp:7:0xE3540005
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a01025, 0xfdffffff }, // mov:6:0xE3A01025
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC5AD
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_DisableDispatch[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF165
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF177
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1C4
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0x01a0000f, 0xfdffffff }, // mov:6:0x03A0000F
	{   9, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{  10, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  12, 0x60616e45, 0xfdffffff }, // rsb:6:0x62616E45
	{  15, 0x3a000000, 0xff000000 }, // b, bl:3:0x3A206863
	{  17, 0x7066206c, 0xfdffffff }, // rsb:6:0x7266206C
	{  19, 0x7065746e, 0xfdffffff }, // rsb:6:0x7265746E
	{  22, 0x70656c64, 0xfdffffff }, // rsb:6:0x72656C64
	{  23, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_EnableDispatch[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF142
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe59f0020, 0xfdffffff }, // ldr:4:0xE59F0020
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF154
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1AD
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF14F
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  12, 0xe49df004, 0xfdffffff }, // ldr:4:0xE49DF004
	{  21, 0x70726574, 0xfdffffff }, // rsb:6:0x72726574
	{  22, 0x20747075, 0xfdffffff }, // rsb:6:0x20747075
	{ -1, -1, -1 },
	/* 15/24 */
};

static FuncSig func_sig_ExitTask[] = {
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEFFE
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0xe1a07000, 0xfdffffff }, // mov:6:0xE3A07000
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{   5, 0xe59f00e8, 0xfdffffff }, // ldr:4:0xE59F00E8
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF00F
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0D5
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF074
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  12, 0xe59f00d0, 0xfdffffff }, // ldr:4:0xE59F00D0
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFEFE7
	{  15, 0xe59f60c8, 0xfdffffff }, // ldr:4:0xE59F60C8
	{  16, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  17, 0xe1a01065, 0xfdffffff }, // mov:6:0xE3A01065
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF950
	{  21, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000025
	{  23, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_Fclose_Fut[] = {
	{   1, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{   2, 0xe04dd054, 0xfdffffff }, // sub:6:0xE24DD054
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000030
	{   5, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{   6, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098097
	{   8, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{   9, 0xd08d5030, 0xfdffffff }, // add:6:0xD28D5030
	{  10, 0xd1a08005, 0xfdffffff }, // mov:6:0xD1A08005
	{  11, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000003
	{  12, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFEAFDD
	{  14, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  15, 0xe08d8030, 0xfdffffff }, // add:6:0xE28D8030
	{  16, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  17, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098033
	{  19, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  20, 0xe5964008, 0xfdffffff }, // ldr:4:0xE5964008
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCC7
	{  22, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  23, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_Fopen_Fut[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCE8
	{   4, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   5, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000F0B
	{   7, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   8, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001220
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFCEA
	{  13, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{  17, 0xe04dd054, 0xfdffffff }, // sub:6:0xE24DD054
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000030
	{  20, 0xe0864020, 0xfdffffff }, // add:6:0xE2864020
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB098097
	{  23, 0xe1500020, 0xfdffffff }, // cmp:7:0xE3500020
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_Fread_Fut[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC9B
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  13, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001228
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC9D
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  21, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{  22, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  23, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_FreeMemory[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0AF4DC
	{   5, 0x00000064, 0xfdffffff }, // and:6:0x00000064
	{   8, 0x00000000, 0xfdffffff }, // and:6:0x00000000
	{  10, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  12, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  13, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  14, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ADFDA
	{  17, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  18, 0xe1a01043, 0xfdffffff }, // mov:6:0xE3A01043
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007D5
	{  20, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 16/24 */
};

static FuncSig func_sig_Fseek_Fut[] = {
	{   1, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{   2, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC62
	{   8, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   9, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  10, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  11, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0012C8
	{  13, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  14, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC65
	{  16, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  19, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  20, 0xe0840020, 0xfdffffff }, // add:6:0xE2840020
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC52
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_Fwrite_Fut[] = {
	{   1, 0xe0537000, 0xfdffffff }, // sub:6:0xE2537000
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   4, 0xe0870020, 0xfdffffff }, // add:6:0xE2870020
	{   5, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC87
	{   9, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  10, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a03007, 0xfdffffff }, // mov:6:0xE1A03007
	{  13, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001264
	{  15, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC89
	{  18, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  21, 0xe0524000, 0xfdffffff }, // sub:6:0xE2524000
	{  22, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  23, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_GetSystemTime[] = {
	{   1, 0xe59f6030, 0xfdffffff }, // ldr:4:0xE59F6030
	{   2, 0xe5965000, 0xfdffffff }, // ldr:4:0xE5965000
	{   3, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xe1a00017, 0xfdffffff }, // mov:6:0xE3A00017
	{   6, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{   7, 0x15843000, 0xfdffffff }, // str:4:0x15843000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C50
	{  10, 0xe5963008, 0xfdffffff }, // ldr:4:0xE5963008
	{  11, 0xe5843000, 0xfdffffff }, // str:4:0xE5843000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C50
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  15, 0x00001d34, 0xfdffffff }, // and:6:0x00001D34
	{  17, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  18, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{  19, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{  20, 0xe1a08003, 0xfdffffff }, // mov:6:0xE1A08003
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002C44
	{  22, 0xe085e014, 0xfdffffff }, // add:6:0xE285E014
	{  23, 0xe59e2004, 0xfdffffff }, // ldr:4:0xE59E2004
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_ints_disable[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9D
	{   3, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   4, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9F
	{   6, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   7, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9B
	{  10, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  11, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0ABA09
	{  13, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  15, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  16, 0xe1a00726, 0xfdffffff }, // mov:6:0xE3A00726
	{  17, 0xe0800c96, 0xfdffffff }, // add:6:0xE2800C96
	{  18, 0xe0800080, 0xfdffffff }, // add:6:0xE2800080
	{  19, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  20, 0x0000000a, 0xfdffffff }, // and:6:0x0000000A
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_ints_enable[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9F
	{   3, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   4, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   5, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0A5A9B
	{   7, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA0ABA09
	{  10, 0xe1a00001, 0xfdffffff }, // mov:6:0xE3A00001
	{  11, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  12, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  13, 0xe1a00726, 0xfdffffff }, // mov:6:0xE3A00726
	{  14, 0xe0800c96, 0xfdffffff }, // add:6:0xE2800C96
	{  15, 0xe0800080, 0xfdffffff }, // add:6:0xE2800080
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0x0000000a, 0xfdffffff }, // and:6:0x0000000A
	{ -1, -1, -1 },
	/* 18/24 */
};

static FuncSig func_sig_ioctl[] = {
	{   0, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00037F
	{   1, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{   3, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   4, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   5, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   7, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   9, 0xe1520002, 0xfdffffff }, // cmp:7:0xE3520002
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{  11, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00002B
	{  12, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  13, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  18, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000025
	{  19, 0xe1a01008, 0xfdffffff }, // mov:6:0xE3A01008
	{  20, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE9
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001F
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_kbd_p1_f[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002F
	{   3, 0xe59f70a4, 0xfdffffff }, // ldr:4:0xE59F70A4
	{   4, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   5, 0xe59f50a0, 0xfdffffff }, // ldr:4:0xE59F50A0
	{   6, 0xe59f40a0, 0xfdffffff }, // ldr:4:0xE59F40A0
	{   7, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE3A0C002
	{   8, 0xe1a0e006, 0xfdffffff }, // mov:6:0xE1A0E006
	{   9, 0xe1a0210c, 0xfdffffff }, // mov:6:0xE1A0210C
	{  10, 0xe5973002, 0xfdffffff }, // ldr:4:0xE7973002
	{  11, 0xe5951002, 0xfdffffff }, // ldr:4:0xE7951002
	{  12, 0xe5940002, 0xfdffffff }, // ldr:4:0xE7940002
	{  13, 0xe0033001, 0xfdffffff }, // and:6:0xE0033001
	{  15, 0xe05cc001, 0xfdffffff }, // sub:6:0xE25CC001
	{  16, 0xe58e3002, 0xfdffffff }, // str:4:0xE78E3002
	{  17, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF6
	{  18, 0xe59f4074, 0xfdffffff }, // ldr:4:0xE59F4074
	{  19, 0xe59f5074, 0xfdffffff }, // ldr:4:0xE59F5074
	{  20, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  21, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  22, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002B
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_kbd_p1_f_cont[] = {
	{   0, 0xe59f70a4, 0xfdffffff }, // ldr:4:0xE59F70A4
	{   1, 0xe1a0600d, 0xfdffffff }, // mov:6:0xE1A0600D
	{   2, 0xe59f50a0, 0xfdffffff }, // ldr:4:0xE59F50A0
	{   3, 0xe59f40a0, 0xfdffffff }, // ldr:4:0xE59F40A0
	{   4, 0xe1a0c002, 0xfdffffff }, // mov:6:0xE3A0C002
	{   5, 0xe1a0e006, 0xfdffffff }, // mov:6:0xE1A0E006
	{   6, 0xe1a0210c, 0xfdffffff }, // mov:6:0xE1A0210C
	{   7, 0xe5973002, 0xfdffffff }, // ldr:4:0xE7973002
	{   8, 0xe5951002, 0xfdffffff }, // ldr:4:0xE7951002
	{   9, 0xe5940002, 0xfdffffff }, // ldr:4:0xE7940002
	{  10, 0xe0033001, 0xfdffffff }, // and:6:0xE0033001
	{  12, 0xe05cc001, 0xfdffffff }, // sub:6:0xE25CC001
	{  13, 0xe58e3002, 0xfdffffff }, // str:4:0xE78E3002
	{  14, 0x5a000000, 0xff000000 }, // b, bl:3:0x5AFFFFF6
	{  15, 0xe59f4074, 0xfdffffff }, // ldr:4:0xE59F4074
	{  16, 0xe59f5074, 0xfdffffff }, // ldr:4:0xE59F5074
	{  17, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{  18, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  19, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00002B
	{  21, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000345
	{  23, 0xe1a01002, 0xfdffffff }, // mov:6:0xE3A01002
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_kbd_p2_f[] = {
	{   1, 0xe04dd014, 0xfdffffff }, // sub:6:0xE24DD014
	{   2, 0xe08d5007, 0xfdffffff }, // add:6:0xE28D5007
	{   3, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001F
	{   4, 0xe08d4008, 0xfdffffff }, // add:6:0xE28D4008
	{   6, 0xe59f1190, 0xfdffffff }, // ldr:4:0xE59F1190
	{   7, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{   8, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00032D
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000A
	{  12, 0xe59d0000, 0xfdffffff }, // ldr:4:0xE59D0000
	{  13, 0xe1500102, 0xfdffffff }, // cmp:7:0xE3500102
	{  14, 0x11500000, 0xfdffffff }, // cmp:7:0x13500000
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  16, 0xe1500106, 0xfdffffff }, // cmp:7:0xE3500106
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  18, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000059
	{  21, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000000
	{  22, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000081
	{  23, 0xe59fc150, 0xfdffffff }, // ldr:4:0xE59FC150
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_kbd_pwr_off[] = {
	{   0, 0xe1a020d0, 0xfdffffff }, // mov:6:0xE3A020D0
	{   1, 0xe0822103, 0xfdffffff }, // add:6:0xE2822103
	{   2, 0xe0822822, 0xfdffffff }, // add:6:0xE2822822
	{   3, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{   5, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{   6, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   9, 0x00632e6f, 0xfdffffff }, // rsb:6:0x00632E6F
	{  10, 0xe59f1044, 0xfdffffff }, // ldr:4:0xE59F1044
	{  11, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  12, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  13, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB7E5
	{  15, 0xe1500015, 0xfdffffff }, // cmp:7:0xE3500015
	{  17, 0x10032001, 0xfdffffff }, // and:6:0x12032001
	{  18, 0x01a02001, 0xfdffffff }, // mov:6:0x03A02001
	{  19, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  20, 0xe1a0108f, 0xfdffffff }, // mov:6:0xE3A0108F
	{  21, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB138
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_kbd_pwr_on[] = {
	{   0, 0xe1a020d0, 0xfdffffff }, // mov:6:0xE3A020D0
	{   1, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   2, 0xe0822103, 0xfdffffff }, // add:6:0xE2822103
	{   3, 0xe0822822, 0xfdffffff }, // add:6:0xE2822822
	{   4, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{   6, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{   7, 0xe1a00032, 0xfdffffff }, // mov:6:0xE3A00032
	{   8, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{  10, 0xe1a020d0, 0xfdffffff }, // mov:6:0xE3A020D0
	{  11, 0xe0822103, 0xfdffffff }, // add:6:0xE2822103
	{  12, 0xe0822822, 0xfdffffff }, // add:6:0xE2822822
	{  13, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  15, 0xe5823000, 0xfdffffff }, // str:4:0xE5823000
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  19, 0x00632e6f, 0xfdffffff }, // rsb:6:0x00632E6F
	{  20, 0xe59f1044, 0xfdffffff }, // ldr:4:0xE59F1044
	{  21, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{  22, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  23, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_kbd_read_keys_r2[] = {
	{   1, 0xe1a04822, 0xfdffffff }, // mov:6:0xE3A04822
	{   2, 0xe0844a03, 0xfdffffff }, // add:6:0xE2844A03
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000186
	{   6, 0xe59f6038, 0xfdffffff }, // ldr:4:0xE59F6038
	{   8, 0xe1a012a3, 0xfdffffff }, // mov:6:0xE1A012A3
	{   9, 0xe5952101, 0xfdffffff }, // ldr:4:0xE7952101
	{  10, 0xe003301f, 0xfdffffff }, // and:6:0xE203301F
	{  12, 0xe5852101, 0xfdffffff }, // str:4:0xE7852101
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00017D
	{  16, 0xe1a012a2, 0xfdffffff }, // mov:6:0xE1A012A2
	{  17, 0xe5953101, 0xfdffffff }, // ldr:4:0xE7953101
	{  18, 0xe002201f, 0xfdffffff }, // and:6:0xE202201F
	{  20, 0xe5853101, 0xfdffffff }, // str:4:0xE7853101
	{ -1, -1, -1 },
	/* 14/24 */
};

static FuncSig func_sig_lseek[] = {
	{   0, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   6, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   8, 0xe1520002, 0xfdffffff }, // cmp:7:0xE3520002
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{  10, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00002B
	{  11, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{  12, 0xe1a01007, 0xfdffffff }, // mov:6:0xE3A01007
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  14, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  16, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000025
	{  18, 0xe1a01008, 0xfdffffff }, // mov:6:0xE3A01008
	{  19, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFE9
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001F
	{  23, 0xe08bb000, 0xfdffffff }, // add:6:0xE08BB000
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_MakeDirectory[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFCD
	{   4, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   5, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500D
	{   6, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   7, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF1A
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF29
	{  12, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000
	{  13, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  14, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  15, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EA9
	{  18, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  19, 0xe1a01020, 0xfdffffff }, // mov:6:0xE3A01020
	{  20, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008
	{  21, 0xe1a0a006, 0xfdffffff }, // mov:6:0xE1A0A006
	{  22, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000004
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D62
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_memcmp[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   1, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   2, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   7, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   9, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  13, 0xe04c0003, 0xfdffffff }, // sub:6:0xE04C0003
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  16, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  17, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{  18, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB3B7
	{  20, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  22, 0xe1510000, 0xfdffffff }, // cmp:7:0xE1510000
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_memcpy[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   3, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB3B7
	{   5, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   7, 0xe1510000, 0xfdffffff }, // cmp:7:0xE1510000
	{   9, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  10, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{  11, 0x2a000000, 0xff000000 }, // b, bl:3:0x2A00000E
	{  12, 0xe081c002, 0xfdffffff }, // add:6:0xE081C002
	{  13, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE15C0000
	{  14, 0x9a000000, 0xff000000 }, // b, bl:3:0x9A00000B
	{  15, 0xe0811002, 0xfdffffff }, // add:6:0xE0811002
	{  16, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  17, 0xe080b002, 0xfdffffff }, // add:6:0xE080B002
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  20, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_memset[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xe1a01003, 0xfdffffff }, // mov:6:0xE1A01003
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB5B8
	{   6, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{   8, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  10, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{  12, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001
	{  14, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  17, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  18, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  19, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{  21, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{  22, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_mkdir[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0500d, 0xfdffffff }, // mov:6:0xE1A0500D
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xe1a01004, 0xfdffffff }, // mov:6:0xE1A01004
	{   5, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF4C
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF5B
	{   9, 0xe1a06000, 0xfdffffff }, // mov:6:0xE3A06000
	{  10, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{  11, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  12, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{  13, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EDB
	{  15, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{  16, 0xe1a0101f, 0xfdffffff }, // mov:6:0xE3A0101F
	{  17, 0xe1a02008, 0xfdffffff }, // mov:6:0xE1A02008
	{  18, 0xe1a0a006, 0xfdffffff }, // mov:6:0xE1A0A006
	{  19, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000004
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D94
	{  21, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  22, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097D41
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_Open[] = {
	{   1, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{   2, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F6A
	{   4, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{   5, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00022B
	{   8, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DD0
	{  13, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00024D
	{  16, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097EC2
	{  22, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{  23, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_open[] = {
	{   0, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{   1, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF68
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   4, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{   6, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  11, 0xe1a00002, 0xfdffffff }, // mov:6:0xE3A00002
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF04A
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000E
	{  15, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  16, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFED
	{  18, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  19, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  21, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000007
	{  22, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  23, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_PhySw_testgpio[] = {
	{   1, 0xe59f3068, 0xfdffffff }, // ldr:4:0xE59F3068
	{   2, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   3, 0xe1a03800, 0xfdffffff }, // mov:6:0xE1A03800
	{   4, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   5, 0xe1a010c1, 0xfdffffff }, // mov:6:0xE3A010C1
	{   6, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{   7, 0xe1a04843, 0xfdffffff }, // mov:6:0xE1A04843
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFB112
	{  11, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  12, 0xe1a03804, 0xfdffffff }, // mov:6:0xE1A03804
	{  13, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  14, 0xe1b03823, 0xfdffffff }, // mov:6:0xE1B03823
	{  15, 0xe0822173, 0xfdffffff }, // add:6:0xE2822173
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  17, 0xe1a02822, 0xfdffffff }, // mov:6:0xE3A02822
	{  18, 0xe0822a03, 0xfdffffff }, // add:6:0xE2822A03
	{  19, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{  20, 0xe0822193, 0xfdffffff }, // add:6:0xE2822193
	{  21, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{  22, 0xe1a010d2, 0xfdffffff }, // mov:6:0xE3A010D2
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_ProtectFile[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   3, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D94
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   7, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   8, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000E
	{  10, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D46
	{  12, 0xe0505000, 0xfdffffff }, // sub:6:0xE2505000
	{  13, 0xd1a00000, 0xfdffffff }, // mov:6:0xD3A00000
	{  14, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000009
	{  15, 0xe59d1004, 0xfdffffff }, // ldr:4:0xE59D1004
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001DB8
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  19, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001D47
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  23, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_Read[] = {
	{   0, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{   1, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DC3
	{   4, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DDC
	{   6, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   7, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   8, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000216
	{   9, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{  12, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  13, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F32
	{  15, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  16, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  17, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00027A
	{  19, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  21, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  22, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DE7
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_read[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb8fc, 0xfdffffff }, // ldr:4:0xE59FB8FC
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   5, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   6, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{  10, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  11, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  12, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  13, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  14, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008
	{  15, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000339
	{  17, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  18, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  21, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_reateTaskStrict[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe59dc00c, 0xfdffffff }, // ldr:4:0xE59DC00C
	{   3, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFBA0
	{   5, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   6, 0xe1540005, 0xfdffffff }, // cmp:7:0xE3540005
	{   7, 0xe59f0018, 0xfdffffff }, // ldr:4:0xE59F0018
	{   8, 0xe1a01019, 0xfdffffff }, // mov:6:0xE3A01019
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC5BA
	{  11, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  12, 0xe08dd004, 0xfdffffff }, // add:6:0xE28DD004
	{  14, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF639
	{  18, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  19, 0xe1540005, 0xfdffffff }, // cmp:7:0xE3540005
	{  20, 0xe59f0010, 0xfdffffff }, // ldr:4:0xE59F0010
	{  21, 0xe1a01025, 0xfdffffff }, // mov:6:0xE3A01025
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  23, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFC5AD
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_sprintf[] = {
	{   2, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{   3, 0xe59f2b48, 0xfdffffff }, // ldr:4:0xE59F2B48
	{   4, 0xe08d100c, 0xfdffffff }, // add:6:0xE28D100C
	{   5, 0xe08d3004, 0xfdffffff }, // add:6:0xE28D3004
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFC51
	{   7, 0xe59dc004, 0xfdffffff }, // ldr:4:0xE59DC004
	{   8, 0xe1a03000, 0xfdffffff }, // mov:6:0xE3A03000
	{   9, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{  12, 0xe08dd010, 0xfdffffff }, // add:6:0xE28DD010
	{  13, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  14, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  16, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01C
	{  17, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  18, 0xe58d2040, 0xfdffffff }, // str:4:0xE58D2040
	{  19, 0xe58d3044, 0xfdffffff }, // str:4:0xE58D3044
	{  20, 0xe59fcb0c, 0xfdffffff }, // ldr:4:0xE59FCB0C
	{  21, 0xe1a04001, 0xfdffffff }, // mov:6:0xE1A04001
	{  22, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  23, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_strcmp[] = {
	{   2, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF8
	{   7, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  10, 0xe04c0003, 0xfdffffff }, // sub:6:0xE04C0003
	{  11, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  13, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  14, 0xe0808020, 0xfdffffff }, // add:6:0xE2808020
	{  15, 0xe080902c, 0xfdffffff }, // add:6:0xE280902C
	{  16, 0xe58bb028, 0xfdffffff }, // str:4:0xE58BB028
	{  17, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  18, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008
	{  19, 0xe1a02020, 0xfdffffff }, // mov:6:0xE3A02020
	{  20, 0xe1a03009, 0xfdffffff }, // mov:6:0xE1A03009
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000140
	{  22, 0xe1b0a000, 0xfdffffff }, // mov:6:0xE1B0A000
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_strcpy[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   2, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{   5, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{   6, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   7, 0xe0802001, 0xfdffffff }, // add:6:0xE2802001
	{  10, 0xe1590000, 0xfdffffff }, // cmp:7:0xE3590000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000005
	{  12, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{  14, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0AFFFFF8
	{  16, 0xe159000a, 0xfdffffff }, // cmp:7:0xE159000A
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  18, 0xe0400002, 0xfdffffff }, // sub:6:0xE0400002
	{  21, 0xe04dd01c, 0xfdffffff }, // sub:6:0xE24DD01C
	{  22, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  23, 0xe1b0a001, 0xfdffffff }, // mov:6:0xE1B0A001
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_strlen[] = {
	{   0, 0xe0801001, 0xfdffffff }, // add:6:0xE2801001
	{   2, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{   4, 0xe0400001, 0xfdffffff }, // sub:6:0xE0400001
	{   5, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   6, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000E
	{   9, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  11, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{  13, 0xe04bb001, 0xfdffffff }, // sub:6:0xE24BB001
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000001
	{  15, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  18, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{  21, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  22, 0x01a0c000, 0xfdffffff }, // mov:6:0x03A0C000
	{ -1, -1, -1 },
	/* 18/24 */
};

static FuncSig func_sig_TakeSemaphore[] = {
	{   1, 0xe0506000, 0xfdffffff }, // sub:6:0xE2506000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   4, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000015
	{   5, 0xe0165003, 0xfdffffff }, // and:6:0xE2165003
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000013
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF264
	{   8, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  10, 0xe59f0140, 0xfdffffff }, // ldr:4:0xE59F0140
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF276
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF2DD
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  15, 0xe59f0130, 0xfdffffff }, // ldr:4:0xE59F0130
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF271
	{  17, 0xe58d5000, 0xfdffffff }, // str:4:0xE58D5000
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF336
	{  19, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF24D
	{  21, 0xe5963000, 0xfdffffff }, // ldr:4:0xE5963000
	{  22, 0xe0433002, 0xfdffffff }, // sub:6:0xE2433002
	{  23, 0xe1530001, 0xfdffffff }, // cmp:7:0xE3530001
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskIdListGet[] = {
	{   1, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001A9
	{   5, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   6, 0xe1a0200a, 0xfdffffff }, // mov:6:0xE1A0200A
	{   7, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{   8, 0xe590300c, 0xfdffffff }, // ldr:4:0xE590300C
	{   9, 0xe5933030, 0xfdffffff }, // ldr:4:0xE5933030
	{  10, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  11, 0xe1a0f003, 0xfdffffff }, // mov:6:0xE1A0F003
	{  12, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001CA
	{  14, 0xe1590000, 0xfdffffff }, // cmp:7:0xE3590000
	{  15, 0xda000000, 0xff000000 }, // b, bl:3:0xDA000005
	{  16, 0xe1a0a009, 0xfdffffff }, // mov:6:0xE1A0A009
	{  17, 0xe59bc000, 0xfdffffff }, // ldr:4:0xE59BC000
	{  18, 0xe05aa001, 0xfdffffff }, // sub:6:0xE25AA001
	{  19, 0xe04cc020, 0xfdffffff }, // sub:6:0xE24CC020
	{  20, 0xe48bc004, 0xfdffffff }, // str:4:0xE48BC004
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  22, 0xe08dd008, 0xfdffffff }, // add:6:0xE28DD008
	{  23, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskLock[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59fc970, 0xfdffffff }, // ldr:4:0xE59FC970
	{   3, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001B
	{   6, 0xe59f3964, 0xfdffffff }, // ldr:4:0xE59F3964
	{   7, 0xe1a0b211, 0xfdffffff }, // mov:6:0xE3A0B211
	{   8, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{   9, 0xe0033211, 0xfdffffff }, // and:6:0xE2033211
	{  10, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  12, 0xe59fcea0, 0xfdffffff }, // ldr:4:0xE59FCEA0
	{  13, 0xe1a00039, 0xfdffffff }, // mov:6:0xE3A00039
	{  14, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  16, 0xe1a0f00c, 0xfdffffff }, // mov:6:0xE1A0F00C
	{  17, 0xe59fca14, 0xfdffffff }, // ldr:4:0xE59FCA14
	{  18, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  19, 0xe00cc00b, 0xfdffffff }, // and:6:0xE00CC00B
	{  20, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  21, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000B
	{  22, 0xe59fca08, 0xfdffffff }, // ldr:4:0xE59FCA08
	{  23, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskName[] = {
	{   1, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000606
	{   2, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   3, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   5, 0xe5900034, 0xfdffffff }, // ldr:4:0xE5900034
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x059f0158, 0xfdffffff }, // ldr:4:0x059F0158
	{  10, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  11, 0xe59fb14c, 0xfdffffff }, // ldr:4:0xE59FB14C
	{  12, 0xe59f114c, 0xfdffffff }, // ldr:4:0xE59F114C
	{  13, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{  14, 0xe59b300c, 0xfdffffff }, // ldr:4:0xE59B300C
	{  15, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  16, 0xe5933034, 0xfdffffff }, // ldr:4:0xE5933034
	{  17, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  18, 0xe1a0f003, 0xfdffffff }, // mov:6:0xE1A0F003
	{  19, 0xe1b0a000, 0xfdffffff }, // mov:6:0xE1B0A000
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFAEE0
	{  22, 0xe59fc128, 0xfdffffff }, // ldr:4:0xE59FC128
	{  23, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_taskResume[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59fcd50, 0xfdffffff }, // ldr:4:0xE59FCD50
	{   3, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   4, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000032
	{   7, 0xe59f3d40, 0xfdffffff }, // ldr:4:0xE59F3D40
	{   8, 0xe1a0b271, 0xfdffffff }, // mov:6:0xE3A0B271
	{   9, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  10, 0xe0033271, 0xfdffffff }, // and:6:0xE2033271
	{  11, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000018
	{  13, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000016
	{  15, 0xe59f0d08, 0xfdffffff }, // ldr:4:0xE59F0D08
	{  16, 0xe59ab030, 0xfdffffff }, // ldr:4:0xE59AB030
	{  17, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  18, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE15B0000
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000008
	{  20, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  22, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  23, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskSuspend[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe1b09000, 0xfdffffff }, // mov:6:0xE1B09000
	{   3, 0x059faf1c, 0xfdffffff }, // ldr:4:0x059FAF1C
	{   4, 0xe59fcf1c, 0xfdffffff }, // ldr:4:0xE59FCF1C
	{   5, 0x059aa000, 0xfdffffff }, // ldr:4:0x059AA000
	{   6, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   7, 0x11a0a000, 0xfdffffff }, // mov:6:0x11A0A000
	{   8, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000032
	{  10, 0xe59f3f08, 0xfdffffff }, // ldr:4:0xE59F3F08
	{  11, 0xe1a0b271, 0xfdffffff }, // mov:6:0xE3A0B271
	{  12, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  13, 0xe0033271, 0xfdffffff }, // and:6:0xE2033271
	{  14, 0xe153000b, 0xfdffffff }, // cmp:7:0xE153000B
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000019
	{  16, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000017
	{  18, 0xe59f0ed0, 0xfdffffff }, // ldr:4:0xE59F0ED0
	{  19, 0xe59ab030, 0xfdffffff }, // ldr:4:0xE59AB030
	{  20, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  21, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE15B0000
	{  22, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000
	{  23, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskUnlock[] = {
	{   1, 0xe04dd018, 0xfdffffff }, // sub:6:0xE24DD018
	{   2, 0xe59f98c8, 0xfdffffff }, // ldr:4:0xE59F98C8
	{   3, 0xe59fb8c0, 0xfdffffff }, // ldr:4:0xE59FB8C0
	{   4, 0xe599c000, 0xfdffffff }, // ldr:4:0xE599C000
	{   5, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00001B
	{   8, 0xe59f38b4, 0xfdffffff }, // ldr:4:0xE59F38B4
	{   9, 0xe1a0a211, 0xfdffffff }, // mov:6:0xE3A0A211
	{  10, 0xe5933000, 0xfdffffff }, // ldr:4:0xE5933000
	{  11, 0xe0033211, 0xfdffffff }, // and:6:0xE2033211
	{  12, 0xe153000a, 0xfdffffff }, // cmp:7:0xE153000A
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  14, 0xe59fcdf0, 0xfdffffff }, // ldr:4:0xE59FCDF0
	{  15, 0xe1a0003a, 0xfdffffff }, // mov:6:0xE3A0003A
	{  16, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  17, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  18, 0xe1a0f00c, 0xfdffffff }, // mov:6:0xE1A0F00C
	{  19, 0xe59fc964, 0xfdffffff }, // ldr:4:0xE59FC964
	{  20, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  21, 0xe00cc00a, 0xfdffffff }, // and:6:0xE00CC00A
	{  22, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE15C000A
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000B
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_Write[] = {
	{   1, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097DDC
	{   3, 0xe1a05000, 0xfdffffff }, // mov:6:0xE1A05000
	{   4, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000216
	{   6, 0xe1a00005, 0xfdffffff }, // mov:6:0xE1A00005
	{   9, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  10, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB097F32
	{  12, 0xe1a01005, 0xfdffffff }, // mov:6:0xE1A01005
	{  13, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  14, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00027A
	{  16, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  18, 0xe52de004, 0xfdffffff }, // str:4:0xE52DE004
	{  19, 0xe49de004, 0xfdffffff }, // ldr:4:0xE49DE004
	{  20, 0xea000000, 0xff000000 }, // b, bl:3:0xEA097DE7
	{  22, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  23, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_write[] = {
	{   1, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   2, 0xe59fb88c, 0xfdffffff }, // ldr:4:0xE59FB88C
	{   3, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   4, 0xe1a08001, 0xfdffffff }, // mov:6:0xE1A08001
	{   5, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   6, 0xe59ba000, 0xfdffffff }, // ldr:4:0xE59BA000
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe08d1008, 0xfdffffff }, // add:6:0xE28D1008
	{  10, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  11, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  12, 0xe1a0f00a, 0xfdffffff }, // mov:6:0xE1A0F00A
	{  13, 0xe1a00009, 0xfdffffff }, // mov:6:0xE1A00009
	{  14, 0xe1a01008, 0xfdffffff }, // mov:6:0xE1A01008
	{  15, 0xe1a02007, 0xfdffffff }, // mov:6:0xE1A02007
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000354
	{  17, 0xe59bb000, 0xfdffffff }, // ldr:4:0xE59BB000
	{  18, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  19, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  21, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskCreateHookAdd[] = {
	{   0, 0xe59f1380, 0xfdffffff }, // ldr:4:0xE59F1380
	{   1, 0xe1a02010, 0xfdffffff }, // mov:6:0xE3A02010
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFE3
	{   4, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   5, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   6, 0xe1a0a002, 0xfdffffff }, // mov:6:0xE1A0A002
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B17
	{   8, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   9, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  10, 0xda000000, 0xff000000 }, // b, bl:3:0xDA00000E
	{  11, 0xe59bc100, 0xfdffffff }, // ldr:4:0xE79BC100
	{  12, 0xe15c0009, 0xfdffffff }, // cmp:7:0xE15C0009
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{  14, 0xe08bb100, 0xfdffffff }, // add:6:0xE08BB100
	{  15, 0xe59bc004, 0xfdffffff }, // ldr:4:0xE59BC004
	{  16, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{  17, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  18, 0xe48bc004, 0xfdffffff }, // str:4:0xE48BC004
	{  19, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFA
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B34
	{  21, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000006
	{  23, 0xe0800001, 0xfdffffff }, // add:6:0xE2800001
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_taskDeleteHookAdd[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B4C
	{   4, 0xe59f042c, 0xfdffffff }, // ldr:4:0xE59F042C
	{   5, 0xe590c040, 0xfdffffff }, // ldr:4:0xE590C040
	{   6, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   8, 0xe59f0410, 0xfdffffff }, // ldr:4:0xE59F0410
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFD85F
	{  11, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000008
	{  12, 0xe1a0200e, 0xfdffffff }, // mov:6:0xE3A0200E
	{  13, 0xe0801038, 0xfdffffff }, // add:6:0xE2801038
	{  14, 0xe591c000, 0xfdffffff }, // ldr:4:0xE591C000
	{  15, 0xe0422001, 0xfdffffff }, // sub:6:0xE2422001
	{  16, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  17, 0xe581c004, 0xfdffffff }, // str:4:0xE581C004
	{  18, 0xe0411004, 0xfdffffff }, // sub:6:0xE2411004
	{  19, 0xaa000000, 0xff000000 }, // b, bl:3:0xAAFFFFF9
	{  20, 0xe580a000, 0xfdffffff }, // str:4:0xE580A000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002B64
	{  22, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_SleepTask[] = {
	{   1, 0xe0507000, 0xfdffffff }, // sub:6:0xE2507000
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000023
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF126
	{   5, 0xe1a08000, 0xfdffffff }, // mov:6:0xE3A08000
	{   6, 0xe1500008, 0xfdffffff }, // cmp:7:0xE1500008
	{   7, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF137
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF1FD
	{  11, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF114
	{  13, 0xe1a02004, 0xfdffffff }, // mov:6:0xE1A02004
	{  14, 0xe1a01065, 0xfdffffff }, // mov:6:0xE3A01065
	{  15, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{  16, 0xe59f0068, 0xfdffffff }, // ldr:4:0xE59F0068
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFA7E
	{  18, 0xe0504000, 0xfdffffff }, // sub:6:0xE2504000
	{  19, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007
	{  20, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{  21, 0xe0440014, 0xfdffffff }, // sub:6:0xE2440014
	{  22, 0xe0445058, 0xfdffffff }, // sub:6:0xE2445058
	{  23, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_CreateTask[] = {
	{   1, 0xe0509000, 0xfdffffff }, // sub:6:0xE2509000
	{   2, 0xe04dd00c, 0xfdffffff }, // sub:6:0xE24DD00C
	{   3, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   4, 0xe1a07002, 0xfdffffff }, // mov:6:0xE1A07002
	{   5, 0xe1a0b003, 0xfdffffff }, // mov:6:0xE1A0B003
	{   6, 0x059f31a8, 0xfdffffff }, // ldr:4:0x059F31A8
	{   7, 0x05939000, 0xfdffffff }, // ldr:4:0x05939000
	{   8, 0xe04a3001, 0xfdffffff }, // sub:6:0xE24A3001
	{   9, 0xe153001f, 0xfdffffff }, // cmp:7:0xE353001F
	{  10, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000001
	{  11, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  12, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000001
	{  13, 0xe1a00003, 0xfdffffff }, // mov:6:0xE3A00003
	{  14, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00005F
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0E0
	{  16, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  18, 0xe59f017c, 0xfdffffff }, // ldr:4:0xE59F017C
	{  19, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0F2
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF0D1
	{  21, 0xe59f2174, 0xfdffffff }, // ldr:4:0xE59F2174
	{  22, 0xe5923000, 0xfdffffff }, // ldr:4:0xE5923000
	{  23, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_CreatePhysicalVram[] = {
	{   1, 0xe59fc098, 0xfdffffff }, // ldr:4:0xE59FC098
	{   2, 0xe59ce000, 0xfdffffff }, // ldr:4:0xE59CE000
	{   3, 0xe15e0001, 0xfdffffff }, // cmp:7:0xE35E0001
	{   4, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   5, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   6, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   7, 0xe1a010d4, 0xfdffffff }, // mov:6:0xE3A010D4
	{   8, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   9, 0xe1a04003, 0xfdffffff }, // mov:6:0xE1A04003
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFBC6EE
	{  12, 0xe1550000, 0xfdffffff }, // cmp:7:0xE3550000
	{  13, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  14, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{  15, 0xe1570000, 0xfdffffff }, // cmp:7:0xE3570000
	{  17, 0xe1530000, 0xfdffffff }, // cmp:7:0xE3530000
	{  18, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{  19, 0xe1a010d7, 0xfdffffff }, // mov:6:0xE3A010D7
	{  20, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000006
	{  21, 0xe1540000, 0xfdffffff }, // cmp:7:0xE3540000
	{  22, 0x11a03000, 0xfdffffff }, // mov:6:0x13A03000
	{  23, 0x01a03001, 0xfdffffff }, // mov:6:0x03A03001
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_DisplayImagePhysicalScreen[] = {
	{   1, 0xe59f2198, 0xfdffffff }, // ldr:4:0xE59F2198
	{   2, 0xe1a04001, 0xfdffffff }, // mov:6:0xE3A04001
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   4, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   5, 0xe1a08004, 0xfdffffff }, // mov:6:0xE1A08004
	{   6, 0xe1560002, 0xfdffffff }, // cmp:7:0xE1560002
	{   7, 0xe1a05003, 0xfdffffff }, // mov:6:0xE1A05003
	{   8, 0xe59d7034, 0xfdffffff }, // ldr:4:0xE59D7034
	{   9, 0xe1a09004, 0xfdffffff }, // mov:6:0xE1A09004
	{  10, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{  11, 0xe1a0a008, 0xfdffffff }, // mov:6:0xE1A0A008
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000D
	{  13, 0x8a000000, 0xff000000 }, // b, bl:3:0x8A000005
	{  14, 0xe1a03541, 0xfdffffff }, // mov:6:0xE3A03541
	{  15, 0xe0833aaf, 0xfdffffff }, // add:6:0xE2833AAF
	{  16, 0xe0833eaa, 0xfdffffff }, // add:6:0xE2833EAA
	{  17, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  18, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000D
	{  20, 0xe59f3150, 0xfdffffff }, // ldr:4:0xE59F3150
	{  21, 0xe1560003, 0xfdffffff }, // cmp:7:0xE1560003
	{  22, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  23, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000009
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_ExecuteEventProcedure[] = {
	{   2, 0xe59f3088, 0xfdffffff }, // ldr:4:0xE59F3088
	{   3, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   4, 0xe59fc084, 0xfdffffff }, // ldr:4:0xE59FC084
	{   5, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{   6, 0xe59d1010, 0xfdffffff }, // ldr:4:0xE59D1010
	{   7, 0xe1a0200d, 0xfdffffff }, // mov:6:0xE1A0200D
	{   8, 0xe58dc000, 0xfdffffff }, // str:4:0xE58DC000
	{   9, 0xe08d5014, 0xfdffffff }, // add:6:0xE28D5014
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFE7D
	{  11, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{  12, 0xe1500019, 0xfdffffff }, // cmp:7:0xE3500019
	{  13, 0xe59f1068, 0xfdffffff }, // ldr:4:0xE59F1068
	{  14, 0xe59f2068, 0xfdffffff }, // ldr:4:0xE59F2068
	{  15, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{  17, 0xe59d3010, 0xfdffffff }, // ldr:4:0xE59D3010
	{  18, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0ACBD0
	{  19, 0xe1a00004, 0xfdffffff }, // mov:6:0xE1A00004
	{  20, 0xe59f3054, 0xfdffffff }, // ldr:4:0xE59F3054
	{  21, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  22, 0xe593f000, 0xfdffffff }, // ldr:4:0xE593F000
	{  23, 0xe59f304c, 0xfdffffff }, // ldr:4:0xE59F304C
	{ -1, -1, -1 },
	/* 22/24 */
};

static FuncSig func_sig_GetPropertyCase[] = {
	{   1, 0xe59f3064, 0xfdffffff }, // ldr:4:0xE59F3064
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   4, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   5, 0xe1a01e11, 0xfdffffff }, // mov:6:0xE3A01E11
	{   6, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   7, 0xe59f5050, 0xfdffffff }, // ldr:4:0xE59F5050
	{   8, 0xe59f0050, 0xfdffffff }, // ldr:4:0xE59F0050
	{   9, 0xe0811001, 0xfdffffff }, // add:6:0xE2811001
	{  10, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBE3C
	{  13, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  14, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  15, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF29C
	{  17, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  18, 0xe1a01007, 0xfdffffff }, // mov:6:0xE1A01007
	{  19, 0xe1a02006, 0xfdffffff }, // mov:6:0xE1A02006
	{  20, 0xe5950000, 0xfdffffff }, // ldr:4:0xE5950000
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFC3
	{  22, 0xe5953000, 0xfdffffff }, // ldr:4:0xE5953000
	{  23, 0xe1a04000, 0xfdffffff }, // mov:6:0xE1A04000
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_SetPropertyCase[] = {
	{   1, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{   2, 0xe593c000, 0xfdffffff }, // ldr:4:0xE593C000
	{   3, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   4, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   5, 0xe1a05001, 0xfdffffff }, // mov:6:0xE1A05001
	{   6, 0xe59f705c, 0xfdffffff }, // ldr:4:0xE59F705C
	{   7, 0xe59f005c, 0xfdffffff }, // ldr:4:0xE59F005C
	{   8, 0xe1a010e9, 0xfdffffff }, // mov:6:0xE3A010E9
	{   9, 0xe1a04002, 0xfdffffff }, // mov:6:0xE1A04002
	{  10, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000000
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFBE84
	{  12, 0xe5973000, 0xfdffffff }, // ldr:4:0xE5973000
	{  13, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  14, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF2E4
	{  16, 0xe1a01006, 0xfdffffff }, // mov:6:0xE1A01006
	{  17, 0xe1a02005, 0xfdffffff }, // mov:6:0xE1A02005
	{  18, 0xe1a03004, 0xfdffffff }, // mov:6:0xE1A03004
	{  19, 0xe5970000, 0xfdffffff }, // ldr:4:0xE5970000
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFF8A
	{  21, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  22, 0xe1a010ee, 0xfdffffff }, // mov:6:0xE3A010EE
	{  23, 0xe59f001c, 0xfdffffff }, // ldr:4:0xE59F001C
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_malloc[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0070, 0xfdffffff }, // ldr:4:0xE59F0070
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFFDF
	{   3, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   4, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   6, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   7, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   8, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   9, 0xea000000, 0xff000000 }, // b, bl:3:0xEA003068
	{  10, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{  11, 0x0000eb7c, 0xfdffffff }, // and:6:0x0000EB7C
	{  12, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  13, 0x000a0754, 0xfdffffff }, // and:6:0x000A0754
	{  14, 0x0000eb64, 0xfdffffff }, // and:6:0x0000EB64
	{  16, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  17, 0x0000e9ac, 0xfdffffff }, // and:6:0x0000E9AC
	{  18, 0x000a0318, 0xfdffffff }, // and:6:0x000A0318
	{  19, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  20, 0x000a0260, 0xfdffffff }, // and:6:0x000A0260
	{  21, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  22, 0x000a0244, 0xfdffffff }, // and:6:0x000A0244
	{  23, 0x0000eb74, 0xfdffffff }, // and:6:0x0000EB74
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_free[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   5, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA003068
	{   7, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{   8, 0x0000eb7c, 0xfdffffff }, // and:6:0x0000EB7C
	{   9, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  10, 0x000a0754, 0xfdffffff }, // and:6:0x000A0754
	{  11, 0x0000eb64, 0xfdffffff }, // and:6:0x0000EB64
	{  13, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  14, 0x0000e9ac, 0xfdffffff }, // and:6:0x0000E9AC
	{  15, 0x000a0318, 0xfdffffff }, // and:6:0x000A0318
	{  16, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  17, 0x000a0260, 0xfdffffff }, // and:6:0x000A0260
	{  18, 0x10000100, 0xfdffffff }, // and:6:0x10000100
	{  19, 0x000a0244, 0xfdffffff }, // and:6:0x000A0244
	{  20, 0x0000eb74, 0xfdffffff }, // and:6:0x0000EB74
	{  21, 0x0000eb70, 0xfdffffff }, // and:6:0x0000EB70
	{  22, 0x000a0368, 0xfdffffff }, // and:6:0x000A0368
	{  23, 0x0000eb88, 0xfdffffff }, // and:6:0x0000EB88
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_strcat[] = {
	{   0, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   2, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   3, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFC
	{   4, 0xe0400001, 0xfdffffff }, // sub:6:0xE2400001
	{   6, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{   8, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{   9, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{  13, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{  14, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{  16, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  17, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{  18, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  19, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  22, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{ -1, -1, -1 },
	/* 16/24 */
};

static FuncSig func_sig_strchr[] = {
	{   0, 0xe00110ff, 0xfdffffff }, // and:6:0xE20110FF
	{   2, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{   3, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   6, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF9
	{   7, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  14, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF8
	{  16, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  17, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  19, 0xe04c0003, 0xfdffffff }, // sub:6:0xE04C0003
	{  20, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  22, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  23, 0xe0808020, 0xfdffffff }, // add:6:0xE2808020
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_RefreshPhysicalScreen[] = {
	{   1, 0xe04dd010, 0xfdffffff }, // sub:6:0xE24DD010
	{   2, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0002AA
	{   3, 0xe0105001, 0xfdffffff }, // and:6:0xE2105001
	{   4, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000022
	{   5, 0xe59f3090, 0xfdffffff }, // ldr:4:0xE59F3090
	{   6, 0xe5932000, 0xfdffffff }, // ldr:4:0xE5932000
	{   7, 0xe1520001, 0xfdffffff }, // cmp:7:0xE3520001
	{   8, 0xe59f0088, 0xfdffffff }, // ldr:4:0xE59F0088
	{   9, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000003
	{  10, 0xe59f3084, 0xfdffffff }, // ldr:4:0xE59F3084
	{  11, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFAC5D4
	{  13, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000019
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFA9C6A
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF476
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFF113
	{  17, 0xe59f406c, 0xfdffffff }, // ldr:4:0xE59F406C
	{  18, 0xe59fe06c, 0xfdffffff }, // ldr:4:0xE59FE06C
	{  19, 0xe59f306c, 0xfdffffff }, // ldr:4:0xE59F306C
	{  20, 0xe59fc06c, 0xfdffffff }, // ldr:4:0xE59FC06C
	{  21, 0xe5931000, 0xfdffffff }, // ldr:4:0xE5931000
	{  22, 0xe59e2000, 0xfdffffff }, // ldr:4:0xE59E2000
	{  23, 0xe59c3000, 0xfdffffff }, // ldr:4:0xE59C3000
	{ -1, -1, -1 },
	/* 23/24 */
};

static FuncSig func_sig_opendir[] = {
	{   1, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001196
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   7, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000019
	{   9, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  10, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  12, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000D
	{  15, 0xe00cca0f, 0xfdffffff }, // and:6:0xE20CCA0F
	{  16, 0xe1a0c80c, 0xfdffffff }, // mov:6:0xE1A0C80C
	{  17, 0xe1a0c82c, 0xfdffffff }, // mov:6:0xE1A0C82C
	{  18, 0xe15c0901, 0xfdffffff }, // cmp:7:0xE35C0901
	{  19, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  20, 0xe1a00014, 0xfdffffff }, // mov:6:0xE3A00014
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0001DD
	{  22, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{  23, 0xe1a0006c, 0xfdffffff }, // mov:6:0xE3A0006C
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_closedir[] = {
	{   1, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   3, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001013
	{   5, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   6, 0x11a0000a, 0xfdffffff }, // mov:6:0x11A0000A
	{   7, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B001C22
	{   8, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  11, 0xe1a01026, 0xfdffffff }, // mov:6:0xE3A01026
	{  12, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00105A
	{  14, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  15, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  16, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001196
	{  19, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  20, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  21, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000019
	{  22, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  23, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_readdir[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   3, 0xe1a01025, 0xfdffffff }, // mov:6:0xE3A01025
	{   4, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00106E
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x11a00000, 0xfdffffff }, // mov:6:0x13A00000
	{   8, 0x008b0008, 0xfdffffff }, // add:6:0x028B0008
	{  10, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{  11, 0xe580c004, 0xfdffffff }, // str:4:0xE580C004
	{  12, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  14, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  15, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001013
	{  18, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  19, 0x11a0000a, 0xfdffffff }, // mov:6:0x11A0000A
	{  20, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B001C22
	{  21, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  23, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_rewinddir[] = {
	{   0, 0xe1a0c000, 0xfdffffff }, // mov:6:0xE3A0C000
	{   1, 0xe580c004, 0xfdffffff }, // str:4:0xE580C004
	{   2, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   4, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{   5, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001013
	{   8, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   9, 0x11a0000a, 0xfdffffff }, // mov:6:0x11A0000A
	{  10, 0x1b000000, 0xff000000 }, // b, bl:3:0x1B001C22
	{  11, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  13, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  14, 0xe1a01026, 0xfdffffff }, // mov:6:0xE3A01026
	{  15, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00105A
	{  17, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{  18, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  19, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  20, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001196
	{  22, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  23, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{ -1, -1, -1 },
	/* 19/24 */
};

static FuncSig func_sig_isalpha[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0003, 0xfdffffff }, // and:6:0xE20C0003
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   5, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{   6, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   7, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   9, 0xe00c00a0, 0xfdffffff }, // and:6:0xE20C00A0
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  12, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  13, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe00c0004, 0xfdffffff }, // and:6:0xE20C0004
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  18, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  19, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  21, 0xe00c0017, 0xfdffffff }, // and:6:0xE20C0017
	{  22, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  23, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_isdigit[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0004, 0xfdffffff }, // and:6:0xE20C0004
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   5, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{   6, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   7, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   9, 0xe00c0017, 0xfdffffff }, // and:6:0xE20C0017
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  12, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  13, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe00c0002, 0xfdffffff }, // and:6:0xE20C0002
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  18, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  19, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  21, 0xe00c001f, 0xfdffffff }, // and:6:0xE20C001F
	{  22, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  23, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_isspace[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0028, 0xfdffffff }, // and:6:0xE20C0028
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   5, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{   6, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   7, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   9, 0xe00c0001, 0xfdffffff }, // and:6:0xE20C0001
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  12, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  13, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe00c0040, 0xfdffffff }, // and:6:0xE20C0040
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  18, 0xe040c041, 0xfdffffff }, // sub:6:0xE240C041
	{  19, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{  20, 0x90800020, 0xfdffffff }, // add:6:0x92800020
	{  21, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  22, 0xe040c061, 0xfdffffff }, // sub:6:0xE240C061
	{  23, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_isupper[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0001, 0xfdffffff }, // and:6:0xE20C0001
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   5, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{   6, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   7, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   9, 0xe00c0040, 0xfdffffff }, // and:6:0xE20C0040
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  12, 0xe040c041, 0xfdffffff }, // sub:6:0xE240C041
	{  13, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{  14, 0x90800020, 0xfdffffff }, // add:6:0x92800020
	{  15, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  16, 0xe040c061, 0xfdffffff }, // sub:6:0xE240C061
	{  17, 0xe15c0019, 0xfdffffff }, // cmp:7:0xE35C0019
	{  18, 0x90400020, 0xfdffffff }, // sub:6:0x92400020
	{  19, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  20, 0xe59f0000, 0xfdffffff }, // ldr:4:0xE59F0000
	{  21, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  22, 0x0000deb0, 0xfdffffff }, // and:6:0x0000DEB0
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_islower[] = {
	{   0, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   1, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   3, 0xe00c0002, 0xfdffffff }, // and:6:0xE20C0002
	{   4, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   5, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{   6, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{   7, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{   9, 0xe00c001f, 0xfdffffff }, // and:6:0xE20C001F
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  11, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  12, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  13, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  15, 0xe00c0010, 0xfdffffff }, // and:6:0xE20C0010
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{  18, 0xe59fc00c, 0xfdffffff }, // ldr:4:0xE59FC00C
	{  19, 0xe59cc000, 0xfdffffff }, // ldr:4:0xE59CC000
	{  21, 0xe00c0028, 0xfdffffff }, // and:6:0xE20C0028
	{  22, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  23, 0x0000f6d0, 0xfdffffff }, // and:6:0x0000F6D0
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_strncmp[] = {
	{   0, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   1, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   2, 0x01a0f00e, 0xfdffffff }, // mov:6:0x01A0F00E
	{   5, 0xe15c0003, 0xfdffffff }, // cmp:7:0xE15C0003
	{   7, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000005
	{   8, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE35C0000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  10, 0xe0522001, 0xfdffffff }, // sub:6:0xE2522001
	{  11, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFF6
	{  12, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  13, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  15, 0xe04c0003, 0xfdffffff }, // sub:6:0xE04C0003
	{  16, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  17, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  19, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000C
	{  22, 0xe013c0ff, 0xfdffffff }, // and:6:0xE213C0FF
	{ -1, -1, -1 },
	/* 17/24 */
};

static FuncSig func_sig_strtol[] = {
	{   0, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   2, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   3, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   4, 0xe58d0028, 0xfdffffff }, // str:4:0xE58D0028
	{   5, 0xe58d102c, 0xfdffffff }, // str:4:0xE58D102C
	{   6, 0xe59f7180, 0xfdffffff }, // ldr:4:0xE59F7180
	{   7, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   8, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   9, 0xe5977000, 0xfdffffff }, // ldr:4:0xE5977000
	{  12, 0xe1130028, 0xfdffffff }, // tst:7:0xE3130028
	{  13, 0x1a000000, 0xff000000 }, // b, bl:3:0x1AFFFFFB
	{  14, 0xe15b002d, 0xfdffffff }, // cmp:7:0xE35B002D
	{  15, 0x01a05001, 0xfdffffff }, // mov:6:0x03A05001
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{  17, 0xe15b002b, 0xfdffffff }, // cmp:7:0xE35B002B
	{  19, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{  20, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  21, 0xe1520010, 0xfdffffff }, // cmp:7:0xE3520010
	{  22, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000008
	{  23, 0xe15b0030, 0xfdffffff }, // cmp:7:0xE35B0030
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_rand[] = {
	{   0, 0xe59f002c, 0xfdffffff }, // ldr:4:0xE59F002C
	{   1, 0xe59f102c, 0xfdffffff }, // ldr:4:0xE59F102C
	{   2, 0xe59fc02c, 0xfdffffff }, // ldr:4:0xE59FC02C
	{   3, 0xe5903000, 0xfdffffff }, // ldr:4:0xE5903000
	{   5, 0xe5801000, 0xfdffffff }, // str:4:0xE5801000
	{   6, 0xe59fc020, 0xfdffffff }, // ldr:4:0xE59FC020
	{   7, 0xe00c0821, 0xfdffffff }, // and:6:0xE00C0821
	{   8, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   9, 0xe59fc008, 0xfdffffff }, // ldr:4:0xE59FC008
	{  10, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{  11, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  12, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{  13, 0x0000e00c, 0xfdffffff }, // and:6:0x0000E00C
	{  14, 0x00003039, 0xfdffffff }, // and:6:0x00003039
	{  16, 0x00007fff, 0xfdffffff }, // and:6:0x00007FFF
	{  18, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  20, 0xe59f33b0, 0xfdffffff }, // ldr:4:0xE59F33B0
	{  21, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  22, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  23, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{ -1, -1, -1 },
	/* 20/24 */
};

static FuncSig func_sig_srand[] = {
	{   0, 0xe59fc008, 0xfdffffff }, // ldr:4:0xE59FC008
	{   1, 0xe58c0000, 0xfdffffff }, // str:4:0xE58C0000
	{   2, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{   3, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E
	{   4, 0x0000e00c, 0xfdffffff }, // and:6:0x0000E00C
	{   5, 0x00003039, 0xfdffffff }, // and:6:0x00003039
	{   7, 0x00007fff, 0xfdffffff }, // and:6:0x00007FFF
	{   9, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{  11, 0xe59f33b0, 0xfdffffff }, // ldr:4:0xE59F33B0
	{  12, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  13, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{  14, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{  15, 0xe1a0100b, 0xfdffffff }, // mov:6:0xE1A0100B
	{  16, 0xe1a0000a, 0xfdffffff }, // mov:6:0xE1A0000A
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE42C
	{  18, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{  19, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  20, 0xe1a00006, 0xfdffffff }, // mov:6:0xE1A00006
	{  21, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFE41C
	{  22, 0xe1a0300b, 0xfdffffff }, // mov:6:0xE1A0300B
	{  23, 0xe1a0200a, 0xfdffffff }, // mov:6:0xE1A0200A
	{ -1, -1, -1 },
	/* 21/24 */
};

static FuncSig func_sig_stat[] = {
	{   1, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   2, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   3, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001171
	{   6, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{   9, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFCB
	{  12, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  13, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000FD6
	{  17, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{  18, 0xe1a0102e, 0xfdffffff }, // mov:6:0xE3A0102E
	{  19, 0xea000000, 0xff000000 }, // b, bl:3:0xEA001021
	{  21, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{  22, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{  23, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{ -1, -1, -1 },
	/* 18/24 */
};

FuncsList func_list[] = {
	{ "AllocateMemory", func_sig_AllocateMemory },
	{ "Close", func_sig_Close },
	{ "close", func_sig_close },
	{ "CreateTaskStrict", func_sig_CreateTaskStrict },
	{ "DisableDispatch", func_sig_DisableDispatch },
	{ "EnableDispatch", func_sig_EnableDispatch },
	{ "ExitTask", func_sig_ExitTask },
	{ "Fclose_Fut", func_sig_Fclose_Fut },
	{ "Fopen_Fut", func_sig_Fopen_Fut },
	{ "Fread_Fut", func_sig_Fread_Fut },
	{ "FreeMemory", func_sig_FreeMemory },
	{ "Fseek_Fut", func_sig_Fseek_Fut },
	{ "Fwrite_Fut", func_sig_Fwrite_Fut },
	{ "GetSystemTime", func_sig_GetSystemTime },
	{ "ints_disable", func_sig_ints_disable },
	{ "ints_enable", func_sig_ints_enable },
	{ "ioctl", func_sig_ioctl },
	{ "kbd_p1_f", func_sig_kbd_p1_f },
	{ "kbd_p1_f_cont", func_sig_kbd_p1_f_cont },
	{ "kbd_p2_f", func_sig_kbd_p2_f },
	{ "kbd_pwr_off", func_sig_kbd_pwr_off },
	{ "kbd_pwr_on", func_sig_kbd_pwr_on },
	{ "kbd_read_keys_r2", func_sig_kbd_read_keys_r2 },
	{ "lseek", func_sig_lseek },
	{ "MakeDirectory", func_sig_MakeDirectory },
	{ "memcmp", func_sig_memcmp },
	{ "memcpy", func_sig_memcpy },
	{ "memset", func_sig_memset },
	{ "mkdir", func_sig_mkdir },
	{ "Open", func_sig_Open },
	{ "open", func_sig_open },
	{ "PhySw_testgpio", func_sig_PhySw_testgpio },
	{ "ProtectFile", func_sig_ProtectFile },
	{ "Read", func_sig_Read },
	{ "read", func_sig_read },
	{ "reateTaskStrict", func_sig_reateTaskStrict },
	{ "sprintf", func_sig_sprintf },
	{ "strcmp", func_sig_strcmp },
	{ "strcpy", func_sig_strcpy },
	{ "strlen", func_sig_strlen },
	{ "TakeSemaphore", func_sig_TakeSemaphore },
	{ "taskIdListGet", func_sig_taskIdListGet },
	{ "taskLock", func_sig_taskLock },
	{ "taskName", func_sig_taskName },
	{ "taskResume", func_sig_taskResume },
	{ "taskSuspend", func_sig_taskSuspend },
	{ "taskUnlock", func_sig_taskUnlock },
	{ "Write", func_sig_Write },
	{ "write", func_sig_write },
	{ "taskCreateHookAdd", func_sig_taskCreateHookAdd },
	{ "taskDeleteHookAdd", func_sig_taskDeleteHookAdd },
	{ "SleepTask", func_sig_SleepTask },
	{ "CreateTask", func_sig_CreateTask },
	{ "CreatePhysicalVram", func_sig_CreatePhysicalVram },
	{ "DisplayImagePhysicalScreen", func_sig_DisplayImagePhysicalScreen },
	{ "ExecuteEventProcedure", func_sig_ExecuteEventProcedure },
	{ "GetPropertyCase", func_sig_GetPropertyCase },
	{ "SetPropertyCase", func_sig_SetPropertyCase },
	{ "malloc", func_sig_malloc },
	{ "free", func_sig_free },
	{ "strcat", func_sig_strcat },
	{ "strchr", func_sig_strchr },
	{ "RefreshPhysicalScreen", func_sig_RefreshPhysicalScreen },
	{ "opendir", func_sig_opendir },
	{ "closedir", func_sig_closedir },
	{ "readdir", func_sig_readdir },
	{ "rewinddir", func_sig_rewinddir },
	{ "isalpha", func_sig_isalpha },
	{ "isdigit", func_sig_isdigit },
	{ "isspace", func_sig_isspace },
	{ "isupper", func_sig_isupper },
	{ "islower", func_sig_islower },
	{ "strncmp", func_sig_strncmp },
	{ "strtol", func_sig_strtol },
	{ "rand", func_sig_rand },
	{ "srand", func_sig_srand },
	{ "stat", func_sig_stat },
	{ NULL }
};
