#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/types.h"

#include "buttons.hpp"
#include "malloc.h"

int Button::buttonCounter = 0;
bool Button::isDebouncing = false;
bool Button::debounceTimerInit = false;
int Button::debouncePin = 0;

Button** Button::buttonCollection = (Button**) malloc(MAX_BUTTONS);
int* Button::pinCollection = (int *) malloc(MAX_BUTTONS);

void Button::debounceCallback(uint gpio, uint32_t events)
{
    // Disable button interrupts
    for (size_t i = 0; i < Button::buttonCounter; i++)
        gpio_set_irq_enabled (pinCollection[i], GPIO_IRQ_EDGE_FALL, false);

    // Store cause of interrupts
    Button::debouncePin = gpio;

    // Set next debounce callback time
    hardware_alarm_set_target(ALARM_NUMBER, (time_us_64() + DEBOUNCE_TIME_US));
}

void debounceTimerCallback(uint alarmNumber)
{
    for (size_t i = 0; i < Button::buttonCounter; i++)
    {
        gpio_set_irq_enabled (Button::pinCollection[i], GPIO_IRQ_EDGE_FALL, true);
        if (Button::pinCollection[i] == Button::debouncePin && gpio_get(Button::debouncePin) == 0)
        {
            Button::buttonCollection[i]->callback();
        }
    }

}

Button::Button(int pinNum, void (*buttonCallback)())
{
    if (Button::debounceTimerInit == false)
    {
        Button::debounceTimerInit = true;
        hardware_alarm_set_callback(ALARM_NUMBER, &debounceTimerCallback);
    }

    // Init pin 
    gpio_init(pinNum);
    // Set callback on logic change falling
    gpio_set_irq_enabled_with_callback(pinNum, GPIO_IRQ_EDGE_FALL, true, Button::debounceCallback);
    // Set pin as input 
    gpio_set_dir(pinNum, 0);
    // Enable internal gpio pull-up
    gpio_set_pulls(pinNum, true, false);
    // Pull Pin high
    gpio_set_drive_strength(pinNum, GPIO_DRIVE_STRENGTH_2MA);


    // Save gpio pin to class
    this->pinNum = pinNum;

    // Set Button callback
    this->callback = buttonCallback;
    this->indexInList = this->buttonCounter;
    Button::buttonCollection[Button::buttonCounter] = this;
    Button::pinCollection[Button::buttonCounter] = pinNum;

    // Increase counter
    Button::buttonCounter++;
}

Button::~Button()
{
    // Free 
    free(Button::buttonCollection);
    free(Button::pinCollection);
}