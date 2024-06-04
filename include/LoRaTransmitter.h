#ifndef LORA_TRANSMITTER_H
#define LORA_TRANSMITTER_H

// Include any necessary libraries here
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "LoRa-RP2040.h"

#include "LoRaData.hpp"

class LoRaTransmitter 
{
public:
    // Constructor and destructor (if needed)

    // Add any necessary member functions here
    /*! \brief Initialize LoRa transmit
    */
    void start();
    /*! \brief Send data over LoRa
    * \param data LoRaData struct to be send over LoRa to another monitor
    */
    void send(lora_data* data);
private:
    // Add any necessary member variables here

};

#endif // LORA_TRANSMITTER_H