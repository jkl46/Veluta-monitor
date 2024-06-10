#include "flash.hpp"
#include "main.hpp"

#include <hardware/gpio.h>
#include <stdlib.h>

Flash::Flash()
{
    this->flashInfo = (flash_info_t*) READ_FLASH_INFO_ADRESS;

    // If invalid flash info
    if (this->flashInfo->checksum != FLASH_CHECKSUM)
    {
        // blinkLed(100);
        // Create new flash Info
        flash_info_t newFlashInfo;
        newFlashInfo.checksum = FLASH_CHECKSUM;
        newFlashInfo.bootNumber = 0;
        
        // Erase flash info region
        flash_range_erase(WRITE_FLASH_INFO_ADRESS, RECORD_OFFSET);
        // Program flash info region
        write_flash_page((uint8_t*) &newFlashInfo, (uint8_t) sizeof(flash_info_t), WRITE_FLASH_INFO_ADRESS);

        // Erase record region
        flash_range_erase(WRITE_RECORDS_ADRESS, ((FLASH_PAGE_SIZE * RECORD_MAX) + (FLASH_SECTOR_SIZE % (FLASH_PAGE_SIZE *RECORD_MAX))));
    }

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
    int availableReferenceIndex = 0;
    while(this->hornetRecordReference[availableReferenceIndex] != nullptr && availableReferenceIndex < RECORD_MAX)
        availableReferenceIndex++;

    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        hornet_record_t* thisRecord_ptr = (hornet_record_t*) (READ_RECORDS_ADRESS + (FLASH_PAGE_SIZE * i));
        if (thisRecord_ptr->checksum != RECORD_CHECKSUM)
        {
            
            write_flash_page((uint8_t*) record, sizeof(hornet_record_t), WRITE_RECORDS_ADRESS + (FLASH_PAGE_SIZE * i)); 
            
            this->hornetRecordReference[availableReferenceIndex] = thisRecord_ptr;
            return 1;
        }
    }

    return 0;
}



void Flash::print_records()
{
    // int n = 0;
    // printf("Hornet reference!");
    // for (size_t x = 0; x < RECORD_MAX; x++)
    // {
    //     if (this->hornetRecordReference[x] != nullptr)
    //     {
    //         printf("%p ", this->hornetRecordReference[x]);
    //     } else
    //     {
    //         printf("EMPTY ");
    //     }
    // }
    int n = 0;
    char printBuff[20];
    for (size_t i = 0; i < RECORD_MAX; i++)
    {
        // If valid record at adress
        if (this->hornetRecordReference[i] != nullptr)
        {
            hornet_record_t* thisRecord_ptr = this->hornetRecordReference[i];
            printf("%llu", 0x12345678);
            stdio_flush();
        }
    }
    
    // }
    // printf("\n");
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

    printf("WRITTEN PAGE!");
    stdio_flush();
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
