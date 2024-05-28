#include "flash_storage.h"

Flash::Flash(void)
{
    // init I2C
    i2c_init(I2C, HUNDRED_KHZ);

    // Set GPIO functions
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    // Set GPIO pullup
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // Enable I2C on GPIO
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
}

uint8_t* parse_address(uint8_t address, uint8_t* data)
{
    // Create new package with starting byte as address
    uint8_t* package = new uint8_t[PACKAGE_SIZE + ADDRESS_BUFFER];
    package[0] = address;
    for (uint8_t count = 1; count < PACKAGE_SIZE + ADDRESS_BUFFER; count++)
        package[count] = data[count - 1];
    return package;
}

void Flash::read_from_address(uint8_t address, uint8_t* data)
{
    // Set reading address in EEPROM
    i2c_write_blocking(I2C, READ_ADDRESS, &address, 1, true);
    // Read data from I2C and save it in pointer data
    i2c_read_blocking(I2C, READ_ADDRESS, data, PACKAGE_SIZE, false);
}

void Flash::write_to_address(uint8_t address, uint8_t* data)
{
    // Parse data into package with address
    uint8_t* package = parse_address(address, data);
    // Write data in pointer data to I2C
    i2c_write_blocking(I2C, WRITE_ADDRESS, package, PACKAGE_SIZE + ADDRESS_BUFFER, false);
    // Delete package after use
    delete[] package;
}
