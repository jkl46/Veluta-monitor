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
    static bool debounceTimerInit;
    static bool isDebouncing;
    static int debouncePin;

    static Button** buttonCollection;
    static int* pinCollection;
    static int buttonCounter;
    static void debounceCallback(uint gpio, uint32_t events);

    int pinNum;
    void (*callback)();
    int indexInList;
    Button(int pinNum, void (*buttonCallback)());
    ~Button();
};

void debounceTimerCallback(uint alarmNumber);

#endif // BUTTONS_HPP