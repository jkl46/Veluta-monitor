#include <LoRaTransmitter.h>

void LoRaTransmitter::start()
{
    if (!LoRa.begin(500E6)) {
        printf("Starting LoRa failed!\n");
    }

    printf("LoRa Started\n");
}

void LoRaTransmitter::send(lora_data* data)
{
    LoRa.beginPacket();
    LoRa.print("**SLAVE_ID: #" + std::to_string(data->id) + "@;gps: latitude #"+ data->latitude +"@;longitude #" + data->longitude + "@;Hornet_id: #" + std::to_string(data->hornet_id) + "@");	
    LoRa.endPacket();
}