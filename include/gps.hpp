#ifndef LORA_RP2040_H
#define LORA_RP2040_H

#include <stdint.h>
#include "LoRa-RP2040.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>

// Function prototypes
void sendPakket(char* data);
void initUART(uart_inst_t *UART_ID, uint UART_TX_PIN, uint UART_RX_PIN, uint BAUDRATE);
void initLoRa();
char *readUART(uart_inst_t *UART_ID);

#endif // LORA_RP2040_H
