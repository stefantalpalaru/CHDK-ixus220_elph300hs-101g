// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.01G
//   Canon IXUS 220HS

// Values for makefile.inc
//   PLATFORMID = 12841 (0x3229) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x07ffffff
//   KEYSYS = d4c                // Found @ 0xffff3620
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff3630

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NSTUB(kbd_pwr_off                             ,0xff865570) //  2 60%
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0xff841798

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff89e7f8 -> ff89b194 -> ff9b139c -> ffb04244 -> ffc4eea0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(physw_status                            ,0x0003418c) // Found @0xff834e18,          stubs_min = 0x0003418c (0x0003418c)
//DEF(physw_run                               ,0x00001c3c) // Found @0xff8349bc,          stubs_min = 0x00001c3c (0x00001c3c)
//DEF(levent_table                            ,0xffbeb268) // Found @0xffbeb268,          stubs_min = 0xffbeb268 (0xffbeb268)
//DEF(FlashParamsTable                        ,0xffc4f0e0) // Found @0xffc4f0e0,          stubs_min = 0xffc4f0e0 (0xffc4f0e0)
//DEF(movie_status                            ,0x00006dcc) // Found @0xff984bd0,          stubs_min = 0x00006dcc (0x00006dcc)
//DEF(full_screen_refresh                     ,0x00009d00) // Found @0xffa32dfc,          stubs_min = 0x00009d00 (0x00009d00)
//DEF(canon_menu_active                       ,0x00003210) // Found @0xff896910,          stubs_min = 0x00003210 (0x00003210)
//DEF(canon_shoot_menu_active                 ,0x000083d9) // Found @0xff9c8c1c,          stubs_min = 0x000083d9 (0x000083d9)
//DEF(playrec_mode                            ,0x00002f38) // Found @0xff888774,          stubs_min = 0x00002f38 (0x00002f38)
//DEF(zoom_status                             ,0x0000ded8) // Found @0xffb07900,          stubs_min = 0x0000ded8 (0x0000ded8)
//DEF(some_flag_for_af_scan                   ,0x000071cc) // Found @0xff989240,          stubs_min = 0x000071cc (0x000071cc)
//DEF(zoom_busy                               ,0x00006cf4) // Found @0xff97fd74,          stubs_min = 0x00006cf4 (0x00006cf4)
//DEF(focus_busy                              ,0x00006b68) // Found @0xff97af60,          stubs_min = 0x00006b68 (0x00006b68)
//DEF(recreview_hold                          ,0x00003828) // Found @0xff8a6510, ** != ** stubs_min = 0x000094c4 (0x93D4+0xF0)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; } // Found @0xff85fd1c
//void *vid_get_viewport_fb()      { return (void*)0x405c6b80; } // Found @0xffb5e17c
//char *camera_jpeg_count_str()    { return (char*)0x000babac; } // Found @0xffa2a298
//long hook_raw_size()             { return 0x0123eaf0; }        // Found @0xffb61674
//int get_flash_params_count(void) { return 0xa0; }              // Found @0xff9b23d4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffba2c18, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xffba2c38, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffba2be0, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffba2be0, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffba2bd8, levent 0x00
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xffba2b98, levent 0x09
//    { 2, KEY_SET             ,0x00000002 }, // Found @0xffba2ba0, levent 0x08
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffba2ba8, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffba2bb0, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffba2bb8, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffba2bc0, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffba2bc8, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffba2bd0, levent 0x04
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4168 // Found @0xff952bb4
//#define CAM_RAW_ROWS      3060 // Found @0xff952bc0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83c0f0

// Misc stuff
DEF(ctypes, 0xffba014a)

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NSTUB(AllocateMemory                          ,0xffaf253c) //101
NSTUB(AllocateUncacheableMemory               ,0xff83c0a8) //112
NSTUB(Close                                   ,0xff8383e8) //101
NSTUB(CreateTask                              ,0xff81e9b0) //101
NSTUB(DebugAssert                             ,0xff81ec88) //111
NSTUB(DeleteFile_Fut                          ,0xff837d00) //112
NSTUB(DoAFLock                                ,0xff839c28) //102
NSTUB(EnterToCompensationEVF                  ,0xff839e84) //104
NSTUB(ExecuteEventProcedure                   ,0xff8920f8) //  2
NSTUB(ExitFromCompensationEVF                 ,0xff839ec8) //104
NSTUB(ExitTask                                ,0xff81ec40) //101
NSTUB(ExpCtrlTool_StartContiAE                ,0xff848730) //104
NSTUB(ExpCtrlTool_StopContiAE                 ,0xff848808) //104
NSTUB(Fclose_Fut                              ,0xff837e7c) //101
NSTUB(Feof_Fut                                ,0xff838068) //  1
NSTUB(Fflush_Fut                              ,0xff8380a4) //  1
NSTUB(Fgets_Fut                               ,0xff837fd0) //  6
NSTUB(Fopen_Fut                               ,0xff837e3c) //101
NSTUB(Fread_Fut                               ,0xff837f28) //101
NSTUB(FreeMemory                              ,0xffaf2534) //101
NSTUB(FreeUncacheableMemory                   ,0xff83c0e8) //112
NSTUB(Fseek_Fut                               ,0xff83801c) //101
NSTUB(Fwrite_Fut                              ,0xff837f7c) //101
NSTUB(GetBatteryTemperature                   ,0xff868d7c) //102
NSTUB(GetCCDTemperature                       ,0xff868d08) //102
NSTUB(GetCurrentAvValue                       ,0xff97cb48) //102
NSTUB(GetDrive_ClusterSize                    ,0xff87630c) //  6
NSTUB(GetDrive_FreeClusters                   ,0xff876364) //  6
NSTUB(GetDrive_TotalClusters                  ,0xff87633c) //  6
NSTUB(GetFocusLensSubjectDistance             ,0xff97bbe4) //102
NSTUB(GetFocusLensSubjectDistanceFromLens     ,0xff97c044) //  3
NSTUB(GetImageFolder                          ,0xff959b4c) //  6
NSTUB(GetKbdState                             ,0xff865558) //109
NSTUB(GetMemInfo                              ,0xff81a29c) //  3
NSTUB(GetOpticalTemperature                   ,0xff868df0) //102
NSTUB(GetParameterData                        ,0xff9b2394) //101
NSTUB(GetPropertyCase                         ,0xff895e60) //102
NSTUB(GetSystemTime                           ,0xffaf2594) //101
NSTUB(GetZoomLensCurrentPoint                 ,0xff9801ec) //102
NSTUB(GetZoomLensCurrentPosition              ,0xffadccd0) //102
NSTUB(GiveSemaphore                           ,0xff83baa0) //112
NSTUB(IsStrobeChargeCompleted                 ,0xff8e8b94) //102
NSTUB(LEDDrive                                ,0xff864a7c) //101
NSTUB(LocalTime                               ,0xff88f988) //  6
NSTUB(LockMainPower                           ,0xff89ad84) //103
NSTUB(Lseek                                   ,0xff838604) //101
NSTUB(MakeDirectory_Fut                       ,0xff837d74) //  6
NSTUB(MakeSDCardBootable                      ,0xff87659c) //105
NSTUB(MoveFocusLensToDistance                 ,0xffb5a478) //102
NSTUB(MoveIrisWithAv                          ,0xffaeed0c) //102
NSTUB(MoveZoomLensWithPoint                   ,0xffaef3c4) //102
NSTUB(NewTaskShell                            ,0xff8958a8) //101
NSTUB(Open                                    ,0xff838320) //101
NSTUB(PB2Rec                                  ,0xff89dd28) //104
NSTUB(PT_MoveDigitalZoomToWide                ,0xff87fbcc) //102
NSTUB(PT_MoveOpticalZoomAt                    ,0xff87fba4) //102
NSTUB(PT_PlaySound                            ,0xff88a774) //  6
NSTUB(PostLogicalEventForNotPowerType         ,0xff89a540) //103
NSTUB(PostLogicalEventToUI                    ,0xff89a58c) //103
NSTUB(PutInNdFilter                           ,0xffaef20c) //102
NSTUB(PutOutNdFilter                          ,0xffaef230) //102
NSTUB(Read                                    ,0xff81ad58) //101
NSTUB(ReadFastDir                             ,0xffaca2bc) //  6
NSTUB(Rec2PB                                  ,0xff89dd68) //104
NSTUB(RefreshPhysicalScreen                   ,0xff8b1da0) //104
NSTUB(Remove                                  ,0xff83855c) //  6
NSTUB(RenameFile_Fut                          ,0xff837c6c) //  6
NSTUB(Restart                                 ,0xff83d8bc) //106
NSTUB(ScreenLock                              ,0xff8b2f98) //  4
NSTUB(ScreenUnlock                            ,0xff8b2ffc) //  3
NSTUB(SetAE_ShutterSpeed                      ,0xffb5d2f4) //102
NSTUB(SetAutoShutdownTime                     ,0xff89adf8) //103
NSTUB(SetCurrentCaptureModeType               ,0xff8a3510) //101
NSTUB(SetFileTimeStamp                        ,0xff838774) //  6
NSTUB(SetLogicalEventActive                   ,0xff89aaec) //101
NSTUB(SetParameterData                        ,0xff9b2304) //101
NSTUB(SetPropertyCase                         ,0xff895d44) //102
NSTUB(SetScriptMode                           ,0xff89ab3c) //101
NSTUB(SleepTask                               ,0xff83bd4c) //101
NSTUB(TakeSemaphore                           ,0xff83b9d0) //101
NSTUB(TurnOffBackLight                        ,0xff8aa31c) //104
NSTUB(TurnOnBackLight                         ,0xff8aa304) //104
NSTUB(UIFS_WriteFirmInfoToFile                ,0xff9a2184) //101
NSTUB(UnlockAF                                ,0xff839c60) //102
NSTUB(UnlockMainPower                         ,0xff89acd8) //103
NSTUB(VbattGet                                ,0xff833050) //101
NSTUB(Write                                   ,0xff83843c) //101
NSTUB(WriteSDCard                             ,0xff96b024) //108
NSTUB(_log                                    ,0xffb9cc70) //111
NSTUB(_log10                                  ,0xffb9d1b0) //112
NSTUB(_pow                                    ,0xffb9d328) //114
NSTUB(_sqrt                                   ,0xffb9ef4c) //  6
NSTUB(add_ptp_handler                         ,0xffa7be20) //  6
NSTUB(apex2us                                 ,0xffa3b18c) //  4
NSTUB(close                                   ,0xff81abb4) //  6
NSTUB(closedir                                ,0xffaca118) //  4
NSTUB(err_init_task                           ,0xff815fd4) //  4
NSTUB(exmem_alloc                             ,0xff890950) //101
NSTUB(free                                    ,0xff814244) //112
NSTUB(kbd_p1_f                                ,0xff834e94) //109
NSTUB(kbd_p1_f_cont                           ,0xff834ea0) //109
NSTUB(kbd_p2_f                                ,0xff83468c) //109
NSTUB(kbd_read_keys                           ,0xff834e18) //109
NSTUB(kbd_read_keys_r2                        ,0xff864f74) //109
NSTUB(lseek                                   ,0xff838604) //101
NSTUB(malloc                                  ,0xff8141ec) //112
NSTUB(memcmp                                  ,0xff820934) //101
NSTUB(memcpy                                  ,0xff84179c) //101
NSTUB(memset                                  ,0xffa3a18c) //101
NSTUB(mkdir                                   ,0xff838884) //  6
NSTUB(mktime_ext                              ,0xff8b3e10) //  1
NSTUB(open                                    ,0xff81ab04) //  6
NSTUB(opendir                                 ,0xffaca168) //  6
NSTUB(openfastdir                             ,0xffaca168) //  6
NSTUB(qsort                                   ,0xffb3d6cc) //  6
NSTUB(rand                                    ,0xffa3a2cc) //  6
NSTUB(read                                    ,0xff81ad58) //101
NSTUB(readfastdir                             ,0xffaca2bc) //  6
NSTUB(reboot_fw_update                        ,0xffacf758) //  6
NSTUB(rename                                  ,0xff837c6c) //  6
NSTUB(set_control_event                       ,0xff89a7b0) //111
NSTUB(srand                                   ,0xffa3a2c0) //  6
NSTUB(stat                                    ,0xff83864c) //  3
NSTUB(strcat                                  ,0xff8b35c8) //  1
NSTUB(strchr                                  ,0xff8140b8) //  1
NSTUB(strcmp                                  ,0xff8208f0) //101
NSTUB(strcpy                                  ,0xff8208d8) //101
NSTUB(strftime                                ,0xff8b3810) //113
NSTUB(strlen                                  ,0xff814104) //101
NSTUB(strncmp                                 ,0xff81406c) //  1
NSTUB(strncpy                                 ,0xff814030) //  1
NSTUB(strrchr                                 ,0xff8140dc) //  1
NSTUB(strtol                                  ,0xff841a9c) //101
NSTUB(strtolx                                 ,0xff8418a0) //109
  DEF(task_CaptSeq                            ,0xff882920) //110
  DEF(task_ExpDrv                             ,0xff8cbcbc) //110
  DEF(task_InitFileModules                    ,0xff89e66c) //110
  DEF(task_MovieRecord                        ,0xff985e5c) //110
  DEF(task_PhySw                              ,0xff8349b8) //110
NSTUB(time                                    ,0xff88ff64) //  6
NSTUB(vsprintf                                ,0xff820898) //  6
NSTUB(write                                   ,0xff83843c) //101
