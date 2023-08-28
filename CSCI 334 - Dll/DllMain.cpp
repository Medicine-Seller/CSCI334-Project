//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

//File: DllMain.cpp
//Contains the modification for a data in the text application
#include "DllHeader.h"

/// <summary>
/// Main entry for dll
/// </summary>
/// <param name="hModule">Base address of this module</param>
void MainThread(HMODULE hModule)
{
    Console(true);                                                  //Enable the console

    uintptr_t baseAddr_Process = (uintptr_t)GetModuleHandle(NULL);  //Get the base address of this process
    std::cout << "This module base address is: " << std::hex << (uintptr_t)hModule << std::dec << std::endl;
    std::cout << "This process base address is: " << std::hex << baseAddr_Process << std::dec << std::endl;

    char* str = (char*)(baseAddr_Process + 0x11000);                //Get the data value at 0x11000
    std::cout << "Variable is at: " << std::hex << (uintptr_t)str << std::dec << " -> \"" << str << "\"" << std::endl;
    
    std::string input;                                              //A string variable to hold our inputs
    while (input != "exit")                                         //If exit, break loop
    {
        std::cout << ">:";
        std::cin >> input;                                          //Get input

        if (input == "set")                                         //If input is "set" then do...
        {
            std::getline(std::cin, input);                          //Get the next line input
            memset(str, 0, 1024);                                   //Set the data at variable baseAddr_Process + 0x11000 with zero
            memcpy(str, input.data()+1, input.size());              //Replace the data at variable with our input
        }
    }
    std::cout << "Dll unloaded!" << std::endl;

    Console(false);                                                 //Free the console
    FreeLibraryAndExitThread(hModule, 0);                           //Free library and exit the thread
}

/// <summary>
/// Entry of when the dll is injected
/// </summary>
/// <param name="hModule">Base address of this module</param>
/// <param name="ul_reason_for_call">The call reason</param>
/// <param name="lpReserved">Reserved space</param>
/// <returns>True or False</returns>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0); break; //On process attach do...
    case DLL_THREAD_ATTACH:     //On thread attach do...
    case DLL_THREAD_DETACH:     //On thread detach do...
    case DLL_PROCESS_DETACH:    //On process detach do...
        break;
    }
    return TRUE;
}


void Console(bool enabled)
{
    static bool isEnabled = false;                      //Static variable to keep track of console state

    if (!enabled && isEnabled)                          //Disable multiple initialization and allow closing
    {   
        isEnabled = false;
        FreeConsole();
        return;
    }

    AllocConsole();                                     //Allocate a console within the target process
    SetConsoleTitle(L"Console");                        //Set the console title
    FILE* newstreamptr;                                 //Create a new stream ptr
    freopen_s(&newstreamptr, "CONIN$", "r", stdin);     //Set streams for input
    freopen_s(&newstreamptr, "CONOUT$", "w", stdout);   //  for output
    freopen_s(&newstreamptr, "CONOUT$", "w", stderr);   //  for error
    isEnabled = true;
}