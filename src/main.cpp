#include <Arduino.h> 
#include "pico/stdlib.h"
#include <trilaterate.hpp>
#include <LoRaReceiver.h>


int main(void)
{
    stdio_init_all();

    LoRaReceiver lora;
    lora.start();

    while (1)
    {
        lora.read();
    }
    
    return 0;
}
