#include "stubs_asm.h"

NHSTUB(Close,0xFFE46B58)  
NHSTUB(Read, 0xFFE46BEC) 
NHSTUB(Remove, 0xFFE46B78) 
NHSTUB(Write, 0xFFE46BF8)
NHSTUB(DisplayImagePhysicalScreen, 0xFFDDBEEC)
NHSTUB(free, 0xFFCD9B84)
NHSTUB(kbd_read_keys_r2, 0xFFDE74F0)
NHSTUB(Mount_FileSystem, 0xFFE45E7C)
NHSTUB(kbd_pwr_off, 0xFFDE7BD4)
NHSTUB(SetPropertyCase, 0xFFC0BB5C)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFD670E8)  //null stub
NHSTUB(GetDrive_ClusterSize, 0xFFE46344)
NHSTUB(GetDrive_TotalClusters, 0xFFE46380)
NHSTUB(GetDrive_FreeClusters, 0xFFE463BC)
NHSTUB(WriteSDCard, 0xFFE58EEC)


///////////
// Following functions are for dgmod. If there is documentation for them, it is
// likely to be found in platform/s5is/sub/101b/stubs_entry_2.S.
// Currently these functions ALL point to nullsub_1 (FFC017E4). They are here
// only to get CHDK to compile. Please do not use the functions using these,
// behaviour may be undefined.
NHSTUB(GetISPitchPWM,                             0xFFE0F148)
NHSTUB(GetISYawPWM,                               0xFFE0F15C)
NHSTUB(GetISShiftLensPitchPosition,               0xFFE0F170)
NHSTUB(GetISShiftLensYawPosition,                 0xFFE0F184)
NHSTUB(SetISPitchPWM,                             0xFFE0EEE4)
NHSTUB(SetISYawPWM,                               0xFFE0EEF4)
NHSTUB(MoveISLensToTopLimitPosition,              0xFFE0EDD8)
NHSTUB(MoveISLensToBottomLimitPosition,           0xFFE0EDC8)
NHSTUB(MoveISLensToLeftLimitPosition,             0xFFE0EDB8)
NHSTUB(MoveISLensToRightLimitPosition,            0xFFE0EDA8)
NHSTUB(MoveISLensToCentralPosition,               0xFFE0F01C)

NHSTUB(GetISHallDevicePitchOffset,                0xFFE0F0E8)
NHSTUB(GetISHallDeviceYawOffset,                  0xFFE0F0F8)
NHSTUB(GetISHallDevicePitchGain,                  0xFFE0F108)
NHSTUB(GetISHallDeviceYawGain,                    0xFFE0F118)
NHSTUB(GetISGyroPitchOffset,                      0xFFE0ED60)
NHSTUB(GetISGyroYawOffset,                        0xFFE0ED58)
NHSTUB(GetISGyroPitchGain,                        0xFFE0F128)
NHSTUB(GetISGyroYawGain,                          0xFFE0F138)
NHSTUB(GetISLensCenterShiftAaxis,                 0xFFE0ED2C)
NHSTUB(GetISLensCenterShiftBaxis,                 0xFFE0ED34)
NHSTUB(GetISLensEViAaxis,                         0xFFE0F198)
NHSTUB(GetISLensEViBaxis,                         0xFFE0F1AC)
NHSTUB(GetISLensDampAaxis,                        0xFFE0F1C0)
NHSTUB(GetISLensDampBaxis,                        0xFFE0F1D4)

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                           0xFFE8B054)
NHSTUB(GetISDriveBaxis,                           0xFFE8B090)
NHSTUB(GetISPositionAaxis,                        0xFFE8B0D0)
NHSTUB(GetISPositionBaxis,                        0xFFE8B110)
NHSTUB(GetISHallOffsetAaxis,                      0xFFE8B154)
NHSTUB(GetISHallOffsetBaxis,                      0xFFE8B198)
NHSTUB(GetISHallGainAaxis,                        0xFFE8B1D8)
NHSTUB(GetISHallGainBaxis,                        0xFFE8B218)
NHSTUB(GetISGyroGainAaxis,                        0xFFE8B258)
NHSTUB(GetISGyroGainBaxis,                        0xFFE8B298)
NHSTUB(GetISCoefficientP_A,                       0xFFE8B79C)
NHSTUB(GetISCoefficientP_B,                       0xFFE8B7DC)
NHSTUB(GetISCoefficientI_A,                       0xFFE8B81C)
NHSTUB(GetISCoefficientI_B,                       0xFFE8B85C)
NHSTUB(GetISCoefficientD_A,                       0xFFE8B89C)
NHSTUB(GetISCoefficientD_B,                       0xFFE8B8DC)
NHSTUB(GetISPLFAaxis,                             0xFFE8B618)
NHSTUB(GetISPLFBaxis,                             0xFFE8B648)
NHSTUB(GetISLPFAaxis,                             0xFFE8B698)
NHSTUB(GetISLPFBaxis,                             0xFFE8B6C8)
NHSTUB(GetISDbgData,                              0xFFE8B364)
NHSTUB(GetISADData,                               0xFFE8B3A8)
NHSTUB(GetISDampAaxis,                            0xFFE8B4F8)
NHSTUB(GetISDampBaxis,                            0xFFE8B530)
NHSTUB(GetISEViAaxis,                             0xFFE8B568)
NHSTUB(GetISEViBaxis,                             0xFFE8B5A0)
NHSTUB(GetISHallOut1Amp,                          0xFFE8B498)
NHSTUB(ISActive,                                  0xFFC017E4) // nullsub_1

NHSTUB(GetWBStruct,                               0xFFC017E4) // nullsub_1, useless for now

NHSTUB(MuteOffPhysicalScreen,                     0xFFC34DD8)


NHSTUB(PostLEDMessage,                            0xFFDE581C)

NHSTUB(TurnOnDisplay,                             0xFFC34CE8)
NHSTUB(TurnOffDisplay,                            0xFFC34D14)
NHSTUB(TurnOnBackLight,                           0xFFC34D40)
NHSTUB(TurnOffBackLight,                          0xFFC34D70)
NHSTUB(SwitchOnDisplay,                           0xFFE0C218)
NHSTUB(SwitchOffDisplay,                          0xFFE0C1E4)

NHSTUB(StopContinuousVRAMData,                    0xFFC017E4) // nullsub_1, useless for now

NHSTUB(GetShutterReadyStateVar,                   0xFFC017E4) // nullsub_1, useless for now

