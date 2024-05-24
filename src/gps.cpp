
#include "gps.hpp"
#define UART_data_bits 8
#define UART_stop_bits 1

void init_UART(uart_inst_t *UART_ID, uint UART_TX_PIN, uint UART_RX_PIN, uint BAUDRATE) // Initialize UART
{
    /*
    uart_init = Set UART baudrate
    gpio_set_function = set pin for UART function
    uart_set_hw_flow = Set UART flow control
    uart_set_format = Set UART format

    This function initializes the UART, 
    sets the baudrate, pin for UART function, flow control, and UART format
    */
    uart_init(UART_ID, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); 
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); 
    uart_set_hw_flow(UART_ID, false, false); 
    uart_set_format(UART_ID, UART_data_bits, UART_stop_bits, UART_PARITY_NONE); // Set UART format
}

char *read_UART(uart_inst_t *UART_ID) // Read data from UART
{
    /*
    const u_int8_t = Maximum size of the array of received data
    static char = Array to store received data
    return gps_data = Return received data

    This function reads data from the UART,
    and stores it in an array and returns the array

    */
    const u_int8_t array_size = 255; 
    static char gps_data[array_size]; 
    int index = 0;
    while (uart_is_readable(UART_ID) && index < array_size)
    {
        char ch = uart_getc(UART_ID);
        gps_data[index++] = ch;
    }
    gps_data[index] = '\0';
    return gps_data; 
}
