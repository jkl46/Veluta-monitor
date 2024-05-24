#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "LoRaReceiver.h"

//Inlude Library
#include "LoRa-RP2040.h"


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
            //for now print to serial, this will change once we are able to save it to the flash
            printf("%c", i);
         }
    }
}