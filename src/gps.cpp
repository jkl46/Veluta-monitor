
#include "gps.hpp"


void sendPakket(char* data)
{
    printf("Sending packets: ");
    //send packet
    for (uint8_t counter = 0; counter < 5; counter++)
    {
        LoRa.beginPacket();
        LoRa.print("\n  ");
        LoRa.print(data);
        LoRa.endPacket();
        sleep_ms(1000);
    }
    printf("Packets sent\n");
    sleep_ms(5000);
}

void initUART(uart_inst_t *UART_ID, uint UART_TX_PIN, uint UART_RX_PIN, uint BAUDRATE)
{
    uart_init(UART_ID, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
}

void initLoRa()
{
    printf("Starting LoRa\n");

    if (!LoRa.begin(500E6))
    {
        printf("Starting LoRa failed!\n");
        while (1) // if lora failed start loop forever
            ;
    }
}

char *readUART(uart_inst_t *UART_ID)
{
    static char gps_data[256];
    int index = 0;
    while (uart_is_readable(UART_ID) && index < 255)
    {
        char ch = uart_getc(UART_ID);
        gps_data[index++] = ch;
    }
    gps_data[index] = '\0';
    return gps_data;
}
