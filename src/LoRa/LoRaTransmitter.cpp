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
    printf("**SALVE_ID: #%d@;gps: latitude #%f@;longitude #%f@;Hornet_id: #%d@", data->id, data->latitude, data->longitude, data->hornet_id);
    LoRa.beginPacket();
    LoRa.print("**SLAVE_ID: #" + std::to_string(data->id) + "@;gps: latitude #"+ std::to_string(data->latitude) +"@;longitude #" + std::to_string(data->longitude) + "@;Hornet_id: #" + std::to_string(data->hornet_id) + "@");	
    LoRa.endPacket();
}