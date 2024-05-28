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

void Flash::read_from_address(uint8_t address, uint8_t* data)
{
    // Read data from I2C and save it in pointer data
    i2c_read_blocking(I2C, READ_ADDRESS + address, data, PACKAGE_SIZE, false);
}

void Flash::write_to_address(uint8_t address, uint8_t* data)
{
    // Write data in pointer data to I2C
    i2c_write_blocking(I2C, WRITE_ADDRESS + address, data, PACKAGE_SIZE, false);
}
