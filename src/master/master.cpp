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
        lora_data data;
        if (receiver.read(&data))
        {
            // Use data struct to read data from LoRa
            printf("ID: %d, Hornet_ID: %d, long: %f, lat: %f\n", data.id, data.hornet_id, data.longitude, data.latitude);
        }
    }
    
    return 0;
}