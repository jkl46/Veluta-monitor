#include <LoRaTransmitter.h>

void LoRaTransmitter::start(){
    if (!LoRa.begin(500E6)) {
        printf("Starting LoRa failed!\n");
    }

    printf("LoRa Started\n");
}

void LoRaTransmitter::send(char* latitude, char* longitude, uint8_t slave_id, uint8_t hornet_id){
    LoRa.beginPacket();
    LoRa.print("SLAVE_ID: #" + std::to_string(slave_id) + "gps: latitude #"+ latitude +"longitude #" + longitude + "Hornet_id: #" + std::to_string(hornet_id));	
    LoRa.endPacket();
}