#ifndef MASTER_HPP
#define MASTER_HPP

#include "trilaterate.hpp"
#include "main.hpp"

struct recordsInfoCollection {
    uint32_t avgTime[MONITOR_COUNT];
	coord_t monitorPos[MONITOR_COUNT];
	record_t record[MONITOR_COUNT];
    uint8_t area[MONITOR_COUNT];

	recordsInfoCollection();
    void emptyBuffers();
};

extern struct recordsInfoCollection recordsBuffer;

#endif // MASTER_HPP