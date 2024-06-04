
#include "LoRaReceiver.h"

const string message_start = "**";
const char   message_data_start = '#';
const char   message_data_end   = '@';

//Inlude Library

void LoRaReceiver::start()
{
   if (!LoRa.begin(500E6)) {
      printf("Starting LoRa failed!\n");
   }

   printf("LoRa Started\n");   
}

void LoRaReceiver::read(lora_data* data)
{
   int packet_size = LoRa.parsePacket();
   if (packet_size) {
      // received a packet
      printf("Received packet \n'");

      parse_message(data);
   }
}

void LoRaReceiver::parse_message(lora_data* data)
{
   string message = "";
   uint8_t character_counter = 0;
   // read packet
   while (LoRa.available()) {
      char character = LoRa.read();
      
      // looking for data end key
      if (character = message_data_end)
         save_data(data, message);
      
      message += character;

      // looking for message start key
      if (character_counter == 1 && message != message_start)
         break;

      // looking for data start key
      if (character = message_data_start)
         message = "";

      character_counter++;
   }
}

static uint8_t save_data_counter = 0;
void LoRaReceiver::save_data(lora_data* data, string message)
{
   save_data_counter++;

   switch(save_data_counter)
   {
      case 1:
         data->id = std::stoi(message);
         break;
      case 2:
         data->hornet_id = std::stoi(message);
         break;
      case 3:
         data->latitude = message;
         break;
      case 4:
         data->longitude = message;
         save_data_counter = 0;
         break;
   }
}
