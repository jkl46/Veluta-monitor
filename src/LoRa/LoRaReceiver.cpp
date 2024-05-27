
#include "LoRaReceiver.h"

//Inlude Library


void LoRaReceiver::start(){
    if (!LoRa.begin(500E6)) {
      Serial.println("Starting LoRa failed!\n");
   }

    Serial.println("LoRa Started\n");   
}

void LoRaReceiver::read(){
      int packetSize = LoRa.parsePacket();
      if (packetSize) {
         // received a packet
         Serial.println("Received packet \n'");

         // read packet
         while (LoRa.available()) {
            char i = LoRa.read();
            //for now print to serial, this will change once we are able to save it to the flash
            Serial.println(i);
         }
    }
}