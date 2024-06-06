/*________________CHANGE COMMENT BELOW__________________*/

//define MASTER
#define SLAVE

/*_______________________________________________________*/

#include <pico/stdlib.h>
#include "buttons.hpp"

#ifdef MASTER
#warning "BUILDING MASTER!"
extern int master_main(int argc, char** argv);
#endif

#ifdef SLAVE
#warning "BUILDING SLAVE!"
extern int slave_main(int argc, char** argv);
#endif

/*_____________Code Below_________________________________*/

// Prototypes
void button1Callback();
void button2Callback();
void button3Callback();

int main(int argc, char** argv)
{
    stdio_init_all();

    Button btn1 = Button(11, &button1Callback);
    Button btn2 = Button(14, &button2Callback);
    Button btn3 = Button(15, &button3Callback);
    
    /*__________Run master or slave main________*/
    #ifdef MASTER
    return master_main(argc, argv);
    #endif

    #ifdef SLAVE
    return slave_main(argc, argv);
    #endif
}


void button1Callback()
{
    printf("button1!\n");
}

void button2Callback()
{
    printf("button2!\n");
}

void button3Callback()
{
    printf("button3!\n");
}
