#ifndef LORA_RECEIVER_H
#define LORA_RECEIVER_H
// .h file instead of a .hpp cause that didnt work for some reason
#include <string.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "LoRa-RP2040.h"

#include "LoRaData.hpp"

class LoRaReceiver 
{
public:
    /*! \brief Start LoRa receiver
    */
    void start();
    /*! \brief Read message from LoRa
    * \param data LoRaData struct holding return data
    */
    bool read(lora_data* data);

    // Add your public member functions here

private:
    // Add your private member variables and functions here
};

#endif // LORA_RECEIVER_H