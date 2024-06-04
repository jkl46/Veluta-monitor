#warning "BUILDING SLAVE"
#include <LoRaTransmitter.h>
#include <gps.hpp>

#include "LoRaData.hpp"

#define SLAVE_ID 1
//#define SLAVE_ID 2
int slave_main(int argc, char** argv)
{
    // Main code here
    init_UART(uart0, 5, 6, 9600);
    double gps_data_1 = 52.4995467;
    double gps_data_2 = 6.0799891;
    LoRaTransmitter transmitter;
    transmitter.start();

    while (1) {
        // send
        lora_data data;
        data.id = SLAVE_ID;
        data.hornet_id = 1;
        data.longitude = gps_data_1;
        data.latitude = gps_data_2;
        transmitter.send(&data);
        printf("Sending packets: ");
        printf("Packets send\n");
        sleep_ms(5000);
    }

    return 0;
}