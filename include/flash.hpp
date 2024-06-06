#ifndef FLASH_HPP
#define FLASH_HPP

#include <stdio.h>
#include <hardware/flash.h>
#include <hardware/address_mapped.h>

#define FLASH_TARGET_OFFSET (256 * 1024)                                    // Base of flash
#define WRITE_CHECKSUM_ADRESS (FLASH_TARGET_OFFSET)                           // Adress where flash status is stored
#define WRITE_RECORDS_ADRESS (FLASH_TARGET_OFFSET + 4096)       // Adress where hornet records are stored

#define READ_TARGET_ADRESS   (uint8_t*)(XIP_BASE + FLASH_TARGET_OFFSET)
#define READ_CHECKSUM_ADRESS (uint8_t*)(XIP_BASE + WRITE_CHECKSUM_ADRESS)
#define READ_RECORDS_ADRESS  (uint8_t*)(XIP_BASE + WRITE_RECORDS_ADRESS)

#define RECORD_MAX 100


typedef struct {
    uint64_t timeOfCreation; 

    // This value stores the times the monitor is restarted. 
    // Records form different boots can't be used for finding time.
    // Because time is relative to monitor startup
    uint16_t bootCount;       
} hornet_record_t;

class Flash
{
private:
    uint16_t checksum;

public:
    Flash();

    int recordsInFlash();
    void writeRecord();
    void removeRecord();
};


#endif // FLASH_HPP