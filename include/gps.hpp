#ifndef GPS_H
#define GPS_H

#include <stdint.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>
#include <pico/stdlib.h>
#include <stdbool.h>
#include <vector>
#include <cstdlib>
#include <string>

struct Coordinates {
    double latitude;
    double longitude;;
};

class gps {
    public:
        gps();
        ~gps();
        void init_gps();
        std::vector<char> read_gps();
        Coordinates send_gps(std::vector<char> gps_data);
        char* send_lon();
        char* send_lat();

    private:
        const int UART_data_bits = 8;
        const int UART_stop_bits = 1;
        const int UART_TX_PIN = 5;
        const int UART_RX_PIN = 6;
        const int BAUDRATE = 9600;
        const int MAX_ARRAY_SIZE = 255;
};



#endif 