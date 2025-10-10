# Process Scheduling Simulator

A comprehensive C++ program that simulates various CPU scheduling algorithms used in Operating Systems. This project is perfect for students learning about process management and OS concepts.

---

## 📋 Features

This simulator implements **4 major scheduling algorithms**:

1. **First-Come, First-Served (FCFS)** - Processes execute in arrival order
2. **Round Robin (RR)** - Each process gets a time quantum

### What You'll See:

- ✅ **Gantt Charts** - Visual timeline of process execution
- ✅ **Performance Metrics** - Waiting time and turnaround time for each process
- ✅ **Algorithm Comparison** - Compare all algorithms side-by-side
- ✅ **Detailed Output** - Complete breakdown of each process

## 🚀 Getting Started

### Prerequisites

- C++ compiler (g++, clang++, or Visual Studio)
- GNU Make (usually pre-installed on Linux/Mac)
- Text editor for creating the input file

### Installation & Build

1. **Clone or download the repository**

2. **Create the input file** `processes.txt` in the same directory:

```
PID Arrival_Time Burst_Time Priority
1 0 5 2
2 1 3 1
3 2 8 3
4 3 6 2
5 4 4 1
```

**Format explanation:**

- **PID**: Process ID (unique identifier)
- **Arrival_Time**: When the process enters the system
- **Burst_Time**: How long the process needs the CPU
- **Priority**: Priority level (lower number = higher priority)


3. **Build the program using Makefile:**

```bash
make
```

4. **Run the program:**

```bash
make run
```

5. **Clean build files (optional):**

```bash
make clean
```

6. **Force rebuild (optional):**

```bash
make rebuild
```

## 📖 How to Use

1. When you run the program, it automatically loads processes from `processes.txt`
2. You'll see a menu with 6 options:

```
========================================
SELECT AN OPTION:
1. First-Come, First-Served (FCFS)
2. Round Robin (RR)
0. Exit
```

3. **Select an algorithm** (1-2) to see it in action
4. For **Round Robin**, you'll be asked to enter a time quantum (try 2 or 3)
6. Press **0** to exit

## 📊 Understanding the Output

### Example Output:

```
Gantt Chart (Process Execution Timeline):
| P1   | P2   | P3   | P1   |
0      2      5      8      11

FCFS Results:
PID   Arrival   Burst   Complete   Turnaround   Waiting
---   -------   -----   --------   ----------   -------
1     0         5       5          5            0
2     1         3       8          7            4
3     2         4       12         10           6

*** Average Waiting Time: 3.33 ***
*** Average Turnaround Time: 7.33 ***
```

**Key Metrics:**

- **Completion Time**: When the process finishes
- **Turnaround Time**: Completion Time - Arrival Time (total time in system)
- **Waiting Time**: Turnaround Time - Burst Time (time spent waiting)

## 🎯 Sample Test Cases

### Test Case 1: Simple Sequential Processes

```
PID Arrival_Time Burst_Time Priority
1 0 5 2
2 2 3 1
3 4 1 3
```

### Test Case 2: All Arrive Together

```
PID Arrival_Time Burst_Time Priority
1 0 8 3
2 0 4 1
3 0 9 2
4 0 5 2
```

### Test Case 3: Staggered Arrivals

```
PID Arrival_Time Burst_Time Priority
1 0 10 2
2 1 1 1
3 2 2 3
4 3 1 4
5 4 5 2
```

## 🔧 Customization Tips

### Adding More Processes

Simply add more lines to `processes.txt`:

```
1 0 7 2
2 1 4 1
3 2 1 3
4 3 3 2
... (add as many as you want)
```

### Changing Time Quantum

When selecting Round Robin, experiment with different quantum values:

- **Small quantum (1-2)**: More context switches, better responsiveness
- **Large quantum (5-10)**: Fewer context switches, approaches FCFS

### Understanding Priority

- **Lower number = Higher priority**
- Priority 1 runs before Priority 2, which runs before Priority 3, etc.

## 🎓 Algorithm Comparison Guide

| Algorithm    | Best For               | Worst For                       | Complexity |
| ------------ | ---------------------- | ------------------------------- | ---------- |
| **FCFS**     | Simple, predictable    | Short jobs behind long jobs     | O(n log n) |
| **RR**       | Time-sharing, fairness | Overhead from context switching | O(n)       |
