/*_________________CHANGE COMMENT BELOW__________________*/
// #define MASTER
#define SLAVE
#define SLAVE_ID 1
// #define SLAVE_ID 2
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

// Defines

// Prototypes

// objects (Add define objects with external reference in main.hpp for use in slave- and master.cpp)
/*___ Monitor ___*/
this_monitor_t thisMonitor;

/*___ Buttons ___ */
Button button1(BUTTON1_PIN, nullptr);
Button button2(BUTTON2_PIN, nullptr);
Button button3(BUTTON3_PIN, nullptr);

int main(int argc, char** argv)
{
    // setup pico for serial printing. 
    // TODO: remove in final version
    stdio_init_all();

    // Set monitor type
    #ifdef MASTER
    thisMonitor.type = MASTER_MONITOR;
    #else
    thisMonitor.type = SLAVE_MONITOR;
    thisMonitor.id = SLAVE_ID;
    #endif

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