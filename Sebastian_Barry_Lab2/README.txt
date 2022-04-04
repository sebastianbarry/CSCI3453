*******************************************************
*  Name      :  Sebastian Barry        
*  Student ID:  107506806               
*  Class     :  CSC 3453           
*  Due Date  :  Apr. 3, 2022
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program will accept a file of CPU jobs and simulate
the chosen CPU scheduling algorithm which afterwards will 
display the CPU burst times, waiting times, turn around times,
and context switching times. Options for CPU scheduling algorithms
are FCFS, SRTF, and RR (with quantum time).

*******************************************************
*  Source files
*******************************************************

Name:  lab2.cpp
   Main program. It parses the input parameters and
   decides which algorithm to send the CPU jobs to

Name: process.cpp
   It contains the constructors for the simple object
   for "process", containing variables processID, priority, 
   num_contexts, comp_data, arrivalTime, burstTime, and 
   remaining_time.

Name: readyQueue.cpp
   It contains the queue functions for readyQueue which
   will be used for the "process" objects.

Name: scheduler.cpp
   It contains the most important functions for executing
   this program. It contains the functions which conduct
   the scheduling algorithm simulations, which also outputs
   the correct output for each function. It also contains
   additional supporting functions for the CPU scheduling
   algorithms such as quicksort.

*******************************************************
*  Status of program
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on VScode g++.  It was 
   compiled, run, and tested on csegrid.ucdenver.pvt.

