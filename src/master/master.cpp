#warning "BUILDING MASTER"
#include <LoRaReceiver.h>

int master_main(int argc, char** argv)
{
    LoRaReceiver receiver;
    receiver.start();
    while (1)
    {
        receiver.read();
    }
    

    return 0;
}