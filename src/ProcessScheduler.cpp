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
        cout << "Error: Could not open " << filename << endl;
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
    cout << "Successfully loaded " << processes.size() << " processes from " << filename << endl;
}

// Display loaded processes
void displayProcesses(const vector<Process>& procs) {
    cout << "\nProcess Information:" << endl;
    cout << "PID\tArrival\tBurst\tPriority" << endl;
    cout << "---\t-------\t-----\t--------" << endl;
    
    for (const auto& p : procs) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" 
             << p.burstTime << "\t" << p.priority << endl;
    }
}

void displayGanttChart(const vector<string>& chart, const vector<int>& times) {
    cout << "\nGantt Chart (Process Execution Timeline):\n" << endl;

    // Top border
    cout << " ";
    for (size_t i = 0; i < chart.size(); i++) {
        cout << "-------";
    }
    cout << "-" << endl;

    // Process names inside boxes
    cout << "|";
    for (size_t i = 0; i < chart.size(); i++) {
        cout << "  " << setw(3) << left << chart[i] << " |";
    }
    cout << endl;

    // Bottom border
    cout << " ";
    for (size_t i = 0; i < chart.size(); i++) {
        cout << "-------";
    }
    cout << "-" << endl;

    // Time labels
    for (size_t i = 0; i < times.size(); i++) {
        cout << setw(6) << left << times[i];
    }
    cout << endl;
}

// Display results with waiting time and turnaround time
void displayResults(vector<Process>& procs, const string& algorithm) {
    cout << "\n" << algorithm << " Results:" << endl;
    cout << "PID\tArrival\tBurst\tComplete\tTurnaround\tWaiting" << endl;
    cout << "---\t-------\t-----\t--------\t----------\t-------" << endl;
    
    double totalWT = 0, totalTAT = 0;
    
    // Print each process's metrics
    for (const auto& p : procs) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime 
             << "\t" << p.completionTime << "\t\t" << p.turnaroundTime 
             << "\t\t" << p.waitingTime << endl;
        
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }
    
    // Calculate and display averages
    cout << "\n*** Average Waiting Time: " << fixed << setprecision(2) 
         << totalWT / procs.size() << " ***" << endl;
    cout << "*** Average Turnaround Time: " << fixed << setprecision(2) 
         << totalTAT / procs.size() << " ***" << endl;
}

void runFCFS() { 
    cout << "\n========================================" << endl;
    cout << "FIRST-COME, FIRST-SERVED (FCFS)" << endl;
    cout << "========================================" << endl;
    
    // Get Process 
    vector<Process> fcfsProcesses = processes;
    
    vector<string> ganttChart;
    vector<int> timePoints;
    timePoints.push_back(0);  // Start at time 0

    // Sort by arrival time
    sort(fcfsProcesses.begin(), fcfsProcesses.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Execute in order of arrival time
    int currentTime = 0;
    for (auto& p : fcfsProcesses) {
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }
        p.startTime = currentTime;
        p.completionTime = currentTime + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        
        // FIXED: Add to Gantt chart
        ganttChart.push_back("P" + to_string(p.pid));
        currentTime = p.completionTime;
        timePoints.push_back(currentTime);
    }

    displayGanttChart(ganttChart, timePoints);
    displayResults(fcfsProcesses, "FCFS");
}


void runRoundRobin() {
    cout << "\n========================================" << endl;
    cout << "ROUND ROBIN (RR)" << endl;
    cout << "========================================" << endl;

    int quantum;
    cout << "Enter Time Quantum (2 or 3): ";  
    cin >> quantum;

    vector<Process> rrProcesses = processes;
    queue<Process*> readyQueue;
    vector<string> ganttChart;
    vector<int> timePoints;

    int currentTime = 0;
    int completedCount = 0;
    timePoints.push_back(0);

    sort(rrProcesses.begin(), rrProcesses.end(),
        [](const Process& a, const Process& b) {
            return a.arrivalTime < b.arrivalTime;
        });

    vector<bool> inQueue(rrProcesses.size(), false);

    for (size_t i = 0; i < rrProcesses.size(); i++) {
        if (rrProcesses[i].arrivalTime <= currentTime) {
            readyQueue.push(&rrProcesses[i]);
            inQueue[i] = true;
        }
    }

    while (completedCount < (int)rrProcesses.size()) {  
        if (readyQueue.empty()) {
            currentTime++;  
            for (size_t i = 0; i < rrProcesses.size(); i++) {
                if (rrProcesses[i].arrivalTime <= currentTime && 
                    rrProcesses[i].remainingTime > 0 && !inQueue[i]) {
                    readyQueue.push(&rrProcesses[i]);
                    inQueue[i] = true;
                }
            }
            continue;
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


int main() {
    cout << "========================================" << endl;
    cout << "    PROCESS SCHEDULING SIMULATOR" << endl;
    cout << "========================================" << endl;
    cout << "\nMake sure 'processes.txt' is in the same folder!" << endl << endl;
    
    // Load processes from file
    readProcessesFromFile("processes.txt");
    
    // Check if processes were loaded
    if (processes.empty()) {
        cout << "\nNo processes were loaded!" << endl;
        cout << "Please create a processes.txt file with format:" << endl;
        cout << "PID Arrival_Time Burst_Time Priority" << endl;
        cout << "1 0 5 2" << endl;
        cout << "2 2 3 1" << endl;
        return 1;
    }
    
    // Show loaded processes
    displayProcesses(processes);
    
    // Main menu loop
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "SELECT AN OPTION:" << endl;
        cout << "1. First-Come, First-Served (FCFS)" << endl;
        cout << "2. Round Robin (RR)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                runFCFS();
                break;
            case 2:
                runRoundRobin();
                break;
            case 0:
                cout << "\nThank you for using the Process Scheduler!" << endl;
                break;
            default:
                cout << "\nInvalid choice! Please enter 0-3." << endl;
        }
    } while (choice != 0);
    
    return 0;
}