#include "main.hpp"
#include "LoRaReceiver.h"
// #include "LoRaData.hpp" TODO: branch merge

int master_main(int argc, char** argv)
{
    LoRaReceiver receiver;
    sleep_ms(2000);
    printf("Starting receiver\n");
    receiver.start();
    while (1)
    {
        receiver.read();
    }
    

    return 0;
}