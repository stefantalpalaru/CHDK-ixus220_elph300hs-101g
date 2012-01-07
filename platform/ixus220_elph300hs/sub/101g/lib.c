#include "platform.h"

/*
IXUS220HS / ELPH300HS
full 19131120
0x1048 *  BF4   =  C29CA0
4168 * 3060 = 12754080 
*/

char *hook_raw_image_addr()
{

	if (*((int*)0x2E94) != 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x413391A0;  // FFB615BC

}

char *hook_alt_raw_image_addr()
{

	if (*((int*)0x2E94) == 0)
		return (char*) 0x46000000;
	else
		return (char*) 0x413391A0;  // FFB615BC

}

long hook_raw_size()
{
	//FF375484 dword_FF375484  DCD 0x123EAF0
	return 0x0123eaf0;
	
}

void *vid_get_viewport_live_fb()
{
	return (void*)(void*)(*(int*)(0x2258));
	
  	// Found by searching RAM locations that referenced 0x405D7980 (viewport buffer)
	// and also changed to the other buffer addresses over time. Then used each here
	// and selected value that gave the fastest Motion Detect response using http://dataghost.com/chdk/md_meter.html.
}

// OSD buffer
void *vid_get_bitmap_fb()
{	
	//FF050F24                 LDR     R0, =0x40471000
	return (void*)0x40471000;
}	                           

// Live picture buffer (shoot half-pressed)
void *vid_get_viewport_fb()
{
	return (void*)0x405c6b80;  					                   // found by search for VRAM Address @FF371E8C
}

void *vid_get_viewport_fb_d()
{
	//FF06C580 dword_FF06C580  DCD 0x3C70
	//FF06D300                 STR     R12, [R5,#0x58
	return (void*)(*(int*)(0x3C70+0x58));                  

}

char *camera_jpeg_count_str()
{
	//FF2327FC                 LDR     R0, =0xCA790
	return (void*)0x000babac;                                      

}

