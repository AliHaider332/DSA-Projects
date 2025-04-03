#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> tasks; 

void create() 
{
    ofstream File("ABC.txt"); 
    if (!File) 
    {
        cout << "Error creating file!\n";
    } 
    else 
    {
        cout << "File created successfully.\n";
    }
    File.close();
}

// Load tasks from file into the vector
void loadTasks()
{
    tasks.clear(); 
    ifstream File("ABC.txt");
    if (!File) 
    {
        cout << "Error opening file!\n";
        return;
    }

    string task;
    while (getline(File, task)) 
    {
        tasks.push_back(task);
    }
    File.close();
}

void AddTask()
{
    ofstream File("ABC.txt", ios::app); 
    if (!File) 
    {
        cout << "Error opening file!\n";
        return;
    }

    cin.ignore(); 
    cout << "Enter the task: ";
    string s;
    getline(cin, s);

    File << s << endl;  
    File.close();
    cout << "Task added successfully!\n";
}

void ViewTask()
{
    loadTasks(); // Ensure the tasks are loaded before displaying

    if (tasks.empty()) 
    {
        cout << "No tasks found!\n";
        return;
    }

    cout << "\nYour Tasks:\n";
    for (int i = 0; i < tasks.size(); i++) 
    {
        cout << i + 1 << ". " << tasks[i] << endl;
    }
}

void DeleteTask()
{
    loadTasks(); 

    if (tasks.empty()) 
    {
        cout << "No tasks to delete!\n";
        return;
    }

    ViewTask();
    cout << "Enter which task you want to delete: ";
    int x;
    cin >> x;

    if (x < 1 || x > tasks.size()) 
    {
        cout << "This task is not present in the file.\n";
        return;
    }

    tasks.erase(tasks.begin() + x - 1); 

    // Write the updated tasks back to the file
    ofstream File("ABC.txt"); 
    
    for (int i = 0; i < tasks.size(); i++)  
    {
        File << tasks[i] << '\n';
    }

    File.close();

    cout << "Task deleted successfully!\n";
}

void menu()
{
    int choice;
    while (true)
    {
        cout << "\nOption List Menu:\n";
        cout << "1. Add Task\n2. View Tasks\n3. Delete Task\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: AddTask(); break;
            case 2: ViewTask(); break;
            case 3: DeleteTask(); break;
            case 4: cout << "Goodbye!\n"; return;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}

int main()
{
    create();
    menu();
    return 0;
}
