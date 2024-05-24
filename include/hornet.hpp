#ifndef HORNET_HPP
#define HORNET_HPP

#define COUNTRY 1
#define URBAN 2
#define CITY 3

#define COUNTRY_FORMULA(time) 1.56666 * time + 107
#define URBAN_FORMULA(time) 1.56666 * time - 17
#define CITY_FORMULA(time) 1.56666 * time - 27

double time_to_distance(double time, int area);

#endif // HORNET_HPP