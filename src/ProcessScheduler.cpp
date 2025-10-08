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

void runFCFS(){ 
    //Get Process 
    vector<Process> fcfsProcesses = processes;

    // Sort by arrival time
    sort(fcfsProcesses.begin(), fcfsProcesses.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    //Excecute in order of arrival time
    int currentTime = 0;
    for (auto& p : fcfsProcesses) {
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        p.startTime = currentTime;
        p.completionTime = currentTime + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        currentTime = p.completionTime;
    }

    //displayGanttChart(ganttChart, timePoints);
    //displayResults(fcfsProcesses, "FCFS");

}

void runRoundRobin {
    cout << "\n========================================" << endl;
    cout << "ROUND ROBIN (RR)" << endl;
    cout << "========================================" << endl;

    int quantum;
    cout << "Enter Time Quantum (2 or 3): " << endl;
    cin >> quantum;

    vector<processes> rrProcess = processes;
    queue<processes*> readyQueue;
    vector<string> ganttChart;
    vector<int> timePoints;

    int currentTime = 0;
    int completedCount =0;
    timePoints.push_back = 0

    sort(rrProcess.begin(), rrProcess.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

    vector<bool> inQueue(rrProcess.size(), false);

    for (size_t i = 0; i < rrProcesses.size(); i++) {
        if (rrProcesses[i].arrivalTime <= currentTime) {
            readyQueue.push(&rrProcesses[i]);
            inQueue[i] = true;
        }
    }

    while (completedCount < rrProcess.size()) {
        if (readyQueue.empty()) {
            for (size_t i = 0; i << rrProcesses.size(); i++) {
                if (rrProcesses[i].arrivalTime <= currentTime && 
                    rrProcesses[i].remainingTime > 0 && !inQueue[i]) {
                    readyQueue.push(&rrProcesses[i]);
                    inQueue[i] = true;
                }
            }
            continue
        }
     Process* current = readyQueue.front();
        readyQueue.pop();
        
        // Find the index of current process
        int currentIndex = -1;
        for (size_t i = 0; i < rrProcesses.size(); i++) {
            if (rrProcesses[i].pid == current->pid) {
                currentIndex = i;
                break;
            }
        }
        inQueue[currentIndex] = false;
        
        // Record start time if this is first time running
        if (!current->started) {
            current->startTime = currentTime;
            current->started = true;
        }
        
        // Execute for quantum time or until completion
        int executeTime = min(quantum, current->remainingTime);
        ganttChart.push_back("P" + to_string(current->pid));
        currentTime += executeTime;
        timePoints.push_back(currentTime);
        current->remainingTime -= executeTime;
        
        // Check for newly arrived processes
        for (size_t i = 0; i < rrProcesses.size(); i++) {
            if (rrProcesses[i].arrivalTime <= currentTime && 
                rrProcesses[i].remainingTime > 0 && !inQueue[i] &&
                rrProcesses[i].pid != current->pid) {
                readyQueue.push(&rrProcesses[i]);
                inQueue[i] = true;
            }
        }
        
        // If process not finished, add back to queue
        if (current->remainingTime > 0) {
            readyQueue.push(current);
            inQueue[currentIndex] = true;
        } else {
            // Process completed
            current->completionTime = currentTime;
            current->turnaroundTime = current->completionTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
            completedCount++;
        }
    }
    
    displayGanttChart(ganttChart, timePoints);
    displayResults(rrProcesses, "Round Robin (Quantum=" + to_string(quantum) + ")");

}