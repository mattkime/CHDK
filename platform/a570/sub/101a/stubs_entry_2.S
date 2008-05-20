#include "stubs_asm.h"

NHSTUB(Close,0xFFE46BCC)
NHSTUB(Read,0xFFE46C60) 
NHSTUB(Remove,0xFFE46BEC)
NHSTUB(Write,0xFFE46C6C)
NHSTUB(DisplayImagePhysicalScreen ,0xFFDDBF60) 
NHSTUB(free,0xFFCD9B84) 
NHSTUB(kbd_read_keys_r2  ,0xFFDE7564) 
NHSTUB(Mount_FileSystem ,0xFFE45EF0) 
NHSTUB(kbd_pwr_off, 0xFFDE7C48)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFD670E8)
NHSTUB(SetPropertyCase,0xFFC0BB5C)
NHSTUB(GetDrive_ClusterSize, 0xFFE463B8)
NHSTUB(GetDrive_TotalClusters, 0xFFE463F4)
NHSTUB(GetDrive_FreeClusters, 0xFFE46430)
NHSTUB(WriteSDCard, 0xFFE58F60)


///////////
// Following functions are for dgmod. If there is documentation for them, it is
// likely to be found in platform/s5is/sub/101b/stubs_entry_2.S.
NHSTUB(GetISPitchPWM,                             0xFFE0F1BC)
NHSTUB(GetISYawPWM,                               0xFFE0F1D0)
NHSTUB(GetISShiftLensPitchPosition,               0xFFE0F1E4)
NHSTUB(GetISShiftLensYawPosition,                 0xFFE0F1F8)
NHSTUB(SetISPitchPWM,                             0xFFE0EF58)
NHSTUB(SetISYawPWM,                               0xFFE0EF68)
NHSTUB(MoveISLensToTopLimitPosition,              0xFFE0EE4C)
NHSTUB(MoveISLensToBottomLimitPosition,           0xFFE0EE3C)
NHSTUB(MoveISLensToLeftLimitPosition,             0xFFE0EE2C)
NHSTUB(MoveISLensToRightLimitPosition,            0xFFE0EE1C)
NHSTUB(MoveISLensToCentralPosition,               0xFFE0F090)

NHSTUB(GetISHallDevicePitchOffset,                0xFFE0F15C)
NHSTUB(GetISHallDeviceYawOffset,                  0xFFE0F16C)
NHSTUB(GetISHallDevicePitchGain,                  0xFFE0F17C)
NHSTUB(GetISHallDeviceYawGain,                    0xFFE0F18C)
NHSTUB(GetISGyroPitchOffset,                      0xFFE0EDD4)
NHSTUB(GetISGyroYawOffset,                        0xFFE0EDCC)
NHSTUB(GetISGyroPitchGain,                        0xFFE0F19C)
NHSTUB(GetISGyroYawGain,                          0xFFE0F1AC)
NHSTUB(GetISLensCenterShiftAaxis,                 0xFFE0EDA0)
NHSTUB(GetISLensCenterShiftBaxis,                 0xFFE0EDA8)
NHSTUB(GetISLensEViAaxis,                         0xFFE0F20C)
NHSTUB(GetISLensEViBaxis,                         0xFFE0F220)
NHSTUB(GetISLensDampAaxis,                        0xFFE0F234)
NHSTUB(GetISLensDampBaxis,                        0xFFE0F248)

// Second set of IS lens controls
NHSTUB(GetISDriveAaxis,                           0xFFE8B0C8)
NHSTUB(GetISDriveBaxis,                           0xFFE8B104)
NHSTUB(GetISPositionAaxis,                        0xFFE8B144)
NHSTUB(GetISPositionBaxis,                        0xFFE8B184)
NHSTUB(GetISHallOffsetAaxis,                      0xFFE8B1C8)
NHSTUB(GetISHallOffsetBaxis,                      0xFFE8B20C)
NHSTUB(GetISHallGainAaxis,                        0xFFE8B24C)
NHSTUB(GetISHallGainBaxis,                        0xFFE8B28C)
NHSTUB(GetISGyroGainAaxis,                        0xFFE8B2CC)
NHSTUB(GetISGyroGainBaxis,                        0xFFE8B30C)
NHSTUB(GetISCoefficientP_A,                       0xFFE8B810)
NHSTUB(GetISCoefficientP_B,                       0xFFE8B850)
NHSTUB(GetISCoefficientI_A,                       0xFFE8B890)
NHSTUB(GetISCoefficientI_B,                       0xFFE8B8D0)
NHSTUB(GetISCoefficientD_A,                       0xFFE8B910)
NHSTUB(GetISCoefficientD_B,                       0xFFE8B950)
NHSTUB(GetISPLFAaxis,                             0xFFE8B68C)
NHSTUB(GetISPLFBaxis,                             0xFFE8B6BC)
NHSTUB(GetISLPFAaxis,                             0xFFE8B70C)
NHSTUB(GetISLPFBaxis,                             0xFFE8B73C)
NHSTUB(GetISDbgData,                              0xFFE8B3D8)
NHSTUB(GetISADData,                               0xFFE8B41C)
NHSTUB(GetISDampAaxis,                            0xFFE8B56C)
NHSTUB(GetISDampBaxis,                            0xFFE8B5A4)
NHSTUB(GetISEViAaxis,                             0xFFE8B5DC)
NHSTUB(GetISEViBaxis,                             0xFFE8B614)
NHSTUB(GetISHallOut1Amp,                          0xFFE8B50C)
NHSTUB(ISActive,                                  0xFFC017E4) // nullsub_1

NHSTUB(GetWBStruct,                               0xFFC017E4) // nullsub_1, useless for now

NHSTUB(MuteOffPhysicalScreen,                     0xFFC34DD8)


NHSTUB(PostLEDMessage,                            0xFFDE5890)

NHSTUB(TurnOnDisplay,                             0xFFC34CE8)
NHSTUB(TurnOffDisplay,                            0xFFC34D14)
NHSTUB(TurnOnBackLight,                           0xFFC34D40)
NHSTUB(TurnOffBackLight,                          0xFFC34D70)
NHSTUB(SwitchOnDisplay,                           0xFFE0C28C)
NHSTUB(SwitchOffDisplay,                          0xFFE0C258)

NHSTUB(StopContinuousVRAMData,                    0xFFC017E4) // nullsub_1, useless for now

NHSTUB(GetShutterReadyStateVar,                   0xFFC017E4) // nullsub_1, useless for now



