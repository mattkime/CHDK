#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    uint32_t offs;
    uint32_t value;
    uint32_t mask;
} FuncSig;

typedef struct {
    const char *name;
    FuncSig *sig;
} FuncsList;

#include "signatures.h"

void usage()
{
    printf("finsig <primary> <base>\n");
    exit(1);
}

int main(int argc, char **argv)
{
    uint32_t *buf;
    FILE *f;
    int size;
    int i,j,k;
    int fail;
    long long base = 0xffc00000;
    FuncSig *sig;
    int count;
    int ret = 0;

    if (argc != 3)
	usage();

    f = fopen(argv[1], "r+b");

    if (f == NULL)
	usage();

    base = strtoll(argv[2], NULL, 0);

    printf("// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!\n");
    printf("#include \"stubs_asm.h\"\n\n");

    fseek(f,0,SEEK_END);
    size=ftell(f)/4;
    fseek(f,0,SEEK_SET);

    buf=malloc(size*4);
    fread(buf, 4, size, f);

    for (k=0;func_list[k].name;k++){
	sig = func_list[k].sig;
	count = 0;
	for (i=0;i<size;i++){
	    fail = 0;
	    for (j=0;sig[j].offs!=-1;j++){
		if ((i+sig[j].offs) >= size || (buf[i+sig[j].offs] & sig[j].mask) != sig[j].value){
		    fail = 1;
		    break;
		}
	    }
	    if (!fail){
		if (count > 1)
		    printf("// ");
		printf("NSTUB(%s, 0x%08x)\n", func_list[k].name, base+i*4);
		count ++;
	    }
	}
	if (count == 0 ){
	    printf("// WARNING: %s is not found!\n", func_list[k].name);
	    ret = 1;
	} else
	if (count > 1){
	    printf("// WARNING: %s found more than once!\n", func_list[k].name);
	    ret = 1;
	}
    }

    return ret;
}

