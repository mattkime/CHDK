#include "stubs_asm.h"

NHSTUB(VbattGet, 0xFF82C328)
NHSTUB(GetZoomLensCurrentPosition, 0xFFAE8474)
NHSTUB(GetZoomLensCurrentPoint, 0xFFAE8460)
NHSTUB(MoveZoomLensWithPoint, 0xFFAE8280)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFAE83F8)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFEA2F3C)

NHSTUB(platformsub_kbd_fetch_data, 0xFF8281C4)
NHSTUB(kbd_read_keys_r2, 0xFF827BC0)

NHSTUB(free, 0xFFB571E4)
NHSTUB(malloc, 0xFFB571D8)

NHSTUB(UniqueLedOn, 0xFF82DC3C)
NHSTUB(UniqueLedOff, 0xFF82DCA0)

NHSTUB(GetDrive_ClusterSize, 0xFF870710)
NHSTUB(GetDrive_TotalClusters, 0xFF87076C)
NHSTUB(GetDrive_FreeClusters, 0xFF8707A8)
NHSTUB(WriteSDCard, 0xFF87FFF8)
NHSTUB(UnsetZoomForMovie, 0xFF8117EC)  //null stub

///////////
// Following functions are for dgmod. If there is documentation for them, it is
// likely to be found in platform/s5is/sub/101b/stubs_entry_2.S.
// Currently these functions ALL point to nullsub_1 (FF8117EC). They are here
// only to get CHDK to compile. Please do not use the functions using these,
// behaviour may be undefined.
NHSTUB(GetISPitchPWM,                   0xFF8117EC)
NHSTUB(GetISYawPWM,                     0xFF8117EC)
NHSTUB(GetISShiftLensPitchPosition,     0xFF8117EC)
NHSTUB(GetISShiftLensYawPosition,       0xFF8117EC)
NHSTUB(SetISPitchPWM,                   0xFF8117EC)
NHSTUB(SetISYawPWM,                     0xFF8117EC)
NHSTUB(MoveISLensToTopLimitPosition,    0xFF8117EC)
NHSTUB(MoveISLensToBottomLimitPosition, 0xFF8117EC)
NHSTUB(MoveISLensToLeftLimitPosition,   0xFF8117EC)
NHSTUB(MoveISLensToRightLimitPosition,  0xFF8117EC)
NHSTUB(MoveISLensToCentralPosition,     0xFF8117EC)

NHSTUB(GetISHallDevicePitchOffset,      0xFF8117EC)
NHSTUB(GetISHallDeviceYawOffset,        0xFF8117EC)
NHSTUB(GetISHallDevicePitchGain,        0xFF8117EC)
NHSTUB(GetISHallDeviceYawGain,          0xFF8117EC)
NHSTUB(GetISGyroPitchOffset,            0xFF8117EC)
NHSTUB(GetISGyroYawOffset,              0xFF8117EC)
NHSTUB(GetISGyroPitchGain,              0xFF8117EC)
NHSTUB(GetISGyroYawGain,                0xFF8117EC)
NHSTUB(GetISLensCenterShiftAaxis,       0xFF8117EC)
NHSTUB(GetISLensCenterShiftBaxis,       0xFF8117EC)
NHSTUB(GetISLensEViAaxis,               0xFF8117EC)
NHSTUB(GetISLensEViBaxis,               0xFF8117EC)
NHSTUB(GetISLensDampAaxis,              0xFF8117EC)
NHSTUB(GetISLensDampBaxis,              0xFF8117EC)

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                 0xFF8117EC)
NHSTUB(GetISDriveBaxis,                 0xFF8117EC)
NHSTUB(GetISPositionAaxis,              0xFF8117EC)
NHSTUB(GetISPositionBaxis,              0xFF8117EC)
NHSTUB(GetISHallOffsetAaxis,            0xFF8117EC)
NHSTUB(GetISHallOffsetBaxis,            0xFF8117EC)
NHSTUB(GetISHallGainAaxis,              0xFF8117EC)
NHSTUB(GetISHallGainBaxis,              0xFF8117EC)
NHSTUB(GetISGyroGainAaxis,              0xFF8117EC)
NHSTUB(GetISGyroGainBaxis,              0xFF8117EC)
NHSTUB(GetISCoefficientP_A,             0xFF8117EC)
NHSTUB(GetISCoefficientP_B,             0xFF8117EC)
NHSTUB(GetISCoefficientI_A,             0xFF8117EC)
NHSTUB(GetISCoefficientI_B,             0xFF8117EC)
NHSTUB(GetISCoefficientD_A,             0xFF8117EC)
NHSTUB(GetISCoefficientD_B,             0xFF8117EC)
NHSTUB(GetISPLFAaxis,                   0xFF8117EC)
NHSTUB(GetISPLFBaxis,                   0xFF8117EC)
NHSTUB(GetISLPFAaxis,                   0xFF8117EC)
NHSTUB(GetISLPFBaxis,                   0xFF8117EC)
NHSTUB(GetISDbgData,                    0xFF8117EC)
NHSTUB(GetISADData,                     0xFF8117EC)
NHSTUB(GetISDampAaxis,                  0xFF8117EC)
NHSTUB(GetISDampBaxis,                  0xFF8117EC)
NHSTUB(GetISEViAaxis,                   0xFF8117EC)
NHSTUB(GetISEViBaxis,                   0xFF8117EC)
NHSTUB(GetISHallOut1Amp,                0xFF8117EC)
NHSTUB(ISActive,                        0xFF8117EC)

NHSTUB(GetWBStruct,                     0xFF8117EC)

NHSTUB(MuteOffPhysicalScreen,           0xFF8117EC)


NHSTUB(PostLEDMessage,                  0xFF8117EC)

NHSTUB(TurnOnDisplay,                   0xFF8117EC)
NHSTUB(TurnOffDisplay,                  0xFF8117EC)
NHSTUB(TurnOnBackLight,                 0xFF8117EC)
NHSTUB(TurnOffBackLight,                0xFF8117EC)
NHSTUB(SwitchOnDisplay,                 0xFF8117EC)
NHSTUB(SwitchOffDisplay,                0xFF8117EC)

NHSTUB(StopContinuousVRAMData,          0xFF8117EC)

NHSTUB(GetShutterReadyStateVar,         0xFF8117EC)

