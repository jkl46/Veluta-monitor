#include "main.hpp"
#include "LoRaReceiver.h"
#include "LoRaData.hpp" 
#include "trilaterate.hpp"
#include "flash.hpp"

// Defines
#define MICRO_SECONDS 1000000 // micro seconds in seconds

// Prototypes
void master_button1_callBack();
void master_button2_callBack();
void master_button3_callBack();

void handle_hornet_data(lora_data* data);
void handle_hornet_data(int id);

void trilaterate_hornets(/*hornet records from eeprom (preferably in 2x3 list of record**) */); // TODO: can do after object of hornet in eeprom is known

// Objects
/* Flash */
Flash flash = Flash();

/* LoRa */
LoRaReceiver receiver;
lora_data hornetDataBuffer;

/* trilaterate */
record_t recordBuffer[MONITOR_COUNT];

int master_main(int argc, char** argv)
{
    // Init LoRa
    // receiver.start();

    // Attach button callbacks for master
    button1.callback = &master_button1_callBack;
    button2.callback = &master_button2_callBack;
    button3.callback = &master_button3_callBack;

    while(1)
    {
        // Receive hornet data
        if (receiver.read(&hornetDataBuffer))
        {
            handle_hornet_data(&hornetDataBuffer);

            // Use data struct to read data from LoRa
            printf("ID: %d, Hornet_ID: %d, long: %f, lat: %f\n", hornetDataBuffer.monitor_id, hornetDataBuffer.hornet_id, hornetDataBuffer.longitude, hornetDataBuffer.latitude);

        }
    }
    return 0;
}

void trilaterate_hornets(/* 2d array of 3 hornets' first and second arrival*/)
{
    coord_t trilaterationCoord; // object for trilateration result
    coord_t triangulationCoord; // object for triangulation result
    double flightTimes[3]; // store flight times

    // calculate flight time in seconds for hornets. use formula for appropriate area
    // double distance = formula(time1 - time2 / pow(10, 6))
    //..
    //..

    record_t r1; // = {{lat, lon}, distance};
    record_t r2; // = {{lat, lon}, distance};
    record_t r3; // = {{lat, lon}, distance};

    if(trilaterate(r1, r2, r3, &trilaterationCoord, &triangulationCoord) == -1)
    {
        // TODO: What if trilateration fails? maybe message to thing network?
        return;
    }

    // TODO: Send trilateration coordinate to thing network along with some other shit
}

// Determine if trilateration is possible. If possible set record into recordBuffer
bool is_trilateration_possible(record_t* recordBuffer)
{
    static coord_t monitorBuffer[MONITOR_COUNT];
    static uint32_t avgTimeBuffer[MONITOR_COUNT];

    // Empty average time array
    for (size_t i = 0; i < MONITOR_COUNT; i++)
        avgTimeBuffer[i] = 0;
    
    // create copy for record reference
    hornet_record_t* hornetReferenceCopy[RECORD_MAX];

    for (size_t i = 0; i < RECORD_MAX; i++)
        hornetReferenceCopy[i] = flash.hornetRecordReference[i];


    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        if (hornetReferenceCopy[i] == nullptr)
            continue;
        
        for (size_t x = i+1; x < RECORD_MAX; x++)
        {
            if (hornetReferenceCopy[x] == nullptr)
                continue;
            
            // If record from the same boot and monitor
            if (hornetReferenceCopy[i]->bootNumber == hornetReferenceCopy[x]->bootNumber && 
                hornetReferenceCopy[i]->data.monitor_id == hornetReferenceCopy[x]->data.monitor_id &&
                hornetReferenceCopy[i]->data.hornet_id == hornetReferenceCopy[x]->data.hornet_id)
            { 
                uint8_t monitorNum = hornetReferenceCopy[i]->data.monitor_id;

                // uint64_t - uint64_t seems to raise problems. Converting microseconds to seconds here.
                uint32_t timeDifference = (hornetReferenceCopy[x]->timeOfCreation / MICRO_SECONDS) - (hornetReferenceCopy[i]->timeOfCreation / MICRO_SECONDS);

                // Remove used records from array
                hornetReferenceCopy[i] = nullptr;
                hornetReferenceCopy[x] = nullptr;

                if (avgTimeBuffer[monitorNum] == 0) // If first record in buffer, the average cannot be calculated
                {
                    avgTimeBuffer[monitorNum] = timeDifference; 
                }
                else
                {
                    avgTimeBuffer[monitorNum] = (avgTimeBuffer[monitorNum] + timeDifference) / 2;
                }
            }
        }
        
    }

    // Check if trilateration is possible
    for (size_t i = 0; i < MONITOR_COUNT; i++)
    {
        // If no average for monitor then
        if (avgTimeBuffer[i] == 0) 
        {
            return false;
        }
    }
    
    printf("times: %d, %d, %d\n", avgTimeBuffer[0], avgTimeBuffer[1], avgTimeBuffer[2]);

    return true;
}

void handle_hornet_data(lora_data* data)
{
    // Create record
    hornet_record_t thisRecord = 
    {
        RECORD_CHECKSUM,
        flash.flashInfo->bootNumber,
        time_us_64(),
        *data
    };

    flash.insert_record(&thisRecord);

    if(!is_trilateration_possible())
    {
        return;
    }
    // Trilateration is possible

    coord_t trilaterationResult;

    // printf("times: %d, %d, %d\n", avgTimeBuffer[0], avgTimeBuffer[1], avgTimeBuffer[2]);
    // Trilateration is possible. Times are in avgTimeBuffer.

}


// Handle hornet signal when signal comes from master. Not recieved from slave.
// Create record and use handler for slave
void handle_hornet_data(int hornetID)
{
    lora_data data = {
        (uint16_t) hornetID, // Master has no ID
        (uint8_t) hornetID,
        (uint8_t) 1, 
        thisMonitor.location.longitude,
        thisMonitor.location.latitude,
    };

    handle_hornet_data(&data);
}


void master_button1_callBack()
{
    handle_hornet_data(0);
}

void master_button2_callBack()
{
    handle_hornet_data(1);
}

void master_button3_callBack()
{
    handle_hornet_data(2);
}
