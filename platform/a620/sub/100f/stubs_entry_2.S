#include "stubs_asm.h"

//NHSTUB(VbattGet, 0xFFC1B4AC)
//NHSTUB(GetZoomLensCurrentPosition, 0xFFE59D2C)
//NHSTUB(GetZoomLensCurrentPoint, 0xFFE59D18)
//NHSTUB(GetFocusLensSubjectDistance, 0xFFE6D4AC)

NHSTUB(malloc, 0xFFEC5BC0)
NHSTUB(free, 0xFFEC5BCC)

//NHSTUB(isalpha, 0xFFEB8A94)
//NHSTUB(isdigit, 0xFFEB8AC4)
//NHSTUB(islower, 0xFFEB8AF4)
//NHSTUB(isspace, 0xFFEB8B3C)
//NHSTUB(isupper, 0xFFEB8B54)
//NHSTUB(rand, 0xFFEBBF78)
//NHSTUB(srand, 0xFFEBBF9C)

NHSTUB(GetDrive_ClusterSize, 0xffc5c668)
NHSTUB(GetDrive_TotalClusters, 0xffc5c6a4)
NHSTUB(GetDrive_FreeClusters, 0xffc5c6e0)

NHSTUB(SetZoomActuatorSpeedPercent, 0xFFC19688)  //null stub

//NHSTUB(PutInNdFilter, 0xFFE78410) 
//NHSTUB(PutOutNdFilter, 0xFFE78458)

///////////
// Following functions are for dgmod. If there is documentation for them, it is
// likely to be found in platform/s5is/sub/101b/stubs_entry_2.S.
// Currently these functions ALL point to nullsub_1 (FFC0183C). They are here
// only to get CHDK to compile. Please do not use the functions using these,
// behaviour may be undefined.
NHSTUB(GetISPitchPWM,                   0xFFC0183C)
NHSTUB(GetISYawPWM,                     0xFFC0183C)
NHSTUB(GetISShiftLensPitchPosition,     0xFFC0183C)
NHSTUB(GetISShiftLensYawPosition,       0xFFC0183C)
NHSTUB(SetISPitchPWM,                   0xFFC0183C)
NHSTUB(SetISYawPWM,                     0xFFC0183C)
NHSTUB(MoveISLensToTopLimitPosition,    0xFFC0183C)
NHSTUB(MoveISLensToBottomLimitPosition, 0xFFC0183C)
NHSTUB(MoveISLensToLeftLimitPosition,   0xFFC0183C)
NHSTUB(MoveISLensToRightLimitPosition,  0xFFC0183C)
NHSTUB(MoveISLensToCentralPosition,     0xFFC0183C)

NHSTUB(GetISHallDevicePitchOffset,      0xFFC0183C)
NHSTUB(GetISHallDeviceYawOffset,        0xFFC0183C)
NHSTUB(GetISHallDevicePitchGain,        0xFFC0183C)
NHSTUB(GetISHallDeviceYawGain,          0xFFC0183C)
NHSTUB(GetISGyroPitchOffset,            0xFFC0183C)
NHSTUB(GetISGyroYawOffset,              0xFFC0183C)
NHSTUB(GetISGyroPitchGain,              0xFFC0183C)
NHSTUB(GetISGyroYawGain,                0xFFC0183C)
NHSTUB(GetISLensCenterShiftAaxis,       0xFFC0183C)
NHSTUB(GetISLensCenterShiftBaxis,       0xFFC0183C)
NHSTUB(GetISLensEViAaxis,               0xFFC0183C)
NHSTUB(GetISLensEViBaxis,               0xFFC0183C)
NHSTUB(GetISLensDampAaxis,              0xFFC0183C)
NHSTUB(GetISLensDampBaxis,              0xFFC0183C)

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                 0xFFC0183C)
NHSTUB(GetISDriveBaxis,                 0xFFC0183C)
NHSTUB(GetISPositionAaxis,              0xFFC0183C)
NHSTUB(GetISPositionBaxis,              0xFFC0183C)
NHSTUB(GetISHallOffsetAaxis,            0xFFC0183C)
NHSTUB(GetISHallOffsetBaxis,            0xFFC0183C)
NHSTUB(GetISHallGainAaxis,              0xFFC0183C)
NHSTUB(GetISHallGainBaxis,              0xFFC0183C)
NHSTUB(GetISGyroGainAaxis,              0xFFC0183C)
NHSTUB(GetISGyroGainBaxis,              0xFFC0183C)
NHSTUB(GetISCoefficientP_A,             0xFFC0183C)
NHSTUB(GetISCoefficientP_B,             0xFFC0183C)
NHSTUB(GetISCoefficientI_A,             0xFFC0183C)
NHSTUB(GetISCoefficientI_B,             0xFFC0183C)
NHSTUB(GetISCoefficientD_A,             0xFFC0183C)
NHSTUB(GetISCoefficientD_B,             0xFFC0183C)
NHSTUB(GetISPLFAaxis,                   0xFFC0183C)
NHSTUB(GetISPLFBaxis,                   0xFFC0183C)
NHSTUB(GetISLPFAaxis,                   0xFFC0183C)
NHSTUB(GetISLPFBaxis,                   0xFFC0183C)
NHSTUB(GetISDbgData,                    0xFFC0183C)
NHSTUB(GetISADData,                     0xFFC0183C)
NHSTUB(GetISDampAaxis,                  0xFFC0183C)
NHSTUB(GetISDampBaxis,                  0xFFC0183C)
NHSTUB(GetISEViAaxis,                   0xFFC0183C)
NHSTUB(GetISEViBaxis,                   0xFFC0183C)
NHSTUB(GetISHallOut1Amp,                0xFFC0183C)
NHSTUB(ISActive,                        0xFFC0183C)

NHSTUB(GetWBStruct,                     0xFFC0183C)

NHSTUB(MuteOffPhysicalScreen,           0xFFC0183C)


NHSTUB(PostLEDMessage,                  0xFFC0183C)

NHSTUB(TurnOnDisplay,                   0xFFC0183C)
NHSTUB(TurnOffDisplay,                  0xFFC0183C)
NHSTUB(TurnOnBackLight,                 0xFFC0183C)
NHSTUB(TurnOffBackLight,                0xFFC0183C)
NHSTUB(SwitchOnDisplay,                 0xFFC0183C)
NHSTUB(SwitchOffDisplay,                0xFFC0183C)

NHSTUB(StopContinuousVRAMData,          0xFFC0183C)

NHSTUB(GetShutterReadyStateVar,         0xFFC0183C)

