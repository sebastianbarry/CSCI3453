// Sebastian Barry
// CSCI 3453
// Lab 2
// 4/3/2022

#ifndef lab2_file
#define lab2_file

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <ctype.h>
#include "scheduler.hpp"
#include "readyQueue.hpp"
#include "process.hpp"
#include "common.hpp"

using namespace std;

const char* ARRIVAL_TIME = "arrival_time";
const char* PRIORITY = "priority";

int main(int argc, char * argv[]){

    int pid, arrival, burst, priority;
    ReadyQueue *readyQueue = new ReadyQueue();

    ifstream data(argv[1]);
    if(!data){
        cout << "Unable to open the file";
        exit(1);
    }

    int count = 0;
    while(data >> pid >> arrival >> burst >> priority){
        readyQueue->enqueue(new Process(pid, arrival, burst, priority));
        count++;
    }

    Scheduler scheduler;
    if (strcmp(argv[2], "FCFS") == 0 || strcmp(argv[2], "fcfs") == 0) {
        printf("************************************************************\n"
               "************ Scheduling algorithm : FCFS *******************\n"
               "************************************************************\n");
        scheduler.fcfsSchedule(readyQueue);
    }
    
    if (strcmp(argv[2], "SRTF") == 0 || strcmp(argv[2], "srtf") == 0) {
        printf("************************************************************\n"
               "************ Scheduling algorithm : SRTF *******************\n"
               "************************************************************\n");
        scheduler.srtfSchedule(readyQueue);
    }
    
    int quantum_size = atoi(argv[3]);
    if (strcmp(argv[2], "RR") == 0 || strcmp(argv[2], "rr") == 0) {
        printf("************************************************************\n"
               "************ Scheduling algorithm : ROUND ROBIN ************\n"
               "************************************************************\n");
        scheduler.rrSchedule(readyQueue,quantum_size);
    }
}

#endif