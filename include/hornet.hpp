#ifndef HORNET_HPP
#define HORNET_HPP

#include "stdint.h"

#define COUNTRY 1
#define URBAN 2
#define CITY 3

#define COUNTRY_FORMULA(time) (1.56666 * (double) time) + 107
#define URBAN_FORMULA(time) (1.56666 * (double) time) - 17
#define CITY_FORMULA(time) (1.56666 * (double) time) - 27

double time_to_distance(uint32_t time, uint8_t area);

#endif // HORNET_HPP