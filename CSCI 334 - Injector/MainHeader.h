//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

//File: MainHeader.h
//Contains macros and the functions for Main.cpp

#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

/// @warning If the process name is changed, the injector will not be able to find the process
#define PROCESS_NAME "CSCI 334 - Project.exe"  
/// @warning If the dll name is changed, the inject will not be able to locate the dll
#define DLL_NAME "CSCI 334 - Dll.dll"

/// <summary>
/// Inject the specified dll into the target process id
/// </summary>
/// <param name="dllName">The dll name including file extension</param>
/// <param name="procId">The id of the target process</param>
/// <returns>True if injection is sucessful, otherwise false</returns>
bool InjectDll(const char* dllName, DWORD procId);


/// <summary>
/// Get the process id from the name of a process
/// </summary>
/// <param name="procName">The name of the process</param>
/// <returns>Nonzero if the process is found and the process id is valid</returns>
DWORD GetProcId(const char* procName);