#ifndef LORA_TRANSMITTER_H
#define LORA_TRANSMITTER_H

// Include any necessary libraries here
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "LoRa-RP2040.h"

class LoRaTransmitter {
public:
    // Constructor and destructor (if needed)

    // Add any necessary member functions here
    void start();
    void send(const char* data[2], uint8_t slave_id, uint8_t hornet_id);
private:
    // Add any necessary member variables here

};

#endif // LORA_TRANSMITTER_H