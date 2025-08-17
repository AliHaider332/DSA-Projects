#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// Process States as enum (cleaner than strings)
enum ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };

// Convert enum to string
string stateToString(ProcessState state) {
    switch (state) {
        case NEW: return "New";
        case READY: return "Ready";
        case RUNNING: return "Running";
        case WAITING: return "Waiting";
        case TERMINATED: return "Terminated";
    }
    return "Unknown";
}

// Process Control Block (PCB)
struct PCB {
    string name;
    int pid;
    int programCounter;
    int priority;
    ProcessState state;
    PCB* next;

    // static tracking for uniqueness
    static vector<int> usedPIDs;
    static vector<int> usedPriorities;

    PCB() {
        cout << "\nEnter Process Name: ";
        getline(cin, name);

        cout << "Enter Process ID: ";
        cin >> pid;
        while (find(usedPIDs.begin(), usedPIDs.end(), pid) != usedPIDs.end()) {
            cout << "Process ID already used! Enter unique ID: ";
            cin >> pid;
        }
        usedPIDs.push_back(pid);

        cout << "Enter Program Counter: ";
        cin >> programCounter;

        cout << "Enter Priority: ";
        cin >> priority;
        while (find(usedPriorities.begin(), usedPriorities.end(), priority) != usedPriorities.end()) {
            cout << "Priority already exists! Enter different priority: ";
            cin >> priority;
        }
        usedPriorities.push_back(priority);

        state = NEW;
        next = nullptr;
        cin.ignore(); // clean buffer
    }

    void display(bool header = false) {
        if (header) {
            cout << "\n--------------------------------------------------------------------------------------\n";
            cout << "| " << setw(15) << "Name"
                 << "| " << setw(10) << "PID"
                 << "| " << setw(15) << "Program Counter"
                 << "| " << setw(10) << "Priority"
                 << "| " << setw(15) << "State"
                 << "|\n";
            cout << "--------------------------------------------------------------------------------------\n";
        }

        cout << "| " << setw(15) << name
             << "| " << setw(10) << pid
             << "| " << setw(15) << programCounter
             << "| " << setw(10) << priority
             << "| " << setw(15) << stateToString(state)
             << "|\n";
        cout << "--------------------------------------------------------------------------------------\n";
    }
};

vector<int> PCB::usedPIDs;
vector<int> PCB::usedPriorities;


// ================= Scheduler Class =================
class Scheduler {
private:
    PCB* head;
    queue<PCB*> rrQueue;
    int quantum;

public:
    Scheduler() { head = nullptr; quantum = 2; }

    // ---------- FCFS ----------
    void addFCFS() {
        PCB* p = new PCB();
        if (!head) head = p;
        else {
            PCB* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = p;
        }
    }

    // ---------- SJF ----------
    void addSJF() {
        PCB* p = new PCB();
        if (!head || p->programCounter < head->programCounter) {
            p->next = head;
            head = p;
        } else {
            PCB* temp = head;
            while (temp->next && p->programCounter >= temp->next->programCounter)
                temp = temp->next;
            p->next = temp->next;
            temp->next = p;
        }
    }

    // ---------- Priority ----------
    void addPriority() {
        PCB* p = new PCB();
        if (!head || p->priority > head->priority) {
            p->next = head;
            head = p;
        } else {
            PCB* temp = head;
            while (temp->next && p->priority <= temp->next->priority)
                temp = temp->next;
            p->next = temp->next;
            temp->next = p;
        }
    }

    // ---------- Round Robin ----------
    void addRR() {
        PCB* p = new PCB();
        rrQueue.push(p);
    }

    void runRR() {
        if (rrQueue.empty()) {
            cout << "\nNo processes in Round Robin queue.\n";
            return;
        }

        queue<PCB*> tempQ;
        while (!rrQueue.empty()) {
            PCB* p = rrQueue.front(); rrQueue.pop();
            p->programCounter -= quantum;
            if (p->programCounter > 0) {
                p->state = READY;
                tempQ.push(p);
            } else {
                p->state = TERMINATED;
            }
        }

        // Show one as running
        if (!tempQ.empty()) {
            tempQ.front()->state = RUNNING;
        }

        // Display
        if (!tempQ.empty()) tempQ.front()->display(true);
        while (!tempQ.empty()) {
            PCB* p = tempQ.front(); tempQ.pop();
            p->display();
            rrQueue.push(p);
        }
    }

    // ---------- Display ----------
    void displayAll(bool exec = false) {
        PCB* temp = head;
        if (!temp) {
            cout << "No processes added yet.\n";
            return;
        }
        bool headerPrinted = false;
        int count = 0;
        while (temp) {
            if (!headerPrinted) { temp->display(true); headerPrinted = true; }
            if (exec) {
                if (count == 0) temp->state = RUNNING;
                else temp->state = READY;
            }
            temp->display();
            temp = temp->next;
            count++;
        }
    }
};


// ================= MAIN =================
int main() {
    Scheduler scheduler;
    int choice;
    cout << "Choose Scheduling Algorithm:\n";
    cout << "1. FCFS\n2. Priority\n3. SJF\n4. Round Robin\n";
    cout << "Choice: ";
    cin >> choice; cin.ignore();

    string cmd;
    if (choice == 1) {
        while (true) {
            cout << "\nAdd Process? (yes/no): ";
            getline(cin, cmd);
            if (cmd == "yes" || cmd == "YES") scheduler.addFCFS();
            else break;
        }
        scheduler.displayAll(true);
    }
    else if (choice == 2) {
        while (true) {
            cout << "\nAdd Process? (yes/no): ";
            getline(cin, cmd);
            if (cmd == "yes" || cmd == "YES") scheduler.addPriority();
            else break;
        }
        scheduler.displayAll(true);
    }
    else if (choice == 3) {
        while (true) {
            cout << "\nAdd Process? (yes/no): ";
            getline(cin, cmd);
            if (cmd == "yes" || cmd == "YES") scheduler.addSJF();
            else break;
        }
        scheduler.displayAll(true);
    }
    else if (choice == 4) {
        int q;
        cout << "Enter Quantum: ";
        cin >> q; cin.ignore();
        scheduler = Scheduler(); // reset
        while (true) {
            cout << "\nAdd Process? (yes/no): ";
            getline(cin, cmd);
            if (cmd == "yes" || cmd == "YES") scheduler.addRR();
            else break;
        }
        while (true) {
            scheduler.runRR();
            cout << "\nRun again? (yes/no): ";
            getline(cin, cmd);
            if (!(cmd == "yes" || cmd == "YES")) break;
        }
    }
    return 0;
}
