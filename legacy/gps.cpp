#include "gps.hpp"
#define UART_data_bits 8
#define UART_stop_bits 1

void init_UART(uart_inst_t *UART_ID, uint UART_TX_PIN, uint UART_RX_PIN, uint BAUDRATE) 
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

std::vector<char> read_UART(uart_inst_t *UART_ID)
{
    /*
    this function reads the UART data and stores it in a vector
    the function reads the UART data until it reaches the stop character #
    the function gps_data.push_back(ch) puts the character in the vector
    */
    const char stop_char = '#';
    std::vector<char> gps_data;
    int index = 0;
    while (uart_is_readable(UART_ID) && gps_data[index-1] != stop_char)
    {
        char ch = uart_getc(UART_ID);
        gps_data.push_back(ch);
        index++;
    }
    return gps_data;
}

Coordinates gps::send_gps(std::vector<char> gps_data) {
    /*
    this function first converts the vector to an array
    it puts a null character at the end of the array to make sure 
    the program knows where the array ends, and that it wil not crash.
    then it tokenizes the array to extract the latitude and longitude

    it does this by using strtok to tokenize the array
    this function works by counting the number of commas 
    in the array and divides the array into tokens(segments).

    if the count is 2, the token is the latitude
    if the count is 4, the token is the longitude

    the function then converts the tokens to double and stores them in a struct Coordinates
    */
    char gps_array[MAX_ARRAY_SIZE];
    Coordinates coordinates;
    coordinates.longitude = 0.0;
    coordinates.latitude = 0.0;

    for (size_t i = 0; i < gps_data.size(); i++) {
        gps_array[i] = gps_data[i];
    }

    gps_array[gps_data.size()] = '\0';

    char *token = strtok(gps_array, ",");
    int count = 0;

    while (token != NULL) {
        if (count == 2) {
            coordinates.latitude = atof(token);
        } else if (count == 4) {
            coordinates.longitude = atof(token);
        }
        token = strtok(NULL, ",");
        count++;
    }

    this->latitude = coordinates.latitude;
    this->longitude = coordinates.longitude; 

    return coordinates;
}

/*
these functions return the latitude and longitude of the gps.
this is for easy acces to the latitude and longitude of the gps
*/

double gps::recieve_lon(){
    return this->longitude;
}

double gps::recieve_lat(){
    return this->latitude;
}
