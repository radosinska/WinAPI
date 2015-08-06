#include "Form1.h"

Form1::Form1()
{
	InitializeComponent();
}

Form1::~Form1()
{
}

void Form1::button1_Click(void* sender, EventArgs* e)
{
	PSTR message;
	int textLength;
	
	textLength = GetWindowTextLength(textBox1->hWnd);
	// Allocate memory for the string and copy the string into the memory. 
	message = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(textLength + 1), MEM_COMMIT, PAGE_READWRITE);

	GetWindowTextA(textBox1->hWnd, message, textLength + 1);
	
	MessageBox::Show(message, "MessageBox");

	// Free the memory 
	VirtualFree(message, 0, MEM_RELEASE);
}

void Form1::Form1_FormClosing(void* sender, EventArgs* e)
{
	//MessageBox::Show("FormClosing", "MessageBox");
	MessageBox(this->hWnd, "FormClosing", "MessageBox", MB_ICONASTERISK | MB_OK);
}

void Form1::Form1_FormClosed(void* sender, EventArgs* e)
{
	MessageBox::Show("FormClosed", "MessageBox");
}

void Form1::InitializeComponent()
{
	this->button1 = new Button();
	this->textBox1 = new TextBox();

	this->SuspendLayout();
	
	// 
	// button1
	// 
	this->button1->Location = new Drawing::Point(20, 190);
	this->button1->Name = "button1";
	this->button1->Size = new Drawing::Size(75, 23);
	this->button1->Text = "button1";
	this->button1->Click += new EventHandler::New<Form1>(this, &Form1::button1_Click);

	// 
	// textBox1
	// 
	this->textBox1->Location = new Drawing::Point(20, 20);
	this->textBox1->Name = "textBox1";
	this->textBox1->Size = new Drawing::Size(300, 150);

	// 
	// MainForm
	// 
	this->ClientSize = new Drawing::Size(500, 300);
	
	this->Controls->Add(this->button1);
	this->Controls->Add(this->textBox1);

	this->FormClosing += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosing);
	this->FormClosed += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosed);

	this->Name = "MainForm";
	this->Text = "Nazwa aplikacji";
	this->ResumeLayout(false);
}