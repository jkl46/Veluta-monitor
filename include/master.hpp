#ifndef MASTER_HPP
#define MASTER_HPP

#include "trilaterate.hpp"
#include "main.hpp"

struct recordsInfoCollection {
    uint32_t avgTime[MONITOR_COUNT];
	coord_t monitorPos[MONITOR_COUNT];
	record_t record[MONITOR_COUNT];
    uint8_t area[MONITOR_COUNT];

	recordsInfoCollection()
	{
		// Connect records with monitors
		for (size_t i = 0; i < MONITOR_COUNT; i++)
		{
			this->record[i].pos = (this->monitorPos+i);
		}
		
	}

    void emptyBuffers()
    {
        for (size_t i = 0; i < MONITOR_COUNT; i++)
        {
            this->avgTime[i] = 0;
            this->monitorPos[i] = {0,0};
            this->record[i].r = 0;
            this->area[i] = 0;
        }
    }

};

extern struct recordsInfoCollection recordsBuffer;

#endif // MASTER_HPP