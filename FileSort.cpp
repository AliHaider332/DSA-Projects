#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

void File_Sort(string s, vector<string> &v)
{
    string Folder = s;

    // Check if directory exists
    if (!fs::exists(Folder))
    {
        cout << "Error: Directory does not exist!" << endl;
        return;
    }

    vector<string> file;

    // Collect file names
    for (const auto &f : fs::directory_iterator(Folder))
    {
        if (fs::is_regular_file(f))
        {
            file.push_back(f.path().filename().string());
        }
    }

    // Sort files alphabetically
    sort(file.begin(), file.end());

    // Store original filenames
    v = file;

    // Rename files by adding numbering (1. filename, 2. filename, ...)
    int x = 1;
    for (const auto &filename : file)
    {
        fs::path old_path = fs::path(Folder) / filename;
        fs::path new_path = fs::path(Folder) / (to_string(x) + ". " + filename);

        try
        {
            fs::rename(old_path, new_path);
            cout << "Renamed: " << old_path.filename() << " -> " << new_path.filename() << endl;
        }
        catch (const fs::filesystem_error &e)
        {
            cout << "Error renaming " << filename << ": " << e.what() << endl;
        }
        x++;
    }
}

void Undo(vector<string> &v, string s)
{
    string Folder = s;

    // Check if directory exists
    if (!fs::exists(Folder))
    {
        cout << "Error: Directory does not exist!" << endl;
        return;
    }

    vector<string> file;

    // Collect renamed file names
    for (const auto &f : fs::directory_iterator(Folder))
    {
        if (fs::is_regular_file(f))
        {
            file.push_back(f.path().filename().string());
        }
    }

    // Undo renaming by restoring original names
    int x = 0;
    for (const auto &filename : file)
    {
        fs::path old_path = fs::path(Folder) / filename;
        fs::path new_path = fs::path(Folder) / v[x]; // Restore original name

        try
        {
            fs::rename(old_path, new_path);
            cout << "Restored: " << old_path.filename() << " -> " << new_path.filename() << endl;
        }
        catch (const fs::filesystem_error &e)
        {
            cout << "Error restoring " << filename << ": " << e.what() << endl;
        }
        x++;
    }
}

int main()
{
    cout << "Welcome to my code!" << endl;
    cout << "Enter the exact path of the Folder (e.g., C:\\Users\\Administrator\\Documents\\Files): ";

    vector<string> v;
    string s;
    getline(cin, s); // Read folder path from user

    File_Sort(s, v); // Call function to sort and rename files

    cout << "If you are unsatisfied, you can undo the changes. Enter 1 to undo: ";
    int x;
    cin >> x;

    if (x == 1)
    {
        Undo(v, s); // Fixed function call
    }

    return 0;
}
