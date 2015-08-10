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
	
	gameButtonArray = new ImageButton*[ARRAY_LENGTH];
	resultButtonArray = new ImageButton*[ARRAY_LENGTH];
	buttonVector = new ImageButton*[VECTOR_LENGTH];

	InitializeComponent();

	_beginthread(updateLoop, 0, messagesView->hWnd);
}

Form1::~Form1()
{
	delete[] gameButtonArray;
	delete[] resultButtonArray;
	delete[] buttonVector;
}

void Form1::InitializeComponent()
{
	this->messagesView = new TextView();
	this->messageBox = new TextBox();
	this->sendButton = new Button();

	this->checkButton = new Button();

	this->SuspendLayout();

	// 
	// messagesView
	// 
	this->messagesView->Location = new Drawing::Point(300, 35);
	this->messagesView->Name = "textBox2";
	this->messagesView->Size = new Drawing::Size(365, 250);
	
	// 
	// messageBox
	// 
	this->messageBox->Location = new Drawing::Point(300, 295);
	this->messageBox->Name = "messageBox";
	this->messageBox->Size = new Drawing::Size(365, 110);

	// 
	// sendButton
	// 
	this->sendButton->Location = new Drawing::Point(585, 415);
	this->sendButton->Name = "sendButton";
	this->sendButton->Size = new Drawing::Size(80, 25);
	this->sendButton->Text = "send";

	this->sendButton->Click += new EventHandler::New<Form1>(this, &Form1::sendButton_Click);
	
	// 
	// checkButton
	// 
	this->checkButton->Location = new Drawing::Point(45, 385);
	this->checkButton->Name = "checkButton";
	this->checkButton->Size = new Drawing::Size(210, 20);
	this->checkButton->Text = "check";

	Drawing::Size * gameButtonSize = new Drawing::Size(25, 25);

	int i = 0;
	int x = 0;
	int y = 0;

	for (i; i < ARRAY_LENGTH; i++)
	{
		gameButtonArray[i] = new ImageButton();

		int remainder = i % 4;
		switch (remainder)
		{
		case 0:
			y += 35;
			x = 35;
			break;
		default:
			x += 35;
			break;
		}
		
		gameButtonArray[i]->Location = new Drawing::Point(x, y);
		gameButtonArray[i]->Size = gameButtonSize;
	}

	Drawing::Size * resultButtonSize = new Drawing::Size(15, 15);

	i = 0;
	x = 0;
	y = 5;
	for (i; i < ARRAY_LENGTH; i++)
	{
		resultButtonArray[i] = new ImageButton();

		int remainder = i % 4;
		switch (remainder)
		{
		case 0:
			x = 175;
			y += 35;
			break;
		default:
			x += 25;
			break;
		}

		resultButtonArray[i]->Location = new Drawing::Point(x, y);
		resultButtonArray[i]->Size = resultButtonSize;
	}
	
	y = 415-50;
	i = 0;
	for (i; i < VECTOR_LENGTH; i++)
	{
		buttonVector[i] = new ImageButton();

		int remainder = i % 7;
		switch (remainder)
		{
		case 0:
			y += 50;
			x = 35;
			break;
		default:
			x += 35;
			break;
		}

		buttonVector[i]->Location = new Drawing::Point(x, y);
		buttonVector[i]->Size = gameButtonSize;
	}

	// 
	// MainForm
	// 
	this->ClientSize = new Drawing::Size(700, 470);
	
	this->Controls->Add(this->messagesView);
	this->Controls->Add(this->messageBox);
	this->Controls->Add(this->sendButton);

	this->Controls->Add(this->checkButton);

	i = 0;
	for (i; i < ARRAY_LENGTH; i++)
	{
		this->Controls->Add(gameButtonArray[i]);
	}

	i = 0;
	for (i; i < ARRAY_LENGTH; i++)
	{
		this->Controls->Add(resultButtonArray[i]);
	}

	i = 0;
	for (i; i < VECTOR_LENGTH; i++)
	{
		this->Controls->Add(buttonVector[i]);
	}

	//this->FormClosing += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosing);
	//this->FormClosed += new EventHandler::New<Form1>(this, &Form1::Form1_FormClosed);

	this->Name = "MainForm";
	this->Text = "Nazwa aplikacji";
	this->ResumeLayout(false);

	i = 0;
	HBITMAP hBitmap;
	int idBitmap = IDB_BITMAP1;

	i = ARRAY_LENGTH - ROW_LENGTH;
	for (i; i < ARRAY_LENGTH; i++)
	{
		hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
		SendMessage(gameButtonArray[i]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	}

	i = 0;
	for (i; i < VECTOR_LENGTH; i++)
	{
		hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
		SendMessage(buttonVector[i]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		idBitmap++;
	}
}

void Form1::sendButton_Click(void* sender, EventArgs* e)
{
	PSTR message;
	int textLength;

	textLength = GetWindowTextLength(messageBox->hWnd);
	message = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(textLength + 1), MEM_COMMIT, PAGE_READWRITE);
	GetWindowTextA(messageBox->hWnd, message, textLength + 1);

	client->sendActionPackets(message);

	SetWindowText(messageBox->hWnd, (LPSTR)NULL);

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