/*_________________CHANGE COMMENT BELOW__________________*/
#define MASTER
// #define SLAVE
// #define SLAVE_ID 2
// #define SLAVE_ID 3
/*_________________ DO NOT CHANGE BELOW__________________*/
#if defined(MASTER)
#warning "BUILDING MASTER!"
extern int master_main(int argc, char** argv);

#elif defined(SLAVE)
#if !defined(SLAVE_ID)
    #error No slave ID specified!
#endif
#warning "BUILDING SLAVE!"
extern int slave_main(int argc, char** argv);
#else
    #error No master or slave not specified!
#endif
/*___________________CODE BELOW__________________________*/

// Includes
#include <pico/stdlib.h>
#include "buttons.hpp"
#include "main.hpp"
#include "flash.hpp"

// Defines

// Prototypes

// objects (Add define objects with external reference in main.hpp for use in slave- and master.cpp)
/*___ Flash ___*/
Flash flash = Flash();

/*___ Monitor ___*/
#if defined(MASTER)
this_monitor_t thisMonitor = {{}, MASTER_MONITOR, 0};
#elif defined(SLAVE)
this_monitor_t thisMonitor = {{}, SLAVE_MONITOR, SLAVE_ID};
#endif

void btn1Callback();
void btn2Callback();

/*___ Buttons ___ */
Button button1(BUTTON1_PIN, nullptr);
Button button2(BUTTON2_PIN, nullptr);
Button button3(BUTTON3_PIN, nullptr);

int main(int argc, char** argv)
{        
    // TODO: remove below
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, true);
    button1.callback = &btn1Callback;
    button2.callback = &btn2Callback;

    // setup pico for serial printing. 
    // TODO: remove in final version
    stdio_init_all();
    stdio_flush();

    for(;;)
    {
    }

    /*___ GPS ___*/
    // TODO: Init GPS
    // TODO: get gps location
    //// Put latitude in thisMonitor.location.latitude
    //// Put longitude in thisMonitor.location.longitude
    /*__________Run master or slave main________*/
    #ifdef MASTER
    return master_main(argc, argv);
    #endif

    #ifdef SLAVE
    return slave_main(argc, argv);
    #endif
}


void switchLed()
{
    static bool status = false;
    status = (status) ? false : true;
    gpio_put(LED_PIN, status);
}

void blinkLed(int ms)
{
    switchLed();
    sleep_ms(ms);
    switchLed();
}


void btn1Callback()
{
    static int n = 1;
    lora_data mock_lora_data = {1, n++, 3, 4.4, 5.5};
    hornet_record_t mock_hornet_record = {FLASH_CHECKSUM, 0, time_us_64(), mock_lora_data};
    flash.insert_record(&mock_hornet_record);
}

void btn2Callback()
{
    flash.print_records();
}