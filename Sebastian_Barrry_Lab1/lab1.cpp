// Sebastian Barry
// CSCI 3453
// Lab 1
// 2/13/2022
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <sys/utsname.h>

using namespace std;


string getInfo(string fileName, string line){ // read specified line from file
    string info;
    ifstream in;
    size_t check;

    in.open(fileName);

    if(in.is_open() == false){ // if file does not open
        return "data reading failure";
    }
    while(!in.eof()){ // while still in the file
        getline(in, info); // get the next line
        check = info.find(line); // find the specified search term

        if(check != string::npos){ //if found, return info
            return info;
        }
    }

    return "data reading failure";
}


string getInfoUntilChar(string fileName, string line, char stop){ // read specified line from file up to a stopping point
    string info;
    ifstream in;

    in.open(fileName);

    if(in.is_open() == false){ // if file does not open
        return "data reading fail";
    }

    getline(in, info, stop); // get line until stopping point

    return info; //return the string.
}



int main(){
    
    //part A
    struct utsname systeminfo; //struct holds system info

    if (uname(&systeminfo) < 0) //get information and check for fail
        cout << "!!! UNAME FAILURE !!!" << endl;
    else {
        cout << "\n--------------------\n";
        cout << "System name - " <<  systeminfo.sysname << endl;
        cout << "Nodename - " <<  systeminfo.nodename << endl;
        cout << "Release - " <<  systeminfo.release << endl;
        cout << "Version - " <<  systeminfo.version << endl;
        cout << "Machine - " <<  systeminfo.machine << endl;
        cout << "\n--------------------\n";
    }

    
    //part B
    int epoch;
    char formattedOutput[80];
    
    
    // 1. time when system was last booted
    string bootTime = getInfo("/proc/stat", "btime");
    istringstream bootTimeStream(bootTime);
    bootTimeStream >> epoch;
    bootTimeStream >> epoch; // run this command twice to trash the first line and store the important info
    time_t bootTimeTimestamp = epoch; // convert integer to time_t
    struct tm * bootTimeTimeInfo = localtime(&bootTimeTimestamp); //convert time_t into struct tm*
    size_t bootTimeSize = strftime(formattedOutput, 80, "Time of last boot         - %F %X", bootTimeTimeInfo); // convert struct tm* into required format

    cout << formattedOutput << endl;

    
    
    // 2. the amount of time since system was last booted
    string upTime = getInfoUntilChar("/proc/uptime", "btime", ' ');
    istringstream upTimeStream(upTime);
    upTimeStream >> epoch;
    time_t upTimeTimestamp = epoch;
    struct tm * upTimeTimeInfo = localtime(&upTimeTimestamp);
    size_t upTimeSize = strftime(formattedOutput, 80, "Time since last boot      - %j:%X", upTimeTimeInfo);

    cout << formattedOutput << endl;

    
    
    // 3. amount of time CPU has spent in user mode and system mode
    string cpuTime = getInfo("/proc/stat", "cpu");
    istringstream cpuTimeStream(cpuTime);
    cpuTimeStream >> cpuTime;
    cpuTimeStream >> epoch;
    cout << "Time spent in user mode   - " << (epoch/100) << " sec" << endl;
    
    cpuTimeStream >> epoch;
    cpuTimeStream >> epoch;
    cout << "Time spent in system mode - " << (epoch/100) << " sec" << endl;

    
    
    // 4. the total amount of memory in the system and the amount of memory currently available.
    int memory;
    string totalMemory = getInfo("/proc/meminfo", "MemTotal");
    stringstream totalMemoryStream(totalMemory);
    totalMemoryStream >> totalMemory;
    totalMemoryStream >> memory;
    cout << "Total Memory              - " << memory << " kB" << endl;

    string availableMemory = getInfo("/proc/meminfo", "MemAvailable");
    stringstream catalyst4(availableMemory);
    catalyst4 >> availableMemory;
    catalyst4 >> memory;
    cout << "Available Memory          - " << memory << " kB" << endl;

    
    
    cout << endl;
    return 0;
}
