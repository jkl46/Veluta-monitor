#include <LoRaTransmitter.h>

void LoRaTransmitter::start(){
    if (!LoRa.begin(500E6)) {
        printf("Starting LoRa failed!\n");
    }

    printf("LoRa Started\n");
}

void LoRaTransmitter::send(const char* data[2], uint8_t slave_id, uint8_t hornet_id){
    LoRa.beginPacket();
    LoRa.print("SLAVE_ID: #" + std::to_string(slave_id) + "gps: latitude #"+ data[0] +"longitude #" + data[1] + "Hornet_id: #" + std::to_string(hornet_id));	
    LoRa.endPacket();
}