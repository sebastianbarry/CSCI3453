#include <string>
#include <iomanip>
#include <sstream>
#include "process.hpp"
#include "readyQueue.hpp"

using namespace std;

ReadyQueue::ReadyQueue() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

void ReadyQueue::enqueue(Process *process) {
    if(size == 0){
        head = process;
        tail = process;
    }else{
        tail->next = process;
        tail = process;
    }
    size++;
}

Process* ReadyQueue::dequeue() {
    if(size <= 0){
        return nullptr;
    }
    else{
        Process *temp = head;
        head = head->next;
        size--;
        return temp;
    }
}
