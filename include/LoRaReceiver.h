#ifndef LORA_RECEIVER_H
#define LORA_RECEIVER_H
// .h file instead of a .hpp cause that didnt work for some reason

#include <string.h>

class LoRaReceiver {
public:
    void start();
    void read();

    // Add your public member functions here

private:
    // Add your private member variables and functions here
};

#endif // LORA_RECEIVER_H