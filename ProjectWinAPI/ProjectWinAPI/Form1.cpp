#include "Form1.h"
#include "ClientProcedures.h"
#include <process.h>

ClientProcedures * client;
void updateLoop(void *);

void updateLoop(void * arg)
{
	while (true)
	{
		char* message = client->update();
		if (message)
		{
			//SetWindowTextA((HWND)arg, tmp);
			HWND hMessagesBox = (HWND)arg;
			PSTR content;
			int contentLength;

			contentLength = GetWindowTextLength(hMessagesBox);
			content = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(contentLength + 1), MEM_COMMIT, PAGE_READWRITE);
			GetWindowTextA(hMessagesBox, content, contentLength + 1);

			PSTR newContent = (char *)malloc(1 + contentLength + strlen(message) + strlen("\n>>"));
			strcpy(newContent, content);
			strcat(newContent, ">>");
			strcat(newContent, message);
			strcat(newContent, "\n");

			SetWindowText(hMessagesBox, newContent);

			free(newContent);
			VirtualFree(content, 0, MEM_RELEASE);
		}
	}
}

Form1::Form1()
{
	client = new ClientProcedures();

	InitializeComponent();

	_beginthread(updateLoop, 0, textView1->hWnd);
}

Form1::~Form1()
{
}

void Form1::button1_Click(void* sender, EventArgs* e)
{
	PSTR message;
	int textLength;

	textLength = GetWindowTextLength(textBox1->hWnd);
	message = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(textLength + 1), MEM_COMMIT, PAGE_READWRITE);
	GetWindowTextA(textBox1->hWnd, message, textLength + 1);

	client->sendActionPackets(message);

	SetWindowText(textBox1->hWnd, (LPSTR)NULL);



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
	this->textView1 = new TextView();
	this->imageButton1 = new ImageButton();

	this->SuspendLayout();

	// 
	// textView1
	// 
	this->textView1->Location = new Drawing::Point(20, 20);
	this->textView1->Name = "textBox2";
	this->textView1->Size = new Drawing::Size(300, 150);
	
	// 
	// textBox1
	// 
	this->textBox1->Location = new Drawing::Point(20, 180);
	this->textBox1->Name = "textBox1";
	this->textBox1->Size = new Drawing::Size(300, 50);


	// 
	// button1
	// 
	this->button1->Location = new Drawing::Point(240, 240);
	this->button1->Name = "button1";
	this->button1->Size = new Drawing::Size(80, 25);
	this->button1->Text = "send";
	this->button1->Click += new EventHandler::New<Form1>(this, &Form1::button1_Click);

	// 
	// imageButton1
	// 
	this->imageButton1->Location = new Drawing::Point(20, 240);
	this->imageButton1->Name = "imageButton1";
	this->imageButton1->Size = new Drawing::Size(80, 80);
	this->imageButton1->Text = "withImage";


	// 
	// MainForm
	// 
	this->ClientSize = new Drawing::Size(500, 500);

	this->Controls->Add(this->button1);
	this->Controls->Add(this->textBox1);
	this->Controls->Add(this->textView1);
	this->Controls->Add(this->imageButton1);

	this->FormClosing += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosing);
	this->FormClosed += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosed);

	this->Name = "MainForm";
	this->Text = "Nazwa aplikacji";
	this->ResumeLayout(false);

	//TODO:To past in different place; only to test 
	HBITMAP b = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	SendMessage(this->imageButton1->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)b);
}