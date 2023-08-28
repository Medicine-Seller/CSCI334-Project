//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

// File: Main.cpp
// The dll injector used to inject a specific dll into a target process
// The program uses the Windows and TlHelp32 header

#include "MainHeader.h"

/// <summary>
/// Main entry for the injector
/// </summary>
/// <returns></returns>
int main()
{
    DWORD procId = 0;

    do
    {                                                       //Loop continously until a process id
        procId = GetProcId(PROCESS_NAME);                   //Attempt to get the process id
        std::cout << "Waiting for process..." << std::endl; //Print to the terminal the status
        Sleep(1000);
    } while (procId == 0);                                  //Check if process id is equal to zero, if not end

    if (!InjectDll(DLL_NAME, procId))                       //Inject the dll into the target process id
    {
        std::cout << "Dll failed to inject" << std::endl;   //Print to the terminal the status of the injection
        system("pause");                                    //Pause the program for feedback
    }

    return 0;
}

DWORD GetProcId(const char* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //Create a snapshot of all processes in the system

    if (hSnap == INVALID_HANDLE_VALUE)                              //If snapshot handle is invalid, return
    {
        CloseHandle(hSnap);
        return 0;
    }

    PROCESSENTRY32 procEntry;
    procEntry.dwSize = sizeof(procEntry);                           //Set size of process entry

    if (Process32First(hSnap, &procEntry))                          //If first process found, loop through all
    {
        do
        {                                                           
            if (strcmp(procEntry.szExeFile, procName) == 0)         //String compare the parameter with the process name
            {
                procId = procEntry.th32ProcessID;                   //If equal, set the procId to the process id then break
                break;
            }
        } while (Process32Next(hSnap, &procEntry));                 //Move onto the next process
    }
    CloseHandle(hSnap);
    return procId;                                                  //Return procId
}

bool InjectDll(const char* dllName, DWORD procId)
{
    struct stat buffer;                                             //Check if dll exist
    if (stat(dllName, &buffer))
    {
        std::cout << dllName << " does not exist" << std::endl;
        return false;
    }

    char dllPath[MAX_PATH];     
    if (!GetFullPathName(dllName, MAX_PATH, dllPath, 0))            //Get the full path of the dll
    {
        std::cout << "Can not get full path name" << std::endl;
        return false;
    }

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);      //Open a handle to the process id with PROCESS_ALL_ACCESS right
    if (hProc == INVALID_HANDLE_VALUE)                              //If handle is invalid, return
    {
        CloseHandle(hProc);
        std::cout << "Invalid handle value" << std::endl;
        return false;
    }

    void* allocLoc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);  //Allocate memory for the dll in the target process
    WriteProcessMemory(hProc, allocLoc, dllName, strlen(dllName) + 1, 0);                           //Write the path into allocated memory
    HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocLoc, 0, 0); //Create a thread (LoadLibrary) within the target process
                                                                                                            //Loadlibrary will load the path dll into the target process

    if (hThread)
        CloseHandle(hThread);

    if (hProc)
        CloseHandle(hProc);

    return true;
}