#include "main.hpp"
#include "LoRaReceiver.h"
#include "LoRaData.hpp" 
#include "trilaterate.hpp"
#include "flash.hpp"
#include "master.hpp"
#include "hornet.hpp"

// Defines
#define MICRO_SECONDS 1000000 // micro seconds in seconds

// Prototypes
void master_button1_callBack();
void master_button2_callBack();
void master_button3_callBack();

void handle_hornet_data(lora_data* data);
void handle_hornet_data(int id);

bool is_trilateration_possible();

// Objects
/* Flash */
Flash flash = Flash();

/* LoRa */
LoRaReceiver receiver;
lora_data hornetDataBuffer;

/* trilaterate */
recordsInfoCollection recordsBuffer;

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
        // Receive hornet data
        if (receiver.read(&hornetDataBuffer))
        {
            printf("test123");
            stdio_flush();
            // handle_hornet_data(&hornetDataBuffer);
            // Use data struct to read data from LoRa
            printf("ID: %d, Hornet_ID: %d, area %d, long: %f, lat: %f\n", hornetDataBuffer.monitor_id, hornetDataBuffer.hornet_id, hornetDataBuffer.area_code, hornetDataBuffer.longitude, hornetDataBuffer.latitude);

        }
    }
    return 0;
}

void trilaterate_hornets()
{
    // Trilateration is possible with the records in the recordsBuffer
    coord_t trilaterationCoord; // object for trilateration result
    coord_t triangulationCoord; // object for triangulation result

    // Calculate distance from average time of monitor
    for (size_t i = 0; i < MONITOR_COUNT; i++)
    {
        recordsBuffer.record[i].r = time_to_distance(recordsBuffer.avgTime[i], recordsBuffer.area[i]);
    }

    if(!trilaterate(recordsBuffer.record[0], recordsBuffer.record[1], recordsBuffer.record[2], &trilaterationCoord, &triangulationCoord))
    {
        // Trilateration has failed
        return;
    }

    // printf("trilateration successfull!\n");
    // printf("trilateration coords are lat %f, lon %f\n", trilaterationCoord.lat, trilaterationCoord.lon);
    // stdio_flush();

}

// Determine if trilateration is possible. If possible set record into recordBuffer
bool is_trilateration_possible()
{
    // reset buffers and variables
    recordsBuffer.emptyBuffers();
    
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
                
                // Store monitor position and area in recordsbuffer
                recordsBuffer.monitorPos[monitorNum] = {hornetReferenceCopy[i]->data.latitude, hornetReferenceCopy[i]->data.longitude};
                recordsBuffer.area[monitorNum] = hornetReferenceCopy[i]->data.area_code;

                // Remove used records from array
                hornetReferenceCopy[i] = nullptr;
                hornetReferenceCopy[x] = nullptr;

                if (recordsBuffer.avgTime[monitorNum] == 0) // If first record in buffer, the average cannot be calculated
                {
                    recordsBuffer.avgTime[monitorNum] = timeDifference; 
                }
                else
                {
                    recordsBuffer.avgTime[monitorNum] = (recordsBuffer.avgTime[monitorNum] + timeDifference) / 2;
                    
                }
            }
        }
        
    }

    // Check if trilateration is possible
    for (size_t i = 0; i < MONITOR_COUNT; i++)
    {
        // If no average for monitor then return false
        if (recordsBuffer.avgTime[i] == 0) 
        {
            return false;
        }
    }

    return true;
}

void handle_hornet_data(lora_data* data)
{
    // Create record
    hornet_record_t thisRecord = { RECORD_CHECKSUM, flash.flashInfo->bootNumber, time_us_64(), *data };

    // write record to flash
    flash.insert_record(&thisRecord);

    // Check if trilateration is possible
    if(is_trilateration_possible())
    {
        // Trilateration is possible. Records and relevant info is stored in recordsBuffer. Trilaterate!
        trilaterate_hornets();
    }
}


// Handle hornet signal when signal comes from master. Not recieved from slave.
// Create record and use handler for slave
void handle_hornet_data(int hornetID)
{
    lora_data data = {thisMonitor.id, (uint8_t) hornetID, thisMonitor.area, thisMonitor.location.longitude, thisMonitor.location.latitude};

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
