#include "gps.hpp"


void gps::init_gps() {
    uart_init(uart1, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); 
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); 
    uart_set_hw_flow(uart1, false, false); 
    uart_set_format(uart1, UART_data_bits, UART_stop_bits, UART_PARITY_NONE);    
}

std::vector<char> gps::read_gps() {
    std::vector<char> gps_data;
    bool end_of_sentence = false;

    while (uart_is_readable(uart1) && !end_of_sentence) {
        char ch = uart_getc(uart1);
        gps_data.push_back(ch);
        if (ch == '\n') {
            end_of_sentence = true;
            break;
        }
    }

    if (!end_of_sentence) {
        gps_data.clear();
    }

    return gps_data;
}

Coordinates gps::send_gps(std::vector<char> gps_data) {
    char gps_array[MAX_ARRAY_SIZE];
    Coordinates coordinates;
    coordinates.longitude = 0.0; // Initialize longitude
    coordinates.latitude = 0.0; // Initialize latitude

    for (size_t i = 0; i < gps_data.size(); i++) {
        gps_array[i] = gps_data[i];
    }
    gps_array[gps_data.size()] = '\0';  // Ensure null termination

    char *token = strtok(gps_array, ",");
    int count = 0;

    while (token != NULL) {
        if (count == 3) {
            coordinates.latitude = atof(token);
        } else if (count == 4) {
            coordinates.longitude = atof(token);
        }
        token = strtok(NULL, ",");
        count++;
    }
    return coordinates;
}

double gps::recieve_lon(){
    Coordinates coordinates;
    return coordinates.longitude;
}

double gps::recieve_lat(){
    Coordinates coordinates;
    return coordinates.latitude;
}