# Windows Process Viewer (C++)

A lightweight system utility written in C++ that lists all currently running processes on a Windows machine using the Windows Tool Help API.

---

# Overview

This project demonstrates low-level Windows system programming using native APIs. It retrieves and displays active processes in a structured table format, similar to a simplified Task Manager.

It is useful for learning:
- Windows API programming
- Process enumeration
- Memory-safe handle management
- System-level C++ development

---

# Features

- Lists all running processes on the system
- Displays Process ID (PID)
- Displays executable names
- Clean tabular console output
- Uses Windows Tool Help API
- Proper handle cleanup to prevent memory leaks

---

# Tech Stack

- C++
- Windows API
- Tool Help Library (`tlhelp32.h`)
- iostream & iomanip (standard C++ libraries)

---

# How It Works

1. Creates a snapshot of all running processes
2. Reads the first process using `Process32First`
3. Iterates through all processes using `Process32Next`
4. Prints each Process ID and name in a formatted table
5. Closes the system handle safely

---

# Code Overview

## Include Libraries

```cpp
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>
```

---

## Process Listing Function

This function captures and prints all running processes:

```cpp
void ListProcesses() {
    
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Failed to create snapshot." << endl;
        return; 
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    cout << left << setw(10) << "PID" << " | " << "Process Name" << endl;
    cout << "------------------------------------------" << endl;

    do {
        cout << left << setw(10) << pe32.th32ProcessID
             << " | " << pe32.szExeFile << endl;

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}
```

---

## Main Function

Entry point of the program:

```cpp
int main() {
    ListProcesses();
    
    system("pause");
    return 0;
}
```

---

# Compilation (Windows)

You can compile using MinGW or MSVC.

## Using g++

```bash
g++ main.cpp -o process_viewer
```

## Run the program

```bash
process_viewer.exe
```

---

# Example Output

```text
PID        | Process Name
------------------------------------------
1234       | chrome.exe
5678       | explorer.exe
9101       | code.exe
```

---

# Safety Notes

- This program only reads system process information
- It does NOT modify or terminate processes
- Requires Windows OS to run (uses Windows API)

---

# Future Improvements

- Add CPU and memory usage per process
- Add search/filter functionality
- Export process list to CSV or JSON
- Add GUI version using Qt or WinAPI
- Add process termination feature (advanced)

---

# License

For educational and learning purposes only.
