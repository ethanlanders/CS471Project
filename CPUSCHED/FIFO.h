#ifndef FIFO_H
#define FIFO_H

#include <vector>

bool compareArrivalTime(const CPU_Process& p1, const CPU_Process& p2);
void FIFO(std::vector<CPU_Process> processes);

#endif // FIFO_H