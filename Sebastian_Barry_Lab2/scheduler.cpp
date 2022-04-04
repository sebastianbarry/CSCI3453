#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "scheduler.hpp"
#include "process.hpp"
#include "readyQueue.hpp"
#include "common.hpp"

using namespace std;

Process* toArray(ReadyQueue *readyQueue){
    Process* temp = readyQueue->head;
    Process *processArray = new Process[readyQueue->size];
    int i = 0;
    while(temp != nullptr){
        processArray[i] = *temp;
        temp = temp->next;
        i++;
    }
    return processArray;
}

Process *getTail(Process *cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

Process *partition(Process *head, Process *end,
                   Process **newHead, Process **newEnd) {
    Process *pivot = end;
    Process *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->comp_data < pivot->comp_data)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) {
                prev->next = cur->next;
            }
            Process *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;

    return pivot;
}

Process *quickSortRecur(Process *head, Process *end) {
    if (!head || head == end)
        return head;

    Process *newHead = NULL, *newEnd = NULL;

    Process *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        Process *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next =  pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(Process **headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

void Scheduler::fcfsSchedule(ReadyQueue *readyQueue) {
    clearStats();
    printf("PID\tArrival\tCPU-burst\tPriority\tFinish\tWaiting Time\tTurn around\tResponse Time\tNo.of Context\n");
    sort(readyQueue,ARRIVAL_TIME);
    int current_time = 0;
    int n_process = readyQueue->size;
    while(readyQueue->head != nullptr){
        Process *process = readyQueue->dequeue();

        int finish_time = current_time + process->burstTime;
        int waiting_time = current_time - process->arrivalTime;
        int turn_around_time = waiting_time + process->burstTime;
        int response_time = waiting_time;

        _avg_waiting_time += waiting_time;
        _avg_cpuburst_time += process->burstTime;
        _avg_response_time += response_time;
        _avg_turnaround_time += turn_around_time;
        cout<<process->processID << "\t"<<process->arrivalTime<<"\t"<<process->burstTime<<"\t\t"<<process->priority<<"\t\t"
            <<finish_time<<"\t"<<waiting_time<<"\t\t"<<turn_around_time<<"\t\t"<<response_time<<"\t\t"<<0<<endl;
        current_time += process->burstTime;
    }
    //Calculate the averages
    _avg_cpuburst_time /= n_process;
    _avg_waiting_time /= n_process;
    _avg_turnaround_time /= n_process;
    printStats();
}

void Scheduler::srtfSchedule(ReadyQueue *readyQueue) {
    clearStats();
    printf("PID\tArrival\tCPU-burst\tPriority\tFinish\tWaiting Time\tTurn around\tResponse Time\tNo.of Context\n");
    sort(readyQueue,PRIORITY); // sort the scheduler
    int current_time = 0;
    int n_process = readyQueue->size;
    while(readyQueue->head != nullptr){
        Process *process = readyQueue->dequeue();

        int finish_time = current_time + process->burstTime;
        int waiting_time = current_time - process->priority;
        int turnaround_time = waiting_time + process->burstTime;
        int response_time = waiting_time;

        _avg_waiting_time += waiting_time;
        _avg_cpuburst_time += process->burstTime;
        _avg_response_time += response_time;
        _avg_turnaround_time += turnaround_time;
        cout << process->processID << "\t" << process->arrivalTime << "\t" << process->burstTime << "\t\t" << process->priority << "\t\t"
            << finish_time << "\t" << waiting_time << "\t\t" << turnaround_time << "\t\t" << response_time << "\t\t" << 0 << endl;
        current_time += process->burstTime;
    }
    //Calculate the averages
    _avg_cpuburst_time /= n_process;
    _avg_waiting_time /= n_process;
    _avg_turnaround_time /= n_process;
    printStats();
}

void Scheduler::rrSchedule(ReadyQueue *readyQueue, int quantumSize) {
    sort(readyQueue,ARRIVAL_TIME);
    printf("PID\tArrival\tCPU-burst\tPriority\tFinish\tWaiting Time\tTurn around\tResponse Time\tNo.of Context\n");
    Process *processList = toArray(readyQueue);
    
    float finishTimes[readyQueue->size];
    float responseTimes[readyQueue->size];
    int n_process = readyQueue->size;
    int n_complete = 0;
    float current_time = 0;

    while(n_complete != n_process){
        for(int i = 0; i < n_process; i++){
            if(processList[i].arrivalTime > current_time){
                int prev_complete = 0;
                for(int j = 0; j < i; j++){
                    if(processList[j].remaining_time == 0){
                        prev_complete++;
                    }
                }
                if(prev_complete == i){
                    current_time = processList[i].arrivalTime;
                }
                break;
            }
            if(processList[i].remaining_time <= 0){
                continue;
            }
            if(processList[i].remaining_time == processList[i].burstTime){
                responseTimes[i] = current_time - processList[i].arrivalTime;
            }
            if(processList[i].remaining_time <= quantumSize){
                current_time += processList[i].remaining_time;
                processList[i].remaining_time = 0;
                finishTimes[i] = current_time;
                n_complete++;
            }
            else{
                current_time += (quantumSize + 0.5);
                processList[i].remaining_time -= quantumSize;
                processList[i].num_contexts++;
            }
        }
    }
    int total_contexts = 0;
    for(int i = 0; i < readyQueue->size; i++){
        float turnaround_time = finishTimes[i]-processList[i].arrivalTime;
        float waiting_time = finishTimes[i] - (processList[i].arrivalTime+processList[i].burstTime);
        float finish_time = finishTimes[i];
        float response_time = responseTimes[i];

        _avg_waiting_time += waiting_time;
        _avg_cpuburst_time += processList[i].burstTime;
        _avg_response_time += responseTimes[i];
        _avg_turnaround_time += turnaround_time;
        
        total_contexts += processList[i].num_contexts;
        cout<<processList[i].processID<<"\t"<<processList[i].arrivalTime<<"\t"<<processList[i].burstTime<<"\t\t"<<processList[i].priority<<"\t\t"
            <<finish_time<<"\t"<<waiting_time<<"\t\t"<<turnaround_time<<"\t\t"<<response_time<<"\t\t"<<processList[i].num_contexts<<endl;
    }
    //Calculate the averages
    _avg_cpuburst_time /= n_process;
    _avg_waiting_time /= n_process;
    _avg_turnaround_time /= n_process;
    _context_switches = total_contexts;
    printStats();
}

void Scheduler::sort(ReadyQueue *readyQueue, const char *comparator){
    if(strcmp(comparator,ARRIVAL_TIME) == 0){
        Process *temp = readyQueue->head;
        while (temp != nullptr){
            temp->comp_data = temp->arrivalTime;
            temp = temp->next;
        }
        quickSort(&readyQueue->head);
    }
}

void Scheduler::printStats(){
    printf("Average CPU burst time = %f ms\n", _avg_cpuburst_time);
    printf("Average waiting time = %f ms\n", _avg_waiting_time);
    printf("Average turn around time = %f ms\n", _avg_turnaround_time);
    printf("Total No. of Context Switching Performed = %i\n", _context_switches);
}

void Scheduler::clearStats() {
    _avg_cpuburst_time = 0;
    _avg_response_time = 0;
    _avg_turnaround_time = 0;
    _avg_waiting_time = 0;
    _context_switches = 0;
}