#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>

void init_UART(uart_inst_t *UART_ID, uint UART_TX_PIN, uint UART_RX_PIN, uint BAUDRATE);
char *read_UART(uart_inst_t *UART_ID);

#endif 
