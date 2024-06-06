#warning "BUILDING MASTER"
#include <LoRaReceiver.h>
#include <gps.hpp>

int master_main(int argc, char** argv)
{
    LoRaReceiver receiver;
    gps gps;
    sleep_ms(2000);
    printf("Starting receiver\n");
    receiver.start();
    while (1)
    {
        receiver.read();
    }
    

    return 0;
}