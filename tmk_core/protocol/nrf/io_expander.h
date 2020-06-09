/*
 * io_expander.h
 *
 *  Created on: 2018/12/21
 *      Author: sekigon-gonnoc
 */

#ifndef TMK_CORE_PROTOCOL_NRF_IO_EXPANDER_H_
#define TMK_CORE_PROTOCOL_NRF_IO_EXPANDER_H_

#ifdef USE_I2C_IOEXPANDER

#include "matrix.h"

typedef enum {
  TCA9555,
  PCA9654
} IOEXPANDER_TYPEDEF;

matrix_row_t read_row_ioexpander (uint8_t row);

#endif
#endif /* TMK_CORE_PROTOCOL_NRF_IO_EXPANDER_H_ */
