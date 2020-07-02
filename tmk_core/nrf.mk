# Hey Emacs, this is a -*- makefile -*-
##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
#ifeq ($(USE_PROCESS_STACKSIZE),)
#  USE_PROCESS_STACKSIZE = 0x800
#endif
#
## Stack size to the allocated to the Cortex-M main/exceptions stack. This
## stack is used for processing interrupts and exceptions.
#ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
#  USE_EXCEPTIONS_STACKSIZE = 0x400
#endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Imported source files and paths
ROOT_DIR ?= .
NRFSDK_ROOT := $(ROOT_DIR)/lib/nrf52

NRFCFLAGS += -DNRF_SDK_MAJOR_VER=15

ifeq ($(NRF_DEBUG), yes)
  NRFCFLAGS += -DDEBUG=DEBUG
  NRFCFLAGS += -DNRF_LOG_ENABLED=1
  NRFCFLAGS += -DNRF_LOG_BACKEND_UART_ENABLED=1
  NRFCFLAGS += -DNRF_LOG_DEFAULT_LEVEL=4
else
  NRFCFLAGS += -DNRF_LOG_ENABLED=1
  NRFCFLAGS += -DNRF_LOG_BACKEND_UART_ENABLED=0
  NRFCFLAGS += -DNRF_LOG_DEFAULT_LEVEL=3
endif

COMMON_VPATH += $(DRIVER_PATH)/nrf52

NRFLIBSRC += \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_backend_rtt.c \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_backend_serial.c \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_backend_uart.c \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_default_backends.c \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_frontend.c \
  $(NRFSDK_ROOT)/components/libraries/log/src/nrf_log_str_formatter.c \
  $(NRFSDK_ROOT)/components/libraries/button/app_button.c \
  $(NRFSDK_ROOT)/components/libraries/util/app_error.c \
  $(NRFSDK_ROOT)/components/libraries/util/app_error_handler_gcc.c \
  $(NRFSDK_ROOT)/components/libraries/util/app_error_weak.c \
  $(NRFSDK_ROOT)/components/libraries/scheduler/app_scheduler.c \
  $(NRFSDK_ROOT)/components/libraries/timer/app_timer.c \
  $(NRFSDK_ROOT)/components/libraries/util/app_util_platform.c \
  $(NRFSDK_ROOT)/components/libraries/crc16/crc16.c \
  $(NRFSDK_ROOT)/components/libraries/fds/fds.c \
  $(NRFSDK_ROOT)/components/libraries/hardfault/hardfault_implementation.c \
  $(NRFSDK_ROOT)/components/libraries/util/nrf_assert.c \
  $(NRFSDK_ROOT)/components/libraries/atomic_fifo/nrf_atfifo.c \
  $(NRFSDK_ROOT)/components/libraries/atomic_flags/nrf_atflags.c \
  $(NRFSDK_ROOT)/components/libraries/atomic/nrf_atomic.c \
  $(NRFSDK_ROOT)/components/libraries/balloc/nrf_balloc.c \
  $(NRFSDK_ROOT)/external/fprintf/nrf_fprintf.c \
  $(NRFSDK_ROOT)/external/fprintf/nrf_fprintf_format.c \
  $(NRFSDK_ROOT)/components/libraries/fstorage/nrf_fstorage.c \
  $(NRFSDK_ROOT)/components/libraries/fstorage/nrf_fstorage_sd.c \
  $(NRFSDK_ROOT)/components/libraries/memobj/nrf_memobj.c \
  $(NRFSDK_ROOT)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c \
  $(NRFSDK_ROOT)/components/libraries/experimental_section_vars/nrf_section_iter.c \
  $(NRFSDK_ROOT)/components/libraries/ringbuf/nrf_ringbuf.c \
  $(NRFSDK_ROOT)/components/libraries/strerror/nrf_strerror.c \
  $(NRFSDK_ROOT)/integration/nrfx/legacy/nrf_drv_clock.c \
  $(NRFSDK_ROOT)/integration/nrfx/legacy/nrf_drv_uart.c \
  $(NRFSDK_ROOT)/integration/nrfx/legacy/nrf_drv_power.c \
  $(NRFSDK_ROOT)/integration/nrfx/legacy/nrf_drv_twi.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_gpiote.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_clock.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_power.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/prs/nrfx_prs.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_uart.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_uarte.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_saadc.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_spim.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_systick.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_twi.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_twim.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_twis.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_pwm.c \
  $(NRFSDK_ROOT)/external/segger_rtt/SEGGER_RTT.c \
  $(NRFSDK_ROOT)/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c \
  $(NRFSDK_ROOT)/external/segger_rtt/SEGGER_RTT_printf.c \
  $(NRFSDK_ROOT)/components/ble/common/ble_advdata.c \
  $(NRFSDK_ROOT)/components/ble/ble_advertising/ble_advertising.c \
  $(NRFSDK_ROOT)/components/ble/common/ble_conn_state.c \
  $(NRFSDK_ROOT)/components/ble/ble_link_ctx_manager/ble_link_ctx_manager.c \
  $(NRFSDK_ROOT)/components/ble/common/ble_srv_common.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/gatt_cache_manager.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/gatts_cache_manager.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/id_manager.c \
  $(NRFSDK_ROOT)/components/ble/nrf_ble_qwr/nrf_ble_qwr.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/peer_data_storage.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/peer_database.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/peer_id.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/peer_manager.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/pm_buffer.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/security_manager.c \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_bas/ble_bas.c \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_dis/ble_dis.c \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_hids/ble_hids.c \
  $(NRFSDK_ROOT)/modules/nrfx/soc/nrfx_atomic.c \
  $(NRFSDK_ROOT)/components/softdevice/common/nrf_sdh.c \
  $(NRFSDK_ROOT)/components/softdevice/common/nrf_sdh_soc.c \
  $(NRFSDK_ROOT)/components/libraries/queue/nrf_queue.c \
  $(NRFSDK_ROOT)/modules/nrfx/mdk/system_nrf52840.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid/app_usbd_hid.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid/generic/app_usbd_hid_generic.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/cdc/acm/app_usbd_cdc_acm.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/app_usbd.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/app_usbd_string_desc.c \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/dummy/app_usbd_dummy.c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/src/nrfx_usbd.c

NRFSRC +=  $(NRFSDK_ROOT)/modules/nrfx/mdk/gcc_startup_nrf52840.S \
  $(NRFSDK_ROOT)/components/libraries/usbd/app_usbd_core.c \
  $(NRFSDK_ROOT)/components/ble/peer_manager/security_dispatcher.c \
  $(NRFSDK_ROOT)/components/softdevice/common/nrf_sdh_ble.c \
  $(NRFSDK_ROOT)/components/ble/common/ble_conn_params.c \
  $(NRFSDK_ROOT)/components/ble/nrf_ble_gatt/nrf_ble_gatt.c \


#  $(NRFSDK_ROOT)/components/libraries/bsp/bsp.c \
  $(NRFSDK_ROOT)/components/libraries/bsp/bsp_btn_ble.c \
  $(NRFSDK_ROOT)/components/boards/boards.c \

# Include folders common to all targets
EXTRAINCDIRS += \
  $(TMK_PATH)/protocol/nrf \
  $(TMK_PATH)/protocol/nrf/pca10056/config \
  $(TMK_PATH)/protocol/chibios/lufa_utils \
  $(NRFSDK_ROOT)/components/nfc/ndef/generic/message \
  $(NRFSDK_ROOT)/components/nfc/t2t_lib \
  $(NRFSDK_ROOT)/components/nfc/t4t_parser/hl_detection_procedure \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_ancs_c \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_ias_c \
  $(NRFSDK_ROOT)/components/libraries/pwm \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/cdc/acm \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid/generic \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/msc \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid \
  $(NRFSDK_ROOT)/modules/nrfx/hal \
  $(NRFSDK_ROOT)/components/libraries/log \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_gls \
  $(NRFSDK_ROOT)/components/libraries/fstorage \
  $(NRFSDK_ROOT)/components/nfc/ndef/text \
  $(NRFSDK_ROOT)/components/libraries/mutex \
  $(NRFSDK_ROOT)/components/libraries/gpiote \
  $(NRFSDK_ROOT)/components/libraries/log/src \
  $(NRFSDK_ROOT)/components/libraries/bootloader/ble_dfu \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/common \
  $(NRFSDK_ROOT)/components/boards \
  $(NRFSDK_ROOT)/components/nfc/ndef/generic/record \
  $(NRFSDK_ROOT)/components/libraries/memobj \
  $(NRFSDK_ROOT)/components/nfc/t4t_parser/cc_file \
  $(NRFSDK_ROOT)/components/ble/ble_advertising \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_bas_c \
  $(NRFSDK_ROOT)/modules/nrfx/drivers/include \
  $(NRFSDK_ROOT)/components/libraries/experimental_task_manager \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_hrs_c \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/le_oob_rec \
  $(NRFSDK_ROOT)/components/libraries/queue \
  $(NRFSDK_ROOT)/components/libraries/pwr_mgmt \
  $(NRFSDK_ROOT)/components/ble/ble_dtm \
  $(NRFSDK_ROOT)/components/toolchain/cmsis/include \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_rscs_c \
  $(NRFSDK_ROOT)/components/ble/common \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_lls \
  $(NRFSDK_ROOT)/components/libraries/bsp \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/ac_rec \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_bas \
  $(NRFSDK_ROOT)/components/libraries/experimental_section_vars \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_ans_c \
  $(NRFSDK_ROOT)/components/libraries/slip \
  $(NRFSDK_ROOT)/components/libraries/delay \
  $(NRFSDK_ROOT)/components/libraries/experimental_mpu \
  $(NRFSDK_ROOT)/components/libraries/mem_manager \
  $(NRFSDK_ROOT)/components/libraries/csense_drv \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_nus_c \
  $(NRFSDK_ROOT)/components/libraries/usbd/config \
  $(NRFSDK_ROOT)/components/softdevice/common \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_ias \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid/mouse \
  $(NRFSDK_ROOT)/components/libraries/low_power_pwm \
  $(NRFSDK_ROOT)/components/nfc/ndef/conn_hand_parser/ble_oob_advdata_parser \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_dfu \
  $(NRFSDK_ROOT)/external/fprintf \
  $(NRFSDK_ROOT)/components/libraries/atomic \
  $(NRFSDK_ROOT)/components \
  $(NRFSDK_ROOT)/components/libraries/scheduler \
  $(NRFSDK_ROOT)/components/libraries/cli \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_lbs \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_hts \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_cts_c \
  $(NRFSDK_ROOT)/components/libraries/crc16 \
  $(NRFSDK_ROOT)/components/nfc/t4t_parser/apdu \
  $(NRFSDK_ROOT)/components/libraries/util \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/cdc \
  $(NRFSDK_ROOT)/components/libraries/csense \
  $(NRFSDK_ROOT)/components/libraries/balloc \
  $(NRFSDK_ROOT)/components/libraries/ecc \
  $(NRFSDK_ROOT)/components/libraries/hardfault \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_cscs \
  $(NRFSDK_ROOT)/components/libraries/hci \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/hid/kbd \
  $(NRFSDK_ROOT)/components/libraries/timer \
  $(NRFSDK_ROOT)/integration/nrfx \
  $(NRFSDK_ROOT)/components/nfc/t4t_parser/tlv \
  $(NRFSDK_ROOT)/components/libraries/sortlist \
  $(NRFSDK_ROOT)/components/libraries/spi_mngr \
  $(NRFSDK_ROOT)/components/libraries/stack_guard \
  $(NRFSDK_ROOT)/components/libraries/led_softblink \
  $(NRFSDK_ROOT)/components/nfc/ndef/conn_hand_parser \
  $(NRFSDK_ROOT)/components/libraries/sdcard \
  $(NRFSDK_ROOT)/components/nfc/ndef/parser/record \
  $(NRFSDK_ROOT)/modules/nrfx/mdk \
  $(NRFSDK_ROOT)/components/ble/ble_link_ctx_manager \
  $(NRFSDK_ROOT)/components/nfc/ndef/conn_hand_parser/le_oob_rec_parser \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_nus \
  $(NRFSDK_ROOT)/components/libraries/twi_mngr \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_hids \
  $(NRFSDK_ROOT)/components/libraries/strerror \
  $(NRFSDK_ROOT)/components/libraries/crc32 \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/ble_oob_advdata \
  $(NRFSDK_ROOT)/components/nfc/t2t_parser \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/ble_pair_msg \
  $(NRFSDK_ROOT)/components/libraries/usbd/class/audio \
  $(NRFSDK_ROOT)/components/nfc/t4t_lib/hal_t4t \
  $(NRFSDK_ROOT)/components/libraries/sensorsim \
  $(NRFSDK_ROOT)/components/nfc/t4t_lib \
  $(NRFSDK_ROOT)/components/ble/peer_manager \
  $(NRFSDK_ROOT)/components/drivers_nrf/usbd \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_tps \
  $(NRFSDK_ROOT)/components/nfc/ndef/parser/message \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_dis \
  $(NRFSDK_ROOT)/components/nfc/ndef/uri \
  $(NRFSDK_ROOT)/components/ble/nrf_ble_gatt \
  $(NRFSDK_ROOT)/components/ble/nrf_ble_qwr \
  $(NRFSDK_ROOT)/components/libraries/gfx \
  $(NRFSDK_ROOT)/components/libraries/button \
  $(NRFSDK_ROOT)/modules/nrfx \
  $(NRFSDK_ROOT)/components/libraries/twi_sensor \
  $(NRFSDK_ROOT)/integration/nrfx/legacy \
  $(NRFSDK_ROOT)/components/libraries/usbd \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/ep_oob_rec \
  $(NRFSDK_ROOT)/external/segger_rtt \
  $(NRFSDK_ROOT)/external/utf_converter \
  $(NRFSDK_ROOT)/components/libraries/atomic_fifo \
  $(NRFSDK_ROOT)/components/libraries/ringbuf \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_lbs_c \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/ble_pair_lib \
  $(NRFSDK_ROOT)/components/libraries/crypto \
  $(NRFSDK_ROOT)/components/ble/ble_racp \
  $(NRFSDK_ROOT)/components/libraries/fds \
  $(NRFSDK_ROOT)/components/nfc/ndef/launchapp \
  $(NRFSDK_ROOT)/components/libraries/atomic_flags \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_rscs \
  $(NRFSDK_ROOT)/components/nfc/ndef/connection_handover/hs_rec \
  $(NRFSDK_ROOT)/components/nfc/t2t_lib/hal_t2t \
  $(NRFSDK_ROOT)/components/nfc/ndef/conn_hand_parser/ac_rec_parser \
  $(NRFSDK_ROOT)/components/ble/ble_services/ble_hrs \
  $(NRFSDK_ROOT)/components/ble/ble_db_discovery \
  $(NRFSDK_ROOT)/components/ble/ble_radio_notification \
  $(NRFSDK_ROOT)/components/softdevice/s140/headers \
  $(NRFSDK_ROOT)/components/softdevice/s140/headers/nrf52 \

NRFLIB := libnrf.sdk15.$(MCU_SERIES)

ifeq ($(strip $(NRF_SEPARATE)), master)
  NRFSRC += \
    $(NRFSDK_ROOT)/components/ble/ble_db_discovery/ble_db_discovery.c \
    $(NRFSDK_ROOT)/components/ble/ble_services/ble_nus_c/ble_nus_c.c \

  EXTNRFCFLAGS += -DBLE_DB_DISCOVERY_ENABLED=1
  EXTNRFCFLAGS += -DBLE_NUS_C_ENABLED=1
  EXTNRFCFLAGS += -DPM_CENTRAL_ENABLED=1
  EXTNRFCFLAGS += -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=1
  EXTNRFCFLAGS += -DNRF_SDH_BLE_TOTAL_LINK_COUNT=2
endif

ifeq ($(strip $(NRF_SEPARATE)), dongle)
  NRFSRC += \
    $(NRFSDK_ROOT)/components/ble/ble_db_discovery/ble_db_discovery.c \
    $(NRFSDK_ROOT)/components/ble/ble_services/ble_nus_c/ble_nus_c.c \

  EXTNRFCFLAGS += -DBLE_DB_DISCOVERY_ENABLED=1
  EXTNRFCFLAGS += -DBLE_NUS_C_ENABLED=1
  EXTNRFCFLAGS += -DPM_CENTRAL_ENABLED=1
  EXTNRFCFLAGS += -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=5
  EXTNRFCFLAGS += -DNRF_SDH_BLE_TOTAL_LINK_COUNT=6
  EXTNRFCFLAGS += -DBLE_GATT_DB_MAX_CHARS=16
  EXTNRFCFLAGS += -DNRF_SDH_BLE_GATT_MAX_MTU_SIZE=247
endif

ifeq ($(strip $(NRF_SEPARATE)), slave)
  NRFSRC += \
    $(NRFSDK_ROOT)/components/ble/ble_services/ble_nus/ble_nus.c \

  EXTNRFCFLAGS += -DNRF_SDH_BLE_PERIPHERAL_LINK_COUNT=1
  EXTNRFCFLAGS += -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=0
  EXTNRFCFLAGS += -DNRF_SDH_BLE_TOTAL_LINK_COUNT=1
  EXTNRFCFLAGS += -DNRF_SDH_BLE_GATT_MAX_MTU_SIZE=247
  EXTNRFCFLAGS += -DBLE_NUS_ENABLED=1
endif

  NRFCFLAGS += -DAPP_USBD_VID=VENDOR_ID
  NRFCFLAGS += -DAPP_USBD_PID=PRODUCT_ID
  NRFCFLAGS += -DBOARD_PCA10056
#  NRFCFLAGS += -DCONFIG_GPIO_AS_PINRESET
  NRFCFLAGS += -DCONFIG_NFCT_PINS_AS_GPIOS
  NRFCFLAGS += -DFLOAT_ABI_HARD
  NRFCFLAGS += -DSOFTDEVICE_PRESENT
  NRFCFLAGS += -DSWI_DISABLE0
  NRFCFLAGS += -mcpu=cortex-m4
  NRFCFLAGS += -mthumb -mabi=aapcs
#  NRFCFLAGS += -Wall -Werror
  NRFCFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # keep every function in a separate section, this allows linker to discard unused ones
  NRFCFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
  NRFCFLAGS += -fno-builtin -fshort-enums
  NRFCFLAGS += -Os

  NRFCFLAGS += -DNRF52840_XXAA
  NRFCFLAGS += -DNRF_SD_BLE_API_VERSION=6
  NRFCFLAGS += -DS140
  ASFLAGS += -DNRF52840_XXAA
  ASFLAGS += -DNRF_SD_BLE_API_VERSION=6
  ASFLAGS += -DS140

  ASFLAGS += -mcpu=cortex-m4
  ASFLAGS += -mthumb -mabi=aapcs
  ASFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  ASFLAGS += -DBOARD_PCA10056
#  ASFLAGS += -DCONFIG_GPIO_AS_PINRESET
  ASFLAGS += -DFLOAT_ABI_HARD
  ASFLAGS += -DSOFTDEVICE_PRESENT
  ASFLAGS += -DSWI_DISABLE0

  NRFCFLAGS += -D__HEAP_SIZE=0
  NRFCFLAGS += -D__STACK_SIZE=16384
  ASMFLAGS += -D__HEAP_SIZE=0
  ASMFLAGS += -D__STACK_SIZE=16384

  # Linker flags
  LDFLAGS += -mthumb -mabi=aapcs -L$(NRFSDK_ROOT)/modules/nrfx/mdk -T$(LDSCRIPT)
  LDFLAGS += -mcpu=cortex-m4
  LDFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # let linker to dump unused sections
  LDFLAGS += -Wl,--gc-sections
  # use newlib in nano version
  LDFLAGS += --specs=nano.specs -lc -lnosys
#  LDFLAGS += -L. $(NRFLIB)

ifeq ($(NRF_DEBUG), yes)
	NRFLIB := $(NRFLIB).debug.a
else
	NRFLIB := $(NRFLIB).a
endif

# Project, sources and paths
##############################################################################

# Define linker script file here
LDSCRIPT = $(TMK_PATH)/protocol/nrf/pca10056/ld/$(MCU_LDSCRIPT).ld


##############################################################################
# Compiler settings
#
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
AR = arm-none-eabi-ar
NM = arm-none-eabi-nm
HEX = $(OBJCOPY) -O $(FORMAT)
EEP =
BIN = $(OBJCOPY) -O binary

#THUMBFLAGS = -DTHUMB_PRESENT -mno-thumb-interwork -DTHUMB_NO_INTERWORKING -mthumb -DTHUMB

#COMPILEFLAGS += -fomit-frame-pointer
#COMPILEFLAGS += -falign-functions=16
#COMPILEFLAGS += -ffunction-sections
#COMPILEFLAGS += -fdata-sections
#COMPILEFLAGS += -fno-common
#COMPILEFLAGS += -fshort-wchar
#COMPILEFLAGS += $(THUMBFLAGS)

NRFCFLAGS += $(COMPILEFLAGS)

#ASFLAGS += $(THUMBFLAGS)

CPPFLAGS += $(COMPILEFLAGS)
CPPFLAGS += -fno-rtti

# let linker to dump unused sections


MCUFLAGS = -mcpu=$(MCU)

OPT_DEFS += -DPROTOCOL_NRF

# FPU options default (Cortex-M4 and Cortex-M7 single precision).
ifeq ($(USE_FPU_OPT),)
  USE_FPU_OPT = -mfloat-abi=$(USE_FPU) -mfpu=fpv4-sp-d16 -fsingle-precision-constant
endif

# FPU-related options
ifeq ($(USE_FPU),)
  USE_FPU = no
endif
ifneq ($(USE_FPU),no)
  OPT    += $(USE_FPU_OPT)
  OPT_DEFS  += -DCORTEX_USE_FPU=TRUE
else
  OPT_DEFS  += -DCORTEX_USE_FPU=FALSE
endif

DEBUG = gdb

DFU_ARGS ?=
ifneq ("$(SERIAL)","")
	DFU_ARGS += -S $(SERIAL)
endif

# List any extra directories to look for libraries here.
EXTRALIBDIRS = $(RULESPATH)/ld .

DFU_UTIL ?= dfu-util

BOARD_INC :=

ifneq ("$(wildcard $(KEYBOARD_PATH_5)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_5)
    BOARD_INC += $(KEYBOARD_PATH_5)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_4)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_4)
    BOARD_INC += $(KEYBOARD_PATH_4)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_3)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_3)
    BOARD_INC += $(KEYBOARD_PATH_3)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_2)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_2)
    BOARD_INC += $(KEYBOARD_PATH_2)/board
else ifneq ("$(wildcard $(KEYBOARD_PATH_1)/board/custom_board.h)","")
    BOARD_PATH = $(KEYBOARD_PATH_1)
    BOARD_INC += $(KEYBOARD_PATH_1)/board
else ifneq ("$(wildcard $(TOP_DIR)/drivers/board/custom_board.h)","")
    BOARD_PATH = $(TOP_DIR)/drivers
    BOARD_INC += $(TOP_DIR)/drivers/board/custom_board.h
endif

ifneq ("$(wildcard $(BOARD_INC))","")
    EXTRAINCDIRS += $(BOARD_INC)
endif

# Generate a .qmk for the QMK-FF
qmk: $(BUILD_DIR)/$(TARGET).bin
	zip $(TARGET).qmk -FSrj $(KEYMAP_PATH)/*
	zip $(TARGET).qmk -u $<
	printf "@ $<\n@=firmware.bin\n" | zipnote -w $(TARGET).qmk
	printf "{\n  \"generated\": \"%s\"\n}" "$$(date)" > $(BUILD_DIR)/$(TARGET).json
	if [ -f $(KEYBOARD_PATH_5)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_5)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_4)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_4)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_3)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_3)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_2)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_2)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	if [ -f $(KEYBOARD_PATH_1)/info.json ]; then \
		jq -s '.[0] * .[1]' $(BUILD_DIR)/$(TARGET).json $(KEYBOARD_PATH_1)/info.json | ex -sc 'wq!$(BUILD_DIR)/$(TARGET).json' /dev/stdin; \
	fi
	zip $(TARGET).qmk -urj $(BUILD_DIR)/$(TARGET).json
	printf "@ $(TARGET).json\n@=info.json\n" | zipnote -w $(TARGET).qmk

dfu-util: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	$(DFU_UTIL) $(DFU_ARGS) -D $(BUILD_DIR)/$(TARGET).bin

bin: $(BUILD_DIR)/$(TARGET).bin sizeafter
	$(COPY) $(BUILD_DIR)/$(TARGET).bin $(TARGET).bin;

	python ./util/uf2conv.py $(BUILD_DIR)/$(TARGET).hex -c -f 0xADA52840 -o $(BUILD_DIR)/$(TARGET).uf2

nrfutil: $(BUILD_DIR)/$(TARGET).bin cpfirmware sizeafter
	nrfutil pkg generate --hw-version 52 --application-version 1 --sd-req 0xB6 --application $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).zip
	$(call EXEC_NRFUTIL)

GREP ?= grep

define EXEC_NRFUTIL
	USB= ;\
	if $(GREP) -q -s Microsoft /proc/version; then \
		echo 'ERROR: NRF flashing cannot be automated within the Windows Subsystem for Linux (WSL) currently. Instead, take the .hex file generated and flash it using AVRDUDE, AVRDUDESS, or XLoader.'; \
	else \
		printf "Detecting USB port, reset your controller now."; \
		ls /dev/tty* > /tmp/1; \
		while [ -z $$USB ]; do \
			sleep 0.5; \
			printf "."; \
			ls /dev/tty* > /tmp/2; \
			USB=`comm -13 /tmp/1 /tmp/2 | $(GREP) -o '/dev/tty.*'`; \
			mv /tmp/2 /tmp/1; \
		done; \
		echo ""; \
		echo "Device $$USB has appeared; assuming it is the controller."; \
		if $(GREP) -q -s 'MINGW\|MSYS' /proc/version; then \
			USB=`echo "$$USB" | perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
			echo "Remapped MSYS2 USB port to $$USB"; \
			sleep 1; \
		else \
			printf "Waiting for $$USB to become writable."; \
			while [ ! -w "$$USB" ]; do sleep 0.5; printf "."; done; echo ""; \
		fi; \
		nrfutil dfu usb-serial -pkg $(BUILD_DIR)/$(TARGET).zip -p $$USB; \
	fi
            endef

uf2: $(BUILD_DIR)/$(TARGET).bin
	./util/uf2conv.py -f nrf52 -b 0x26000 -o $(TARGET).uf2 $(BUILD_DIR)/$(TARGET).bin -c
	-./util/uf2conv.py -f nrf52 -b 0x26000 $(BUILD_DIR)/$(TARGET).bin

elf: $(NRFLIB)

NRFLIBOBJ := $(NRFLIBSRC:%.c=$(BUILD_DIR)/$(NRFLIB)/%.o)
NRFLIBINC := $(patsubst %,-I%,$(EXTRAINCDIRS))
NRFLIBDEPS := $(patsubst %.o,%.d,$(NRFLIBOBJ))

$(BUILD_DIR)/$(NRFLIB)/%.o: %.c $(BUILD_DIR)/$(NRFLIB)/%.d $(BUILD_DIR)/$(NRFLIB)/cflags.txt
	@mkdir -p $(@D)
	@$(SILENT) || printf "$(MSG_COMPILING) $<" | $(AWK_CMD)
	$(CC) -c $(NRFCFLAGS) $(NRFLIBINC) -MMD -MP -MF $(patsubst %.o,%.td,$@) $< -o $@ && mv -f $(patsubst %.o,%.td,$@) $(patsubst %.o,%.d,$@)
	@$(BUILD_CMD)

$(BUILD_DIR)/$(NRFLIB)/force:

$(BUILD_DIR)/$(NRFLIB)/cflags.txt: $(BUILD_DIR)/$(NRFLIB)/force
	@mkdir -p $(@D)
	echo '$(NRFCFLAGS)' | cmp -s - $@ || echo '$(NRFCFLAGS)' > $@

# Keep the .d files
.PRECIOUS: $(NRFLIBDEPS)
# Empty rule to force recompilation if the .d file is missing
$(NRFLIBDEPS):

$(NRFLIB): $(NRFLIBOBJ)
	$(AR) rcs $@ $^

# Include the dependency files.
-include $(patsubst %.o,%.d,$(NRFLIBOBJ))

CFLAGS += $(NRFCFLAGS) $(EXTNRFCFLAGS)
EXTRAOBJ += $(NRFLIBOBJ)
