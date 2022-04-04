#ifndef readyqueue_file
#define readyqueue_file

#include <string>
#include <iomanip>
#include <sstream>
#include "process.hpp"

class ReadyQueue{
public:
    int size;
    Process* head;
    Process* tail;
    ReadyQueue();
    void enqueue(Process *process);
    Process* dequeue();
};

#endif
