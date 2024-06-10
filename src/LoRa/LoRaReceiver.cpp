
#include "LoRaReceiver.h"

const string message_start = "**";
const char   message_data_start = '#';
const char   message_data_end   = '@';

//Inlude Library

static uint8_t save_data_counter = 0;
void save_data(lora_data* data, string message)
{
   save_data_counter++;

   switch(save_data_counter)
   {
      case 1:
         data->monitor_id = std::stoi(message.c_str());
         break;
      case 2:
         data->latitude = std::stod(message.c_str());
         break;
      case 3:
         data->longitude = std::stod(message.c_str());
         break;
      case 4:
         data->area_code = std::stoi(message.c_str());
         break;
      case 5:
         data->hornet_id = std::stoi(message.c_str());
         save_data_counter = 0;
         break;
   }
}

void parse_message(lora_data* data)
{
   string message;

   // read packet
   while (LoRa.available()) {
      char character = LoRa.read();
      
      // looking for data end key
      if (character == message_data_end)
         save_data(data, message);
      
      message += character;

      // looking for data start key
      if (character == message_data_start)
         message = "";
   }
}

void LoRaReceiver::start()
{
   if (!LoRa.begin(500E6)) {
      printf("Starting LoRa failed!\n");
   }

   printf("LoRa Started\n");   
}

bool LoRaReceiver::read(lora_data* data)
{
   int packet_size = LoRa.parsePacket();
   if (packet_size) {
      // received a packet
      printf("Received packet \n'");

      parse_message(data);

      return true;
   }
   return false;
}
