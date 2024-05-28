// Buttons.hpp provides a class for using buttons on the gpio
// Buttons are debounced and scalable
// Create Button instance Button(int pinNum, void (*buttonCallback)())
// Callbacks are run at butten press

#ifndef BUTTONS_HPP
#define BUTTONS_HPP

#include <stdio.h>
#include "hardware/timer.h"

#define MAX_BUTTONS 10
#define ALARM_NUMBER 2

// Debounce time in micro seconds
#define DEBOUNCE_TIME_US 40000

class Button 
{
public:
    static bool debounce_timer_init;
    static int debounce_pin;

    static Button** button_collection;
    static int* pin_collection;
    static int button_counter;
    static void debounce_callback(uint gpio, uint32_t events);

    int pin_num;
    void (*callback)();
    int index_in_list;
    Button(int pinNum, void (*buttonCallback)());
    ~Button();
};

void debounce_timer_callback(uint alarmNumber);

#endif // BUTTONS_HPP