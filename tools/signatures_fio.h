static FuncSig func_sig_fclose[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe590a000, 0xfdffffff }, // ldr:4:0xE590A000
	{   3, 0xe59f00d0, 0xfdffffff }, // ldr:4:0xE59F00D0
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   5, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE15A0000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{   7, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  10, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE15C000A
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  12, 0xe59fb0b0, 0xfdffffff }, // ldr:4:0xE59FB0B0
	{  13, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000003
	{  15, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  17, 0xe1a0b009, 0xfdffffff }, // mov:6:0xE3A0B009
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fdopen[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   3, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   4, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00246D
	{   6, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000010
	{   8, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   9, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  10, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00013E
	{  11, 0xe1b0a000, 0xfdffffff }, // mov:6:0xE1B0A000
	{  12, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0007F8
	{  15, 0xe1b0b000, 0xfdffffff }, // mov:6:0xE1B0B000
	{  16, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  17, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_feof[] = {
	{   1, 0xe59f1058, 0xfdffffff }, // ldr:4:0xE59F1058
	{   2, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   3, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   4, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   5, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{   7, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{  11, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0018EF
	{  14, 0xe59fc028, 0xfdffffff }, // ldr:4:0xE59FC028
	{  15, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  16, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_ferror[] = {
	{   1, 0xe59f1058, 0xfdffffff }, // ldr:4:0xE59F1058
	{   2, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   3, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   4, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   5, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{   7, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{  11, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0018D4
	{  14, 0xe59fc028, 0xfdffffff }, // ldr:4:0xE59FC028
	{  15, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  16, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fflush[] = {
	{   1, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   2, 0xe5901000, 0xfdffffff }, // ldr:4:0xE5901000
	{   3, 0xe59f0058, 0xfdffffff }, // ldr:4:0xE59F0058
	{   4, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   5, 0xe1510000, 0xfdffffff }, // cmp:7:0xE1510000
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{   7, 0xe1510000, 0xfdffffff }, // cmp:7:0xE3510000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  10, 0xe15c0001, 0xfdffffff }, // cmp:7:0xE15C0001
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  12, 0xe59fb038, 0xfdffffff }, // ldr:4:0xE59FB038
	{  13, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000005
	{  14, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  17, 0xe11c0008, 0xfdffffff }, // tst:7:0xE31C0008
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fgetc[] = {
	{   1, 0xe59f1074, 0xfdffffff }, // ldr:4:0xE59F1074
	{   2, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   3, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   4, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   5, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{   7, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{  11, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00186C
	{  14, 0xe59fc044, 0xfdffffff }, // ldr:4:0xE59FC044
	{  15, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000B
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fgetpos[] = {
	{   1, 0xe1a0b001, 0xfdffffff }, // mov:6:0xE1A0B001
	{   2, 0xe59f104c, 0xfdffffff }, // ldr:4:0xE59F104C
	{   3, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   4, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   5, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   7, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00184B
	{  13, 0xe59fc024, 0xfdffffff }, // ldr:4:0xE59FC024
	{  14, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000004
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000314
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fgets[] = {
	{   1, 0xe59f8120, 0xfdffffff }, // ldr:4:0xE59F8120
	{   2, 0xe592a000, 0xfdffffff }, // ldr:4:0xE592A000
	{   3, 0xe1a06000, 0xfdffffff }, // mov:6:0xE1A06000
	{   4, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002
	{   5, 0xe5988000, 0xfdffffff }, // ldr:4:0xE5988000
	{   6, 0xe15a0008, 0xfdffffff }, // cmp:7:0xE15A0008
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   8, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  10, 0xe598c024, 0xfdffffff }, // ldr:4:0xE598C024
	{  11, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE15C000A
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  13, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001831
	{  14, 0xe59fc0f0, 0xfdffffff }, // ldr:4:0xE59FC0F0
	{  15, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  16, 0xe1a00000, 0xfdffffff }, // mov:6:0xE3A00000
	{  17, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000037
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fileno[] = {
	{   1, 0xe59f107c, 0xfdffffff }, // ldr:4:0xE59F107C
	{   2, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   3, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   4, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{   5, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   7, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0017E5
	{  13, 0xe59fc050, 0xfdffffff }, // ldr:4:0xE59FC050
	{  14, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  17, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fopen[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   3, 0xe1a00001, 0xfdffffff }, // mov:6:0xE1A00001
	{   4, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{   5, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFBC
	{   6, 0xe1b09000, 0xfdffffff }, // mov:6:0xE1B09000
	{   7, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000018
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000676
	{  10, 0xe1b0b000, 0xfdffffff }, // mov:6:0xE1B0B000
	{  11, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000014
	{  13, 0xe59d1000, 0xfdffffff }, // ldr:4:0xE59D1000
	{  14, 0xe1a00008, 0xfdffffff }, // mov:6:0xE1A00008
	{  15, 0xe59f204c, 0xfdffffff }, // ldr:4:0xE59F204C
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB002201
	{  17, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fprintf[] = {
	{   2, 0xe59f1054, 0xfdffffff }, // ldr:4:0xE59F1054
	{   3, 0xe5902000, 0xfdffffff }, // ldr:4:0xE5902000
	{   4, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   5, 0xe1520001, 0xfdffffff }, // cmp:7:0xE1520001
	{   6, 0xe1a03001, 0xfdffffff }, // mov:6:0xE1A03001
	{   7, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{   8, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  10, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  11, 0xe1a03002, 0xfdffffff }, // mov:6:0xE1A03002
	{  12, 0xe15c0002, 0xfdffffff }, // cmp:7:0xE15C0002
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB00175D
	{  15, 0xe59fc024, 0xfdffffff }, // ldr:4:0xE59FC024
	{  16, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fputs[] = {
	{   1, 0xe04dd014, 0xfdffffff }, // sub:6:0xE24DD014
	{   2, 0xe1a02000, 0xfdffffff }, // mov:6:0xE1A02000
	{   3, 0xe59f006c, 0xfdffffff }, // ldr:4:0xE59F006C
	{   4, 0xe591b000, 0xfdffffff }, // ldr:4:0xE591B000
	{   5, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   6, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   7, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE15B0000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   9, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  11, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  12, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001715
	{  15, 0xe59fc040, 0xfdffffff }, // ldr:4:0xE59FC040
	{  16, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fread[] = {
	{   1, 0xe1a06001, 0xfdffffff }, // mov:6:0xE1A06001
	{   2, 0xe1a05002, 0xfdffffff }, // mov:6:0xE1A05002
	{   3, 0xe1b09003, 0xfdffffff }, // mov:6:0xE1B09003
	{   4, 0xe1a08000, 0xfdffffff }, // mov:6:0xE1A08000
	{   5, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000000
	{   6, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   7, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000034
	{   9, 0xe59f70d0, 0xfdffffff }, // ldr:4:0xE59F70D0
	{  10, 0xe593b000, 0xfdffffff }, // ldr:4:0xE593B000
	{  11, 0xe5977000, 0xfdffffff }, // ldr:4:0xE5977000
	{  12, 0xe15b0007, 0xfdffffff }, // cmp:7:0xE15B0007
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  14, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  16, 0xe597c024, 0xfdffffff }, // ldr:4:0xE597C024
	{  17, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_freopen[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   3, 0xe59f01c8, 0xfdffffff }, // ldr:4:0xE59F01C8
	{   4, 0xe5928000, 0xfdffffff }, // ldr:4:0xE5928000
	{   5, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE3A0A001
	{   6, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   7, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   8, 0xe1a0b002, 0xfdffffff }, // mov:6:0xE1A0B002
	{   9, 0xe1580000, 0xfdffffff }, // cmp:7:0xE1580000
	{  10, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  11, 0xe1580000, 0xfdffffff }, // cmp:7:0xE3580000
	{  12, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  13, 0xe590c024, 0xfdffffff }, // ldr:4:0xE590C024
	{  14, 0xe15c0008, 0xfdffffff }, // cmp:7:0xE15C0008
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB0016B0
	{  17, 0xe59fc194, 0xfdffffff }, // ldr:4:0xE59FC194
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fscanf[] = {
	{   2, 0xe04dd008, 0xfdffffff }, // sub:6:0xE24DD008
	{   3, 0xe59fa088, 0xfdffffff }, // ldr:4:0xE59FA088
	{   4, 0xe590b000, 0xfdffffff }, // ldr:4:0xE590B000
	{   5, 0xe1a09000, 0xfdffffff }, // mov:6:0xE1A09000
	{   6, 0xe59aa000, 0xfdffffff }, // ldr:4:0xE59AA000
	{   7, 0xe15b000a, 0xfdffffff }, // cmp:7:0xE15B000A
	{   8, 0xe1a0300a, 0xfdffffff }, // mov:6:0xE1A0300A
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A00000A
	{  10, 0xe15b0000, 0xfdffffff }, // cmp:7:0xE35B0000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000003
	{  12, 0xe59ac024, 0xfdffffff }, // ldr:4:0xE59AC024
	{  13, 0xe1a0300b, 0xfdffffff }, // mov:6:0xE1A0300B
	{  14, 0xe15c000b, 0xfdffffff }, // cmp:7:0xE15C000B
	{  15, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  16, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001636
	{  17, 0xe59fc054, 0xfdffffff }, // ldr:4:0xE59FC054
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fseek[] = {
	{   1, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{   2, 0xe59f8388, 0xfdffffff }, // ldr:4:0xE59F8388
	{   3, 0xe590a000, 0xfdffffff }, // ldr:4:0xE590A000
	{   4, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   5, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   6, 0xe5988000, 0xfdffffff }, // ldr:4:0xE5988000
	{   7, 0xe1a06002, 0xfdffffff }, // mov:6:0xE1A06002
	{   8, 0xe15a0008, 0xfdffffff }, // cmp:7:0xE15A0008
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  10, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  12, 0xe598c024, 0xfdffffff }, // ldr:4:0xE598C024
	{  13, 0xe15c000a, 0xfdffffff }, // cmp:7:0xE15C000A
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000001
	{  15, 0xe59fb358, 0xfdffffff }, // ldr:4:0xE59FB358
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00002A
	{  17, 0xe1b02002, 0xfdffffff }, // mov:6:0xE1B02002
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fsetpos[] = {
	{   0, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   1, 0xe1a02000, 0xfdffffff }, // mov:6:0xE3A02000
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFF13
	{   4, 0xe59f10ac, 0xfdffffff }, // ldr:4:0xE59F10AC
	{   5, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   6, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   7, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   8, 0xe1500001, 0xfdffffff }, // cmp:7:0xE1500001
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  12, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  13, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE15C0000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001524
	{  16, 0xe59fc080, 0xfdffffff }, // ldr:4:0xE59FC080
	{  17, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_ftell[] = {
	{   1, 0xe59f10ac, 0xfdffffff }, // ldr:4:0xE59F10AC
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   3, 0xe5900000, 0xfdffffff }, // ldr:4:0xE5900000
	{   4, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   5, 0xe1500001, 0xfdffffff }, // cmp:7:0xE1500001
	{   6, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{   7, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{   8, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{   9, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  10, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE15C0000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  12, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001524
	{  13, 0xe59fc080, 0xfdffffff }, // ldr:4:0xE59FC080
	{  14, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{  16, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00001B
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fwrite[] = {
	{   1, 0xe04dd014, 0xfdffffff }, // sub:6:0xE24DD014
	{   2, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   3, 0xe59f1084, 0xfdffffff }, // ldr:4:0xE59F1084
	{   4, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   5, 0xe5930000, 0xfdffffff }, // ldr:4:0xE5930000
	{   6, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002
	{   7, 0xe5911000, 0xfdffffff }, // ldr:4:0xE5911000
	{   8, 0xe1500001, 0xfdffffff }, // cmp:7:0xE1500001
	{   9, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000009
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000002
	{  12, 0xe591c024, 0xfdffffff }, // ldr:4:0xE591C024
	{  13, 0xe15c0000, 0xfdffffff }, // cmp:7:0xE15C0000
	{  14, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  15, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB001419
	{  16, 0xe59fc054, 0xfdffffff }, // ldr:4:0xE59FC054
	{  17, 0xe580c000, 0xfdffffff }, // str:4:0xE580C000
	{ -1, -1, -1 },
	/* 17/18 */
};

static FuncSig func_sig_fstat[] = {
	{   0, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   1, 0xe1a01026, 0xfdffffff }, // mov:6:0xE3A01026
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000B20
	{   4, 0xe04dd048, 0xfdffffff }, // sub:6:0xE24DD048
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   6, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000C5C
	{   9, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  10, 0x01a00000, 0xfdffffff }, // mov:6:0x03A00000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000019
	{  12, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  13, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  16, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A00000D
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fstatfs[] = {
	{   0, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   1, 0xe1a0102e, 0xfdffffff }, // mov:6:0xE3A0102E
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEA000AE7
	{   4, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   5, 0xe1a01000, 0xfdffffff }, // mov:6:0xE3A01000
	{   6, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   7, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000C23
	{   9, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{  11, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000006
	{  12, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  13, 0xe1a0100a, 0xfdffffff }, // mov:6:0xE1A0100A
	{  14, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFFF0
	{  15, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  16, 0xe1a0000b, 0xfdffffff }, // mov:6:0xE1A0000B
	{  17, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000A88
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fdprintf[] = {
	{   2, 0xe1a03000, 0xfdffffff }, // mov:6:0xE1A03000
	{   3, 0xe59d0008, 0xfdffffff }, // ldr:4:0xE59D0008
	{   4, 0xe59f2848, 0xfdffffff }, // ldr:4:0xE59F2848
	{   5, 0xe08d100c, 0xfdffffff }, // add:6:0xE28D100C
	{   6, 0xeb000000, 0xff000000 }, // b, bl:3:0xEBFFFB91
	{   7, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   9, 0xe08dd010, 0xfdffffff }, // add:6:0xE28DD010
	{  10, 0xe1a0f00e, 0xfdffffff }, // mov:6:0xE1A0F00E	/* RET found, stopping... */
	{ -1, -1, -1 },
	/* 8/18 */
};

static FuncSig func_sig_fioRead[] = {
	{   1, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   2, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   3, 0xe1a0b002, 0xfdffffff }, // mov:6:0xE1A0B002
	{   4, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002
	{   5, 0xea000000, 0xff000000 }, // b, bl:3:0xEA00000C
	{   6, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{   7, 0xe1a01009, 0xfdffffff }, // mov:6:0xE1A01009
	{   8, 0xe1a0200b, 0xfdffffff }, // mov:6:0xE1A0200B
	{   9, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000391
	{  10, 0xe1500000, 0xfdffffff }, // cmp:7:0xE3500000
	{  11, 0xe1a0a000, 0xfdffffff }, // mov:6:0xE1A0A000
	{  13, 0xba000000, 0xff000000 }, // b, bl:3:0xBA000007
	{  14, 0xe15a0000, 0xfdffffff }, // cmp:7:0xE35A0000
	{  15, 0x0048000b, 0xfdffffff }, // sub:6:0x0048000B
	{  16, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000004
	{  17, 0xe04bb00a, 0xfdffffff }, // sub:6:0xE04BB00A
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_fioRdString[] = {
	{   1, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE3A0B000
	{   3, 0xe1520000, 0xfdffffff }, // cmp:7:0xE3520000
	{   4, 0xe1a07000, 0xfdffffff }, // mov:6:0xE1A07000
	{   5, 0xe1a0a001, 0xfdffffff }, // mov:6:0xE1A0A001
	{   6, 0xe1a09002, 0xfdffffff }, // mov:6:0xE1A09002
	{   7, 0xda000000, 0xff000000 }, // b, bl:3:0xDA00001B
	{   8, 0xe1a00007, 0xfdffffff }, // mov:6:0xE1A00007
	{   9, 0xe1a0100d, 0xfdffffff }, // mov:6:0xE1A0100D
	{  10, 0xe1a02001, 0xfdffffff }, // mov:6:0xE3A02001
	{  11, 0xeb000000, 0xff000000 }, // b, bl:3:0xEB000378
	{  13, 0x0a000000, 0xff000000 }, // b, bl:3:0x0A000014
	{  14, 0xe1500001, 0xfdffffff }, // cmp:7:0xE3500001
	{  15, 0x1a000000, 0xff000000 }, // b, bl:3:0x1A000004
	{  17, 0xe151000a, 0xfdffffff }, // cmp:7:0xE351000A
	{ -1, -1, -1 },
	/* 15/18 */
};

static FuncSig func_sig_fioScanV[] = {
	{   0, 0xe04dd004, 0xfdffffff }, // sub:6:0xE24DD004
	{   2, 0xe04dd028, 0xfdffffff }, // sub:6:0xE24DD028
	{   3, 0xe1a0b000, 0xfdffffff }, // mov:6:0xE1A0B000
	{   4, 0xe58d304c, 0xfdffffff }, // str:4:0xE58D304C
	{   5, 0xe1a05000, 0xfdffffff }, // mov:6:0xE3A05000
	{   6, 0xe59d6050, 0xfdffffff }, // ldr:4:0xE59D6050
	{   7, 0xe1a09001, 0xfdffffff }, // mov:6:0xE1A09001
	{   8, 0xe1a08002, 0xfdffffff }, // mov:6:0xE1A08002
	{   9, 0xe1a04005, 0xfdffffff }, // mov:6:0xE1A04005
	{  10, 0xe58d5018, 0xfdffffff }, // str:4:0xE58D5018
	{  11, 0xe4963004, 0xfdffffff }, // ldr:4:0xE4963004
	{  12, 0xe1a00002, 0xfdffffff }, // mov:6:0xE1A00002
	{  13, 0xe58d301c, 0xfdffffff }, // str:4:0xE58D301C
	{  14, 0xe1a0e00f, 0xfdffffff }, // mov:6:0xE1A0E00F
	{  15, 0xe1a0f009, 0xfdffffff }, // mov:6:0xE1A0F009
	{  16, 0xe58d0014, 0xfdffffff }, // str:4:0xE58D0014
	{ -1, -1, -1 },
	/* 16/18 */
};

static FuncSig func_sig_free[] = {
	{   0, 0xe1a01000, 0xfdffffff }, // mov:6:0xE1A01000
	{   1, 0xe59f0064, 0xfdffffff }, // ldr:4:0xE59F0064
	{   2, 0xea000000, 0xff000000 }, // b, bl:3:0xEAFFFE1E
	{   3, 0xe1a01001, 0xfdffffff }, // mov:6:0xE3A01001
	{   4, 0xe080000c, 0xfdffffff }, // add:6:0xE280000C
	{   5, 0xe1a02001, 0xfdffffff }, // mov:6:0xE1A02001
	{   6, 0xea000000, 0xff000000 }, // b, bl:3:0xEA002EE9
	{   7, 0x00110004, 0xfdffffff }, // and:6:0x00110004
	{   8, 0x0000c0cc, 0xfdffffff }, // and:6:0x0000C0CC
	{   9, 0x00580001, 0xfdffffff }, // sub:6:0x00580001
	{  10, 0x0009c294, 0xfdffffff }, // and:6:0x0009C294 mul:11:0x0009C294
	{  11, 0x0000c0b4, 0xfdffffff }, // and:6:0x0000C0B4
	{  13, 0x00110002, 0xfdffffff }, // and:6:0x00110002
	{  14, 0x0000bf04, 0xfdffffff }, // and:6:0x0000BF04
	{  15, 0x0009be58, 0xfdffffff }, // and:6:0x0009BE58
	{  16, 0x00002732, 0xfdffffff }, // and:6:0x00002732
	{  17, 0x0009bda0, 0xfdffffff }, // and:6:0x0009BDA0
	{ -1, -1, -1 },
	/* 18/18 */
};

#define SIG_FIO \
{"fclose",func_sig_fclose }, \
{"fdopen",func_sig_fdopen }, \
{"feof",func_sig_feof }, \
{"ferror",func_sig_ferror }, \
{"fflush",func_sig_fflush }, \
{"fgetc",func_sig_fgetc }, \
{"fgetpos",func_sig_fgetpos }, \
{"fgets",func_sig_fgets }, \
{"fileno",func_sig_fileno }, \
{"fopen",func_sig_fopen }, \
{"fprintf",func_sig_fprintf }, \
{"fputs",func_sig_fputs }, \
{"fread",func_sig_fread }, \
{"freopen",func_sig_freopen }, \
{"fscanf",func_sig_fscanf }, \
{"fseek",func_sig_fseek }, \
{"fsetpos",func_sig_fsetpos }, \
{"ftell",func_sig_ftell }, \
{"fwrite",func_sig_fwrite }, \
{"fstat",func_sig_fstat }, \
{"fstatfs",func_sig_fstatfs }, \
{"fdprintf",func_sig_fdprintf }, \
{"free",func_sig_free }, \
