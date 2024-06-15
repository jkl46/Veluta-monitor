#include "flash.hpp"
#include "main.hpp"

#include <hardware/gpio.h>
#include <stdlib.h>

Flash::Flash()
{
    this->flashInfo = (flash_info_t*) READ_FLASH_INFO_ADRESS;

    // Create new flashInfo
    flash_info_t newFlashInfo = {FLASH_CHECKSUM};

    // If invalid flash info
    if (this->flashInfo->checksum != FLASH_CHECKSUM)
    {
        // Create new flash Info
        flash_info_t newFlashInfo;
        newFlashInfo.bootNumber = 0;

        // Erase record region
        flash_range_erase(WRITE_RECORDS_ADRESS, ((FLASH_PAGE_SIZE * RECORD_MAX) + (FLASH_SECTOR_SIZE % (FLASH_PAGE_SIZE *RECORD_MAX))));
    } 
    else
    {
        // Increase boot number
        newFlashInfo.bootNumber = this->flashInfo->bootNumber + 1;
    }
    // Erase flash info region
    flash_range_erase(WRITE_FLASH_INFO_ADRESS, RECORD_OFFSET);
    // Program flash info region
    write_flash_page((uint8_t*) &newFlashInfo, (uint8_t) sizeof(flash_info_t), WRITE_FLASH_INFO_ADRESS);

    // Read record region
    int n = 0;
    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        hornet_record_t* thisRecord_ptr = (hornet_record_t*) (READ_RECORDS_ADRESS + (FLASH_PAGE_SIZE * i));

        // If valid record at adress
        if (thisRecord_ptr->checksum == RECORD_CHECKSUM)
        {
            // Sequentially reference adress in flash reference array
            this->hornetRecordReference[n++] = thisRecord_ptr;
        }
    }

    // Fill left over space with nullptr
    for(; n < RECORD_MAX; n++)
        this->hornetRecordReference[n] = nullptr;
    return;
}


int Flash::insert_record(hornet_record_t* record)
{
    int recordIndex = 0;
    // Get first available space in flash.recordRefrence
    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        if (this->hornetRecordReference[i] == nullptr)
        {
            recordIndex = i;
            break;
        }
    }
    
    // Get first abailable space in flash region. Write record to this sapce
    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        hornet_record_t* thisRecord_ptr = (hornet_record_t*) (READ_RECORDS_ADRESS + (FLASH_PAGE_SIZE * i));
        if (thisRecord_ptr->checksum != RECORD_CHECKSUM)
        {

            write_flash_page((uint8_t*) record, sizeof(hornet_record_t), WRITE_RECORDS_ADRESS + (FLASH_PAGE_SIZE * i)); 
            
            this->hornetRecordReference[recordIndex] = thisRecord_ptr;
            return 1;
        }
    }
    return 0;
}

void Flash::remove_record(uint32_t recordAdress)
{
    uint8_t flashCopy[FLASH_SECTOR_SIZE]; 
    uint32_t sectorStartAdress = recordAdress - (recordAdress % FLASH_SECTOR_SIZE);

    // copy flash sector where record is present.
    uint32_t readAddres;
    for (size_t i = 0; i < FLASH_SECTOR_SIZE; i++)
    {
        readAddres = sectorStartAdress + i; 

        // Copy flash
        flashCopy[i] = *((uint8_t*)readAddres);
        
        // Set content to 0xFF if byte in record region
        if (readAddres >= recordAdress && readAddres < (recordAdress + FLASH_SECTOR_SIZE))
        {
            flashCopy[i] = 0xFF;
        }
    }
    
    // Disable interrupts
    uint32_t interrupts = save_and_disable_interrupts();

    // Erase flash
    flash_range_erase(sectorStartAdress, FLASH_SECTOR_SIZE);

    // Write flash
    flash_range_program((sectorStartAdress - XIP_BASE), flashCopy, FLASH_PAGE_SIZE);

    // Reenable interrupts
    restore_interrupts(interrupts);
    // Erase flash
}

void write_flash_page(uint8_t* src, uint8_t sizeOfSource, uint32_t dest)
{
    uint8_t page[FLASH_PAGE_SIZE];
    int i = 0;
    for (; i < FLASH_PAGE_SIZE; i++)
    {
        if(i < sizeOfSource)
        {
            page[i] = src[i];
        }
        else
        {
            page[i] = 0xFF;
        }
    }
    // Disable interrupts when writing to flash
    uint32_t interrupts = save_and_disable_interrupts();

    // Write flash
    flash_range_program(dest, page, FLASH_PAGE_SIZE);

    // Reenable interrupts
    restore_interrupts(interrupts);
}


void Flash::print_record_references()
{
    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        if (this->hornetRecordReference[i] != nullptr)
        {
            printf("Index: %d, addr: %p\n", i, this->hornetRecordReference[i]);
        }
    }
    
}

void reverse_copy_bytes(uint8_t* src, uint8_t* dest, int len)
{
    for (size_t i = 0; i < len; i++)
        dest[i] = src[len-i];
}

void copy_bytes(uint8_t* src, uint8_t* dest, int len)
{
    for (size_t i = 0; i < len; i++)
        dest[i] = src[i];
    
}

void print_record(hornet_record_t* thisRecord_ptr)
{
	printf("boot number: %d\nat ticks after boot: %llu\nHornet DATA:\nMonitor ID:%d\nHornet ID:%d\nArea code: %d\nlatitude: %lf\nLongitude: %lf\n", 
	    thisRecord_ptr->bootNumber,
	    thisRecord_ptr->timeOfCreation,
	    thisRecord_ptr->data.monitor_id,
	    thisRecord_ptr->data.hornet_id,
	    thisRecord_ptr->data.area_code,
	    thisRecord_ptr->data.latitude,
	    thisRecord_ptr->data.longitude
	    );
    stdio_flush();
}

void print_buf(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
    stdio_flush();
}


