#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define RAWDATA_AVAILABLE (1)
#define RAWDATA_SAVED (2)

#define NR_ON (2)
#define NR_OFF (1)

static long raw_save_stage;

void capt_seq_hook_raw_here()
{
    raw_save_stage = RAWDATA_AVAILABLE;
    core_rawdata_available();
    while (raw_save_stage != RAWDATA_SAVED){
	_SleepTask(10);
    }
}

void hook_raw_save_complete()
{
    raw_save_stage = RAWDATA_SAVED;
}


void capt_seq_hook_set_nr()
{
    long *nrflag = (long*)0xC2E4;

    switch (core_get_noise_reduction_value()){
    case NOISE_REDUCTION_AUTO_CANON:
	// leave it alone
	break;
    case NOISE_REDUCTION_OFF:
	*nrflag = 1;
	break;
    case NOISE_REDUCTION_ON:
	*nrflag = 2;
	break;
    };
}

void __attribute__((naked,noinline)) sub_FFEABF94_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"    
                "MOV     R4, R0\n"          
                "SUB     SP, SP, #0xC\n"    
                "BL      sub_FFEACA04\n"    
                "MVN    R1, #0\n"          // origianlly 0xFFFFFFFF
                "BL      sub_FFEBD168\n"  
                "MOV     R0, #0x8A\n"       
                "ADD     R1, SP, #4\n"      
                "MOV     R2, #4\n"          
                "BL      sub_FFC0BC94\n"    
                "TST     R0, #1\n"          
                "BEQ     loc_FFEABFD4\n"    
                "MOV     R1, #0x1D0\n"      
                "LDR     R0, =0xFFEABE18\n" 
                "ADD     R1, R1, #2\n"      
                "BL      sub_FFECA824\n"     
"loc_FFEABFD4:\n"                           
                "LDR     R3, =0xA5740\n"    
                "LDR     R2, =0xA5800\n"    
                "LDR     R0, [R3,#0x74]\n"  
                "LDRSH   R1, [R2,#0xE]\n"   
                "BL      sub_FFDEF8B0\n"    
                "MOV     R0, R4\n"          
                "BL      sub_FFEABD9C\n"    
                "BL      capt_seq_hook_set_nr\n"
                "LDR     R3, =0xC2E8\n"     
                "LDR     R0, [R3]\n"

                "B       sub_FFEABFF8\n"
    );
}

void __attribute__((naked,noinline)) sub_FFEA8E50_my(long p)
{
    asm volatile (
                "STMFD   SP!, {R4,LR}\n"    
                "LDR     R4, [R0,#0xC]\n"   
                "LDR     R3, [R4,#8]\n"     
                "ORR     R3, R3, #1\n"      
                "STR     R3, [R4,#8]\n"     
                "MOV     R0, #2\n"          
                "BL      sub_FFE89DE8\n"    
                "BL      sub_FFEA9944\n"    
                "MOV     R0, R4\n"          
                "BL      sub_FFEAAA98\n"    
                "TST     R0, #1\n"          
                "MOV     R2, R4\n"          
                "MOV     R1, #1\n"          
                "BEQ     loc_FFEA8E90\n"    
                "LDMFD   SP!, {R4,LR}\n"    
                "B       sub_FFEA7618\n"    
"loc_FFEA8E90:\n"                           
                "BL      sub_FFC15B00\n"    
                "BL      sub_FFC0BE90\n"    
                "STR     R0, [R4,#0x14]\n"  
                "MOV     R0, R4\n"          
                "BL      sub_FFEABE7C\n"    
                "BL      sub_FFEAC870\n"    
                "MOV     R0, R4\n"          
                "BL      sub_FFEABF94_my\n"    
                "BL      capt_seq_hook_raw_here\n"
                "MOV     R1, #1\n"          
                "MOV     R2, R4\n"          
                "BL      sub_FFEA7618\n"    
                "BL      sub_FFEAC310\n"    
                "CMP     R0, #0\n"          
                "LDRNE   R3, [R4,#8]\n"     
                "ORRNE   R3, R3, #0x2000\n" 
                "STRNE   R3, [R4,#8]\n"     
                "LDMFD   SP!, {R4,PC}\n"    
    );
}

void __attribute__((naked,noinline)) capt_seq_task()
{
	asm volatile (
                "STMFD   SP!, {R4,LR}\n"    
                "SUB     SP, SP, #4\n"      
                "MOV     R4, SP\n"          
                "B       loc_FFEA9360\n"    


"loc_FFEA91F4:\n"                           
                "LDR     R2, [SP]\n"        
                "LDR     R3, [R2]\n"        
                "MOV     R0, R2\n"          
                "CMP     R3, #0x16\n"       
                "LDRLS   PC, [PC,R3,LSL#2]\n" 
                "B       loc_FFEA9334\n"    

                ".long loc_FFEA9268\n"
                ".long loc_FFEA9274\n"
                ".long loc_FFEA927C\n"
                ".long loc_FFEA9290\n"
                ".long loc_FFEA9288\n"
                ".long loc_FFEA9298\n"
                ".long loc_FFEA92A0\n"
                ".long loc_FFEA92AC\n"
                ".long loc_FFEA92B4\n"
                ".long loc_FFEA92C0\n"
                ".long loc_FFEA92C8\n"
                ".long loc_FFEA92D0\n"
                ".long loc_FFEA92D8\n"
                ".long loc_FFEA92E0\n"
                ".long loc_FFEA92E8\n"
                ".long loc_FFEA92F4\n"
                ".long loc_FFEA92FC\n"
                ".long loc_FFEA9304\n"
                ".long loc_FFEA930C\n"
                ".long loc_FFEA9318\n"
                ".long loc_FFEA9324\n"
                ".long loc_FFEA932C\n"
                ".long loc_FFEA9348\n"


"loc_FFEA9268:\n"                           
                                        
                "BL      sub_FFEA9958\n"    
                "BL      sub_FFEA710C\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9274:\n"                           
                                        
                "BL      sub_FFEA8E50_my\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA927C:\n"                           
                                        
                "MOV     R0, #1\n"          
                "BL      sub_FFEA9B60\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9288:\n"                           
                                        
                "BL      sub_FFEA94BC\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9290:\n"                           
                                        
                "BL      sub_FFEA9924\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9298:\n"                           
                                        
                "BL      sub_FFEA9934\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92A0:\n"                           
                                        
                "BL      sub_FFEA9A50\n"    
                "BL      sub_FFEA710C\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92AC:\n"                           
                                        
                "BL      sub_FFEA8F34\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92B4:\n"                           
                                        
                "BL      sub_FFEA9AC4\n"    
                "BL      sub_FFEA710C\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92C0:\n"                           
                                        
                "BL      sub_FFEA9924\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92C8:\n"                           
                                        
                "BL      sub_FFEAB1CC\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92D0:\n"                           
                                        
                "BL      sub_FFEAB3A0\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92D8:\n"                           
                                        
                "BL      sub_FFEAB434\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92E0:\n"                           
                                        
                "BL      sub_FFEAB530\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92E8:\n"                           
                                        
                "MOV     R0, #0\n"          
                "BL      sub_FFEAB79C\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92F4:\n"                           
                                        
                "BL      sub_FFEAB970\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA92FC:\n"                           
                                        
                "BL      sub_FFEABA0c\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9304:\n"                           
                                        
                "BL      sub_FFEABACC\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA930C:\n"                           
                                        
                "MOV     R0, #1\n"          
                "BL      sub_FFEAB79C\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9318:\n"                           
                                        
                "BL      sub_FFEA9CBC\n"    
                "BL      sub_FFEA8D74\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9324:\n"                           
                                        
                "BL      sub_FFEAB670\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA932C:\n"                           
                                        
                "BL      sub_FFEAB6CC\n"    
                "B       loc_FFEA9344\n"    


"loc_FFEA9334:\n"                           
                "MOV     R1, #0x4C0\n"      
                "LDR     R0, =0xFFEA8BD0\n" 
                "ADD     R1, R1, #1\n"      
                "BL      sub_FFECA824\n"     

"loc_FFEA9344:\n"                           
                                        
                "LDR     R2, [SP]\n"        

"loc_FFEA9348:\n"                           
                                        
                "LDR     R3, =0x7EEC0\n"    
                "LDR     R1, [R2,#4]\n"     
                "LDR     R0, [R3]\n"        
                "BL      sub_FFEBCFCC\n"    
                "LDR     R0, [SP]\n"        
                "BL      sub_FFEA8C50\n"    

"loc_FFEA9360:\n"                           
                "LDR     R3, =0x7EEC4\n"    
                "MOV     R1, R4\n"          
                "LDR     R0, [R3]\n"        
                "MOV     R2, #0\n"          
                "BL      sub_FFEBD6E4\n" 
                "TST     R0, #1\n"          
                "BEQ     loc_FFEA91F4\n"    
                "MOV     R1, #0x3F0\n"      
                "LDR     R0, =0xFFEA8BD0\n" 
                "ADD     R1, R1, #3\n"      
                "BL      sub_FFECA824\n"     
                "BL      sub_FFEBECA8\n"    
                "ADD     SP, SP, #4\n"      
                "LDMFD   SP!, {R4,PC}\n"    
	);
}

