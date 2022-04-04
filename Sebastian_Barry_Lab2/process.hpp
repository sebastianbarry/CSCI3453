#ifndef process_file
#define process_file

class Process {
public:
    int processID;
    int priority;
    int num_contexts;
    int comp_data;
    int arrivalTime;
    int burstTime;
    int remaining_time;
    Process *next;
    Process();
    Process(int processID, int arrivalTime, int burstTime, int priority);
};

#endif
