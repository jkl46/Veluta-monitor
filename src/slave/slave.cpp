#warning "BUILDING SLAVE"
#include <LoRaTransmitter.h>
#include <gps.hpp>

#define SLAVE_ID 1
//#define SLAVE_ID 2
int slave_main(int argc, char** argv)
{
    // Main code here
    init_UART(uart0, 5, 6, 9600);
    const char* gps_data[2] = {"52.4995467",  "6.0799891"};
    LoRaTransmitter transmitter;
    transmitter.start();

    while (1) {
        // send 
        transmitter.send(gps_data, SLAVE_ID, 1);
        printf("Sending packets: ");
        printf("Packets send\n");
        sleep_ms(5000);

    }

    return 0;
}