#include "process.hpp"

using namespace std;

Process::Process(int processID, int arrivalTime, int burstTime, int priority) {
    this->processID = processID;
    this->priority = priority;
    num_contexts = 0;
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    remaining_time = burstTime;
}

Process::Process() {
    processID = -1;
    next = nullptr;
    num_contexts = 0;
}
