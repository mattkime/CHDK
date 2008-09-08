
#include <idc.idc>

#include "_initial_names.idc"

#define DUMP_NAME "b.code-4000000"

static main()
{
    memcpy(0x40294, 0x4073FB8, 0x1248);
/*
    createSegments();

    copySegments();

    MakeCode(0x04000000);

    makeNames1();
//*/
}

static createSegments()
{
    auto fh;

    DeleteAll();    // purge database
	SetPrcsr("fr");
	StringStp(0xA);
	Tabs(1);


/*
RAM: 0x00000000 - 0x01000000
(dump.code-4000000:0x003D0000) => 0x002C0000, size 0x00030000
*/
    SegCreate(0x00000000,0x00300000,0,1, saRelByte, scPub);
    fh = fopen(DUMP_NAME, "rb");
    loadfile(fh, 0x003D0000,  0x002C0000, 0x00030000);

/*
RAM2 IO ports mapped?
*/
    SegCreate(0x1700000, 0x1800000,0,1, saRelByte, scPub);

/*
ROM: 0x04000000 - 0x043D0000
(dump.code-4000000:0x00000000) => 0x04000000, size 0x003D0000
*/
    SegCreate(0x04000000,0x043D0000,0,1, saAbs, scPub);
    fh = fopen(DUMP_NAME, "rb");
    loadfile(fh, 0x00000000,  0x04000000, 0x003D0000);

    fclose(fh);
}



static copySegments()
{
// RAM segment copying
    memcpy(0x100400, 0x2D8114, 0x2FCE);
// small RAM segment
    memcpy(0x419C8, 0x002DB0E4, 0xE4);

// init_copy_4073FB8_40294_size1248
    memcpy(0x40294, 0x4073FB8, 0x1248);

}




static memcpy(to, from, size)
{
    auto i, val;

    for (i = 0; i < size; i = i+1)
    {
        val = Byte(from+i);
        PatchByte(to+i, val);
    }

}
