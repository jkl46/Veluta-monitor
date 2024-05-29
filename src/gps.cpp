#include "gps.hpp"

void init_gps() 
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
    uart_set_format(UART_ID, UART_data_bits, UART_stop_bits, UART_PARITY_NONE);
}

char* read_gps() {
    /*
    uart_is_readable = Check if UART is readable
    uart_getc = Get a character from UART
    This function reads the GPS data from the UART and returns it as a string
    the while loop reads the data until it finds /n the end of the sentence
    */
    static char gps_data[MAX_ARRAY_SIZE];
    int index = 0;
    bool end_of_sentence = false;

    while (uart_is_readable(UART_ID)) {
        char ch = uart_getc(UART_ID);
        if (index < MAX_ARRAY_SIZE - 1) {
            gps_data[index++] = ch;
            if (ch == '\n') {
                end_of_sentence = true;
                break;
            }
        } else {
            index = 0;
        }
    }
    gps_data[index] = '\0';

    if (end_of_sentence) {
        return gps_data;
    } else {
        return NULL;
    }
}