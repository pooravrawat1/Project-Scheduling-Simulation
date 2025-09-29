#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;  
    int startTime;
    bool started;
    
    // Default constructor
   Process() {
        pid = 0;
        arrivalTime = 0;
        burstTime = 0;
        priority = 0;
        remainingTime = 0;
        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
        startTime = -1;
        started = false;
    }
    
    // Parameterized constructor
    Process(int pid_, int arrival_, int burst_, int priority_)
        : pid(pid_), arrivalTime(arrival_), burstTime(burst_), priority(priority_),
          remainingTime(burst_), waitingTime(0), turnaroundTime(0), completionTime(0),
          startTime(-1), started(false) {}
};

vector<Process> processes;

void readProcessesFromFile(const string& filename) {  
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << std::endl;  
        return;
    }
    
    string line;
    getline(file, line);  
    
    while (getline(file, line)) {
        stringstream ss(line);
        int pid, arrival, burst, priority;
        
        if (ss >> pid >> arrival >> burst >> priority) {
            processes.push_back(Process(pid, arrival, burst, priority));
        }
    }
    
    file.close();
    cout << "Successfully loaded " << processes.size() << " processes from " << filename << std::endl;
}
