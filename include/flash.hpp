#ifndef FLASH_HPP
#define FLASH_HPP

#include <stdio.h>
#include <hardware/flash.h>
#include <hardware/address_mapped.h>
#include "LoRaData.hpp"

#define FLASH_TARGET_OFFSET (256 * 1024)                                    // Base of flash region

#define FLASH_INFO_OFFSET 0  // Must be multiple of 4KB
#define RECORD_OFFSET FLASH_SECTOR_SIZE

#define WRITE_FLASH_INFO_ADRESS (FLASH_TARGET_OFFSET + FLASH_INFO_OFFSET)       // Adress where flash info is stored
#define WRITE_RECORDS_ADRESS (FLASH_TARGET_OFFSET + RECORD_OFFSET)              // Adress where hornet records are stored

#define READ_TARGET_ADRESS   (uint8_t*)(XIP_BASE + FLASH_TARGET_OFFSET)
#define READ_FLASH_INFO_ADRESS (uint8_t*)(XIP_BASE + WRITE_FLASH_INFO_ADRESS)
#define READ_RECORDS_ADRESS  (uint8_t*)(XIP_BASE + WRITE_RECORDS_ADRESS)

#define FLASH_CHECKSUM (uint16_t) 0x2FA
#define RECORD_CHECKSUM FLASH_CHECKSUM

#define RECORD_MAX 100

typedef struct {
    uint16_t checksum;
    uint8_t bootNumber; // recorded at boot x
    uint64_t timeOfCreation; // Ticks after boot

    lora_data data;
} hornet_record_t;


typedef struct {
    uint16_t checksum;
    uint8_t bootNumber;
} flash_info_t; // Size of struct may not be greater than the record offset

class Flash
{

public:
    flash_info_t* flashInfo;
    hornet_record_t* hornetRecordReference[RECORD_MAX];

    Flash();
    int insert_record(hornet_record_t *record);
    void remove_record(int index);
    void print_record_references();
};

void write_flash_page(uint8_t* src, uint8_t sizeOfSource, uint32_t dest);
void print_buf(const uint8_t *buf, size_t len);
void print_record(hornet_record_t* recordPtr);
void reverse_copy_bytes(uint8_t* src, uint8_t* dest, int len);
void copy_bytes(uint8_t* src, uint8_t* dest, int len);

#endif // FLASH_HPP