#warning "BUILDING SLAVE"
#include <LoRaTransmitter.h>
#include <gps.hpp>

#include "LoRaData.hpp"

#define SLAVE_ID 1
//#define SLAVE_ID 2
int slave_main(int argc, char** argv)
{
    // Main code here
    LoRaTransmitter transmitter;
    Coordinates coordinates;
    gps gps;
    transmitter.start();

    while (1) {
        // send
        lora_data data;
        data.id = SLAVE_ID;
        data.hornet_id = 1;
        data.longitude = coordinates.longitude;
        data.latitude = coordinates.latitude;
        transmitter.send(&data);
        printf("Sending packets: ");
        printf("Packets send\n");
        sleep_ms(5000);
    }

    return 0;
}
