#include "main.hpp"

#include "LoRaTransmitter.h"
#include "LoRaData.hpp"

// Defines

// Prototypes
void slave_button1_callBack();
void slave_button2_callBack();
void slave_button3_callBack();

void send_hornet_data(int hornetID);

// Objects
LoRaTransmitter transmitter;

int slave_main(int argc, char** argv)
{
    // Init Lora
    transmitter.start();

    // Attach button callbacks for slave
    button1.callback = &slave_button1_callBack;
    button2.callback = &slave_button2_callBack;
    button3.callback = &slave_button3_callBack;

    while(1)
    {
        // TODO: sleep mode?
    }
    return 0;
}

void send_hornet_data(int hornetID)
{
    lora_data data = {
        (uint8_t) thisMonitor.id,
        (uint8_t) hornetID,
        thisMonitor.area,
        thisMonitor.location.longitude,
        thisMonitor.location.latitude,
    };

    if (hornetID == 2)
    {
        data.monitor_id = 1;
    }

    printf("pre send\n");
    transmitter.send(&data);
    printf("post send\n");
    stdio_flush();
}

void slave_button1_callBack()
{
    send_hornet_data(0);
}

void slave_button2_callBack()
{
    send_hornet_data(1);
}

void slave_button3_callBack()
{
    send_hornet_data(2);
}
