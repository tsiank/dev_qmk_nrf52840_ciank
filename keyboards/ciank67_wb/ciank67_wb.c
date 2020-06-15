#include "ciank67_wb.h"
#include "nrf_gpio.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10 },
    {  11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
}, {
    {   0,  0 }, {  16,  0 }, {  32,  0 }, {  48,  0 }, {  64,  0 }, { 80,  0 }, { 96,  0 }, { 112,  0 }, { 128,  0 }, { 144,  0 },
    {   4, 16 }, {  18, 16 }, {  34, 16 }, {  50, 16 }, {  66, 16 }, { 82, 16 }, { 98, 16 }, { 114, 16 }, { 130, 16 }, { 146, 16},
  // Underglow LEDs
    /*
    {  18, 16 }, {  50, 16 }, {  82, 16 },  {  114, 16 }, { 146, 16 }, { 178, 16 }, { 220, 16 }, 
    {   4, 32 }, { 220,  32}, 
    {  18, 48 }, {  50, 48 }, {  82, 48 },  {  114, 48 }, { 146, 48 }, { 178, 48 }, { 220, 48 }, */
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  // Underglow LEDs
  /*
        2, 2, 2, 2,2, 2, 2,
    2,                            2,
        2, 2, 2, 2,2, 2, 2
*/
}};
#endif