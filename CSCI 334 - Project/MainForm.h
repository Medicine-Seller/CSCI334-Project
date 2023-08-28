//CSCI 334
//Communication for Computing Sciences
//Date modified: 12-8-2022

//File: MainForm.h
//This file holds the UI form methods

#pragma once

namespace CSCI334Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Text application that prints "Hello world" to the log box when button is pressed
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ LogTextBox;
	protected:
	private: System::Windows::Forms::Button^ Button1;
	private: System::Windows::Forms::Label^ label1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->LogTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->Button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// LogTextBox
			// 
			this->LogTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->LogTextBox->ForeColor = System::Drawing::Color::RosyBrown;
			this->LogTextBox->Location = System::Drawing::Point(12, 73);
			this->LogTextBox->Name = L"LogTextBox";
			this->LogTextBox->ReadOnly = true;
			this->LogTextBox->Size = System::Drawing::Size(361, 116);
			this->LogTextBox->TabIndex = 0;
			this->LogTextBox->Text = L"";
			this->LogTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::LogTextBox_TextChanged);
			// 
			// Button1
			// 
			this->Button1->Location = System::Drawing::Point(12, 12);
			this->Button1->Name = L"Button1";
			this->Button1->Size = System::Drawing::Size(101, 23);
			this->Button1->TabIndex = 1;
			this->Button1->Text = L"Print \"Hello world\"";
			this->Button1->UseVisualStyleBackColor = true;
			this->Button1->Click += gcnew System::EventHandler(this, &MainForm::Button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Log:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(385, 201);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Button1);
			this->Controls->Add(this->LogTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MainForm";
			this->Text = L"CSCI 334 - Text Application";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// <summary>
	/// Output the message into the log text of the application
	/// </summary>
	private: void Log(char str[]) {
		String^ newStr = gcnew String(str);
		LogTextBox->AppendText(newStr+"\n");
	}

	/// <summary>
	/// On button click, log "Hello world" into the log box
	/// </summary>
	private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {
		static char str[1024] = "Hello world\0";
		Log(str);
	}

	/// <summary>
	/// On log text box changes, update the log box to scroll to latest position
	/// </summary>
	private: System::Void LogTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		LogTextBox->SelectionStart = LogTextBox->Text->Length;
		LogTextBox->ScrollToCaret();
	}
	};
}
