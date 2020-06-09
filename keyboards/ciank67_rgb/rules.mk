NRF_DEBUG = no

RGBLIGHT_ENABLE = yes
#RGB_MATRIX_ENABLE = IS31FL3737
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
NKRO_ENABLE = no	    # USB Nkey Rollover
CUSTOM_MATRIX = yes 	# This flag should be on for nrf52

NO_USB_STARTUP_CHECK = yes

## chip/board settings
MCU_FAMILY = NRF52
# linker script to use
# Cortex version
# Teensy LC is cortex-m0; Teensy 3.x are cortex-m4
MCU  = cortex-m4
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7


# it should exist either in <this_dir>/ld/
MCU_LDSCRIPT = nrf52840
MCU_SERIES = NRF52840
NRFSDK_ROOT := ../nRF5_SDK_15  #Path to nRF SDK v15.0.0

# project specific files
#SRC =	matrix.c
#SRC += ssd1306.c

#NRF_SEPARATE = master
#CFLAGS += -DNRF_XTAL_32MHZ

CFLAGS += -DFLIPPED_NRFMICRO
