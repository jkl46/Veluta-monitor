#include "hornet.hpp"

// Convert time in seconds to distance
double time_to_distance(uint32_t time, uint8_t area)
{
    double distance = -1;

    switch (area)
    {
    case COUNTRY:
        distance = (double) COUNTRY_FORMULA(time);
        break;
        
    case URBAN:
        distance = (double) URBAN_FORMULA(time);
        break;
    
    case CITY:
        distance = (double) CITY_FORMULA(time);
        break;

    default:
        break;
   }

    return distance;
}
