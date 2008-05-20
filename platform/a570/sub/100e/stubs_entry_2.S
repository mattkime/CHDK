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
NHSTUB(GetISPitchPWM,                   0xFFC017E4)
NHSTUB(GetISYawPWM,                     0xFFC017E4)
NHSTUB(GetISShiftLensPitchPosition,     0xFFC017E4)
NHSTUB(GetISShiftLensYawPosition,       0xFFC017E4)
NHSTUB(SetISPitchPWM,                   0xFFC017E4)
NHSTUB(SetISYawPWM,                     0xFFC017E4)
NHSTUB(MoveISLensToTopLimitPosition,    0xFFC017E4)
NHSTUB(MoveISLensToBottomLimitPosition, 0xFFC017E4)
NHSTUB(MoveISLensToLeftLimitPosition,   0xFFC017E4)
NHSTUB(MoveISLensToRightLimitPosition,  0xFFC017E4)
NHSTUB(MoveISLensToCentralPosition,     0xFFC017E4)

NHSTUB(GetISHallDevicePitchOffset,      0xFFC017E4)
NHSTUB(GetISHallDeviceYawOffset,        0xFFC017E4)
NHSTUB(GetISHallDevicePitchGain,        0xFFC017E4)
NHSTUB(GetISHallDeviceYawGain,          0xFFC017E4)
NHSTUB(GetISGyroPitchOffset,            0xFFC017E4)
NHSTUB(GetISGyroYawOffset,              0xFFC017E4)
NHSTUB(GetISGyroPitchGain,              0xFFC017E4)
NHSTUB(GetISGyroYawGain,                0xFFC017E4)
NHSTUB(GetISLensCenterShiftAaxis,       0xFFC017E4)
NHSTUB(GetISLensCenterShiftBaxis,       0xFFC017E4)
NHSTUB(GetISLensEViAaxis,               0xFFC017E4)
NHSTUB(GetISLensEViBaxis,               0xFFC017E4)
NHSTUB(GetISLensDampAaxis,              0xFFC017E4)
NHSTUB(GetISLensDampBaxis,              0xFFC017E4)

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                 0xFFC017E4)
NHSTUB(GetISDriveBaxis,                 0xFFC017E4)
NHSTUB(GetISPositionAaxis,              0xFFC017E4)
NHSTUB(GetISPositionBaxis,              0xFFC017E4)
NHSTUB(GetISHallOffsetAaxis,            0xFFC017E4)
NHSTUB(GetISHallOffsetBaxis,            0xFFC017E4)
NHSTUB(GetISHallGainAaxis,              0xFFC017E4)
NHSTUB(GetISHallGainBaxis,              0xFFC017E4)
NHSTUB(GetISGyroGainAaxis,              0xFFC017E4)
NHSTUB(GetISGyroGainBaxis,              0xFFC017E4)
NHSTUB(GetISCoefficientP_A,             0xFFC017E4)
NHSTUB(GetISCoefficientP_B,             0xFFC017E4)
NHSTUB(GetISCoefficientI_A,             0xFFC017E4)
NHSTUB(GetISCoefficientI_B,             0xFFC017E4)
NHSTUB(GetISCoefficientD_A,             0xFFC017E4)
NHSTUB(GetISCoefficientD_B,             0xFFC017E4)
NHSTUB(GetISPLFAaxis,                   0xFFC017E4)
NHSTUB(GetISPLFBaxis,                   0xFFC017E4)
NHSTUB(GetISLPFAaxis,                   0xFFC017E4)
NHSTUB(GetISLPFBaxis,                   0xFFC017E4)
NHSTUB(GetISDbgData,                    0xFFC017E4)
NHSTUB(GetISADData,                     0xFFC017E4)
NHSTUB(GetISDampAaxis,                  0xFFC017E4)
NHSTUB(GetISDampBaxis,                  0xFFC017E4)
NHSTUB(GetISEViAaxis,                   0xFFC017E4)
NHSTUB(GetISEViBaxis,                   0xFFC017E4)
NHSTUB(GetISHallOut1Amp,                0xFFC017E4)
NHSTUB(ISActive,                        0xFFC017E4)

NHSTUB(GetWBStruct,                     0xFFC017E4)

NHSTUB(MuteOffPhysicalScreen,           0xFFC017E4)


NHSTUB(PostLEDMessage,                  0xFFC017E4)

NHSTUB(TurnOnDisplay,                   0xFFC017E4)
NHSTUB(TurnOffDisplay,                  0xFFC017E4)
NHSTUB(TurnOnBackLight,                 0xFFC017E4)
NHSTUB(TurnOffBackLight,                0xFFC017E4)
NHSTUB(SwitchOnDisplay,                 0xFFC017E4)
NHSTUB(SwitchOffDisplay,                0xFFC017E4)

NHSTUB(StopContinuousVRAMData,          0xFFC017E4)

NHSTUB(GetShutterReadyStateVar,         0xFFC017E4)

