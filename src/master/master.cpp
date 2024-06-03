#warning "BUILDING MASTER"
#include <LoRaReceiver.h>

int master_main(int argc, char** argv)
{
    LoRaReceiver receiver;
    sleep_ms(2000);
    printf("Starting receiver\n");
    receiver.start();
    while (1)
    {
        lora_data data;
        receiver.read(&data);

        // Use data struct to read data from LoRa
    }
    
    return 0;
}