#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include <stdbool.h>

#define UART_data_bits 8
#define UART_stop_bits 1
#define UART_PARITY_NONE UART_PARITY_NONE
#define UART_TX_PIN 5
#define UART_RX_PIN 6
#define BAUDRATE 9600
#define UART_ID uart1
#define MAX_ARRAY_SIZE 255

void init_gps();
char *read_gps();

#endif 