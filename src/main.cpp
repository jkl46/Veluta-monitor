#include <Arduino.h> 
#include "pico/stdlib.h"
#include <trilaterate.hpp>
#include <gps.hpp>


int main(void)
{
    stdio_init_all();
    init_gps();
    while (1)
    {
        char *gps_data = read_gps();
        printf("GPS Data: %s\n", gps_data);
        delay(1000);
    }
    return 0;
}
