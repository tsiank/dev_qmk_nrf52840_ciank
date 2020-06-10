#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO(port, pin) ((port << 6) | pin)

//Rows
#define PIN1 GPIO(0,26)
#define PIN2 GPIO(0,29)
#define PIN3 GPIO(0,2)
#define PIN4 GPIO(1,13)
#define PIN5 GPIO(1,11)

//Columns
#define PIN6 GPIO(1,9)
#define PIN7 GPIO(0,28)
#define PIN8 GPIO(0,12)
#define PIN9 GPIO(1,10)
#define PIN10 GPIO(0,7)
#define PIN11 GPIO(0,3)
#define PIN12 GPIO(1,6)
#define PIN13 GPIO(1,4)
#define PIN14 GPIO(1,2)
#define PIN15 GPIO(1,0)
#define PIN16 GPIO(0,24)
#define PIN17 GPIO(0,22)
#define PIN18 GPIO(0,13)
#define PIN19 GPIO(0,20)

//unused
#define PIN20 GPIO(0,31)
#define PIN21 GPIO(0,30)
#define PIN22 GPIO(0,8)
#define PIN23 GPIO(0,6)
#define PIN24 GPIO(0,4)

#define RESET_PIN GPIO(0,18)

//#define LED_PIN GPIO(0,10)
//#define SWO_PIN GPIO(1,0)
//#define DFU_PIN GPIO(1,2)
//#define SWITCH_PIN GPIO(0,4)
//#define POWER_PIN GPIO(0,31)

//analog battery
#define ADC_PIN AIN3

// i2c pins
#define CONFIG_PIN_SCL GPIO(0,15)
#define CONFIG_PIN_SDA GPIO(0,17)


//#define NRF_LOG_ENABLED 0
//#define NRF_LOG_BACKEND_SERIAL_USES_UART 0
//#define NRF_LOG_BACKEND_SERIAL_UART_TX_PIN 5
#define NRF_LOG_BACKEND_UART_TX_PIN 8
//#define DEBUG
// Low frequency clock source to be used by the SoftDevice
#ifdef S210
// #define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
#else

// NRF_CLOCK_LF_SRC_RC - internal oscillator
// NRF_CLOCK_LF_SRC_XTAL - external crystal
// using E73 internal oscillator (assume there's no external crystal soldered)
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 16,                                \
                                 .rc_temp_ctiv  = 2,                                \
                                 .xtal_accuracy = 0}

#endif


#ifdef __cplusplus
}
#endif

#endif // CUSTOM_BOARD_H
