#ifndef LORAWAN_H
#define LORAWAN_H

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string>
#include "hornet.hpp"

#define BAUDRATE 9600
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define UART_data_bits 8
#define UART_stop_bits 1
class LoRaWAN 
{
public:
    void initLoRaWAN();
    void sendLoRaWAN(double latitude, double longitude, uint8_t area_code);

    // Add your public member functions here

private:
    // Add your private member variables and functions here
};
#endif // LORAWAN_H 