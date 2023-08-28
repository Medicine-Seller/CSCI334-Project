//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

//File: MainForm.cpp
//This program creates a form that contains a button and a text log
//When the button is pressed, "Hello world" is printed into the text log

#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

/// <summary>
/// Main entry for the form
/// </summary>
/// <param name="args"></param>
void main(array<String^>^ args) {
	Application::EnableVisualStyles();						//Enable visual style for the form
	Application::SetCompatibleTextRenderingDefault(false);	//Set the compatible text rendering
	CSCI334Project::MainForm form;							//Initialize the mainform
	Application::Run(% form);								//Run the form
}