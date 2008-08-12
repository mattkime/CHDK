
#include <idc.idc>

#include "_initial_names.idc"

#define DUMP_NAME "b.code-4000000"

static main()
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
RAM2
*/
    SegCreate(0x1700000, 0x1800000,0,1, saRelByte, scPub);

/*
ROM: 0x04000000 - 0x043D0000
(dump.code-4000000:0x00000000) => 0x04000000, size 0x003D0000
*/
    SegCreate(0x04000000,0x043D0000,0,1, saAbs, scPub);
    fh = fopen(DUMP_NAME, "rb");
    loadfile(fh, 0x00000000,  0x04000000, 0x003D0000);

    MakeCode(0x04000000);

    makeNames1();


    fclose(fh);
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
