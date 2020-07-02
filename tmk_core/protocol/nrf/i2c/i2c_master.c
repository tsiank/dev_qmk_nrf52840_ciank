#include <string.h>

#include "i2c.h"
#include "nrfx_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_pwr_mgmt.h"
#include "nrfx_twim.h"

#ifndef CONFIG_PIN_SCL
#define CONFIG_PIN_SCL 16
#endif
#ifndef CONFIG_PIN_SDA
#define CONFIG_PIN_SDA 18
#endif

#ifndef CONFIG_I2C_FREQ
#define CONFIG_I2C_FREQ NRF_TWI_FREQ_400K
#endif

static const nrfx_twim_t m_twim_master = NRFX_TWIM_INSTANCE(0);
static int twim_complete = 0;
#ifdef IS31FL3737
static volatile bool     twim_enable   = false;
static uint8_t twi_transfer_buffer[10];
 #endif

void twim_evt_handler(nrfx_twim_evt_t const *p_event, void *p_context) {
  NRF_LOG_INFO("TWIM Event:%d", p_event->type);
  twim_complete = p_event->type + 1;
}

int i2c_init(void) {
#ifdef IS31FL3737
    const nrfx_twim_config_t config = {
      .scl = CONFIG_PIN_SCL,
      .sda = CONFIG_PIN_SDA,
      .frequency = CONFIG_I2C_FREQ,
      .interrupt_priority = 5, 
      .hold_bus_uninit = true
  };
    int res    = (int)nrfx_twim_init(&m_twim_master, &config, twim_evt_handler, NULL);
    // nrfx_twim_enable(&m_twim_master);
    i2c_start();
#else
  const nrfx_twim_config_t config =
  {
     .scl                = CONFIG_PIN_SCL,
     .sda                = CONFIG_PIN_SDA,
     .frequency          = CONFIG_I2C_FREQ,
     .interrupt_priority = APP_IRQ_PRIORITY_LOW,
     .hold_bus_uninit     = false
  };
  int res = (int)nrfx_twim_init(&m_twim_master, &config, twim_evt_handler, NULL);
  nrfx_twim_enable(&m_twim_master);
 #endif
  return res;
}

void i2c_uninit(void) {
  nrfx_twim_uninit(&m_twim_master);
}

#ifdef IS31FL3737
static void i2c_write_register(uint8_t addr, uint8_t reg, uint8_t data) {
    twi_transfer_buffer[0] = reg;
    twi_transfer_buffer[1] = data;
    i2c_transmit(addr << 1, twi_transfer_buffer, 2, 0);
}

void i2c_start(void) {
    nrfx_twim_enable(&m_twim_master);
    twim_enable = true;

    i2c_write_register(DRIVER_ADDR_1, 0xFE, 0xC5);
    i2c_write_register(DRIVER_ADDR_1, 0xFD, 0x03);
    i2c_write_register(DRIVER_ADDR_1, 0x00, 0x01);
    
    i2c_write_register(DRIVER_ADDR_2, 0xFE, 0xC5);
    i2c_write_register(DRIVER_ADDR_2, 0xFD, 0x03);
    i2c_write_register(DRIVER_ADDR_2, 0x00, 0x01);
}

void i2c_stop(void) {
    i2c_write_register(DRIVER_ADDR_1, 0xFE, 0xC5);
    i2c_write_register(DRIVER_ADDR_1, 0xFD, 0x03);
    i2c_write_register(DRIVER_ADDR_1, 0x00, 0x00);
    
    i2c_write_register(DRIVER_ADDR_2, 0xFE, 0xC5);
    i2c_write_register(DRIVER_ADDR_2, 0xFD, 0x03);
    i2c_write_register(DRIVER_ADDR_2, 0x00, 0x00);

    twim_enable = false;
    nrfx_twim_disable(&m_twim_master);
}
#endif

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout)
{
#ifdef IS31FL3737
    if (!twim_enable) {
        return 0;
    }
    nrfx_err_t res;
    twim_complete = 0;

    res = nrfx_twim_tx(&m_twim_master, address >> 1, data, length, false);
    if (res != NRFX_SUCCESS) {
        NRF_LOG_INFO("Twim error:%d", res);
    }

    int cnt = 0;
    if (res == NRFX_SUCCESS) {
        while (twim_complete == 0) {
            nrf_pwr_mgmt_run();
            if (++cnt == 100) break;
        }
    }
    if (cnt == 100) {
        NRF_LOG_INFO("Twim tx timeout");
    }
    if (twim_complete != 1) {
        NRF_LOG_INFO("twim_uncomplete:%d %d %d", length, data[0], data[1]);
    }
#else
  nrfx_err_t res;
  twim_complete = 0;
  res = nrfx_twim_tx(&m_twim_master, address, data, length, false);
  int cnt=0;
  if (res == NRFX_SUCCESS) {
    while (twim_complete == 0) {
//      __WFI();
      nrf_pwr_mgmt_run();
      if(cnt++ == 1000) break;
    }
  }
  if(cnt == 1000) NRF_LOG_INFO("TX TIMEOUT");
#endif
  return twim_complete == 1 ? 0 : 1;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)
{
  nrfx_err_t res;
  twim_complete = 0;
  res = nrfx_twim_rx(&m_twim_master, address, data, length);
  int cnt=0;
  if (res == NRFX_SUCCESS) {
    while (twim_complete == 0) {
//      __WFI();
      nrf_pwr_mgmt_run();
      if(cnt++ == 1000) break;
    }
  }
  if(cnt == 1000) NRF_LOG_INFO("RX TIMEOUT");
  return twim_complete == 1 ? 0 : 1;
}

uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
//  nrfx_twi_tx(&m_twi_master, devaddr, &regaddr, 1, true);
//  return nrfx_twi_rx(&m_twi_master, devaddr, data, length);
  i2c_transmit(devaddr, &regaddr, 1,0);
  return i2c_receive(devaddr, data, length);
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
  static uint8_t buffer[256];
  buffer[0] = regaddr;
  memcpy(&buffer[1], data, length);
  return i2c_transmit(devaddr, buffer, length+1,0);
  return 0;
}
