#include "main.hpp"
#include "LoRaTransmitter.h"
// #include "LoRaData.hpp" TODO: branch merge

// Defines

// Prototypes
void button1_callBack();
void button2_callBack();
void button3_callBack();

void send_hornet_data(int hornetID);

// Objects
LoRaTransmitter transmitter;

int slave_main(int argc, char** argv)
{
    // Init Lora
    transmitter.start();

    // Register button callbacks
    button1.callback = &button1_callBack;
    button2.callback = &button2_callBack;
    button3.callback = &button3_callBack;

    while(1)
    {
        // TODO: sleep mode?
    }
    return 0;
}

/*
TODO: check at merge
void send_hornet_data(int hornetID)
{
    lora_data data = {
        (uint8_t) thisMonitor.id,
        hornetID,
        thisMonitor.location.longitude,
        thisMonitor.location.latitude,
    };
    transmitter.send(&data);
}
*/ 

void button1_callBack()
{
    send_hornet_data(1);
}

void button2_callBack()
{
    send_hornet_data(2);
}

void button3_callBack()
{
    send_hornet_data(3);
}