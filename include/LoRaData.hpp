#ifndef LORADATA_HPP
#define LORADATA_HPP

#include "pico/stdlib.h"
#include "pico/binary_info.h"

/*! \brief Data holding information for transmitting over and receiving from another monitor using LoRa */
struct lora_data
{
    /*! \brief ID of monitor */
    uint8_t monitor_id;
    /*! \brief ID of hornet that has been spotten */
    uint8_t hornet_id;
    /*! \brief Type of area the monitor is placed in*/
    uint8_t area_code;
    /*! \brief Longitude of monitor */
    double longitude;
    /*! \brief Latitude of monitor */
    double latitude;
};

#endif