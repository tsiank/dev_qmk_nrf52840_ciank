#include "ciank67_rgb.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"


#include "matrix.h"
#undef PACKED
#include "wait.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
extern rgblight_config_t rgblight_config;
#endif

#include "nrf/i2c.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

bool has_usb(void) {
  return (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY);
}

static bool ble_flag = false;

void nrfmicro_power_enable(bool enable) {

  if (has_usb())
      enable = true;

  if (enable) {
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_set(POWER_PIN);
  } else {
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_clear(POWER_PIN); // works
    //input with pull-up consumes less than without it when pin is open (Hasu)
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLUP); // doesn't seem to work
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_NOPULL); // neither this
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLDOWN); // or this
  }
}

uint8_t nrfmicro_switch_pin(void) {
  uint8_t value = nrf_gpio_pin_read(SWITCH_PIN);
  return value;
}


void check_ble_switch(bool init) {

  uint8_t value = nrfmicro_switch_pin();

  if (init || ble_flag != value) {
    ble_flag = value;

    // mind that it doesn't disable BLE completely, it only disables send
    set_usb_enabled(!ble_flag);
    set_ble_enabled(ble_flag);

    nrf_gpio_pin_clear(LED_PIN);

    if (ble_flag) {
      // blink twice on ble enabled
      for (int i=0; i<2; i++) {
        nrf_gpio_pin_set(LED_PIN);
        nrf_delay_ms(100);
        nrf_gpio_pin_clear(LED_PIN);
        nrf_delay_ms(100);
      }
    }
  }
}

void nrfmicro_init(void) {

  // configure pins
  nrf_gpio_cfg_output(POWER_PIN);
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);

  nrfmicro_power_enable(true);
  check_ble_switch(true);
}

// called every matrix_scan_user
void nrfmicro_update(void) {
  check_ble_switch(false);
}


void nrfmicro_init(void);
void nrfmicro_update(void);

void unselect_rows(void);
void select_row(uint8_t row);
matrix_row_t read_cols(void);
static bool bootloader_flag = false;

void matrix_init_user() {
  nrfmicro_init();

  select_row(3);
  wait_us(50);
  matrix_row_t row = read_cols();
  unselect_rows();
  if (row == 0b111000) {
    delete_bonds();
  } else if (row == 0b10) {
    bootloader_flag = true;
  }

  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
      iota_gfx_init(!IS_LEFT_HAND);   // turns on the display
  #endif
}

void matrix_scan_user(void) {
  #ifdef SSD1306OLED
    iota_gfx_task();  // this is what updates the display continuously
  #endif

  nrfmicro_update();
}


#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
 /* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */

    {0, A_1,   B_1,   C_1},
   {0, D_1,   E_1,   F_1},
   {0, G_1,   H_1,   I_1},
    {0, J_1,   K_1,   L_1},
   {0, A_6,   B_6,   C_6},
   {0, D_6,   E_6,   F_6},
   {0, G_6,   H_6,   I_6},
    {0, J_6,   K_6,   L_6},
    {1, A_1,   B_1,   C_1},
   {1, D_1,   E_1,   F_1},
   {1, G_1,   H_1,   I_1},
    {1, J_1,   K_1,   L_1},
    {1, A_6,   B_6,   C_6},
   {1, D_6,   E_6,   F_6},

   {0, A_2,   B_2,   C_2},
   {0, D_2,   E_2,   F_2},
   {0, G_2,   H_2,   I_2},
    {0, J_2,   K_2,   L_2},
   {0, A_7,   B_7,   C_7},
   {0, D_7,   E_7,   F_7},
   {0, G_7,   H_7,   I_7},
    {0, J_7,   K_7,   L_7},
    {1, A_2,   B_2,   C_2},
   {1, D_2,   E_2,   F_2},
   {1, G_2,   H_2,   I_2},
    {1, J_2,   K_2,   L_2},
    {1, A_7,   B_7,   C_7},
   {1, D_7,   E_7,   F_7},

   {0, A_3,   B_3,   C_3},
   {0, D_3,   E_3,   F_3},
   {0, G_3,   H_3,   I_3},
    {0, J_3,   K_3,   L_3},
   {0, A_8,   B_8,   C_8},
   {0, D_8,   E_8,   F_8},
   {0, G_8,   H_8,   I_8},
    {0, J_8,   K_8,   L_8},
    {1, A_3,   B_3,   C_3},
   {1, D_3,   E_3,   F_3},
   {1, G_3,   H_3,   I_3},
    {1, J_3,   K_3,   L_3},
    {1, A_8,   B_8,   C_8},

    {0, A_4,   B_4,   C_4},
   {0, D_4,   E_4,   F_4},
   {0, G_4,   H_4,   I_4},
    {0, J_4,   K_4,   L_4},
    {0, A_9,   B_9,   C_9},
   {0, D_9,   E_9,   F_9},
   {0, G_9,   H_9,   I_9},
    {0, J_9,   K_9,   L_9},
    {1, A_4,   B_4,   C_4},
   {1, D_4,   E_4,   F_4},
   {1, G_4,   H_4,   I_4},
    {1, J_4,   K_4,   L_4},
    {1, A_9,   B_9,   C_9},
   {1, D_9,   E_9,   F_9},

   {0, A_5,   B_5,   C_5},
   {0, D_5,   E_5,   F_5},
   {0, G_5,   H_5,   I_5},
    {0, J_5,   K_5,   L_5},
    {0, D_10,  E_10,  F_10},
    {0, G_10,  H_10,  I_10},
    {0, J_10,  K_10,  L_10},
   {1, A_5,   B_5,   C_5},
   {1, G_5,   H_5,   I_5},
    {1, J_5,   K_5,   L_5},
    {1, A_10,  B_10,  C_10},
    {1, D_10,  E_10,  F_10},

    {0, A_11,   B_11,   C_11},
   {0, D_11,   E_11,   F_11},
   {0, G_11,   H_11,   I_11},
    {0, J_11,   K_11,   L_11},
    {0, A_12,   B_12,   C_12},
   {0, D_12,   E_12,   F_12},
   {0, G_12,   H_12,   I_12},
    {0, J_12,   K_12,   L_12},
    {1, A_11,   B_11,   C_11},
   {1, D_11,   E_11,   F_11},
   {1, G_11,   H_11,   I_11},
    {1, J_11,   K_11,   L_11},
    {1, A_12,   B_12,   C_12},
   {1, D_12,   E_12,   F_12},
   {1, G_12,   H_12,   I_12},
    {1, J_12,   K_12,   L_12}
};

led_config_t g_led_config = {{
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
    { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
    { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
    { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54 },
    { 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66}
}, {
    {   0,  0 }, {  16,  0 }, {  32,  0 }, {  48,  0 }, {  64,  0 }, { 80,  0 }, { 96,  0 }, { 112,  0 }, { 128,  0 }, { 144,  0 }, { 160,  0 }, { 176,  0 }, { 192,  0 }, { 216,  0 },
    {   4, 16 }, {  18, 16 }, {  34, 16 }, {  50, 16 }, {  66, 16 }, { 82, 16 }, { 98, 16 }, { 114, 16 }, { 130, 16 }, { 146, 16 }, { 162, 16 }, { 178, 16 }, { 194,  16 }, { 220,  16 },
    {   6, 32 }, {  20, 32 }, {  36, 32 }, {  52, 32 }, {  68, 32 }, { 84, 32 }, { 100, 32 }, { 116, 32 }, { 132, 32 }, { 148, 32 }, { 164, 32 }, { 180, 32 }, { 212,  32 },
    {   9, 48 }, {  27, 48 }, {  43, 48 }, {  59, 48 }, {  75, 48 }, { 91, 48 }, { 107, 48 }, { 123, 48 }, { 139, 48 }, { 155, 48 }, { 171, 48 }, { 187, 48 }, { 203,  48 }, { 219,  48 },
    {   2, 64 }, {  16, 64 }, {  32, 64 }, {  48, 64 }, {  64, 64 }, { 82, 64 }, { 98, 64 }, { 114, 64 }, { 130, 64 }, { 146, 64 }, { 204, 64 }, { 224, 64 },
  // Underglow LEDs
    {  18, 16 }, {  50, 16 }, {  82, 16 },  {  114, 16 }, { 146, 16 }, { 178, 16 }, { 220, 16 }, 
    {   4, 32 }, { 220,  32}, 
    {  18, 48 }, {  50, 48 }, {  82, 48 },  {  114, 48 }, { 146, 48 }, { 178, 48 }, { 220, 48 }, 
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1,    4, 1, 1, 1,     1, 4, 4, 4,
  // Underglow LEDs
        2, 2, 2, 2,2, 2, 2,
    2,                            2,
        2, 2, 2, 2,2, 2, 2
}};
#endif