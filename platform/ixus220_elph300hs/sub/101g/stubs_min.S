#include "stubs_asm.h"

//beta5
DEF(enabled_refresh_physical_screen,0x53C4+0x14) //changed to fix error when displaying menu, was 0x20 FF0A99C0 

//added beta2
DEF(focus_len_table, 0xfffea288)		  // search for 21500 (longest focus length in micrometers) & 4300 (shortest length)

//not touched
DEF(physw_status, 0x0003418c) // Found @0xff834e18
DEF(physw_run, 0x00001c3c) // Found @0xff8349bc
DEF(focus_busy, 0x00006b68)
DEF(zoom_busy, 0x00006cf4)
DEF(canon_menu_active, 0x00003210) // Found @0xff896910
DEF(recreview_hold, 0x93D4 + 0xF0)        // FF1B6640
DEF(playrec_mode, 0x00002f38) // Found @0xff888774
DEF(levent_table,0xffbeb268) // Found @0xffbeb230
DEF(full_screen_refresh, 0x00009d00) // Found @0xffa32dfc
DEF(FlashParamsTable,0xffc4f0e0) // Found @0xffc4f0a8
DEF(some_flag_for_af_scan, 0x000071cc) // Found @0xff989240
DEF(led_table, 0x258C + 0x04)             // FF0557C4
DEF(canon_shoot_menu_active, 0x000083d9) // Found @0xff9c8c1c
DEF(movie_status, 0x00006dcc) // Found @0xff984bd0
DEF(zoom_status, 0x0000ded8) // Found @0xffb078a0

