/*_________________CHANGE COMMENT BELOW__________________*/
#define MASTER
// #define SLAVE
// #define SLAVE_ID 1
// #define SLAVE_ID 2

// Choose area. This can be one of: COUNTRY, URBAN CITY
#define MONITOR_AREA COUNTRY

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
#include "hornet.hpp"

// Defines
// Prototypes

// objects (Add define objects with external reference in main.hpp for use in slave- and master.cpp)
/*___ Monitor ___*/
#if defined(MASTER)
this_monitor_t thisMonitor = {{}, MASTER_MONITOR, 0, MONITOR_AREA};
#elif defined(SLAVE)
this_monitor_t thisMonitor = {{}, SLAVE_MONITOR, SLAVE_ID, MONITOR_AREA};
#endif

/*___ Buttons ___ */
Button button1(BUTTON1_PIN, nullptr);
Button button2(BUTTON2_PIN, nullptr);
Button button3(BUTTON3_PIN, nullptr);

int main(int argc, char** argv)
{        
    /*___ GPS ___*/ /* Currently not functional, please look in release rapport and or README.md for setting the monitor ID by hand. */
    // TODO: Init GPS
    // TODO: get gps location
    // TODO: Store latitude in thisMonitor.latitude. (this must be a double)
    // TODO: Store longitude in thisMonitor.longitude. (this must be a double)

    /*__________Run master or slave main________*/
    #ifdef MASTER
    return master_main(argc, argv);
    #endif

    #ifdef SLAVE
    return slave_main(argc, argv);
    #endif
}
