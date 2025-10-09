int main()
{
    // Welcome message
    cout << "========================================" << endl;
    cout << "    PROCESS SCHEDULING SIMULATOR" << endl;
    cout << "========================================" << endl;
    cout << "\nThis program simulates CPU scheduling algorithms." << endl;
    cout << "Make sure 'processes.txt' is in the same folder!" << endl
         << endl;

    // Load processes from file
    readProcessesFromFile("processes.txt");

    // Check if processes were loaded
    if (processes.empty())
    {
        cout << "\nNo processes were loaded!" << endl;
        cout << "Please create a processes.txt file with the following format:" << endl;
        cout << "PID Arrival_Time Burst_Time Priority" << endl;
        cout << "1 0 5 2" << endl;
        cout << "2 2 3 1" << endl;
        cout << "..." << endl;
        return 1; // Exit with error
    }

    // Show loaded processes
    displayProcesses(processes);

    // Main menu loop
    int choice;
    do
    {
        cout << "\n========================================" << endl;
        cout << "SELECT AN OPTION:" << endl;
        cout << "1. First-Come, First-Served (FCFS)" << endl;
        cout << "2. Shortest Job First (SJF)" << endl;
        cout << "3. Round Robin (RR)" << endl;
        cout << "4. Priority Scheduling" << endl;
        cout << "5. Compare All Algorithms" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user's choice
        switch (choice)
        {
        case 1:
            runFCFS();
            break;
        case 2:
            runSJF();
            break;
        case 3:
            runRoundRobin();
            break;
        case 4:
            runPriority();
            break;
        case 5:
            compareAllAlgorithms();
            break;
        case 0:
            cout << "\nThank you for using the Process Scheduler!" << endl;
            break;
        default:
            cout << "\nInvalid choice! Please enter 0-5." << endl;
        }
    } while (choice != 0);

    return 0; // Exit successfully
}