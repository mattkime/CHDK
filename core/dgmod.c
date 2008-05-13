/* Main code for 'DGmod', DataGhost's CHDK branch
 * 
 * This branch contains some experimental features which may or may not be
 * useful. It also contains some handy developer tools which may aid in
 * debugging and figuring out how a specific camera works/behaves.
 * The purpose of this branch is to aid in development and to determine whether
 * or not functions are useful by community feedback.
 * 
 * As the only camera I (DataGhost) have is a PowerShot S5IS 1.01b, the features
 * found in this branch are targeted mainly at the PowerShot S5IS 1.01b. They
 * are probably easily ported to 1.01a but likely require more work and testing
 * before they work on other cameras. If in doubt, some features have been
 * specifically made unavailable for other cameras than the S5IS, as they may do
 * serious damage to a camera and should be tested by a developer before making
 * them available to the general public.
 *
 * Insert here the standard "no guarantees/warranty whatsoever" text.
 * 
 */

#include "platform.h"
#include "conf.h"
#include "stdlib.h"
#include "keyboard.h"
#include "core.h"
#include "lang.h"
#include "gui.h"
#include "gui_draw.h"
#include "gui_lang.h"
#include "gui_mbox.h"
#include "dgmod.h"


//--- Global variables ----------------------------------------------
int dgconf_br_canlcdlow;
int dgconf_br_canlcdhigh;
int dgconf_br_canevflow;
int dgconf_br_canevfhigh;
int dgconf_br_curlcd;
int dgconf_br_curevf;
Led_control dgconf_lc;

//--- Local global variables ----------------------------------------
static int dg_adjust_is_initial_draw;
static int dg_adjust_is_redraw;
static int dg_adjust_is_warning_continue = 0;
static int dg_adjust_is_limits_override = 0;
static short dg_adjust_is_pitch;
static short dg_adjust_is_yaw;
static short dg_adjust_is_default_pitch = 0;
static short dg_adjust_is_default_yaw = 0;
static short dg_adjust_is_step;
static short dg_adjust_is_pitch_lower_limit;
static short dg_adjust_is_pitch_upper_limit;
static short dg_adjust_is_yaw_lower_limit;
static short dg_adjust_is_yaw_upper_limit;

static int dg_show_is_initial_draw;
static int dg_show_is2_initial_draw;
// FIXME maybe push these into one or several structs for neatness

static Hexviewerdata dg_hv;

static char *dg_game_test_pixbuf;
static char *dg_game_test_trackbuf;
static char *dg_game_test_trackbuf_ahead;
static char *dg_game_test_tmpbuf;
static char *dg_game_test_cambuf;

//--- Function prototypes -------------------------------------------
void dg_init();
void dg_bright_submenu_change(unsigned int item);
void dg_bright_setcurlcd(int arg);
void dg_bright_setcurevf(int arg);

void dg_br_turnondisp(int arg);
void dg_br_turnoffdisp(int arg);
void dg_br_turnonback(int arg);
void dg_br_turnoffback(int arg);

void dg_adjust_is_init();
void dg_adjust_is_kbd_process();
void dg_adjust_is_draw();
void dg_adjust_is_warning_cb(unsigned int btn);

void dg_show_is_init();
void dg_show_is_kbd_process();
void dg_show_is_draw();

void dg_show_is2_init();
void dg_show_is2_kbd_process();
void dg_show_is2_draw();

void dg_orientation_demo_init();
void dg_orientation_demo_kbd_process();
void dg_orientation_demo_draw();

void dg_plm_post(int arg);
void dg_plm_brightness(int arg);

void dg_quick_debugger(int arg);

void dg_disco(int arg);

void dg_hexviewer_init();
void dg_hexviewer_kbd_process();
void dg_hexviewer_draw();

void dg_game_test();

void dg_assert(char *file, long line);


//--- Local function prototypes -------------------------------------
static void dg_bright_load_canon();
static void dg_hexviewer_draw_pixel_buffered(unsigned int offset, color cl);
static void dg_game_test_draw_pixbuf_buffered(unsigned int offset, color cl);
static void dg_game_test_draw_trackbuf_buffered(unsigned int offset, color cl);
static void dg_game_test_draw_trackbuf_ahead_buffered(unsigned int offset, color cl);

//--- Extern function prototypes ------------------------------------
extern short _GetISPitchPWM();
extern short _GetISYawPWM();
extern short _GetISShiftLensPitchPosition();
extern short _GetISShiftLensYawPosition();
extern void _SetISPitchPWM(short *pitch); // Return type unsure, assumed void
extern void _SetISYawPWM(short *yaw); // idem

extern void _MoveISLensToBottomLimitPosition();
extern void _MoveISLensToTopLimitPosition();
extern void _MoveISLensToRightLimitPosition();
extern void _MoveISLensToLeftLimitPosition();
extern void _MoveISLensToCentralPosition();

extern char _GetISHallDevicePitchOffset();
extern char _GetISHallDeviceYawOffset();
extern char _GetISHallDevicePitchGain();
extern char _GetISHallDeviceYawGain();
extern long _GetISGyroPitchOffset();
extern long _GetISGyroYawOffset();
extern char _GetISGyroPitchGain();
extern char _GetISGyroYawGain();
extern long _GetISLensCenterShiftAaxis();
extern long _GetISLensCenterShiftBaxis();
extern short _GetISLensEViAaxis();
extern short _GetISLensEViBaxis();
extern short _GetISLensDampAaxis();
extern short _GetISLensDampBaxis();

extern short _GetISDriveAaxis();
extern short _GetISDriveBaxis();
extern short _GetISPositionAaxis();
extern short _GetISPositionBaxis();
extern char _GetISHallOffsetAaxis();
extern char _GetISHallOffsetBaxis();
extern char _GetISHallGainAaxis();
extern char _GetISHallGainBaxis();
extern char _GetISGyroGainAaxis();
extern char _GetISGyroGainBaxis();
extern short _GetISCoefficientP_A();
extern short _GetISCoefficientP_B();
extern short _GetISCoefficientI_A();
extern short _GetISCoefficientI_B();
extern short _GetISCoefficientD_A();
extern short _GetISCoefficientD_B();
extern short _GetISPLFAaxis();
extern short _GetISPLFBaxis();
extern short _GetISLPFAaxis();
extern short _GetISLPFBaxis();
extern short _GetISDampAaxis();
extern short _GetISDampBaxis();
extern short _GetISEViAaxis();
extern short _GetISEViBaxis();

extern void _PostLEDMessage(Led_control *);

extern void _TurnOnDisplay();
extern void _TurnOffDisplay();
extern void _TurnOnBackLight();
extern void _TurnOffBackLight();
extern void _SwitchOnDisplay();
extern void _SwitchOffDisplay();

extern void _StopContinuousVRAMData();

extern void _CloseMShutter();
extern void _OpenMShutter();


//--- Real stuff ----------------------------------------------------

void dg_init() {
	// Boot-time dgmod initialisation
	
	dg_bright_load_canon();
	
	// Bypass camera's assert function - USE WITH EXTREME CAUTION, CAMERA WILL NOT SHUT DOWN
	// For safety, disabled by default.
	//*((int *) 0x1B14) = (int*)dg_assert;
}

static void dg_bright_load_canon() {
	// Loads Canon preset values from memory
	
	volatile long *lcdpresetaddr = (volatile long *) 0x40BDC; // FIXME S5 only, make it a lib function somewhere
	volatile long *evfpresetaddr = (volatile long *) 0x40BEC; // FIXME idem
	
	dgconf_br_canlcdlow  = (*lcdpresetaddr >> 8) & 0xFF;
	dgconf_br_canlcdhigh = (*lcdpresetaddr >> 24) & 0xFF;
	dgconf_br_canevflow  = (*evfpresetaddr >> 8) & 0xFF;
	dgconf_br_canevfhigh = (*evfpresetaddr >> 24) & 0xFF;
	
}

void dg_bright_submenu_change(unsigned int item) {
	// This function changes the preset LCD/EVF brightness values as settable
	// by Canon firmware. Assumptions: setting format as in S5, camera contains
	// both LCD and EVF which both have adjustable brightness settings.
	
	long mask = 0x00000000;
	volatile long *lcdpresetaddr = (volatile long *) 0x40BDC; // FIXME S5 only, make it a lib function somewhere
	volatile long *evfpresetaddr = (volatile long *) 0x40BEC; // FIXME idem
	
	// First, clean up input values
	if(dgconf_br_canlcdlow  < 0) dgconf_br_canlcdlow  = 0;
	if(dgconf_br_canlcdhigh < 0) dgconf_br_canlcdhigh = 0;
	if(dgconf_br_canevflow  < 0) dgconf_br_canevflow  = 0;
	if(dgconf_br_canevfhigh < 0) dgconf_br_canevfhigh = 0;
	if(dgconf_br_canlcdlow  > 0xFF) dgconf_br_canlcdlow  = 0xFF;
	if(dgconf_br_canlcdhigh > 0xFF) dgconf_br_canlcdhigh = 0xFF;
	if(dgconf_br_canevflow  > 0xFF) dgconf_br_canevflow  = 0xFF;
	if(dgconf_br_canevfhigh > 0xFF) dgconf_br_canevfhigh = 0xFF;

	switch (item) {
		case 0: // Canon LCD brightness
		case 1:
			if(dgconf_br_canlcdlow != 0) 
				mask |= 0x000000FF;
			
			if(dgconf_br_canlcdhigh != 0)
				mask |= 0x00FF0000;
			
			*lcdpresetaddr = mask | ((dgconf_br_canlcdlow & 0xFF) << 8) | ((dgconf_br_canlcdhigh & 0xFF) << 24);
			break;
		
		case 2: // Canon EVF brightness
		case 3:
			if(dgconf_br_canevflow != 0) 
				mask |= 0x000000FF;
			
			if(dgconf_br_canevfhigh != 0)
				mask |= 0x00FF0000;
			
			*evfpresetaddr = mask | ((dgconf_br_canevflow & 0xFF) << 8) | ((dgconf_br_canevfhigh & 0xFF) << 24);
			break;
		
		default:
			break;
	}
}

void dg_bright_setcurlcd(int arg) {
	// Changes the current brightness, does not change if brightness is already
	// set to this value (for some reason, it cannot be changed after setting
	// the already-set value)
	
	short currentvalue;
	short newvalue; 
	volatile short *addr = (volatile short *) 0xC0910080; // FIXME S5 only, make it a lib function somewhere
	
	// Clean up first
	if(dgconf_br_curlcd < 0) dgconf_br_curlcd = 0;
	if(dgconf_br_curlcd > 0xFF) dgconf_br_curlcd = 0xFF;
	
	if(dgconf_br_curlcd != 0) {
		newvalue = ((dgconf_br_curlcd & 0xFF) << 8) | 0xFF;
	} else {
		newvalue = ((dgconf_br_curlcd & 0xFF) << 8);
	}
	
	currentvalue = *addr;
	if(newvalue != currentvalue)
		*addr = newvalue;
	
}

void dg_bright_setcurevf(int arg) {
	// As dg_bright_setcurlcd
	
	short currentvalue;
	short newvalue; 
	volatile short *addr = (volatile short *) 0xC0910004; // FIXME S5 only, make it a lib function somewhere
	
	// Clean up first
	if(dgconf_br_curevf < 0) dgconf_br_curevf = 0;
	if(dgconf_br_curevf > 0xFF) dgconf_br_curevf = 0xFF;
	
	if(dgconf_br_curevf != 0) {
		newvalue = ((dgconf_br_curevf & 0xFF) << 8) | 0xFF;
	} else {
		newvalue = ((dgconf_br_curevf & 0xFF) << 8);
	}
	
	currentvalue = *addr;
	if(newvalue != currentvalue)
		*addr = newvalue;
	
}

void dg_br_turnondisp(int arg) {
	_SwitchOnDisplay(); // Odd, this one doesn't enable the bitmap either but at least it does brightness.
	// _TurnOnDisplay(); // Only does partial (no bitmap or brightness) turn-on when recovering from SwitchOffDisplay
}

void dg_br_turnoffdisp(int arg) {
	_SwitchOffDisplay();
	// _TurnOffDisplay(); // Crashes camera, doesn't seem to want arguments. Maybe in a pointer somewhere. Called from SwitchOffDisplay.
}

void dg_br_turnonback(int arg) {
	_TurnOnBackLight();
}

void dg_br_turnoffback(int arg) {
	_TurnOffBackLight();
}

void dg_quick_debugger(int arg) {
	// Use this to execute any code quickly, without the hassle of creating a new menu entry
	
	// Abuse a 4-int struct (that's what _GetWBStruct wants) and copy it into
	// the debug_vals.
	Led_control meh;
	_GetWBStruct(meh);
	*((long *)0x1850) = meh.led_num;
	*((long *)0x1854) = meh.action;
	*((long *)0x1858) = meh.brightness;
	*((long *)0x185C) = meh.blink_count;
	
}


void dg_disco(int arg) {
	// Does a fancy disco, blinking and fading all leds and both displays
	
	Led_control led_control;
	int i, j;
	
	volatile long *brightcontrlcd = (volatile long *) 0xC0910080; // S5-specific
	volatile long *brightcontrevf = (volatile long *) 0xC0910004; // S5-specific
	volatile long *brightcontr;
	volatile long *brightcontr2;
	long bright;
	long value;
	
	// Determine which display is active and fetch the value
	if(*brightcontrlcd == 0) { // LCD disabled
		brightcontr = brightcontrevf;
		brightcontr2 = brightcontrlcd;
	} else {
		brightcontr = brightcontrlcd;
		brightcontr2 = brightcontrevf;
	}
	
	value = *brightcontr;
	
	
	// Setup basic brightness and post messages to the LEDs
	led_control.brightness = 200;
	
	led_control.led_num = 8;
	led_control.action = 2;
	led_control.blink_count = 20;
	_PostLEDMessage(&led_control);
	msleep(20);
	
	led_control.led_num = 7;
	led_control.action = 4;
	led_control.blink_count = 35;
	_PostLEDMessage(&led_control);
	msleep(20);
	
	led_control.led_num = 4;
	led_control.action = 3;
	led_control.blink_count = 60;
	_PostLEDMessage(&led_control);
	msleep(20);
	
	led_control.led_num = 5;
	led_control.action = 4;
	led_control.blink_count = 35;
	_PostLEDMessage(&led_control);
	msleep(20);
	
	// Setup for the next step, PWM LEDs and LCDs. Turn then on, vary brightness
	led_control.action = 0;
	led_control.blink_count = 1;
	
	// Do this a couple of times
	for(i=1;i<13;i++) {
		// Normal behaviour: fade LED's left/right and fade the *active* LCD
		if(i & 0x3) {
			
			for(bright=70;bright>0;bright-=2) {
				// AF LED
				led_control.led_num = 9;
				led_control.brightness = 210 - 3*bright;
				_PostLEDMessage(&led_control);
				
				// Tally LED
				led_control.led_num=10;
				led_control.brightness = bright+30;
				_PostLEDMessage(&led_control);
				
				// Fade LCD
				value = 0x50FF + 0x100 * (int) (2.5 * bright);
				*brightcontr = value;
				
				// We're not really in a hurry and we should give the OS time, too
				msleep(5);
			}
			
			// This loop as above, the other way around
			for(bright=0;bright<70;bright+=2) {
				led_control.led_num = 9;
				led_control.brightness = 210 - 3*bright;
				_PostLEDMessage(&led_control);
				
				led_control.led_num=10;
				led_control.brightness = bright+30;
				_PostLEDMessage(&led_control);
				
				value = 0x50FF + 0x100 * (int) (2.5 * bright);
				*brightcontr = value;
				
				msleep(5);
			}
		} else { // But every four iterations, blink the LEDs and LCDs
			// Blink AF LED quickly, 10 times
			led_control.led_num = 9;
			led_control.brightness = 200;
			led_control.action = 3;
			led_control.blink_count = 10;
			_PostLEDMessage(&led_control);
			
			// Wait a bit so the LEDs interleave a bit
			msleep(300);
			
			// Blink the Tally LED quickly, 10 times
			led_control.led_num = 10;
			led_control.brightness = 100;
			_PostLEDMessage(&led_control);
			
			// Crank up the active LCD brightness
			value = 0xFFFF;
			*brightcontr = value;
				
			// Make something which takes 1 second and blinks the LCDs
			int lcd;
			for(lcd=0;lcd<10;lcd++) {
				*brightcontr = 0x50FF;
				*brightcontr2 = 0xFFFF;
				msleep(50);
				*brightcontr = 0xFFFF;
				*brightcontr2 = 0x0000;
				msleep(50);
			}
			
			// Prepare for the normal actions again
			led_control.action = 0;
			led_control.blink_count = 1;
		}
	}
	
	// Shut up the AF and Tally LEDs and we're done :)
	led_control.led_num = 9;
	led_control.action = 1;
	led_control.brightness = 0;
	_PostLEDMessage(&led_control);
	
	led_control.led_num=10;
	_PostLEDMessage(&led_control);
}



//--- IS adjustments ------------------------------------------------

// GetISPitchPWM() / GetISYawPWM():
//    Current PWM (= try-to-keep-at) value of the IS lens pitch/yaw thing
//
// SetISPitchPWM(short *pitch) / SetISYawPWM(short *yaw):
//    Sets new PWM values, cleared on camera reboot
//
// GetISShiftLensPitchPosition() / GetISShiftLensYawPosition():
//    Current readout of the sensor position, influenced by camera movement and
//    IS itself, of course.

void dg_adjust_is_init() {
	dg_adjust_is_initial_draw = 1;
	dg_adjust_is_redraw = 1;
	dg_adjust_is_limits_override = 0;
	dg_adjust_is_step = 1;

	// Determine defaults if zero (= no defaults have been determined yet)
	if(dg_adjust_is_default_pitch == 0 && dg_adjust_is_default_yaw == 0) {
		dg_adjust_is_default_pitch = _GetISPitchPWM();
		dg_adjust_is_default_yaw = _GetISYawPWM();
	}
	
	dg_adjust_is_pitch = _GetISPitchPWM();
	dg_adjust_is_yaw = _GetISYawPWM();
}

void dg_adjust_is_kbd_process() {
	int changed = 0;
	switch(kbd_get_autoclicked_key()) {
		case KEY_UP:
			dg_adjust_is_pitch -= dg_adjust_is_step;
			changed = 1;
			break;
		case KEY_DOWN:
			dg_adjust_is_pitch += dg_adjust_is_step;
			changed = 1;
			break;
		case KEY_LEFT:
			dg_adjust_is_yaw -= dg_adjust_is_step;
			changed = 1;
			break;
		case KEY_RIGHT:
			dg_adjust_is_yaw += dg_adjust_is_step;
			changed = 1;
			break;
		case KEY_ZOOM_OUT:
			dg_adjust_is_step *= 10;
			if(dg_adjust_is_step > 100) dg_adjust_is_step = 100;
			break;
		case KEY_ZOOM_IN:
			dg_adjust_is_step /= 10;
			if(dg_adjust_is_step < 1) dg_adjust_is_step = 1;
			break;
		case KEY_SET:
			dg_adjust_is_pitch = dg_adjust_is_default_pitch;
			dg_adjust_is_yaw = dg_adjust_is_default_yaw;
			dg_adjust_is_limits_override = 0;
			dg_adjust_is_redraw = 1;
			changed = 1;
			break;
		case KEY_ERASE: // FUNC on S5
			if(dg_adjust_is_limits_override == 0) {
				dg_adjust_is_limits_override = 1;
			} else {
				dg_adjust_is_limits_override = 0;
			}
			dg_adjust_is_redraw = 1;
			changed = 1;
			break;
	}
	
	// Fix limits, only makes sense if something was actually changed
	if(changed == 1 && dg_adjust_is_limits_override == 0) {
		if(dg_adjust_is_pitch < dg_adjust_is_pitch_lower_limit) {
			dg_adjust_is_pitch = dg_adjust_is_pitch_lower_limit;
		} else if(dg_adjust_is_pitch > dg_adjust_is_pitch_upper_limit) {
			dg_adjust_is_pitch = dg_adjust_is_pitch_upper_limit;
		}
		
		if(dg_adjust_is_yaw < dg_adjust_is_yaw_lower_limit) {
			dg_adjust_is_yaw = dg_adjust_is_yaw_lower_limit;
		} else if(dg_adjust_is_yaw > dg_adjust_is_yaw_upper_limit) {
			dg_adjust_is_yaw = dg_adjust_is_yaw_upper_limit;
		}
	}
	
	// And only set when something was changed.
	if(changed == 1) {
		_SetISPitchPWM(&dg_adjust_is_pitch);
		_SetISYawPWM(&dg_adjust_is_yaw);
	}
}


void dg_adjust_is_draw() {
	// Draws some basic IS settings related to the position of the IS lens and
	// the settings changed in this routine's keyboard handler (above).
	
	char buf[64];
	
	if(dg_adjust_is_initial_draw == 1) {
		gui_mbox_init(LANG_DG_IS_ADJUST_TITLE, LANG_DG_IS_ADJUST_WARN,
		              MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE|MBOX_BTN_YES_NO|MBOX_DEF_BTN1, dg_adjust_is_warning_cb);
		dg_adjust_is_initial_draw = 2;
		
	} else if(dg_adjust_is_initial_draw == 2) {
		if(dg_adjust_is_warning_continue == 0) {
			draw_restore();
			gui_set_mode(GUI_MODE_MENU);
			return;
		}
		
		// Determine limits by moving the lens and reading the PWM values
		// Bottom limit = lower, top limit = upper (pitch)
		// Right limit = lower, left limit = upper (yaw)
		// Pitch up -> image to the bottom => down is +, up is -
		// Yaw up -> image to the right => left is -, right is +
		_MoveISLensToBottomLimitPosition();
		dg_adjust_is_pitch_lower_limit = _GetISPitchPWM();
		
		_MoveISLensToTopLimitPosition();
		dg_adjust_is_pitch_upper_limit = _GetISPitchPWM();
		
		_MoveISLensToRightLimitPosition();
		dg_adjust_is_yaw_lower_limit = _GetISYawPWM();
		
		_MoveISLensToLeftLimitPosition();
		dg_adjust_is_yaw_upper_limit = _GetISYawPWM();
		
		// Restore previous center position
		if(dg_adjust_is_pitch < dg_adjust_is_pitch_lower_limit ||
		   dg_adjust_is_pitch > dg_adjust_is_pitch_upper_limit ||
		   dg_adjust_is_yaw < dg_adjust_is_yaw_lower_limit ||
		   dg_adjust_is_yaw > dg_adjust_is_yaw_upper_limit) {
			
			// Assertion failed, this should never happen. Only thing I can
			// think of is some idiot setting the lens to an extreme or even
			// beyond and then engaging this feature while shaking the camera.
			// Also, limits override is disabled by default so this is invalid.
			// Trust the camera to restore things and then sneak away.
			_MoveISLensToCentralPosition();
			gui_mbox_init(LANG_DG_IS_ADJUST_TITLE, LANG_DG_IS_ADJUST_ASSERT_CENTRAL,
			              MBOX_TEXT_CENTER|MBOX_FUNC_RESTORE, NULL);
			dg_adjust_is_warning_continue = 0;
			return;
		}
			
		_SetISPitchPWM(&dg_adjust_is_pitch);
		_SetISYawPWM(&dg_adjust_is_yaw);
		
		// Continue with the program
		gui_mbox_init(LANG_DG_IS_ADJUST_TITLE, LANG_DG_IS_ADJUST_INFO,
		              MBOX_TEXT_LEFT|MBOX_FUNC_RESTORE, NULL);
		dg_adjust_is_initial_draw = 0;
				
	} else { // Initialisation done, continue with the real stuff
		if(dg_adjust_is_redraw == 1) {
			draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
			if(dg_adjust_is_limits_override == 1) {
				// Draw the warning if overrides are enabled
				draw_string(0, 4*FONT_HEIGHT, lang_str(LANG_DG_IS_ADJUST_WARNLIMIT1), MAKE_COLOR(COLOR_BG, COLOR_FG));
				draw_string(0, 5*FONT_HEIGHT, lang_str(LANG_DG_IS_ADJUST_WARNLIMIT2), MAKE_COLOR(COLOR_BG, COLOR_FG));
			}
			dg_adjust_is_redraw = 0;
		}
		
		sprintf(buf, lang_str(LANG_DG_IS_ADJUST_PITCH), dg_adjust_is_pitch, _GetISShiftLensPitchPosition());
		draw_string(0, 0, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
		sprintf(buf, lang_str(LANG_DG_IS_ADJUST_YAW), dg_adjust_is_yaw, _GetISShiftLensYawPosition());
		draw_string(0, FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
		sprintf(buf, lang_str(LANG_DG_IS_ADJUST_STEP), dg_adjust_is_step);
		draw_string(0, 2*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	}

}

void dg_adjust_is_warning_cb(unsigned int btn) {
	if (btn==MBOX_BTN_YES) {
		dg_adjust_is_warning_continue = 1;
	} else {
		dg_adjust_is_warning_continue = 0;
	}
}



void dg_show_is_init() {
	dg_show_is_initial_draw = 1;
}

void dg_show_is_kbd_process() {

}

void dg_show_is_draw() {
	// Nothing fancy here, just clear the screen if required (read: called from
	// the menu) and then draw the first found set of GetISWhatever functions.
	
	char buf[64];
	
	if(dg_show_is_initial_draw == 1) {
		draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
		dg_show_is_initial_draw = 0;
	}
	
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_PWM), _GetISPitchPWM(), _GetISYawPWM());
	draw_string(0, 0*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_LENS_POSITION), _GetISShiftLensPitchPosition(), _GetISShiftLensYawPosition());
	draw_string(0, 1*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_HALL_DEV_OFFSET), _GetISHallDevicePitchOffset(), _GetISHallDeviceYawOffset());
	draw_string(0, 2*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_HALL_DEV_GAIN), _GetISHallDevicePitchGain(), _GetISHallDeviceYawGain());
	draw_string(0, 3*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_GYRO_OFFSET), _GetISGyroPitchOffset(), _GetISGyroYawOffset());
	draw_string(0, 4*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_GYRO_GAIN), _GetISGyroPitchGain(), _GetISGyroYawGain());
	draw_string(0, 5*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_LENS_CENTER_AXIS), _GetISLensCenterShiftAaxis(), _GetISLensCenterShiftBaxis());
	draw_string(0, 6*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_LENS_DAMP_AXIS), _GetISLensDampAaxis(), _GetISLensDampBaxis());
	draw_string(0, 7*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW_LENS_EVI_AXIS), _GetISLensEViAaxis()-4096, _GetISLensEViBaxis()+4096);
	draw_string(0, 8*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));

}

void dg_show_is2_init() {
	dg_show_is2_initial_draw = 1;
}

void dg_show_is2_kbd_process() {

}

void dg_show_is2_draw() {
	// Nothing fancy here, just clear the screen if required (read: called from
	// the menu) and then draw the second set of GetISWhatever functions.
	
	char buf[64];
	int i = 0;
	
	if(dg_show_is2_initial_draw == 1) {
		draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
		dg_show_is2_initial_draw = 0;
	}
	
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_DRIVE), _GetISDriveAaxis(), _GetISDriveBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_POS), _GetISPositionAaxis(), _GetISPositionBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_HALL_POS), _GetISHallOffsetAaxis(), _GetISHallOffsetBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_HALL_GAIN), _GetISHallGainAaxis(), _GetISHallGainBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_GYRO_GAIN), _GetISGyroGainAaxis(), _GetISGyroGainBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_COEFF_P), _GetISCoefficientP_A(), _GetISCoefficientP_B());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_COEFF_I), _GetISCoefficientI_A(), _GetISCoefficientI_B());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_COEFF_D), _GetISCoefficientD_A(), _GetISCoefficientD_B());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_PLF), _GetISPLFAaxis(), _GetISPLFBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_LPF), _GetISLPFAaxis(), _GetISLPFBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_DAMP), _GetISDampAaxis(), _GetISDampBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	sprintf(buf, lang_str(LANG_DG_IS_SHOW2_EVI), _GetISEViAaxis(), _GetISEViBaxis());
	draw_string(0, (i++)*FONT_HEIGHT, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	
	
}


void dg_orientation_demo_init() {
	
}

void dg_orientation_demo_kbd_process() {

}

void dg_orientation_demo_draw() {
	/*
	Quick inline documentation
	
	- EViAaxis seems to act as fixpt sin(camera_angle) +4000 (4096?) also seems
	    to register camera up/down angle
	- EViBaxis seems to act as fixpt cos(camera_angle) -4000 (4096?)

	Both are more or less usable as 'angle' by applying the correct offset and
	shifting 7 bits to the right.
	
	*/
	
	char buf[64];
	static int inc, val;
	int x, y, x2, y2;
	
	x = ((_GetISLensEViAaxis()-4096) >> 7) + 180;
	y = 120 - ((_GetISLensEViBaxis()+4096) >> 7);
	
	x2 = 180 - ((_GetISLensEViAaxis()-4096) >> 7);
	y2 = ((_GetISLensEViBaxis()+4096) >> 7) + 120;
	
	draw_filled_rect(0, 0, screen_width-1, screen_height-1, MAKE_COLOR(COLOR_TRANSPARENT, COLOR_TRANSPARENT));
	draw_line(x2, y2-1, x, y-1, 0xFF);
	draw_line(x2, y2, x, y, 0x22);
	draw_line(x2+1, y2, x+1, y, 0x11);
	draw_line(x-4, y-4, x+4, y+4, 0x22);
	draw_line(x-4, y+4, x+4, y-4, 0x22);
	draw_line(x2-4, y2-4, x2+4, y2+4, 0xDD);
	draw_line(x2-4, y2+4, x2+4, y2-4, 0xDD);
	
	if(y < 100 && y > 90) {
		inc = 1;
	} else if(y <= 90 && y > 80) {
		inc = 2;
	} else if(y <= 80 && y > 70) {
		inc = 4;
	} else if(y <= 70) {
		inc = 8;
	}
	
	if(y >= 100 && y <= 140) {
		inc = 0;
	}
	
	if(y > 140 && y < 150) {
		inc = -1;
	} else if(y >= 150 && y < 160) {
		inc = -2;
	} else if(y >= 160 && y < 170) {
		inc = -4;
	} else if(y >= 170) {
		inc = -8;
	}
	
	val += inc;
	sprintf(buf, "%2d %d", inc, val);
	draw_string(0, 0, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
	
}



//--- Post LED msg --------------------------------------------------

void dg_plm_brightness(int arg) {
	if(dgconf_lc.brightness > 255) dgconf_lc.brightness = 255;
}

void dg_plm_post(int arg) {
	_PostLEDMessage(&dgconf_lc);
}



//--- Hex viewer ----------------------------------------------------
void dg_hexviewer_init() {
	dg_hv.addr = (volatile long *)0x0007DB28;
	dg_hv.sel_addr = (volatile long *)0x0007DB38;
	dg_hv.sel_type = DG_HV_SELTYPE_DWORD;
}

void dg_hexviewer_kbd_process() {
	
}

void dg_hexviewer_draw() {
	// Should be an advanced hex viewer. Work in progress, expect more later
	
	long x, y, i;
	volatile char *p;
	char txtbuf[30];
	char bgcolor;
	
	
	if (!dg_hv.pixbuf) {
		dg_hv.pixbuf = malloc(screen_buffer_size);
		dg_hv.cambuf = vid_get_bitmap_fb();
	}
	
	if(dg_hv.pixbuf) {
		// First clear our buffer to draw on and enable buffered drawing
		memset(dg_hv.pixbuf, COLOR_TRANSPARENT, screen_buffer_size);
		draw_set_draw_proc(dg_hexviewer_draw_pixel_buffered);
		
		// Do stuff here
		p = (volatile char *) dg_hv.addr;
		for(y=1;y<13;y++) {
			// Draw the address
			sprintf(txtbuf, "%08X", p);
			draw_string(0, y*FONT_HEIGHT, txtbuf, MAKE_COLOR(COLOR_BG, COLOR_FG));
			x = 9 * FONT_WIDTH;
			
			// Draw 8 bytes
			for(i=0;i<8;i++) {
				// Determine the background color based on the current selection address and length
				if(dg_hv.sel_type == DG_HV_SELTYPE_NONE) {
					if(p == (volatile char*) dg_hv.sel_addr) {
						bgcolor = COLOR_BLUE;
					} else {
						bgcolor = COLOR_BG;
					}
				} else {
					if(p >= (volatile char*) dg_hv.sel_addr && p < (volatile char*) dg_hv.sel_addr + dg_hv.sel_type) {
						bgcolor = COLOR_RED;
					} else {
						bgcolor = COLOR_BG;
					}
				}
				
				// Draw one byte in hex
				sprintf(txtbuf, "%02X", *p);
				draw_string(x, y*FONT_HEIGHT, txtbuf, MAKE_COLOR(bgcolor, COLOR_FG));
				if(i == 3) {
					x += 2*FONT_WIDTH + FONT_WIDTH;
				} else {
					x += 2*FONT_WIDTH + FONT_WIDTH/2;
				}
				
				// Represent it in ASCII, ignore control chars (0-32)
				if(*p > 32) {
					draw_char(30*FONT_WIDTH+i*FONT_WIDTH, y*FONT_HEIGHT, *p, MAKE_COLOR(bgcolor, COLOR_FG));
				} else {
					draw_char(30*FONT_WIDTH+i*FONT_WIDTH, y*FONT_HEIGHT, '.', MAKE_COLOR(bgcolor, COLOR_FG));
				}
				
				// Increment the pointer and continue
				p++;
			}
		}
		
		// Copy our buffer to the camera and restore drawing
		draw_set_draw_proc(NULL);
		memcpy(dg_hv.cambuf, dg_hv.pixbuf, screen_buffer_size);
		memcpy(dg_hv.cambuf+screen_buffer_size, dg_hv.pixbuf, screen_buffer_size);
	}
}

static void dg_hexviewer_draw_pixel_buffered(unsigned int offset, color cl) {
    dg_hv.pixbuf[offset] = cl;
}



//--- Game test -----------------------------------------------------

void dg_game_test() {
	// This function is supposed to take over control from the CHDK drawing
	// thread, not releasing it until the game is finished (press 'MENU').
	// Use msleep(1) to pass control back to the OS to prevent watchdog from
	// being a bitch, try to crank out as many frames per sec as possible.
	
	/* Game ideas:
	  - Steering by tilting the camera left/right (+ dead zone)
	  - Accel/decel with zoom rocker
	      F out = e-brake -> draw skidmarks, steering impossible. Possibly make the car spin if already in a curve (later version)
	        out = brake
	      neutr = slow decel (no accel)
	         in = keep speed
	       F in = accel
	  - Randomize to determine curves
	    - draw fast curves in several steps, all straight lines. Make it look like an S-curve
	  - Draw 'visible', edges white + black (extra pix)
	  - Draw middle road lines
	  - Collision detection using display buffer *before* drawing the car
	
	Current implementation:
	  Everything in "Game ideas", except:
	  - Zoom rocker accel/decel. Currently zoom_out is brake, zoom_in is accel.
	  - The S-curve thing. I decided to go with much simpler curves
	  - No middle road lines
	  - No collision detection whatsoever. Be careful when implementing, the
	    car could move *through* the track boundary without touching it.
	
	Game seems to run smoothly, further optimization may be possible but is not
	necessary.
	*/
	
	int cnt = 0;
	char buf[64];
	
	int steering_wheel;
	int car_speed, car_pos;
	int track_last_left, track_last_right, track_last_y;
	int track_new_left, track_new_y;
	int temp1, temp2, temp3;
	int track_width = 120;
	
	// If wanted, the shutter could be closed. Not necessary anymore, because
	// lines are drawn in black and white, ensuring visibility on any background
	//_CloseMShutter();
	
	// Setup buffered drawing and clear the main screen
	if (!dg_game_test_pixbuf) {
		dg_game_test_pixbuf = malloc(screen_buffer_size);
		dg_game_test_trackbuf = malloc(screen_buffer_size);
		dg_game_test_trackbuf_ahead = malloc(screen_buffer_size);
		dg_game_test_tmpbuf = malloc(screen_buffer_size);
		dg_game_test_cambuf = vid_get_bitmap_fb();
	}
	
	// Silently fail if we couldn't malloc
	if(!dg_game_test_pixbuf || !dg_game_test_trackbuf || !dg_game_test_trackbuf_ahead || !dg_game_test_tmpbuf) {
		return;
	}
	
	// Draw the basic track in the buffer
	memset(dg_game_test_trackbuf, COLOR_TRANSPARENT, screen_buffer_size);
	memset(dg_game_test_trackbuf_ahead, COLOR_TRANSPARENT, screen_buffer_size);
	draw_set_draw_proc(dg_game_test_draw_trackbuf_buffered);
	draw_line(180-(track_width/2), 0, 180-(track_width/2), 239, 0x11);
	draw_line(180+(track_width/2), 0, 180+(track_width/2), 239, 0x11);
	draw_line(180-(track_width/2)-1, 0, 180-(track_width/2)-1, 239, 0xFF);
	draw_line(180+(track_width/2)+1, 0, 180+(track_width/2)+1, 239, 0xFF);
	draw_set_draw_proc(dg_game_test_draw_pixbuf_buffered);
	
	// Initialize the game settings
	car_speed = 0; // pixels per frame
	car_pos = 180; // center of the car, pixels
	track_last_left = 180-(track_width/2);
	track_last_right = 180+(track_width/2);
	track_last_y = 239;
	srand(get_tick_count());
	
	
	while(1) {
		// Quick test
		//cnt++;
		//sprintf(buf, "%d", cnt);
		//draw_string(0, 0, buf, MAKE_COLOR(COLOR_BG, COLOR_FG));
		//dg_orientation_demo_draw();
		
		//sprintf(buf, "4:%8x  ", *((long *)0x1964)); // DG
		//draw_txt_string(28, 13, buf, conf.osd_color);
		
		// End quick test
		
		
		// Handle keys
		if(kbd_is_key_pressed(KEY_ZOOM_IN)) {
			car_speed++;
			if(car_speed > 20) {
				car_speed = 20;
			}
		}
		if(kbd_is_key_pressed(KEY_ZOOM_OUT)) {
			car_speed--;
			if(car_speed < 0) {
				car_speed = 0;
			}
		}
		
		// Terminate if MENU is pressed
		if(kbd_is_key_pressed(KEY_MENU)) {
			break;
		}
		
		// Process steering wheel, use range -60..60 and exclude -15..15
		// The steering wheel seems to behave like an actual angle now until about 45 deg :)
		steering_wheel = ((_GetISLensEViBaxis()+4096) >> 7);
		
		if(steering_wheel < -10 || steering_wheel > 10) {
			// Deadzone OK, figure out the 'angle' (crude approximation)
			if(steering_wheel >= -25 && steering_wheel < -10) {
				car_pos -= 1;
			} else if(steering_wheel >= -35 && steering_wheel < -25) {
				car_pos -= 2;
			} else if(steering_wheel >= -45 && steering_wheel < -35) {
				car_pos -= 4;
			} else if(steering_wheel >= -60 && steering_wheel < -45) {
				car_pos -= 8;
			} else if(steering_wheel < -60) {
				car_pos -= 16;
			} else if(steering_wheel > 10 && steering_wheel <= 25) {
				car_pos += 1;
			} else if(steering_wheel > 25 && steering_wheel <= 35) {
				car_pos += 2;
			} else if(steering_wheel > 35 && steering_wheel <= 45) {
				car_pos += 4;
			} else if(steering_wheel > 45 && steering_wheel <= 60) {
				car_pos += 8;
			} else if(steering_wheel > 60) {
				car_pos += 16;
			}
		}
		
		// Fix car bounds
		if(car_pos < 8) car_pos = 8;
		if(car_pos > 350) car_pos = 350;
		
		// Draw track
		//   Fill the track_ahead buffer with at least enough data for the
		//   current-set shift or for the current decision
		while(239 - track_last_y < car_speed) {
			// Decide on a piece of road
			// Generate a random number between 1 and 30 for the track offset
			//   and verify the new offset still results in a drawable track
			// Generate another random number for the length of this particular
			//   piece, at least higher than the offset, so the angle is never
			//   more than 45 deg.
			// Oh yes, and generate a third one to determine the new track
			//   direction (left/right)
			temp1 = (rand()%30)+1;
			temp2 = (rand()%30)+temp1;
			temp3 = (rand()%2);
			
			if(temp3 == 1) {
				track_new_left = track_last_left + temp1;
			} else {
				track_new_left = track_last_left - temp1;
			}
			track_new_y = track_last_y - temp2;
			
			if(track_new_left < 1) track_new_left = 1;
			if(track_new_left > 358-track_width) track_new_left = 358-track_width;
			
			
			// Draw it
			draw_set_draw_proc(dg_game_test_draw_trackbuf_ahead_buffered);
			draw_line(track_last_left, track_last_y, track_new_left, track_new_y, 0x11);
			draw_line(track_last_left-1, track_last_y, track_new_left-1, track_new_y, 0xFF);
			draw_line(track_last_right, track_last_y, track_new_left+track_width, track_new_y, 0x11);
			draw_line(track_last_right+1, track_last_y, track_new_left+track_width+1, track_new_y, 0xFF);
			
			// Change variables accordingly
			track_last_left = track_new_left;
			track_last_right = track_new_left + track_width;
			track_last_y = track_new_y;
		}
		
		
		if(car_speed > 0) {
			//   Move the upper part of the track down by car_speed pixels (lines)
			//   A line is screen_buffer_width bytes
			memcpy(dg_game_test_tmpbuf,
			       dg_game_test_trackbuf,
			       screen_buffer_size - car_speed*screen_buffer_width);
			
			memcpy(dg_game_test_trackbuf + car_speed*screen_buffer_width,
			       dg_game_test_tmpbuf,
			       screen_buffer_size - car_speed*screen_buffer_width);
			
			//   Copy the remaining part from the ahead buffer
			memcpy(dg_game_test_trackbuf,
			       dg_game_test_trackbuf_ahead + screen_buffer_size - car_speed*screen_buffer_width,
			       car_speed*screen_buffer_width);
			
			//   ...and move it down as well, fill the empty part with
			//   COLOR_TRANSPARENT and update the variables
			memcpy(dg_game_test_tmpbuf,
			       dg_game_test_trackbuf_ahead,
			       screen_buffer_size - car_speed*screen_buffer_width);
			
			memcpy(dg_game_test_trackbuf_ahead + car_speed*screen_buffer_width,
			       dg_game_test_tmpbuf,
			       screen_buffer_size - car_speed*screen_buffer_width);
			
			memset(dg_game_test_trackbuf_ahead, COLOR_TRANSPARENT, car_speed*screen_buffer_width);
			
			track_last_y += car_speed;
			
			// Detect collision
			// Not implemented yet
			
		}
		
		// Draw car
		//   Copy trackbuf to pixbuf
		//   Draw car in pixbuf
		memcpy(dg_game_test_pixbuf, dg_game_test_trackbuf, screen_buffer_size);
		draw_set_draw_proc(dg_game_test_draw_pixbuf_buffered);
		draw_rect(car_pos-7, 210, car_pos+7, 230, 0x11);
		draw_rect(car_pos-6, 211, car_pos+6, 229, 0xFF);
		
		// Copy buffer
		memcpy(dg_game_test_cambuf, dg_game_test_pixbuf, screen_buffer_size);
		memcpy(dg_game_test_cambuf+screen_buffer_size, dg_game_test_pixbuf, screen_buffer_size);
		
		// Sleep to avoid watchdog crap
		msleep(1);
	}
	
	// Restore drawing to normal
	draw_set_draw_proc(NULL);
	
	// Clean up buffers?
	//   trackbuf
	//   pixbuf
	
	// If the shutter was closed, we should open it after terminating the game
	//_OpenMShutter();
	
}

static void dg_game_test_draw_pixbuf_buffered(unsigned int offset, color cl) {
    dg_game_test_pixbuf[offset] = cl;
}

static void dg_game_test_draw_trackbuf_buffered(unsigned int offset, color cl) {
    dg_game_test_trackbuf[offset] = cl;
}

static void dg_game_test_draw_trackbuf_ahead_buffered(unsigned int offset, color cl) {
    dg_game_test_trackbuf_ahead[offset] = cl;
}


//--- Assert bypass -------------------------------------------------

void dg_assert(char *file, long line) {
	// Assertion handler, prints file name and line number
	// The original handler (set in memory) suggests that a lot of extra
	// information could be available, will be investigated.
	
	char buf[64];
	
	// This is a good place to do some debugging, your assertion is probably
	// still invalid so it should be possible to find the cause in here.
	
	// Print the actual message
	sprintf(buf, "ASSERTION FAILED:");
	draw_txt_string(0, 10, buf, conf.osd_color);
	sprintf(buf, "File: %s", file);
	draw_txt_string(0, 11, buf, conf.osd_color);
	sprintf(buf, "Line: 0x%X (%d)", line, line);
	draw_txt_string(0, 12, buf, conf.osd_color);
	
	// Assertion probably failed for a good reason, make sure the rest of the
	// code isn't executed. Remove this code and your camera will teleport into
	// an alternate dimension.
	while(1) {
		msleep(100);
	}
}



