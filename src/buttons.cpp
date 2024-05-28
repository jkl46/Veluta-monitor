#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/types.h"

#include "buttons.hpp"
#include "malloc.h"

int Button::button_counter = 0;
bool Button::debounce_timer_init = false;
int Button::debounce_pin = 0;

Button** Button::button_collection = (Button**) malloc(MAX_BUTTONS);
int* Button::pin_collection = (int *) malloc(MAX_BUTTONS);

void Button::debounce_callback(uint gpio, uint32_t events)
{
    // Disable button interrupts
    for (size_t i = 0; i < Button::button_counter; i++)
        gpio_set_irq_enabled (pin_collection[i], GPIO_IRQ_EDGE_FALL, false);

    // Store cause of interrupts
    Button::debounce_pin = gpio;

    // Set next debounce callback time
    hardware_alarm_set_target(ALARM_NUMBER, (time_us_64() + DEBOUNCE_TIME_US));
}

void debounce_timer_callback(uint alarmNumber)
{
    for (size_t i = 0; i < Button::button_counter; i++)
    {
        gpio_set_irq_enabled (Button::pin_collection[i], GPIO_IRQ_EDGE_FALL, true);
        if (Button::pin_collection[i] == Button::debounce_pin && gpio_get(Button::debounce_pin) == 0)
        {
            Button::button_collection[i]->callback();
        }
    }

}

Button::Button(int pin_num, void (*buttonCallback)())
{
    if (Button::debounce_timer_init == false)
    {
        Button::debounce_timer_init = true;
        hardware_alarm_set_callback(ALARM_NUMBER, &debounce_timer_callback);
    }

    // Init pin 
    gpio_init(pin_num);
    // Set callback on logic change falling
    gpio_set_irq_enabled_with_callback(pin_num, GPIO_IRQ_EDGE_FALL, true, Button::debounce_callback);
    // Set pin as input 
    gpio_set_dir(pin_num, 0);
    // Enable internal gpio pull-up
    gpio_set_pulls(pin_num, true, false);
    // Pull Pin high
    gpio_set_drive_strength(pin_num, GPIO_DRIVE_STRENGTH_2MA);


    // Save gpio pin to class
    this->pin_num = pin_num;

    // Set Button callback
    this->callback = buttonCallback;
    this->index_in_list = this->button_counter;
    Button::button_collection[Button::button_counter] = this;
    Button::pin_collection[Button::button_counter] = pin_num;

    // Increase counter
    Button::button_counter++;
}

Button::~Button()
{
    // Free 
    free(Button::button_collection);
    free(Button::pin_collection);
}