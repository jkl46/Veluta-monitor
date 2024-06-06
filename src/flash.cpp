#include "flash.hpp"
#include "main.hpp"

#include <hardware/gpio.h>

const uint16_t CHECKSUM = 0x1234;
const uint8_t *CHECKSUM_ARRAY = (uint8_t*) &CHECKSUM;

Flash::Flash()
{
    // get Checksum
    this->checksum = *((uint16_t*) READ_CHECKSUM_ADRESS);

    // If checksum not valid. format flash
    if (this->checksum != CHECKSUM)
    {
        // TODO: format flash sector
        flash_range_erase(WRITE_CHECKSUM_ADRESS, FLASH_SECTOR_SIZE);
        flash_range_program(WRITE_CHECKSUM_ADRESS, CHECKSUM_ARRAY, FLASH_PAGE_SIZE);

        // TODO: write flash
    }

    // TODO: 

    return;
}
