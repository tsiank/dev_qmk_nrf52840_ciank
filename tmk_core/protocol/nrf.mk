PROTOCOL_DIR = protocol
NRF_DIR = $(PROTOCOL_DIR)/nrf

  SRC += $(NRF_DIR)/matrix.c \
       $(NRF_DIR)/io_expander.c \
       $(NRF_DIR)/ble/ble_common.c \
       $(NRF_DIR)/i2c/i2c_master.c \
       $(NRF_DIR)/i2c/i2c_slave.c \
       $(NRF_DIR)/spi_master.c \
       $(NRF_DIR)/adc.c \
       $(NRF_DIR)/usb/usbd.c \
       $(NRF_DIR)/usb/app_usbd_hid_kbd.c \
       $(NRF_DIR)/usb/app_usbd_hid_mouse.c \
       $(NRF_DIR)/cli.c \
       $(NRF_DIR)/microshell/core/microshell.c \
       $(NRF_DIR)/microshell/core/mscore.c \
       $(NRF_DIR)/microshell/util/mscmd.c \
       $(NRF_DIR)/microshell/util/msopt.c \
       $(NRF_DIR)/microshell/util/ntlibc.c \

VPATH += $(TMK_PATH)/$(NRF_DIR)/microshell/core
VPATH += $(TMK_PATH)/$(NRF_DIR)/microshell/util
VPATH += $(TMK_PATH)/$(NRF_DIR)/ble
VPATH += $(TMK_PATH)/$(NRF_DIR)/i2c
VPATH += $(TMK_PATH)/$(NRF_DIR)/usb

ifeq ($(strip $(NRF_SEPARATE)), slave)
  CFLAGS += -DNRF_SEPARATE_KEYBOARD_SLAVE
  SRC += $(NRF_DIR)/ble/ble_slave.c
  SRC += $(NRF_DIR)/main_slave.c
else
  SRC += $(NRF_DIR)/ble/ble_master.c
  SRC += $(NRF_DIR)/main_master.c
  ifeq ($(strip $(NRF_SEPARATE)), master)
    CFLAGS += -DNRF_SEPARATE_KEYBOARD_MASTER
    SRC += $(NRF_DIR)/ble/ble_central.c
  endif
  ifeq ($(strip $(NRF_SEPARATE)), dongle)
    CFLAGS += -DNRF_SEPARATE_KEYBOARD_DONGLE
    SRC += $(NRF_DIR)/ble/ble_dongle.c
    SRC += $(NRF_DIR)/ble/ble_hid_c.c
  endif
endif

VPATH += $(TMK_PATH)/$(PROTOCOL_DIR)
VPATH += $(TMK_PATH)/$(NRF_DIR)

ifeq ($(strip $(MIDI_ENABLE)), yes)
  include $(TMK_PATH)/protocol/midi.mk
endif

