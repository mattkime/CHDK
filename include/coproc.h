
#define MRC(reg, p, c1, c2, op1, op2)  \
    do{  \
    asm volatile   \
    (  \
        "MRC     " #p ", " #op1 ", r0, " #c1 "," #c2 "," #op2 "\n"        \
        "STR     r0, [%0]"  \
        :: "r"(&(reg)) : "r0"  \
    );   \
    }while(0)


#define MCR(reg, p, c1, c2, op1, op2)  \
    do{  \
    int data = (reg); \
    asm volatile   \
    (  \
        "LDR     r0, [%0]\n"  \
        "MCR     " #p ", " #op1 ", r0, " #c1 "," #c2 "," #op2 "\n"        \
        :: "r"(&data) : "r0"  \
    );   \
    }while(0)
