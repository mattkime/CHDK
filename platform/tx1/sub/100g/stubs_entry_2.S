#include "stubs_asm.h"

NHSTUB(UniqueLedOn, 0xFFA42B88)
NHSTUB(UniqueLedOff, 0xFFA42C30)
NHSTUB(free, 0xFF92B488)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFF841CC0)  // null stub
NHSTUB(UnsetZoomForMovie, 0xFF841CC0)  // null stub

NHSTUB(GetDrive_ClusterSize, 0xFFAAE448)
NHSTUB(GetDrive_TotalClusters, 0xFFAAE484)
NHSTUB(GetDrive_FreeClusters, 0xFFAAE4C0)

NHSTUB(DisplayImagePhysicalScreen, 0xFFA37828)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAFF748)
NHSTUB(Mount_FileSystem, 0xFFAADF80)
NHSTUB(MoveZoomLensWithPoint, 0xFFAFF658)
NHSTUB(Remove, 0xFFAAEC7C)
NHSTUB(Write, 0xFFAAECFC)
NHSTUB(Close, 0xFFAAEC5C)
NHSTUB(Read, 0xFFAAECF0)

NHSTUB(kbd_read_keys_r2, 0xFFA444FC)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAEAB54)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAEA654)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAFF734)
NHSTUB(SetPropertyCase, 0xFF81BC20)
NHSTUB(PostLEDMessage, 0xFFA4288C)
NHSTUB(PutInNdFilter, 0xffa63994)
NHSTUB(PutOutNdFilter, 0xffa639DC)


///////////
// Following functions are for dgmod
// nullsub_1 is at 0xFF8117E8
NHSTUB(GetISPitchPWM,                             0xFFA6D39C)
NHSTUB(GetISYawPWM,                               0xFFA6D3B0)
NHSTUB(GetISShiftLensPitchPosition,               0xFFA6D3C4)
NHSTUB(GetISShiftLensYawPosition,                 0xFFA6D3D8)
NHSTUB(SetISPitchPWM,                             0xFFA6D138)
NHSTUB(SetISYawPWM,                               0xFFA6D148)
NHSTUB(MoveISLensToTopLimitPosition,              0xFFA6D02C)
NHSTUB(MoveISLensToBottomLimitPosition,           0xFFA6D01C)
NHSTUB(MoveISLensToLeftLimitPosition,             0xFFA6D00C)
NHSTUB(MoveISLensToRightLimitPosition,            0xFFA6CFFC)
NHSTUB(MoveISLensToCentralPosition,               0xFFA6D270)

NHSTUB(GetISHallDevicePitchOffset,                0xFFA6D33C)
NHSTUB(GetISHallDeviceYawOffset,                  0xFFA6D34C)
NHSTUB(GetISHallDevicePitchGain,                  0xFFA6D35C)
NHSTUB(GetISHallDeviceYawGain,                    0xFFA6D36C)
NHSTUB(GetISGyroPitchOffset,                      0xFFA6CFB4)
NHSTUB(GetISGyroYawOffset,                        0xFFA6CFAC)
NHSTUB(GetISGyroPitchGain,                        0xFFA6D37C)
NHSTUB(GetISGyroYawGain,                          0xFFA6D38C)
NHSTUB(GetISLensCenterShiftAaxis,                 0xFFA6CF80)
NHSTUB(GetISLensCenterShiftBaxis,                 0xFFA6CF88)
NHSTUB(GetISLensEViAaxis,                         dg_tx1_EViA) // Hack something
NHSTUB(GetISLensEViBaxis,                         dg_tx1_EViB) // Hack something
NHSTUB(GetISLensDampAaxis,                        0xFF8117E8) // nullsub
NHSTUB(GetISLensDampBaxis,                        0xFF8117E8) // nullsub

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                           0xFFB06AB8)
NHSTUB(GetISDriveBaxis,                           0xFFB06AEC)
NHSTUB(GetISPositionAaxis,                        0xFFB06B24)
NHSTUB(GetISPositionBaxis,                        0xFFB06B5C)
NHSTUB(GetISHallOffsetAaxis,                      0xFFB06B98)
NHSTUB(GetISHallOffsetBaxis,                      0xFFB06BD4)
NHSTUB(GetISHallGainAaxis,                        0xFFB06C0C)
NHSTUB(GetISHallGainBaxis,                        0xFFB06C44)
NHSTUB(GetISGyroGainAaxis,                        0xFFB06C7C)
NHSTUB(GetISGyroGainBaxis,                        0xFFB06CB4)
NHSTUB(GetISCoefficientP_A,                       0xFFB07140)
NHSTUB(GetISCoefficientP_B,                       0xFFB07180)
NHSTUB(GetISCoefficientI_A,                       0xFFB071C0)
NHSTUB(GetISCoefficientI_B,                       0xFFB07200)
NHSTUB(GetISCoefficientD_A,                       0xFFB07240)
NHSTUB(GetISCoefficientD_B,                       0xFFB07280)
NHSTUB(GetISPLFAaxis,                             0xFFB06FBC)
NHSTUB(GetISPLFBaxis,                             0xFFB06FEC)
NHSTUB(GetISLPFAaxis,                             0xFFB0703C)
NHSTUB(GetISLPFBaxis,                             0xFFB0706C)
NHSTUB(GetISDbgData,                              0xFFB06D78)
NHSTUB(GetISADData,                               0xFFB06DBC)
NHSTUB(GetISDampAaxis,                            0xFFB06F0C)
NHSTUB(GetISDampBaxis,                            0xFFB06F44)
NHSTUB(GetISEViAaxis,                             dg_tx1_EViA) // Hack something
NHSTUB(GetISEViBaxis,                             dg_tx1_EViB) // Hack something
NHSTUB(GetISHallOut1Amp,                          0xFFB06EAC)
NHSTUB(ISActive,                                  0xFFB072A4)

NHSTUB(GetWBStruct,                               0xFF8117E8) // nullsub, not useful

NHSTUB(MuteOffPhysicalScreen,                     0xFF848AD4)


//NHSTUB(PostLEDMessage,                  0xFFA4290C) // Already in TX1

NHSTUB(TurnOnDisplay,                             0xFF8489E4)
NHSTUB(TurnOffDisplay,                            0xFF848A10)
NHSTUB(TurnOnBackLight,                           0xFF848A3C)
NHSTUB(TurnOffBackLight,                          0xFF848A6C)
NHSTUB(SwitchOnDisplay,                           0xFFA6A444)
NHSTUB(SwitchOffDisplay,                          0xFFA6A410)

NHSTUB(StopContinuousVRAMData,                    0xFF8117E8) // nullsub, not useful

NHSTUB(GetShutterReadyStateVar,                   0xFF8117E8) // nullsub, not useful

