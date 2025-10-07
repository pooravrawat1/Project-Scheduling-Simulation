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

void runSJF() {
    cout << "\n========================================" << endl;
    cout << "SHORTEST JOB FIRST (SJF)" << endl;
    cout << "========================================" << endl;
    
    vector<Process> sjfProcesses = processes;
    vector<bool> isCompleted(sjfProcesses.size(), false);  // Track which processes are done
    vector<string> ganttChart;
    vector<int> timePoints;
    
    int currentTime = 0;
    int completedCount = 0;
    timePoints.push_back(0);
    
    // Keep running until all processes are complete
    while (completedCount < sjfProcesses.size()) {
        int selectedIdx = -1;  // Which process to run
        int minBurstTime = INT_MAX;  // Find shortest burst time
        
        // Look through all processes
        for (size_t i = 0; i < sjfProcesses.size(); i++) {
            // Check if process: has arrived, not completed, and has shortest burst
            if (sjfProcesses[i].arrivalTime <= currentTime && 
                !isCompleted[i] && 
                sjfProcesses[i].burstTime < minBurstTime) {
                
                minBurstTime = sjfProcesses[i].burstTime;
                selectedIdx = i;  // This is our chosen process
            }
        }
        
        // If no process is ready, advance time
        if (selectedIdx == -1) {
            currentTime++;
            continue;
        }
        
        // Execute the selected process
        Process& selected = sjfProcesses[selectedIdx];
        selected.startTime = currentTime;
        selected.completionTime = currentTime + selected.burstTime;
        selected.turnaroundTime = selected.completionTime - selected.arrivalTime;
        selected.waitingTime = selected.turnaroundTime - selected.burstTime;
        
        // Add to Gantt chart
        ganttChart.push_back("P" + to_string(selected.pid));
        currentTime = selected.completionTime;
        timePoints.push_back(currentTime);
        
        isCompleted[selectedIdx] = true;  // Mark as done
        completedCount++;
    }
    
    //displayGanttChart(ganttChart, timePoints);
    //displayResults(sjfProcesses, "SJF");
}
