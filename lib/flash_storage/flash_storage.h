#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define I2C i2c0
#define HUNDRED_KHZ (100 * 1000)

#define PACKAGE_SIZE (16)
#define WRITE_ADDRESS (0x50)
#define READ_ADDRESS (0x50)
#define ADDRESS_BUFFER (1)

class Flash
{
public:
    Flash(void);

    /*! \brief Attempt to read from EEPROM 24LC04B at address.
    *       Data will need to be empty on call
    * \param address Address to data in EEPROM
    *              (Between 0x00 and 0xFF)
    * \return Pointer to data at address
    */
    void read_from_address(uint8_t address, uint8_t* data);

    /*! \brief Attempt to write to EEPROM 24LC04B at address
    *       Data will be deleted after completion
    * \param address Address to data in EEPROM
    *              (Between 0x00 and 0xFF)
    * \param data Pointer to data to be written to EEPROM
    *              (Max 15 bytes, rest is trown away)
    */
    void write_to_address(uint8_t address, uint8_t* data);
};

#endif
