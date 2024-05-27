#include <Arduino.h> 
#include "pico/stdlib.h"
#include <trilaterate.hpp>
#include <LoRaReceiver.h>


int main(void)
{
    Serial.begin(9600);
    stdio_init_all();

    LoRaReceiver lora;
    lora.start();

    while (1)
    {
        lora.read();
    }
}
