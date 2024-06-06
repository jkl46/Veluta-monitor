#warning "BUILDING SLAVE"
#include <LoRaTransmitter.h>
#include <gps.hpp>

#define SLAVE_ID 1
//#define SLAVE_ID 2
int slave_main(int argc, char** argv)
{
    // Main code here
    gps gps;
    LoRaTransmitter transmitter;
    transmitter.start();

    while (1) {
        // send 

        transmitter.send(gps.send_lat(),gps.send_lon(), SLAVE_ID, 1);
        printf("Sending packets: ");
        printf("Packets send\n");
        sleep_ms(5000);

    }

    return 0;
}