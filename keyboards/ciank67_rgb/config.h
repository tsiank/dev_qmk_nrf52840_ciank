/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "custom_board.h"
#define ENABLE_STARTUP_ADV_NOLIST

#define BLE_NUS_MIN_INTERVAL 30
#define BLE_NUS_MAX_INTERVAL 30
#define BLE_HID_MAX_INTERVAL 50
#define BLE_HID_SLAVE_LATENCY 3

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Tsiank
#define PRODUCT         Ciank67_rgb
#define DESCRIPTION     A split keyboard for the cheap makers

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define THIS_DEVICE_ROWS MATRIX_ROWS
#define THIS_DEVICE_COLS MATRIX_COLS

#define MATRIX_ROW_PINS { PIN1, PIN2, PIN3, PIN4, PIN5 }
#define MATRIX_COL_PINS { PIN6, PIN7, PIN8, PIN9, PIN10,  PIN11, PIN12, PIN13, PIN14, PIN15, PIN16, PIN17, PIN18, PIN19 }

#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

#define TAPPING_TERM 200

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#ifdef RGBLIGHT_ENABLE
//#define PROGMEM // arm-gcc does not interpret PROGMEM
#define RGB_DI_PIN PIN23 //D3     // The pin the LED strip is connected to
#define RGBLED_NUM 20
#define RGBLIGHT_ANIMATIONS
//#define #endifRGBLIGHT_SPLIT 6
#endif


#define IS_LEFT_HAND  true

// Helix keyboard OLED support
//      see ./rules.mk: OLED_ENABLE=yes or no
#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif

#ifdef RGB_MATRIX_ENABLE
	#define PERMISSVIE_HOLD
	#define IGNORE_MOD_TAP_INTERRUPT
	#define TAPPING_FORCE_HOLD
	#define ONESHOT_TIMEOUT 120

	#define RGB_MATRIX_KEYPRESSES
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
	#define RGB_MATRIX_LED_PROCESS_LIMIT 20
	#define RGB_MATRIX_LED_FLUSH_LIMIT 26
	#define DRIVER_ADDR_1 0b1010000
	#define DRIVER_ADDR_2 0b1011111

	#define DRIVER_COUNT 2
	#define DRIVER_1_LED_TOTAL 47
	#define DRIVER_2_LED_TOTAL 36
	#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL
#endif
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
