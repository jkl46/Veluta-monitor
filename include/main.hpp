#ifndef MAIN_HPP
#define MAIN_HPP

#include "buttons.hpp"

#define BUTTON1_PIN 11
#define BUTTON2_PIN 14
#define BUTTON3_PIN 15

#define LED_PIN 25

enum monitor_type {SLAVE_MONITOR, MASTER_MONITOR};

typedef struct {
    struct location {
        double latitude;
        double longitude;
    } location;
    monitor_type type;
    int id;
} this_monitor_t;

// Object reference for Slave and master main
extern this_monitor_t thisMonitor;

extern Button button1;
extern Button button2;
extern Button button3;

void switchLed();
void blinkLed(int ms);

#endif // MAIN_HPP