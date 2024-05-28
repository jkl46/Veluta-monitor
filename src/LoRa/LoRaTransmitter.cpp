#include <LoRaTransmitter.h>

void LoRaTransmitter::start(){
    if (!LoRa.begin(500E6)) {
        printf("Starting LoRa failed!\n");
    }

    printf("LoRa Started\n");
}

void LoRaTransmitter::send(const char* message){
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    printf("Message sent: %s\n", message);
}