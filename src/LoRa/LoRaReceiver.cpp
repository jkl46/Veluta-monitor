
#include "LoRaReceiver.h"

//Inlude Library


void LoRaReceiver::start(){
    if (!LoRa.begin(500E6)) {
      printf("Starting LoRa failed!\n");
   }

    printf("LoRa Started\n");   
}

void LoRaReceiver::read(){
      int packetSize = LoRa.parsePacket();
      if (packetSize) {
         // received a packet
         printf("Received packet \n'");

         // read packet
         while (LoRa.available()) {
            char i = LoRa.read();
            printf("%c", i);
         }
    }
}