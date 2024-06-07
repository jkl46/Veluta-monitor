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
    gps gps_device;
    gps_device.init_gps();
    transmitter.start();

    while (1) {
        // send
        lora_data data;
        //data.id = SLAVE_ID;
        std::vector<char> gps_data = gps_device.read_gps();
        gps_device.send_gps(gps_data);
        printf("\n");	
        // printf("Latitude: %f\n", gps_device.latitude);
        // printf("Longitude: %f\n", gps_device.longitude);
        //data.latitude = coordinates.latitude;
        //data.longitude = coordinates.longitude;
        //transmitter.send(&data);
        sleep_ms(500);
    }

    return 0;
}
