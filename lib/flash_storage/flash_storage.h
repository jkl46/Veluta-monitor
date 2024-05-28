#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define I2C i2c0
#define HUNDRED_KHZ (100 * 1000)

#define PACKAGE_SIZE (8)
#define WRITE_ADDRESS (0x50)
#define READ_ADDRESS (0x50)


class Flash
{
public:
    Flash(void);

    /*! \brief Attempt to read from EEPROM 24LC04B at address
    * \param address Address to data in EEPROM
     *              (Between 0x00 and 0x0F)
    * \return Pointer to data at address 
    *      (default 0x00)
    */
    void read_from_address(uint8_t address, uint8_t* data);

    /*! \brief Attempt to write to EEPROM 24LC04B at address
    * \param address Address to data in EEPROM
    *              (Between 0x00 and 0x0F)
    * \param data Pointer to data to be written to EEPROM
    *              (Max 128 bytes)
    */
    void write_to_address(uint8_t address, uint8_t* data);
};

#endif
