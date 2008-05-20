#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFFA42C08)
NHSTUB(UniqueLedOff, 0xFFA42CB0)
NHSTUB(free, 0xFF92B488)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF841CC0)  // null stub
NHSTUB(UnsetZoomForMovie, 0xFF841CC0)  // null stub

NHSTUB(GetDrive_ClusterSize, 0xFFAAE4C8)
NHSTUB(GetDrive_TotalClusters, 0xFFAAE504)
NHSTUB(GetDrive_FreeClusters, 0xFFAAE540)
NHSTUB(DisplayImagePhysicalScreen, 0xFFA378A8)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAFF7C8)
NHSTUB(Mount_FileSystem, 0xFFAAE000)
NHSTUB(MoveZoomLensWithPoint, 0xFFAFF6D8)
NHSTUB(Remove, 0xFFAAECFC)
NHSTUB(Write, 0xFFAAED7C)
NHSTUB(Close, 0xFFAAECDC)
NHSTUB(Read, 0xFFAAED70)
NHSTUB(kbd_read_keys_r2, 0xFFA4457C)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAEABD4)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAEA6D4)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAFF7B4)
NHSTUB(SetPropertyCase, 0xFF81BC20)
NHSTUB(PostLEDMessage, 0xFFA4290C)


///////////
// Following functions are for dgmod
// nullsub_1 is at 0xFF8117E8
NHSTUB(GetISPitchPWM,                             0xFFA6D41C)
NHSTUB(GetISYawPWM,                               0xFFA6D430)
NHSTUB(GetISShiftLensPitchPosition,               0xFFA6D444)
NHSTUB(GetISShiftLensYawPosition,                 0xFFA6D458)
NHSTUB(SetISPitchPWM,                             0xFFA6D1B8)
NHSTUB(SetISYawPWM,                               0xFFA6D1C8)
NHSTUB(MoveISLensToTopLimitPosition,              0xFFA6D0AC)
NHSTUB(MoveISLensToBottomLimitPosition,           0xFFA6D09C)
NHSTUB(MoveISLensToLeftLimitPosition,             0xFFA6D08C)
NHSTUB(MoveISLensToRightLimitPosition,            0xFFA6D07C)
NHSTUB(MoveISLensToCentralPosition,               0xFFA6D2F0)

NHSTUB(GetISHallDevicePitchOffset,                0xFFA6D3BC)
NHSTUB(GetISHallDeviceYawOffset,                  0xFFA6D3CC)
NHSTUB(GetISHallDevicePitchGain,                  0xFFA6D3DC)
NHSTUB(GetISHallDeviceYawGain,                    0xFFA6D3EC)
NHSTUB(GetISGyroPitchOffset,                      0xFFA6D034)
NHSTUB(GetISGyroYawOffset,                        0xFFA6D02C)
NHSTUB(GetISGyroPitchGain,                        0xFFA6D3FC)
NHSTUB(GetISGyroYawGain,                          0xFFA6D40C)
NHSTUB(GetISLensCenterShiftAaxis,                 0xFFA6D000)
NHSTUB(GetISLensCenterShiftBaxis,                 0xFFA6D008)
NHSTUB(GetISLensEViAaxis,                         dg_tx1_EViA) // Hack something
NHSTUB(GetISLensEViBaxis,                         dg_tx1_EViB) // Hack something
NHSTUB(GetISLensDampAaxis,                        0xFF8117E8) // nullsub
NHSTUB(GetISLensDampBaxis,                        0xFF8117E8) // nullsub

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                           0xFFB06B38)
NHSTUB(GetISDriveBaxis,                           0xFFB06B6C)
NHSTUB(GetISPositionAaxis,                        0xFFB06BA4)
NHSTUB(GetISPositionBaxis,                        0xFFB06BDC)
NHSTUB(GetISHallOffsetAaxis,                      0xFFB06C18)
NHSTUB(GetISHallOffsetBaxis,                      0xFFB06C54)
NHSTUB(GetISHallGainAaxis,                        0xFFB06C8C)
NHSTUB(GetISHallGainBaxis,                        0xFFB06CC4)
NHSTUB(GetISGyroGainAaxis,                        0xFFB06CFC)
NHSTUB(GetISGyroGainBaxis,                        0xFFB06D34)
NHSTUB(GetISCoefficientP_A,                       0xFFB071C0)
NHSTUB(GetISCoefficientP_B,                       0xFFB07200)
NHSTUB(GetISCoefficientI_A,                       0xFFB07240)
NHSTUB(GetISCoefficientI_B,                       0xFFB07280)
NHSTUB(GetISCoefficientD_A,                       0xFFB072C0)
NHSTUB(GetISCoefficientD_B,                       0xFFB07300)
NHSTUB(GetISPLFAaxis,                             0xFFB0703C)
NHSTUB(GetISPLFBaxis,                             0xFFB0706C)
NHSTUB(GetISLPFAaxis,                             0xFFB070BC)
NHSTUB(GetISLPFBaxis,                             0xFFB070EC)
NHSTUB(GetISDbgData,                              0xFFB06DF8)
NHSTUB(GetISADData,                               0xFFB06E3C)
NHSTUB(GetISDampAaxis,                            0xFFB06F8C)
NHSTUB(GetISDampBaxis,                            0xFFB06FC4)
NHSTUB(GetISEViAaxis,                             dg_tx1_EViA) // Hack something
NHSTUB(GetISEViBaxis,                             dg_tx1_EViB) // Hack something
NHSTUB(GetISHallOut1Amp,                          0xFFB06F2C)
NHSTUB(ISActive,                                  0xFFB07324)

NHSTUB(GetWBStruct,                               0xFF8117E8) // nullsub, not useful

NHSTUB(MuteOffPhysicalScreen,                     0xFF8883D0)


//NHSTUB(PostLEDMessage,                  0xFFA4290C) // Already in TX1

NHSTUB(TurnOnDisplay,                             0xFF8489E4)
NHSTUB(TurnOffDisplay,                            0xFF848A10)
NHSTUB(TurnOnBackLight,                           0xFF848A3C)
NHSTUB(TurnOffBackLight,                          0xFF848A6C)
NHSTUB(SwitchOnDisplay,                           0xFFA6A4C4)
NHSTUB(SwitchOffDisplay,                          0xFFA6A490)

NHSTUB(StopContinuousVRAMData,                    0xFF8117E8) // nullsub, not useful

NHSTUB(GetShutterReadyStateVar,                   0xFF8117E8) // nullsub, not useful

