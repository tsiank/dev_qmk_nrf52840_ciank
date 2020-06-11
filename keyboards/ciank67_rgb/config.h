#ifndef CONFIG_H
#define CONFIG_H

#define ENABLE_STARTUP_ADV_NOLIST

/* Bluetooth connection setting*/
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
#define DESCRIPTION     Dvorak right-handed keyboard

/* key matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define THIS_DEVICE_ROWS MATRIX_ROWS
#define THIS_DEVICE_COLS MATRIX_COLS

//define GPIO(port, pin) ((port << 5) | (pin & 0x1F))
#define MATRIX_ROW_PINS { 26, 29, 2, 45, 43}
#define MATRIX_COL_PINS { 41, 28, 12, 42, 7, 3, 38, 36, 34, 32, 24, 22, 13, 20 }

// i2c pins
#define CONFIG_PIN_SCL 15
#define CONFIG_PIN_SDA 17

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

#define TAPPING_TERM 200

#define IS_LEFT_HAND  true

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#ifdef RGBLIGHT_ENABLE
	#define RGB_DI_PIN 6
	#define RGBLED_NUM 20
	#define RGBLIGHT_ANIMATIONS
	//#define #endifRGBLIGHT_SPLIT 6
#endif

#ifdef RGB_MATRIX_ENABLE
	#define DRIVER_ADDR_1 0b1010000
	#define DRIVER_ADDR_2 0b1011111
	#define DRIVER_COUNT 2
	#define DRIVER_1_LED_TOTAL 47
	#define DRIVER_2_LED_TOTAL 36
	#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL

	#define PERMISSVIE_HOLD
	#define IGNORE_MOD_TAP_INTERRUPT
	#define TAPPING_FORCE_HOLD
	#define ONESHOT_TIMEOUT 120

	#define RGB_MATRIX_KEYPRESSES
	#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
	#define RGB_MATRIX_LED_PROCESS_LIMIT 20
	#define RGB_MATRIX_LED_FLUSH_LIMIT 26
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

//analog battery measure
#define ADC_PIN NRF_SAADC_INPUT_AIN3

//#define NRF_LOG_ENABLED 0
//#define NRF_LOG_BACKEND_SERIAL_USES_UART 0
//#define NRF_LOG_BACKEND_SERIAL_UART_TX_PIN 5
#define NRF_LOG_BACKEND_UART_TX_PIN 8

// NRF_CLOCK_LF_SRC_RC - internal oscillator
// NRF_CLOCK_LF_SRC_XTAL - external crystal
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 16,                                \
                                 .rc_temp_ctiv  = 2,                                \
                                 .xtal_accuracy = 0}

#endif
