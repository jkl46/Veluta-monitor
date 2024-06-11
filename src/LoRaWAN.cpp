#include "LoRaWAN.h"

void LoRaWAN::initLoRaWAN(){
    uart_init(uart0, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); 
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); 
    uart_set_hw_flow(uart0, false, false); 

    uart_set_format(uart0, UART_data_bits, UART_stop_bits, UART_PARITY_NONE);

    uart_puts(uart0, "AT+JOIN");
}

void LoRaWAN::sendLoRaWAN(double latitude, double longitude, uint8_t area_code)
{
    std::string area_type;
    switch (area_code)
    {
    case 1:
        area_type = "Country";
        break;
    case 2:
        area_type = "Urban";
        break;
    case 3:
        area_type = "City";
        break;
    // Convert the variables to strings before concatenating
    std::string message = "AT+SEND=Hive: gps: Latitude: " + std::to_string(latitude) + ", Longitude: " + std::to_string(longitude) + ", Areatype: " + area_type + "\r\n";
    uart_puts(uart0, message.c_str()); // Use c_str() to convert the string to a const char*
}