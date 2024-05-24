#include "hornet.hpp"

double time_to_distance(double time, int area)
{
    double distance = -1;

    switch (area)
    {
    case COUNTRY:
        distance = COUNTRY_FORMULA(time);
        break;
        
    case URBAN:
        distance = URBAN_FORMULA(time);
        break;
    
    case CITY:
        distance = CITY_FORMULA(time);
        break;

    default:
        break;
    }
    return distance;
}
