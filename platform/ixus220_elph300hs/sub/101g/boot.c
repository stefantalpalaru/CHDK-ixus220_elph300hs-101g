#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

/* void __attribute__((naked,noinline)) my_blinker(int n) {
	asm volatile (
				"STMFD   SP!, {R0-R5,LR}\n"
	);
	
	int i, j;
	for (j=0; j<n; j++)
	{
		*((volatile int *) 0xC0223030) = 0x46; // Turn on AF LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC0223030) = 0x44; // Turn off AF LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
	}
	for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
	asm volatile (
				"LDMFD   SP!, {R0-R5,PC}\n"
	);
}

void __attribute__((naked,noinline)) my_blinker1(int n) {
	asm volatile (
				"STMFD   SP!, {R0-R5,LR}\n"
	);
	
	int i, j;
	for (j=0; j<n; j++)
	{
		*((volatile int *) 0xC0220130) = 0x46; // Turn on Back LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }

		*((volatile int *) 0xC0220130) = 0x44; // Turn off Back LED
		for (i=0; i<0x200000; i++) { asm volatile ( "nop\n" ); }
	}
	for (i=0; i<0x900000; i++) { asm volatile ( "nop\n" ); }
	asm volatile (
				"LDMFD   SP!, {R0-R5,PC}\n"
	);
}
 */

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();

void taskHook(context_t **context)
{ 
	task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	// Replace firmware task addresses with ours
	if(tcb->entry == (void*)task_CaptSeq)			tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)	tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_MovieRecord)		tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)			tcb->entry = (void*)exp_drv_task;
}

/*---------------------------------------------------------------------
  Memory Map:
	0001900     MEMBASEADDR             start of data - used for initialized vars
	0010797???                          end of inited data
	0010798???                          start of bss - used for zeroed/uninited vars
	016E81F???                          end of bss
	016E820???  MEMISOSTART             start of our data / bss

	0400000                             raw buffers
	8000000                             end of raw buffers

	C0xxxxxx                            I/O

	FF810000    ROMBASEADDR             start of rom
	FFFFFFFF                            end of rom
----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
	boot()

	Main entry point for the CHDK code
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) boot() {
	
    asm volatile (
                "LDR     R1, =0xC0410000\n"
                "MOV     R0, #0\n"
                "STR     R0, [R1]\n"
                "MOV     R1, #0x78\n"
                "MCR     p15, 0, R1,c1,c0\n"
                "MOV     R1, #0\n"
                "MCR     p15, 0, R1,c7,c10, 4\n"
                "MCR     p15, 0, R1,c7,c5\n"
                "MCR     p15, 0, R1,c7,c6\n"
                "MOV     R0, #0x3D\n"
                "MCR     p15, 0, R0,c6,c0\n"
                "MOV     R0, #0xC000002F\n"
                "MCR     p15, 0, R0,c6,c1\n"
                "MOV     R0, #0x35\n"					// memory region & size. bits 1 - 5 = size index, actual size = 2^(size index + 1) = 128MB
                "MCR     p15, 0, R0,c6,c2\n"
                "MOV     R0, #0x40000035\n"				// memory region & size. bits 1 - 5 = size index, actual size = 2^(size index + 1) = 128MB
                "MCR     p15, 0, R0,c6,c3\n"
                "MOV     R0, #0x80000017\n"
                "MCR     p15, 0, R0,c6,c4\n"
                "LDR     R0, =0xFF80002D\n"
                "MCR     p15, 0, R0,c6,c5\n"
                "MOV     R0, #0x34\n"
                "MCR     p15, 0, R0,c2,c0\n"
                "MOV     R0, #0x34\n"
                "MCR     p15, 0, R0,c2,c0, 1\n"
                "MOV     R0, #0x34\n"
                "MCR     p15, 0, R0,c3,c0\n"
				"LDR     R0, =0x3333330\n"
                "MCR     p15, 0, R0,c5,c0, 2\n"
                "LDR     R0, =0x3333330\n"
                "MCR     p15, 0, R0,c5,c0, 3\n"
                "MRC     p15, 0, R0,c1,c0\n"
                "ORR     R0, R0, #0x1000\n"
                "ORR     R0, R0, #4\n"
                "ORR     R0, R0, #1\n"
                "MCR     p15, 0, R0,c1,c0\n"
                "MOV     R1, #0x80000006\n"
                "MCR     p15, 0, R1,c9,c1\n"
                "MOV     R1, #6\n"
                "MCR     p15, 0, R1,c9,c1, 1\n"
                "MRC     p15, 0, R1,c1,c0\n"
                "ORR     R1, R1, #0x50000\n"
                "MCR     p15, 0, R1,c1,c0\n"
                "LDR     R2, =0xC0200000\n"
                "MOV     R1, #1\n"
                "STR     R1, [R2,#0x10C]\n"
                "MOV     R1, #0xFF\n"
                "STR     R1, [R2,#0xC]\n"
                "STR     R1, [R2,#0x1C]\n"
                "STR     R1, [R2,#0x2C]\n"
                "STR     R1, [R2,#0x3C]\n"
                "STR     R1, [R2,#0x4C]\n"
                "STR     R1, [R2,#0x5C]\n"
                "STR     R1, [R2,#0x6C]\n"
                "STR     R1, [R2,#0x7C]\n"
                "STR     R1, [R2,#0x8C]\n"
                "STR     R1, [R2,#0x9C]\n"
                "STR     R1, [R2,#0xAC]\n"
                "STR     R1, [R2,#0xBC]\n"
                "STR     R1, [R2,#0xCC]\n"
                "STR     R1, [R2,#0xDC]\n"
                "STR     R1, [R2,#0xEC]\n"
                "STR     R1, [R2,#0xFC]\n"
                "LDR     R1, =0xC0400008\n"
                "LDR     R2, =0x430005\n"
                "STR     R2, [R1]\n"
                "MOV     R1, #1\n"
                "LDR     R2, =0xC0243100\n"
                "STR     R2, [R1]\n"
                "LDR     R2, =0xC0242010\n"
                "LDR     R1, [R2]\n"
                "ORR     R1, R1, #1\n"
                "STR     R1, [R2]\n"

                "LDR     R0, =0xFFC8AB88\n"				// adapted for 101g Firmware
                "LDR     R1, =0x1900\n"
                "LDR     R3, =0x1049C\n"
	"loc_FF00013C:\n"
                "CMP     R1, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF00013C\n"
                "LDR     R1, =0x1774EC\n"
                "MOV     R2, #0\n"
	"loc_FF000154:\n"
                "CMP     R3, R1\n"
                "STRCC   R2, [R3],#4\n"
                "BCC     loc_FF000154\n"
				
                "B       sub_FF000358_my" // -->
    );
}

/*----------------------------------------------------------------------
	sub_FF000358_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF000358_my() {
// FF810358

	//http://chdk.setepontos.com/index.php/topic,4194.0.html
	*(int*)0x1938=(int)taskHook;
	*(int*)0x193C=(int)taskHook;
    
	// replacement of sub_FF024B5C for correct power-on.
	// http://chdk.setepontos.com/index.php?topic=6341.msg76409#msg76409
	*(int*)(0x25F4) = (*(int*)0xC0220130)&1 ? 0x200000 : 0x100000; 
	
	asm volatile (
                "LDR     R0, =0xFF8103D0\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFF810408\n"
	"loc_FF000364:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF000364\n"
                "LDR     R0, =0xFF810408\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFF81061C\n"
	"loc_FF000380:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FF000380\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "LDR     R0, =0x6C4\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"
	"loc_FF0003B4:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FF0003B4\n"
                //"BL      sub_FF0011B0\n" 				// original
                "BL      sub_FF0011B0_my\n" 			// --> patched
     );
}

/*----------------------------------------------------------------------
	sub_FF0011B0_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF0011B0_my() {
// FF8111B0

     asm volatile (
                "STR     LR, [SP,#-4]!\n"
                "SUB     SP, SP, #0x74\n"
                "MOV     R1, #0x74\n"
                "MOV     R0, SP\n"
                "BL      sub_FFB9C68C\n"				// adapted for 101g Firmware
                "MOV     R0, #0x53000\n"
                "STR     R0, [SP,#4]\n"
#if defined(OPT_CHDK_IN_EXMEM)
                "LDR     R0, =0x1774EC\n" 				// use original heap offset since CHDK is loaded in high memory
#else
                "LDR     R0, =new_sa\n"   				// otherwise use patched value
                "LDR     R0, [R0]\n"       
#endif
				"LDR     R2, =0x371F80 \n"
				"STR     R0, [SP,#0x8] \n"
				"SUB     R0, R2, R0 \n"
				"STR     R0, [SP,#0xC] \n"
				"MOV     R0, #0x22 \n"
				"STR     R0, [SP,#0x18] \n"
				"MOV     R0, #0x68 \n"
				"STR     R0, [SP,#0x1C] \n"
				"LDR     R1, =0x379C00 \n"
				"LDR     R0, =0x19B \n"
				"STR     R1, [SP] \n"
				"STR     R0, [SP,#0x20] \n"
				"MOV     R0, #0x96 \n"
				"STR     R2, [SP,#0x10] \n"
				"STR     R1, [SP,#0x14] \n"
				"STR     R0, [SP,#0x24] \n"
				"STR     R0, [SP,#0x28] \n"
				"MOV     R0, #0x64 \n"
				"STR     R0, [SP,#0x2C] \n"
				"MOV     R0, #0 \n"
				"STR     R0, [SP,#0x30] \n"
				"STR     R0, [SP,#0x34] \n"
				"MOV     R0, #0x10 \n"
				"STR     R0, [SP,#0x5C] \n"
				"MOV     R0, #0x800 \n"
				"STR     R0, [SP,#0x60] \n"
				"MOV     R0, #0xA0 \n"
				"STR     R0, [SP,#0x64] \n"
				"MOV     R0, #0x280 \n"
				"STR     R0, [SP,#0x68] \n"
				//"LDR     R1, =sub_FF815EE0 \n" 		// original
				"LDR     R1, =sub_FF005EE0_my \n" 		// --> patched
				"B		sub_FF81124C \n"				// --> continue in firmware
     );
}

/*----------------------------------------------------------------------
	sub_FF005EE0_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) sub_FF005EE0_my() {
// FF815EE0

	asm volatile (
				"STMFD	SP!, {R4,LR} \n"
				"BL	sub_FF810B28 \n"
				"BL	sub_FF81A374 \n"					// dmSetup
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aDmsetup \n"			// "dmSetup"
				"LDRLT	r0, =0xFF815FF4 \n"
				"BLLT	_err_init_task \n"
				"BL	sub_FF815B18 \n"
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aTermdriverinit \n"		// "termDriverInit"
				"LDRLT	R0, =0xFF815FFC \n"
				"BLLT	_err_init_task \n"
				//"ADR	R0, a_term \n"					// "/_term"
				"LDR	R0, =0xFF81600C \n"
				"BL	sub_FF815C00 \n"
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aTermdevicecrea \n"		// "termDeviceCreate"
				"LDRLT	R0, =0xFF816014 \n"
				"BLLT	_err_init_task \n"
				//"ADR	R0, a_term \n"					// "/_term"
				"LDR	R0, =0xFF81600C \n"
				"BL	sub_FF813CA8 \n"
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aStdiosetup \n"			// "stdioSetup"
				"LDRLT	R0, =0xFF816028 \n"
				"BLLT	_err_init_task \n"
				"BL	sub_FF819D00 \n"
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aStdlibsetup \n"		// "stdlibSetup"
				"LDRLT	R0, =0xFF816034 \n"
				"BLLT	_err_init_task \n"
				"BL	sub_FF811690 \n"
				"CMP	R0, #0 \n"
				//"ADRLT	R0, aArmlib_setup \n"		// "armlib_setup"
				"LDRLT	R0, =0xFF816040 \n"
				"BLLT	_err_init_task \n"
				"LDMFD	SP!, {R4,LR} \n"
				//"B	sub_FF81FCB4 \n"				// original taskcreate_Startup
				"B	taskcreate_Startup_my \n"			// --> patched
        );
};

/*----------------------------------------------------------------------
	taskcreate_Startup_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) taskcreate_Startup_my() {
// FF81FCB4

	asm volatile (
				"STMFD   SP!, {R3-R9,LR} \n"
				"MOV     R6, #0 \n"
				//"BL      sub_FF834B44 \n" 			// j_nullsub_107
				"BL      sub_FF83D9B0 \n"
				"LDR     R9, =0xC0220000 \n"
				"MOVS    R7, R0 \n"
				"MOV     R8, #1 \n"
				"BNE     loc_FF00FCE8 \n"
				"BL      sub_FF8372F0 \n"
				"CMP     R0, #0 \n"
				"BEQ     loc_FF00FCE8 \n"
				"LDR     R0, [R9,#0x12C] \n"
				"BIC     R5, R8, R0 \n"
				"LDR     R0, [R9,#0x128] \n"
				"BIC     R4, R8, R0 \n"
				"BL      sub_FF833DDC \n"
				"CMP     R0, #1 \n"
				"MOVEQ   R6, #1 \n"
				"ORR     R0, R4, R5 \n"
				"ORRS    R0, R0, R6 \n"
				"BNE     loc_FF00FCF8 \n"
				"BL      sub_FF834190 \n"
				"MOV     R0, #0x44 \n"
				"STR     R0, [R9,#0x1C] \n"
				"BL      sub_FF834380 \n"
	"loc_FF00FCE4: \n"
				"B       loc_FF00FCE4 \n"
	"loc_FF00FCE8: \n"
				"LDR     R0, [R9,#0x128] \n"
				"BIC     R4, R8, R0 \n"
				"LDR     R0, [R9,#0x12C] \n"
				"BIC     R5, R8, R0 \n"
	"loc_FF00FCF8: \n"
				"MOV     R3, R6 \n"
				"MOV     R2, R7 \n"
				"MOV     R1, R5 \n"
				"MOV     R0, R4 \n"
				//"BL      sub_FF834B4C \n"
				//"BL      sub_FF834B48 \n" 			//j_nullsub_108
				"BL      sub_FF83BB7C \n"
				"LDR     R1, =0x3CE000 \n"
				"MOV     R0, #0 \n"
				"BL      sub_FF83BFEC \n"
				"BL      sub_FF83BD94 \n"
				"MOV     R3, #0 \n"
				"STR     R3, [SP] \n"
				//"LDR     R3, =task_Startup \n" 		// original task_Startup at 0xFF81FBF4
				"LDR     R3, =task_Startup_my \n"   	// --> patched
				"B       sub_FF81FD64 \n"				// --> continue in firmware
     );
}

/*----------------------------------------------------------------------
	task_Startup_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) task_Startup_my() {
// 0xFF81FBF4
	
	asm volatile (
				"STMFD   SP!, {R4,LR} \n"
				"BL      sub_FF816588 \n"
				"BL      sub_FF835D30 \n"
				"BL      sub_FF833DEC \n"
				//"BL      sub_FF83D9F8 \n" 			// j_nullsub_110
				"BL      sub_FF83DBE4 \n"
				"BL      sub_FF834F90 \n"
				"BL      sub_FF833870 \n"
				//"BL      sub_FF83DA8C \n" 			// start diskboot.bin
				"BL      sub_FF83DD90 \n"
				"BL      sub_FF816488\n"
				"BL      sub_FF836A50\n"				// taskcreate_PwrCnt()
				"LDR     R1, =0x7C007C00\n"
				"LDR     R0, =0xC0F1800C\n"
                "BL      sub_FF835D3C\n"
				"LDR     R0, =0xC0F18010\n"
				"MOV     R1, #0\n"
                "BL      sub_FF835D3C\n"
				"LDR     R0, =0xC0F18018\n"
				"MOV     R1, #0\n"
                "BL      sub_FF835D3C\n"				 
				"LDR     R0, =0xC0F1801C\n"
				"MOV     R1, #1000\n"
                "BL      sub_FF835D3C\n"
				"LDR     R0, =0xC0F18020\n"
				"MOV     R1, #8\n"
                "BL      sub_FF835D3C\n"
				"LDR     R0, =0xC022D06C\n"
				"MOV     R1, #0xE000000\n"
                "BL      sub_FF835D3C\n"
                "BL      sub_FF8164C0\n"
 				"BL      sub_FF832280\n"
                "BL      sub_FF83DC14\n"				// taskcreate_WDT()
                "BL      sub_FF83B320\n"
                "BL      sub_FF83DD94\n"				// taskcreate_CtrlSrv()
				"BL      CreateTask_spytask\n"   		// added to create the Spytask (afaik the main CHDK Task)
				 //"BL      sub_FF8349EC\n"				// original taskcreate_PhySw()
				 "BL	  taskcreatePhySw_my\n"  		// --> patched taskcreate_PhySw()
				"BL	sub_FF83927C \n"                      
				"BL	sub_FF83DDAC \n"                      
				//"BL	sub_FF831678 \n" 				// j_nullsub_101
				"BL	sub_FF8331E0 \n"                      
				"BL	sub_FF83D76C \n"                      
				"BL	sub_FF833824 \n"                      
				"BL	sub_FF83317C \n"                      
				"BL	sub_FF8322B4 \n"                      
				"BL	sub_FF83E9AC \n"                      
				"BL	sub_FF833140 \n"				
				"LDMFD	SP!, {R4,LR} \n"                   
				"B	sub_FF8166A8 \n"					// --> continue in firmware  
     );
}

/*----------------------------------------------------------------------
	taskcreatePhySw_my
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) taskcreatePhySw_my() {
// FF8349EC
	
	asm volatile (
				"STMFD   SP!, {R3-R5,LR}\n"
				"LDR     R4, =0x1C3C\n"
				"LDR     R0, [R4,#4]\n"
				"CMP     R0, #0\n"
				"BNE     sub_FF834A20\n"    			// --> continue in firmware
				"MOV     R3, #0\n"
				"STR     R3, [SP]\n"
				//"LDR     R3, =0xFF8349B8 \n" 			// original task_PhySw()
				//"MOV     R2, #0x800\n"
				"LDR     R3, =mykbd_task\n" 			// --> patched PhySw() mykbd_task (responsible for listening to key presses)
				"MOV     R2, #0x2000\n" 				// stack size for new task_PhySw so we don't have to do stack switch
				"B	     sub_FF834A10 \n" 				// --> continue in firmware
	);
}

/*----------------------------------------------------------------------
	spytask
-----------------------------------------------------------------------*/
void spytask(long ua, long ub, long uc, long ud, long ue, long uf)
{
    core_spytask();
}

/*----------------------------------------------------------------------
	CreateTask_spytask
-----------------------------------------------------------------------*/
void CreateTask_spytask() {
	_CreateTask("SpyTask", 0x19, 0x2000, spytask, 0);
}

/*----------------------------------------------------------------------
	init_file_modules_task
-----------------------------------------------------------------------*/
 void __attribute__((naked,noinline)) init_file_modules_task() {
//FF89E66C

	asm volatile(
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FF89669C\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FF89A58C\n"  				// PostLogicalEventToUI
                "BL      sub_FF8966C8\n"
                "BL      core_spytask_can_start\n"      // added CHDK: Set "it's-safe-to-start"-Flag for spytask				 
				 "B		  sub_FF89E68C\n"				// --> continue in firmware
	 );
}			 

///*----------------------------------------------------------------------

