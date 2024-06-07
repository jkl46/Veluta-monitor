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

    while (uart_is_readable(uart1)) {
        char ch = uart_getc(uart1);;
        gps_data.push_back(ch);
        if (ch == '*') {
            break;
        }
    }

    return gps_data;
}

Coordinates gps::send_gps(std::vector<char> gps_data) {
    char gps_array[MAX_ARRAY_SIZE];
    Coordinates coordinates;
    coordinates.longitude = 0.0; // Initialize longitude
    coordinates.latitude = 0.0; // Initialize latitude
    for (size_t i = 0; i < gps_data.max_size(); i++) {
        printf("%c", gps_data[i]);
        printf("\n");
    }

    for (size_t i = 0; i < gps_data.size(); i++) {
        gps_array[i] = gps_data[i];
    }

    gps_array[gps_data.size()] = '\0';  // Ensure null termination

    char *token = strtok(gps_array, ",");
    int count = 0;

    while (token != NULL) {
        if (count == 2) {
            coordinates.latitude = atof(token);
            // printf("Latitude: %f\n", coordinates.latitude);
        } else if (count == 4) {
            coordinates.longitude = atof(token);
        }
        token = strtok(NULL, ",");
        count++;
    }

    this->latitude = coordinates.latitude; // Update class members
    this->longitude = coordinates.longitude; // Update class members

    return coordinates;
}

double gps::recieve_lon(){
    return this->longitude;
}

double gps::recieve_lat(){
    return this->latitude;
}
