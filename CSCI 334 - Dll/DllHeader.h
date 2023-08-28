//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

//File: DllHeader.h
//Contains the functions and library headers for the main dll

#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>

/// <summary>
/// Open or close the console depending on the parameter passed
/// </summary>
/// <param name="enabled">Enable or disable the console</param>
void Console(bool enabled);
