#include <iostream>     // Standard input-output stream library
#include <windows.h>    // The core Windows library (required for Handles and system types)
#include <tlhelp32.h>   // Tool Help library (required for taking snapshots of processes)
#include <iomanip>      // Used for "io manipulators" to format the output table
using namespace std;    // This allows us to use cout, endl, left, etc., without the std:: prefix

void ListProcesses() {
    
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Failed to create snapshot." << endl;
        return; 
    }

    PROCESSENTRY32 pe32;
    
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap); // Always clean up handles to avoid memory leaks.
        return;
    }

    // Formatting the header: 'left' aligns text, 'setw(10)' sets a column width.
    cout << left << setw(10) << "PID" << " | " << "Process Name" << endl;
    cout << "------------------------------------------" << endl;

    do {
        cout << left << setw(10) << pe32.th32ProcessID << " | " << pe32.szExeFile << endl;

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

int main() {
    ListProcesses();
    
    system("pause"); 
    
    return 0; 
}