#ifndef scheduler_file
#define scheduler_file

#include "readyQueue.hpp"

class Scheduler {
public:
    void fcfsSchedule(ReadyQueue *readyQueue);
    void srtfSchedule(ReadyQueue *readyQueue);
    void rrSchedule(ReadyQueue *readyQueue, int quantumSize);
    
private:
    float _avg_cpuburst_time;
    float _avg_turnaround_time;
    float _avg_waiting_time;
    float _avg_response_time;
    int _context_switches;

    void sort(ReadyQueue *readyQueue, const char* comparator);
    void printStats();
    void clearStats();
};

#endif
