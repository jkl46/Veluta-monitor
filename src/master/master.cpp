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
            // A lora_data struct has been recieved from lora. This is stored in hornetDataBuffer.
            handle_hornet_data(&hornetDataBuffer);
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
        // Trilateration has failed. This is likely because the radii do not intersect and cannot trilaterate. 
        // TODO: Handle fail case

        return;
    }

    // At this point trilateration is successful
    // Trilateration coordinate is present in coord_t trilaterationCoord
    // Trilangulation coordinate is present in triangulationCoord
    // TODO: Handle successful trilateration case.

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

                // If first record in buffer, the average cannot be calculated
                if (recordsBuffer.avgTime[monitorNum] == 0) 
                    recordsBuffer.avgTime[monitorNum] = timeDifference; 
                else
                    recordsBuffer.avgTime[monitorNum] = (recordsBuffer.avgTime[monitorNum] + timeDifference) / 2;
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
// Overwrite received GPS coordinates. Automatic setting of GPS location does not work.
// Overwrite with switch case like so
/* 
     switch (data->monitor_id)
    {
    case MONITOR_MASTER_ID: // MASTER
        data->latitude = 51.62366434625694;
        data->longitude = 5.190373872939375;
        break;

    case MONITOR_SLAVE1_ID: // SLAVE 1
        data->latitude = 51.62308845289566;
        data->longitude = 5.184577788820217;
        break;
    case MONITOR_SLAVE2_ID: // SLAVE 2
        data->latitude = 51.6194000526858;
        data->longitude = 5.189355326923746;
        break;

    default:
        break;
    }
*/

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


// construct struct
recordsInfoCollection::recordsInfoCollection()
{
	// Connect records with monitors
	for (size_t i = 0; i < MONITOR_COUNT; i++)
	{
		this->record[i].pos = (this->monitorPos+i);
	}
		
}

// Reset struct members
void recordsInfoCollection::emptyBuffers()
{
    for (size_t i = 0; i < MONITOR_COUNT; i++)
    {
        this->avgTime[i] = 0;
        this->monitorPos[i] = {0,0};
        this->record[i].r = 0;
        this->area[i] = 0;
    }
}
