// Do not change this file
// Work in master/master.cpp and slave/slave.cpp as if this that the main file

/*----------------CHANGE COMMENT BELOW------------------*/

#define MASTER
// #define SLAVE

/*----------------DO NOT CHANGE BELOW-------------------*/

#ifdef MASTER
#warning "BUILDING MASTER!"
extern int master_main(int argc, char** argv);
#endif

#ifdef SLAVE
#warning "BUILDING SLAVE!"
extern int slave_main(int argc, char** argv);
#endif

#include "pico/stdlib.h"

int main(int argc, char** argv)
{
    stdio_init_all();

    /*__________Run master or slave main________*/
    #ifdef MASTER
    return master_main(argc, argv);
    #endif

    #ifdef SLAVE
    return slave_main(argc, argv);
    #endif
}
