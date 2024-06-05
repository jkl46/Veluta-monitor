#include "main.hpp"
#include "LoRaReceiver.h"
#include "LoRaData.hpp" 
#include "trilaterate.hpp"

// Defines

// Prototypes
void master_button1_callBack();
void master_button2_callBack();
void master_button3_callBack();

void handle_hornet_data(lora_data* data);
void handle_hornet_data(int id);

// 2 bij 3 lijst hornet records pointers in flash of eeprom.
void trilaterate_hornets(/*hornet records from eeprom*/); // TODO: can do after object of hornet in eeprom is known

// Objects
LoRaReceiver receiver;

int master_main(int argc, char** argv)
{
    // Init LoRa
    receiver.start();

    // Attach button callbacks for master
    button1.callback = &master_button1_callBack;
    button2.callback = &master_button2_callBack;
    button3.callback = &master_button3_callBack;

    while(1)
    {
        // Receice hornet data.
        // 
    }
    return 0;
}

void trilaterate_hornets(/* 2d array of 3 hornets' first and second arrival*/)
{
    coord_t trilaterationCoord; // object for trilateration result
    coord_t triangulationCoord; // object for triangulation result
    double flightTimes[3];

    
    // calculate flight time in seconds for hornets. use formula for appropriate area
    // double distance = formula(time1 - time2 / pow(10, 6))
    //..
    //..

    record_t r1; // = {{lat, lon}, distance};
    record_t r2; // = {{lat, lon}, distance};
    record_t r3; // = {{lat, lon}, distance};

    if(trilaterate(r1, r2, r3, &trilaterationCoord, &triangulationCoord) == -1 )
    {
        // TODO: What if trilateration fails?
    }

    // TODO: Send trilateration coordinate to thing network along with some other shit
}

void handle_hornet_data(lora_data* data)
{
    uint64_t timeOfSignal = time_us_64();

    // TODO: Create record that includes time and write this to flash.

    // TODO: check if enough records are saved in flash for trilateration.
    // if (trilateration possible)
    // trilaterate_hornets;
}

// Handle hornet signal when signal comes from master. Not recieved from slave.
// Create record and use handler for slave
void handle_hornet_data(int hornetID)
{
    lora_data data = {
        0, // Master has no ID
        hornetID,
        thisMonitor.location.longitude,
        thisMonitor.location.latitude,
    };

    handle_hornet_data(&data);
}


void button1_callBack()
{
    handle_hornet_data(1);
}

void button2_callBack()
{
    handle_hornet_data(2);
}

void button3_callBack()
{
    handle_hornet_data(3);
}
