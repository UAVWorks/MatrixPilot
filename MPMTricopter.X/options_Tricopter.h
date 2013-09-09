// This file is part of the MatrixPilotQuad firmware.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


////////////////////////////////////////////////////////////////////////////////
// options.h
// Bill Premerlani's UAV Dev Board
// 
// This file includes all of the user-configuration for this firmware,
// with the exception of waypoints, which live in the waypoints.h file.
// 
#include "config_Tricopter.h"

////////////////////////////////////////////////////////////////////////////////
// Set Up Board Type
// GREEN_BOARD - Board is green and includes 2 vertical gyro daugter-boards.
// RED_BOARD   - Board is red, and includes 2 vertical gyro daugter-boards.
// UDB3_BOARD  - Board is red, and includes a single, flat, multi-gyro daugter-board.
// See the MatrixPilot wiki for more details on different UDB boards.
// If building for UDB4, use the RollPitchYaw-udb4.mcp project file.
#define BOARD_TYPE 	UDB4_BOARD
#define DUAL_IMU 0

#define AIRFRAME_TYPE AIRFRAME_MULTI

////////////////////////////////////////////////////////////////////////////////
// Select Clock Configuration (Set to CRYSTAL_CLOCK or FRC8X_CLOCK)
// CRYSTAL_CLOCK is the 16 MHz crystal.  This is the speed used in the past, and may be
// more compatible with other add-ons. The CRYSTAL_CLOCK supports a maximum baud rate of 19200 bps.
// FRC8X_CLOCK runs the fast RC clock (7.3728 MHz) with 8X PLL multiplier, and supports much
// faster baud rates.
#define CLOCK_CONFIG 	CRYSTAL_CLOCK

// 18.834 Volts max (in millivolts)
#define MAX_VOLTAGE 18834

// per-cell low voltage warning level
#define LVCELL 3700

////////////////////////////////////////////////////////////////////////////////
// Use board orientation to change the mounting direction of the board.
// The following 4 orientations have the board parallel with the ground.
// ORIENTATION_FORWARDS:  Component-side up,   GPS connector front
// ORIENTATION_BACKWARDS: Component-side up,   GPS connector back
// ORIENTATION_INVERTED:  Component-side down, GPS connector front
// ORIENTATION_FLIPPED:   Component-side down, GPS connector back
// The following 2 orientations are "knife edge" mountings
// ORIENTATION_ROLLCW: Rick's picture #9, board rolled 90 degrees clockwise,
//		from point of view of the pilot
// ORIENTATION_ROLLCW180: Rick's pitcure #11, board rolled 90 degrees clockwise,
//		from point of view of the pilot, then rotate the board 180 around the Z axis of the plane,
//		so that the GPS connector points toward the tail of the plane
// ********** NOTE: orientations are withrespect to the front motor for + configuration,  *******
// or with respect to left front motor, for X configuration
//	rmat is the matrix of direction cosines relating
//	the body and earth coordinate systems.
//	The columns of rmat are the axis vectors of the plane,
//	as measured in the earth reference frame.
//      The UDB4 is installed on the AeroFPV frame with the X axis pointing front-left
//      and the Y axis pointing front-right when in X configuration.
//      The Z axis points downward.
#define BOARD_ORIENTATION   ORIENTATION_FORWARDS

/////////////////////////////////////////////////////////////////////////////
// Specify tricopter, quadcopter, hexacopter, octocopter
#define NUM_ROTORS 3

// Select X flying configuration by uncommenting the following
#define CONFIG_X 0

////////////////////////////////////////////////////////////////////////////////
// Set this value to your GPS type.  (Set to GPS_STD, GPS_UBX_2HZ, or GPS_UBX_4HZ)
#define GPS_TYPE    GPS_NMEA
#define DEFAULT_GPS_BAUD		57600

// Note: As of MatrixPilot 3.0, Dead Reckoning and Wind Estimation are automatically enabled.

// Define MAG_YAW_DRIFT to be 1 to read magnetometer for yaw drift correction.
#define MAG_YAW_DRIFT 	0
// disable MAG drift correction if this is not 1
#define ENABLE_MAG_DRIFT_CORRECTION 0

// if defined, enable magnetometer offset and alignment adjustments
// 17 May: mag offsets grow when sitting still on bench, stopped test at 277,251,458
//#define ENABLE_MAGALIGNMENT
#undef ENABLE_MAGALIGNMENT

// disable GPS yaw drift correction for quad, since GPS heading is independent of yaw
#define GPS_YAW_DRIFT   0

// set this non-zero to use Bill Premerlani's new GPS-based roll_pitch_drift correction
#define NEW_RP_DRIFT  0

// Set this to 1 if you want the UAV Dev Board to fly your plane without a radio transmitter or
// receiver. (Totally autonomous.)  This is just meant for debugging.  It is not recommended that
// you actually use this since there is no automatic landing code yet, and you'd have no manual
// control to fall back on if things go wrong.  It may not even be legal in your area.
#define NORADIO	0


////////////////////////////////////////////////////////////////////////////////
// Enable/Disable core features of this firmware
//
// Roll, Pitch, and Yaw Stabilization
// Set any of these to 0 to disable the stabilization in that axis.
#define ROLL_STABILIZATION_AILERONS			1
#define ROLL_STABILIZATION_RUDDER			0
#define PITCH_STABILIZATION				1
#define YAW_STABILIZATION_RUDDER			1
#define YAW_STABILIZATION_AILERON			1

// Aileron and Rudder Navigation
// Set either of these to 0 to disable use of that control surface for navigation.
#define AILERON_NAVIGATION				1
#define RUDDER_NAVIGATION				1

// Wind Gain Adjustment
// This is an option for modulating the navigation gains in flight
// to maintain a constant turn radius in heavy winds in waypoing mode.
// Define WIND_GAIN_ADJUSTMENT as 1 to turn this feature on.
#define WIND_GAIN_ADJUSTMENT				0

// Altitude Hold
// Use altitude hold in stabilized mode?  In waypoint mode?
// Each of these settings can be AH_NONE, AH_FULL, or AH_PITCH_ONLY
//  - In waypoint mode, the target altitude is defined by the waypoints or logo program.
//  - In stabilized mode, when ALTITUDEHOLD_STABILIZED is set to AH_PITCH_ONLY, the target
// altitude is whatever altitude the plane was at when switched into stabilized mode.
//  - In stabilized mode, when ALTITUDEHOLD_STABILIZED is set to AH_FULL, the target
// altitude is determined by the position of the throttle stick on the transmitter.
// NOTE: even when set to AH_NONE, MatrixPilot will still try to stabilize pitch as int32_t
// as PITCH_STABILIZATION is set to 1 above, but will not aim for any specific altitude.
#define ALTITUDEHOLD_STABILIZED				AH_FULL
#define ALTITUDEHOLD_WAYPOINT				AH_FULL

// Speed Control
// If you define SPEED_CONTROL to be 1, MatrixPilot will take air speed into account
// in the altitude controls, and will trim the throttle and pitch to maintain air speed.
// Define DESIRED_SPEED to be the air speed that you want, in meters/second.
#define SPEED_CONTROL					0
#define DESIRED_SPEED					10.0 // meters/second

// Inverted flight
// Set these to 1 to enable stabilization of inverted flight in stabilized and/or waypoint modes.
#define INVERTED_FLIGHT_STABILIZED_MODE                 0
#define INVERTED_FLIGHT_WAYPOINT_MODE           	0

// Hovering
// Set these to 1 to enable stabilization of hovering in stabilized and/or waypoint modes.
#define HOVERING_STABILIZED_MODE			0
#define HOVERING_WAYPOINT_MODE				0

// Note: As of MatrixPilot 3.0, Dead Reckoning and Wind Estimation are automatically enabled.

// Camera Stabilization
// Set this value to 1, for camera to be stabilized using camera options further below.
#define USE_CAMERA_STABILIZATION			0

// Racing Mode
// Setting RACING_MODE to 1 will keep the plane at a set throttle value while in waypoint mode.
// RACING_MODE_WP_THROTTLE is the throttle value to use, and should be set between 0.0 and 1.0.
// Racing performance can be improved by disabling cross tracking for your waypoints.
#define RACING_MODE					0
#define RACING_MODE_WP_THROTTLE				1.0

////////////////////////////////////////////////////////////////////////////////
// Configure Input and Output Channels

// Use a single PPM input connection from the RC receiver to the UDB on RC input channel 4.
// This frees up RC inputs 3, 2, and 1 to act as RC outputs 4, 5, and 6.
// If you're not sure, leave USE_PPM_INPUT set to 0.
// PPM_NUMBER_OF_CHANNELS is the number of channels sent on the PWM signal.  This is
// often different from the NUM_INPUTS value below, and should usually be left at 8.
// If PPM_ALT_OUTPUT_PINS is set to 0, the 9 available RC outputs will be sent to the
// following pins, in this order: Out1, Out2, Out3, In3, In2, In1, RE0, RE2, RE4.
// With it set to 1, the RC outputs will be in this alternate configuration:
// Out1, Out2, Out3, RE0, RE2, RE4, In3, In2, In1.
#define USE_PPM_INPUT		1
#define PPM_NUMBER_OF_CHANNELS	6
#define PPM_SIGNAL_INVERTED	0
#define PPM_ALT_OUTPUT_PINS	0

// NUM_INPUTS: Set to 0-8
//   1-4 enables only the first 1-4 of the 4 standard input channels
#define NUM_INPUTS	6

// Channel numbers for each input.
// Use as is, or edit to match your setup.
//   - If you're set up to use Rudder Navigation (like MatrixNav), then you may want to swap
//     the aileron and rudder channels so that rudder is CHANNEL_1, and aileron is 5.

//OPTIONS: check input channel mappings in options.h
//#error("input channel mappings not set")
#define THROTTLE_INPUT_CHANNEL                          CHANNEL_3
#define AILERON_INPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_INPUT_CHANNEL				CHANNEL_2
#define RUDDER_INPUT_CHANNEL				CHANNEL_4
#define MODE_SWITCH_INPUT_CHANNEL			CHANNEL_6

#define ROLL_INPUT_CHANNEL	CHANNEL_1
#define PITCH_INPUT_CHANNEL	CHANNEL_2
#define YAW_INPUT_CHANNEL	CHANNEL_4

#define CAMERA_PITCH_INPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_YAW_INPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_MODE_INPUT_CHANNEL			CHANNEL_UNUSED
#define OSD_MODE_SWITCH_INPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_A_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_B_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_C_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_D_INPUT_CHANNEL			CHANNEL_UNUSED


// this needs to be updated
#define NUM_OUTPUTS	8

//OPTIONS: check HARD_TRIMS options.h setting
//#error("HARD_TRIMS option not set")
// make this non-zero if you want the UDB to respect your TX trim settings
#define HARD_TRIMS      0
// set these to the zero-trim values for your RX/TX if you use HARD_TRIMS
#define NEUTRAL_TRIM    3040
#define THROTTLE_IDLE   2250

// Channel numbers for each output
// Use as is, or edit to match your setup.
//   - Only assign each channel to one output purpose
//   - If you don't want to use an output channel, set it to CHANNEL_UNUSED
// 
//OPTIONS: check output channel mappings in options.h
//#error("output channel mappings not set")
#define MOTOR_A_OUTPUT_CHANNEL	CHANNEL_2		// + front or X left front, CCW
#define MOTOR_B_OUTPUT_CHANNEL	CHANNEL_3		// + right or X right front, CW
#define MOTOR_C_OUTPUT_CHANNEL	CHANNEL_1		// + rear or X right rear, CCW
#define MOTOR_D_OUTPUT_CHANNEL	CHANNEL_4		// + left or X left rear,   CW
#define SERVO_TAIL_CHANNEL	CHANNEL_4		// + left or X left rear,   CW


// Channel numbers for each output
// Use as is, or edit to match your setup.
//   - Only assign each channel to one output purpose
//   - If you don't want to use an output channel, set it to CHANNEL_UNUSED
//   - If you're set up to use Rudder Navigation (like MatrixNav), then you may want to swap
//     the aileron and runner channels so that rudder is CHANNEL_1, and aileron is 5.
//
// NOTE: If your board is powered from your ESC through the throttle cable, make sure to
// connect THROTTLE_OUTPUT_CHANNEL to one of the built-in Outputs (1, 2, or 3) to make
// sure your board gets power.
//
#define THROTTLE_OUTPUT_CHANNEL				CHANNEL_1
#define AILERON_OUTPUT_CHANNEL				CHANNEL_2
#define ELEVATOR_OUTPUT_CHANNEL				CHANNEL_3
#define RUDDER_OUTPUT_CHANNEL				CHANNEL_4
#define AILERON_SECONDARY_OUTPUT_CHANNEL	CHANNEL_UNUSED
#define CAMERA_PITCH_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_YAW_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define TRIGGER_OUTPUT_CHANNEL				CHANNEL_UNUSED
#define PASSTHROUGH_A_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_B_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_C_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_D_OUTPUT_CHANNEL		CHANNEL_UNUSED


// change this to -1 for reverse rotation of all motors
#define YAW_SIGN 1

// PWM rate for ESCs
#define ESC_HZ 400
// If set to 1, pwm rate is reduced, useful when output x is a servo while putput y is a fast esc (tricopter case)
#define CHANNEL_1_REDUCED_RATE 0
#define CHANNEL_2_REDUCED_RATE 0
#define CHANNEL_3_REDUCED_RATE 0
#define CHANNEL_4_REDUCED_RATE 1
#define CHANNEL_5_REDUCED_RATE 0
#define CHANNEL_6_REDUCED_RATE 0
// Define how many pwm pulses we have to skip
#define REDUCED_RATE_SKIPS 7
// amount of throttle before fly-by-wire controls engage
#define THROTTLE_DEADBAND 100

// upper limit of throttle
#define THROTTLE_LIMIT  0.90

// SERVOSAT limits servo throw by controlling pulse width saturation.
// set it to 1.0 if you want full servo throw, otherwise set it to the portion that you want
#define SERVOSAT					1.0

////////////////////////////////////////////////////////////////////////////////
// Servo Reversing Configuration
// Here you can choose which reversing switches use hardware switches (only available on classic boards),
// and hard code the rest.
// Note that your servo reversing settings here should match what you set on your transmitter.
// For any of these that evaluate to 1 (either hardcoded or by flipping a switch on the board,
// as you define below), that servo will be sent reversed controls.
#define AILERON_CHANNEL_REVERSED			HW_SWITCH_1
#define ELEVATOR_CHANNEL_REVERSED			HW_SWITCH_2
#define RUDDER_CHANNEL_REVERSED				HW_SWITCH_3
#define AILERON_SECONDARY_CHANNEL_REVERSED              0 // Hardcoded to be unreversed, since we have only 3 switches.
#define THROTTLE_CHANNEL_REVERSED			0 // Set to 1 to hardcode a channel to be reversed
#define CAMERA_PITCH_CHANNEL_REVERSED                   0
#define CAMERA_YAW_CHANNEL_REVERSED			0

// Set this to 1 if you need to switch the left and right elevon or vtail surfaces
#define ELEVON_VTAIL_SURFACES_REVERSED                  0


////////////////////////////////////////////////////////////////////////////////
// The Failsafe Channel is the RX channel that is monitored for loss of signal
// Make sure this is set to a channel you actually have plugged into the UAV Dev Board!
// 
// For a receiver that remembers a failsafe value for when it loses the transmitter signal,
// like the Spektrum AR6100, you can program the receiver's failsafe value to a value below
// the normal low value for that channel.  Then set the FAILSAFE_INPUT_MIN value to a value
// between the receiver's programmed failsafe value and the transmitter's normal lowest
// value for that channel.  This way the firmware can detect the difference between a normal
// signal, and a lost transmitter.
//
// FAILSAFE_INPUT_MIN and _MAX define the range within which we consider the radio on.
// Normal signals should fall within about 2000 - 4000.
//OPTIONS: check failsafe parameters in options.h
//#error("check failsafe parameters")
#define FAILSAFE_INPUT_CHANNEL  THROTTLE_INPUT_CHANNEL
#define FAILSAFE_INPUT_MIN	1980
#define FAILSAFE_INPUT_MAX	4500

// FAILSAFE_TYPE controls the UDB's behavior when in failsafe mode due to loss of transmitter
// signal.  (Set to FAILSAFE_RTL or FAILSAFE_MAIN_FLIGHTPLAN.)
//
// When using FAILSAFE_RTL (Return To Launch), the UDB will begin following the RTL flight plan
// as defined near the bottom of the waypoints.h or flightplan-logo.h files.  By default, this
// is set to return to a point above the location where the UDB was powered up, and to loiter there.
// See the waypoints.h or flightplan-logo.h files for info on modifying this behavior.
//
// When set to FAILSAFE_MAIN_FLIGHTPLAN, the UDB will instead follow the main flight plan as
// defined in either waypoints.h or flightplan-logo.h.  If the UDB was already in waypoint mode
// when it lost signal, the plane will just continue following the main flight plan without
// starting them over.  And if the transmitter is still in waypoint mode when the UDB sees it
// again, the UDB will still continue following the main flight plan without restarting.  If
// the UDB loses signal while not in waypoint mode, it will start the main flight plan from the
// beginning.
#define FAILSAFE_TYPE						FAILSAFE_RTL

// When FAILSAFE_HOLD is set to 1, then once Failsafe has engaged, and you have subsequently
// regained your RC TX-RX connection, you will need to manually change the Mode Switch in order
// to exit Failsafe mode.  This avoids the situation where your plane flies in and out of range,
// and keeps switching into and out of Failsafe mode, which depending on your configuration,
// could be confusing and/or dangerous.
#define FAILSAFE_HOLD						0

//OPTIONS: check ENABLE_GAINADJ and ENABLE_FAILSAFE options.h setting
//#error("check gain adjust/failsafe mux parameters")
// make this non-zero to activate FAILSAFE_MUX_CHANNEL
#define ENABLE__FAILSAFE 0

///////////////////////////
// DON'T change these
#define ROLL_KP_INDEX   0
#define PITCH_KP_INDEX  1
#define RRATE_KP_INDEX  2
#define PRATE_KP_INDEX  3
#define RRATE_KD_INDEX  4
#define PRATE_KD_INDEX  5
#define TILT_KI_INDEX   6
#define YAW_KI_INDEX    7
#define YAW_KP_INDEX    8
#define YAW_KD_INDEX    9
#define ACCEL_K_INDEX   10
#define ACRO_KP_INDEX   11
#define RATE_KI_INDEX   12
///////////////////////////

// Select the gains to be adjusted for mode switch positions 0,1,2
#define ADJ_GAIN_0 ROLL_KP_INDEX
#define ADJ_GAIN_1 PITCH_KP_INDEX
#define ADJ_GAIN_2 YAW_KP_INDEX

// make this non-zero to activate FLIGHT_MODE_CHANNEL and GAIN_CHANNEL for gain adjustment
// Flight mode will be FLIGHT_MODE_TILT, regardless of mode switch position
//FIXME: ??? must cycle UDB4 power when changing ENABLE_GAINADJ from zero to one ???
// otherwise gains stored in eeprom are all zero
#define ENABLE_GAINADJ 0

// make this non-zero to activate FLIGHT_MODE_CHANNEL for flight mode
// If 0, Flight mode will be FLIGHT_MODE_TILT, regardless of mode switch position
#define ENABLE_FLIGHTMODE 1

// flight mode to use if ENABLE_FLIGHTMODE is zero
#define DEFAULT_FLIGHT_MODE TILT_MODE

#if ((ENABLE_GAINADJ != 0) && (ENABLE_FLIGHTMODE != 0))
#error("only one of ENABLE_GAINADJ  and ENABLE_FLIGHTMODE can be selected")
#endif

// use RX channel 5 (gear) for failsafe mux on/off
#define FAILSAFE_MUX_CHANNEL    5
#define FAILSAFE_MUX_THRESH     3000

// use RX channel 6 (flight mode) to select gain for modification
#define MODE_SWITCH_THRESHOLD_LOW   2500
#define MODE_SWITCH_THRESHOLD_HIGH  3500

// map of flight modes to mode switch positions
#define TILT_MODE       0
#define COMPASS_MODE    1
#define POS_MODE        2
#define RATE_MODE       3
#define FLIGHT_MODE_0   TILT_MODE
#define FLIGHT_MODE_1   RATE_MODE
#define FLIGHT_MODE_2   TILT_MODE

#define POS_HOLD_KP 10
#define POS_HOLD_KD 50

// use RX channel 7 as gain inc/dec (connected to UDB input 8)
// there are +/-26 steps on the DX7 hover throttle rocker and 2*790 counts of range for 30 counts/step
// PWM range of channel 7 is 1845 to 4236
#define GAIN_CHANNEL 5
#define GAIN_INC 0.05;
#define GAIN_DELTA 3

////////////////////////////////////////////////////////////////////////////////
// Serial Output Format (Can be SERIAL_NONE, SERIAL_DEBUG, SERIAL_ARDUSTATION, SERIAL_UDB,
// SERIAL_UDB_EXTRA,SERIAL_MAVLINK, SERIAL_CAM_TRACK, or SERIAL_OSD_REMZIBI)
// This determines the format of the output sent out the spare serial port.
// Note that SERIAL_OSD_REMZIBI only works with a ublox GPS.
// SERIAL_UDB_EXTRA will add additional telemetry fields to those of SERIAL_UDB.
// SERIAL_UDB_EXTRA can be used with the OpenLog without characters being dropped.
// SERIAL_UDB_EXTRA may result in dropped characters if used with the XBEE wireless transmitter.
// SERIAL_CAM_TRACK is used to output location data to a 2nd UDB, which will target its camera at this plane.
// SERIAL_MAVLINK is a bi-directional binary format for use with QgroundControl, HKGCS or MAVProxy (Ground Control Stations.)
// SERIAL_MAVLINK is only supported on the UDB4 to ensure that sufficient RAM is available.
// Note that SERIAL_MAVLINK defaults to using a baud rate of 115200 baud (other formats default to 19200)

#define SERIAL_OUTPUT_FORMAT SERIAL_DEBUG

// MAVLink requires an aircraft Identifier (I.D) as it is deaigned to control multiple aircraft
// Each aircraft in the sky will need a unique I.D. in the range from 0-255
#define MAVLINK_SYSID	1

//OPTIONS check telemetry settings
// debug telemetry is the largest set of data, output at TELEMETRY_HZ
// 80Hz is the highest rate allowable at 115.2Kbaud (OpenLog flow control mod may be necessary)
// HEARTRATE_HZ / TELEMETRY_HZ must be an integer

// standard telemetry is type 0 (was DEBUG_TELEMETRY in MatrixPilotQuad rev1174)
// standard parser is parseLogXHz.py, standard analyzer is procLogXaHz.m
// IMU telemetry is type 1, parser parseLogIMU.py, analyzer procLog_drift.m
// IMU/magnetometer is type 2, parser parseLogMag.py, analyzer procLog???
// dead reckoning is type 3, parser parseLogIMU.py, analyzer procGPS_loc.m
// PID is type 4: parser parseLogpid.py, analyzer procLogpid.m
// PID2 with gplane is type 5: parser parseLogpid2.py, analyzer procLogpid2.m
#define TELEMETRY_TYPE  10
#define TELEMETRY_HZ    10
#define TELEMETRY_BAUD  115200

// if non-zero, start telemetry immediately instead of after calibration
#define TEL_ALWAYS_ON   1


//OPTIONS: check ENABLE_RPM_SENSOR options.h setting
//#error("check rpm sensor parameters")
// make this non-zero to read brushless motor rpm sensor on channel input channel 7
#define ENABLE_RPM_SENSOR   0
#define MOTOR_POLES         14
#define COMFREQ_TO_RPM      (60 * 2.0 / MOTOR_POLES)

////////////////////////////////////////////////////////////////////////////////
// Trigger Action
// Use the trigger to do things like drop an item at a certain waypoint, or take a photo every
// N seconds during certain waypoint legs.

// TRIGGER_TYPE can be set to TRIGGER_TYPE_NONE, TRIGGER_TYPE_SERVO, or TRIGGER_TYPE_DIGITAL.
// If using TRIGGER_TYPE_SERVO, set the TRIGGER_OUTPUT_CHANNEL above to choose which output channel
// receives trigger events, and set the TRIGGER_SERVO_LOW and TRIGGER_SERVO_HIGH values below.
// If using TRIGGER_TYPE_DIGITAL, the trigger will be on pin RE4.  In this case make sure to set
// NUM_OUTPUTS to be less than 6 to avoid a conflict between digital output and servo output on
// that pin.

// TRIGGER_ACTION can be: TRIGGER_PULSE_HIGH, TRIGGER_PULSE_LOW, TRIGGER_TOGGLE, or TRIGGER_REPEATING
// The trigger action output is always either low or high.  In servo mode, low and high are servo
// values set below.  In digital mode, low and high are 0V and 5V on pin RE4.
// The action is triggered when starting on a waypoint leg that includes the F_TRIGGER flag (see the
// waypoints.h file).
// If set to TRIGGER_PULSE_HIGH or TRIGGER_PULSE_LOW, then the output will pulse high or low for the
// number of milliseconds set by TRIGGER_PULSE_DURATION.
// If set to TRIGGER_TOGGLE, the output will just switch from high to low, or low to high each time
// the action is triggered.
// If set to TRIGGER_REPEATING, then during any waypoint leg with F_TRIGGER set, high pulses will be
// sent every TRIGGER_REPEAT_PERIOD milliseconds.

// Note, durations in milliseconds are rounded down to the nearest 25ms.

#define TRIGGER_TYPE						TRIGGER_TYPE_NONE
#define TRIGGER_ACTION						TRIGGER_PULSE_HIGH
#define TRIGGER_SERVO_LOW					2000
#define TRIGGER_SERVO_HIGH					4000
#define TRIGGER_PULSE_DURATION                                  250
#define TRIGGER_REPEAT_PERIOD                                   4000


////////////////////////////////////////////////////////////////////////////////
// Control gains.
// All gains should be positive real numbers.
//
// store PID gains in 32KB EEPROM as N 16 bit words starting at address 0x400
#define PID_GAINS_BASE_ADDR     (0X400)
#define PID_GAINS_N             14
//
// Tilt PID(DD) control gains: valid range [0,3.99]
#define TILT_KI 0.0
#define ROLL_KP 0.6
#define ROLL_KD 0.0
#define PITCH_KP 0.6
#define PITCH_KD 0.0
#define RRATE_KP 1.5
#define PRATE_KP 1.5
#define ACRO_KP 2.6
#define RRATE_KD 0.1
#define PRATE_KD 0.1
#define RATE_KI 0.3
//
// Yaw PID control gains
#define YAW_KI 0.5
#define YAW_KP 1.0
#define YAW_KD 0.0
//
// Vertical damping
// ****Note*** if your ESCs work "backwards", meaning that faster speed requires shorter pulses, then flip the sign to minus
// landings seem to be much softer with this turned on
#define ACCEL_K 0.0
//
// limiting values for roll/pitch and yaw control outputs
#define RPY_CLAMP 300
//
////////////////////////////////////////////////////////////////////////////////

// currently unused
//#define MAX_YAW_RATE 51  // maximum yaw rate, degrees per second, must be between 50 and 500 degrees/second
//#define MAX_TILT 45       // maximum roll or pitch, degrees, not to exceed 45 degrees

// Specify maximum tilt angle setpoint as 45 degrees
// PWM command input range is +/-1000 counts
// tilt angle is angle / pi as Q15 fractional
#define CMD_TILT_GAIN (unsigned int) (16384 / 1250)


////////////////////////////////////////////////////////////////////////////////
// Hardware In the Loop Simulation
// Only set this to 1 for testing in the simulator.  Do not try to fly with this set to 1!
// Requires setting GPS_TYPE to GPS_UBX_4HZ.
// See the MatrixPilot wiki for more info on using HILSIM.
#define HILSIM 	0

////////////////////////////////////////////////////////////////////////////////
// Camera Stabilization and Targeting
//
// There are three camera modes within MatrixPilot
/// Canera Mode 1: No stabilisation for camera pitch or yaw
//  Camera Mode 2: Stabilisation of camera pitch but not yaw.
//  Camera Mode 3: Camera targetting. The camera is aimed at a GPS location.

// Control of camera modes
// If CAMERA_MODE_INPUT_CHANNEL is assigned to a channel in the channels section of
// options.h then a three position switch can be used to select between the three camera
// stabilization modes. The following min and max values should work for most transmitters.

#define CAMERA_MODE_THRESHOLD_LOW			2600
#define CAMERA_MODE_THRESHOLD_HIGH			3400

// If you do not have a spare channel for CAMERA_MODE_INPUT_CHANNEL then,
// If CAMERA_MODE_INPUT_CHANNEL is defined as CHANNEL_UNUSED :-
//  In UDB Manual Mode the camera is fixed straight ahead. (Camera mode 1)
//  In UDB Stabilized Mode, the camera stabilizes in the pitch axis but stabilizes a constant yaw
//     relative to the plane's frame of reference. (Camera mode 2).
//  In Waypoint Mode, the direction of the camera is driven from a flight camera plan in waypoints.h
// In all three flight modes, if you set CAMERA_INPUT_CHANNEL then the transmitter camera controls
// will be mixed into the camera stabilisation. This allows a pilot to override the camera stabilization dynamically
// during flight and point the camera at a specific target of interest.

// Setup and configuration of camera targetting at installation of camera servos:-
// To save cpu cycles, you will need to pre-compute the tangent of the desired pitch of the camera
// when in stabilized mode. This should be expressed in 2:14 format.
// Example: You require the camera to be pitched down by 15 degrees from the horizon in stabilized mode.
// Paste the following line into a google search box (without the //)
// tan((( 15 /180 )* 3.1416 ))* 16384
// The result, as an integer, will be 4390. Change the angle, 15, for whatever angle you would like.
// Note that CAM_TAN_PITCH_IN_STABILIZED_MODE should not exceed 32767 (integer overflows to negative).

#define CAM_TAN_PITCH_IN_STABILIZED_MODE            1433	// 1443 is 5 degrees of pitch. Example: 15 degrees is 4389
#define CAM_YAW_IN_STABILIZED_MODE                  0 // in degrees relative to the plane's yaw axis.    Example: 0

// All number should be integers
#define CAM_PITCH_SERVO_THROW                       95	// Camera lens rotation at maximum PWM change (2000 to 4000), in degrees.
#define CAM_PITCH_SERVO_MAX                         85	// Max pitch up that plane can tilt and keep camera level, in degrees.
#define CAM_PITCH_SERVO_MIN                         -22 // Max pitch down that plane can tilt and keep camera level, in degrees.
#define CAM_PITCH_OFFSET_CENTRED                    38 // Offset in degrees of servo that results in a level camera.
											    // Example: 30 would mean that a centered pitch servo points the camera
												// 30 degrees down from horizontal when looking to the front of the plane.

#define CAM_YAW_SERVO_THROW                         350	// Camera yaw movement for maximum yaw PWM change (2000 to 4000) in Degrees.
#define CAM_YAW_SERVO_MAX                           130 // Max positive yaw of camera relative to front of plane in Degrees.
#define CAM_YAW_SERVO_MIN                           -130 // Min reverse  yaw of camera relative to front of plane in Degrees.
#define CAM_YAW_OFFSET_CENTRED                      11	// Yaw offset in degrees that results in camera pointing forward.

// Camera test mode will move the yaw from + 90 degrees to + 90 degrees every 5 seconds. (180 degree turn around)
// That will show whether the CAM_PITCH_SERVO_THROW value is set correctly for your servo.
// Once the camera rotates correctly through 180 degrees, then you can adjust CAM_PITCH_OFFSET_CENTRED to center the camera.
// In Camera test mode, pitch angle changes permanently to 90 degrees down in stabilized mode, and  0 (level) in Manual Mode.

#define CAM_TESTING_OVERIDE                         0 // Set to 1 for camera to move to test angles in stabilized mode.
#define CAM_TESTING_YAW_ANGLE                       90 // e.g. 90 degrees. Will try to swing 90 degrees left, then 90 degrees right
#define CAM_TESTING_PITCH_ANGLE                     90 // In degrees.

// Set this to 1 to ignore camera target data from the flightplan, and instead use camera target data coming in on the serial port.
// This data can be generated by another UDB running MatrixPilot, using SERIAL_CAM_TRACK.
// NOTE: When using camera tracking, both UDBs must be set to use the same fixed origin location.
#define CAM_USE_EXTERNAL_TARGET_DATA                0


////////////////////////////////////////////////////////////////////////////////
// Configure altitude hold
// These settings are only used when Altitude Hold is enabled above.

// Min and Max target heights in meters.  These only apply to stabilized mode.
#define HEIGHT_TARGET_MIN                           25.0
#define HEIGHT_TARGET_MAX                           100.0

// The range of altitude within which to linearly vary the throttle
// and pitch to maintain altitude.  A bigger value makes altitude hold
// smoother, and is suggested for very fast planes.
#define HEIGHT_MARGIN                               10

// Use ALT_HOLD_THROTTLE_MAX when below HEIGHT_MARGIN of the target height.
// Interpolate between ALT_HOLD_THROTTLE_MAX and ALT_HOLD_THROTTLE_MIN
// when within HEIGHT_MARGIN of the target height.
// Use ALT_HOLD_THROTTLE_MIN when above HEIGHT_MARGIN of the target height.
// Throttle values are from 0.0 - 1.0.
#define ALT_HOLD_THROTTLE_MIN				0.35
#define ALT_HOLD_THROTTLE_MAX				1.0

// Use ALT_HOLD_PITCH_MAX when below HEIGHT_MARGIN of the target height.
// Interpolate between ALT_HOLD_PITCH_MAX and ALT_HOLD_PITCH_MIN when
// within HEIGHT_MARGIN of the target height.
// Use ALT_HOLD_PITCH_HIGH when above HEIGHT_MARGIN of the target height.
// Pitch values are in degrees.  Negative values pitch the plane down.
#define ALT_HOLD_PITCH_MIN					-15.0
#define ALT_HOLD_PITCH_MAX					 15.0
#define ALT_HOLD_PITCH_HIGH					-15.0


////////////////////////////////////////////////////////////////////////////////
// Return To Launch Pitch Down in degrees, a real number.
// this is the real angle in degrees that the nose of the plane will pitch downward during a return to launch.
// it is used to increase speed (and wind penetration) during a return to launch.
// set it to zero if you do not want to use this feature.
// This only takes effect when entering RTL mode, which only happens when the plane loses the transmitter signal.
#define RTL_PITCH_DOWN						0.0


// Aileron/Roll Control Gains
// ROLLKP is the proportional gain, approximately 0.25
// ROLLKD is the derivative (gyro) gain, approximately 0.125
// YAWKP_AILERON is the proportional feedback gain for ailerons in response to yaw error
// YAWKD_AILERON is the derivative feedback gain for ailerons in response to yaw rotation
// AILERON_BOOST is the additional gain multiplier for the manually commanded aileron deflection
#define ROLLKP								0.20
#define ROLLKD								0.05
#define YAWKP_AILERON						0.10
#define YAWKD_AILERON						0.05
#define AILERON_BOOST						1.00

// Elevator/Pitch Control Gains
// PITCHGAIN is the pitch stabilization gain, typically around 0.125
// PITCHKD feedback gain for pitch damping, around 0.0625
// RUDDER_ELEV_MIX is the degree of elevator adjustment for rudder and banking
// AILERON_ELEV_MIX is the degree of elevator adjustment for aileron
// ELEVATOR_BOOST is the additional gain multiplier for the manually commanded elevator deflection
#define PITCHGAIN							0.10
#define PITCHKD								0.04
#define RUDDER_ELEV_MIX						0.20
#define ROLL_ELEV_MIX						0.05
#define ELEVATOR_BOOST						0.50

// Neutral pitch angle of the plane (in degrees) when flying inverted
// Use this to add extra "up" elevator while the plane is inverted, to avoid losing altitude.
#define INVERTED_NEUTRAL_PITCH	 			8.0

// Rudder/Yaw Control Gains
// YAWKP_RUDDER is the proportional feedback gain for rudder navigation
// YAWKD_RUDDER is the yaw gyro feedback gain for the rudder in reponse to yaw rotation
// ROLLKP_RUDDER is the feedback gain for the rudder in response to the current roll angle
// ROLLKD_RUDDER is the feedback gain for the rudder in response to the rate of change roll angle
// MANUAL_AILERON_RUDDER_MIX is the fraction of manual aileron control to mix into the rudder when
// in stabilized or waypoint mode.  This mainly helps aileron-initiated turning while in stabilized.
// RUDDER_BOOST is the additional gain multiplier for the manually commanded rudder deflection
#define YAWKP_RUDDER						0.05
#define YAWKD_RUDDER						0.05
#define ROLLKP_RUDDER						0.06
#define ROLLKD_RUDDER						0.05
#define MANUAL_AILERON_RUDDER_MIX			0.00
#define RUDDER_BOOST						1.00

// Gains for Hovering
// Gains are named based on plane's frame of reference (roll means ailerons)
// HOVER_ROLLKP is the roll-proportional feedback gain applied to the ailerons while navigating a hover
// HOVER_ROLLKD is the roll gyro feedback gain applied to ailerons while stabilizing a hover
// HOVER_PITCHGAIN is the pitch-proportional feedback gain applied to the elevator while stabilizing a hover
// HOVER_PITCHKD is the pitch gyro feedback gain applied to elevator while stabilizing a hover
// HOVER_PITCH_OFFSET is the neutral pitch angle for the plane (in degrees) while stabilizing a hover
// HOVER_YAWKP is the yaw-proportional feedback gain applied to the rudder while stabilizing a hover
// HOVER_YAWKD is the yaw gyro feedback gain applied to rudder while stabilizing a hover
// HOVER_YAW_OFFSET is the neutral yaw angle for the plane (in degrees) while stabilizing a hover
// HOVER_PITCH_TOWARDS_WP is the max angle in degrees to pitch the nose down towards the WP while navigating
// HOVER_NAV_MAX_PITCH_RADIUS is the radius around a waypoint in meters, within which the HOVER_PITCH_TOWARDS_WP
//                            value is proportionally scaled down.
#define HOVER_ROLLKP						0.05
#define HOVER_ROLLKD						0.05
#define HOVER_PITCHGAIN						0.2
#define HOVER_PITCHKD						0.25
#define HOVER_PITCH_OFFSET					0.0		// + leans towards top, - leans towards bottom
#define HOVER_YAWKP							0.2
#define HOVER_YAWKD							0.25
#define HOVER_YAW_OFFSET					0.0
#define HOVER_PITCH_TOWARDS_WP			   30.0
#define HOVER_NAV_MAX_PITCH_RADIUS		   20


////////////////////////////////////////////////////////////////////////////////
// Hardware In the Loop Simulation
// Only set this to 1 for testing in the simulator.  Do not try to fly with this set to 1!
// See the MatrixPilot wiki for more info on using HILSIM.
// HILSIM_BAUD is the serial speed for communications with the X-Plane plugin.  Default is
// now 38400.  Make sure the X-Plane plugin's Setup file has its speed set to match.
#define HILSIM 								0
#define HILSIM_BAUD							38400


////////////////////////////////////////////////////////////////////////////////
// Software In the Loop Simulation
// Only set this to 1 when building for simulation directly on your computer instead of
// running on a UDB.
// See the MatrixPilot wiki for more info on using SILSIM.
// Below are settings to configure the simulated UDB UARTs.
// The SERIAL_RC_INPUT settings allow optionally talking over a serial port to a UDB
// passing RC inputs through to the simulated UDB.
#define SILSIM								0
#define SILSIM_GPS_RUN_AS_SERVER			0
#define SILSIM_GPS_PORT						14551		// default port to connect to XPlane HILSIM plugin
#define SILSIM_GPS_HOST						"127.0.0.1"
#define SILSIM_TELEMETRY_RUN_AS_SERVER		0
#define SILSIM_TELEMETRY_PORT				14550		// default port to connect to QGroundControl
#define SILSIM_TELEMETRY_HOST				"127.0.0.1"
#define SILSIM_SERIAL_RC_INPUT_DEVICE		""			// i.e. "COM4" or "/dev/cu.usbserial-A600dP4v", or "" to disable
#define SILSIM_SERIAL_RC_INPUT_BAUD			38400


////////////////////////////////////////////////////////////////////////////////
// Flight Plan handling
//
// You can define your flightplan either using the UDB Waypoints format, or using UDB Logo
// Set this to either FP_WAYPOINTS or FP_LOGO
// The Waypoint definitions and options are located in the waypoints.h file.
// The Logo flight plan definitions and options are located in the flightplan-logo.h file.
#define FLIGHT_PLAN_TYPE					FP_WAYPOINTS


////////////////////////////////////////////////////////////////////////////////
// Debugging defines

// The following can be used to do a ground check of stabilization without a GPS.
// If you define TestGains, stabilization functions
// will be enabled, even without GPS or Tx turned on. (Tx is optional)
// #define TestGains						// uncomment this line if you want to test your gains without using GPS

// Set this to 1 to calculate and print out free stack space
#define RECORD_FREE_STACK_SPACE 			0


///////////////////////////////////////////////////////////////////////////////////
// Vehicle and Pilot Identification

// Once you are flying your plane and swapping flights and telemetry with other's across
// the world, you may like to fill in some of the fields below. This will be embedded in your
// telemetry, and used to make more interesting flights in Google Earth.
// ID_VEHICLE_MODEL_NAME provides indication of what model of plane, quad, car etc you are using
// ID_VEHICLE_REGISTRATION should be short (less than 12 continuous characters with no space
// it will be used in Google Earth as the folder name containing your flights.
// ID_LEAD_PILOT is your lead pilot flight name or alias e.g. "UAV Flight Director"
// ID_DIY_DRONES_URL should be the URL of your member page on DIY Drones.
// That will allow Google Earth viewers of your flights to click straight through to your latest discussions.
// EXAMPLE:-
//#define ID_VEHICLE_MODEL_NAME "Multiplex Twinstar 2"
//#define ID_VEHICLE_REGISTRATION "TW2-PDH-UK"
//#define ID_LEAD_PILOT "Pete Hollands"
//#define ID_DIY_DRONES_URL "http://www.diydrones.com/profile/PeterHollands"
#define ID_VEHICLE_MODEL_NAME "Not Defined"
#define ID_VEHICLE_REGISTRATION "Not Defined"
#define ID_LEAD_PILOT "Not Defined"
#define ID_DIY_DRONES_URL "http://www.diydrones.com"

////////////////////////////////////////////////////////////////////////////////
// The following define is used to enable vertical initialization for VTOL
// To enable vertical initialization, uncomment the line
//#define INITIALIZE_VERTICAL