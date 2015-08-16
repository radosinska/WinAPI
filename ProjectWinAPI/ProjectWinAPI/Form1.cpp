#include "Form1.h"
#include "ClientProcedures.h"
#include <process.h>

ClientProcedures * client;

void updateLoop(void *);
void AddMessageToTextView(HWND, char*, int clientId);
void ActiveGameLevel(int, ImageButton**);
void DisableGameLevel(int, ImageButton**);
void SetInactiveFields(int, ImageButton**);

int Form1::level = 0;
int Form1::clientId = 0;
bool Form1::isGameStart = false;

Form1::Form1()
{
	client = new ClientProcedures();

	gameButtonArray = new ImageButton*[ARRAY_LENGTH];
	resultButtonArray = new ImageButton*[ARRAY_LENGTH];
	buttonVector = new ImageButton*[VECTOR_LENGTH];

	InitializeComponent();

	level = 1;

	DataToPass * data = new DataToPass;
	data->hForm1 = this->hWnd;
	data->hTextView = this->messagesView->hWnd;

	data->hResultButtons = new HWND[ARRAY_LENGTH];
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		data->hResultButtons[i] = this->resultButtonArray[i]->hWnd;
	}

	data->gameButtons = new ImageButton*[ARRAY_LENGTH];
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		data->gameButtons[i] = this->gameButtonArray[i];
	}

	_beginthread(updateLoop, 0, (void*)data);

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

	this->checkButton->Click += new EventHandler::New<Form1>(this, &Form1::checkButton_Click);

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
		gameButtonArray[i]->Name = "gameButton";
		gameButtonArray[i]->ButtonId = i;
		gameButtonArray[i]->BitmapId = 0;
		gameButtonArray[i]->Location = new Drawing::Point(x, y);
		gameButtonArray[i]->Size = gameButtonSize;
		gameButtonArray[i]->Click += new EventHandler::New<Form1>(this, &Form1::gameButton_Click);
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

		resultButtonArray[i]->Name = "resultButton";
		resultButtonArray[i]->ButtonId = i;
		resultButtonArray[i]->BitmapId = 0;
		resultButtonArray[i]->Location = new Drawing::Point(x, y);
		resultButtonArray[i]->Size = resultButtonSize;
	}

	y = 415 - 50;
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

		buttonVector[i]->Name = "gameButton";
		buttonVector[i]->ButtonId = i;
		buttonVector[i]->BitmapId = 0;
		buttonVector[i]->Location = new Drawing::Point(x, y);
		buttonVector[i]->Size = gameButtonSize;
	}

	// 
	// MainForm
	// 
	this->ClientSize = new Drawing::Size(700, 470);

	//this->Controls->Add(this->infoBox);
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
	this->Text = "Chat & Play";
	this->ResumeLayout(false);

	i = 0;
	HBITMAP hBitmap;
	int idBitmap = IDB_BITMAP1;

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

	client->sendMessagePacket(message);

	SetWindowText(messageBox->hWnd, (LPSTR)NULL);

	VirtualFree(message, 0, MEM_RELEASE);

}

void Form1::gameButton_Click(void* sender, EventArgs* e)
{
	if (Form1::isGameStart)
	{
		ImageButton * control = (ImageButton *)sender;

		int idBitmap = control->BitmapId;

		if (idBitmap == 0)
		{

		}
		else if (idBitmap == 121)
		{
			MessageBox(this->hWnd, "Wait ! Your oponent move.", "Information", MB_OK);
		}
		else
		{
			if (idBitmap > 111 && idBitmap < 118)
			{
				idBitmap++;
			}
			else
			{
				idBitmap = 112;
			}

			HBITMAP hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
			SendMessage(control->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

			control->BitmapId = idBitmap;
		}
	}
	else
	{
		MessageBox(this->hWnd, "Wait for your oponent.", "Information", MB_OK);
	}
	
}

void Form1::checkButton_Click(void * sender, EventArgs* e)
{
	if (Form1::isGameStart)
	{
		int idButton = (10 - level) * 4;

		client->sendGamePacket(
			gameButtonArray[idButton]->BitmapId,
			gameButtonArray[idButton + 1]->BitmapId,
			gameButtonArray[idButton + 2]->BitmapId,
			gameButtonArray[idButton + 3]->BitmapId
			);
	}
	else
	{
		MessageBox(this->hWnd, "Wait for your oponent.", "Information", MB_OK);
	}

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

void updateLoop(void * arg)
{
	HWND hForm1;
	HWND hTextView;
	HWND * hResultButtons;
	ImageButton ** gameButtons;

	DataToPass * data = (DataToPass*)arg;

	hForm1 = data->hForm1;
	hTextView = data->hTextView;
	hResultButtons = data->hResultButtons;
	gameButtons = data->gameButtons;

	int black = 0;
	int white = 0;

	while (true)
	{
		Packet packet = client->update();

		if (packet.packet_type == GAME_EVENT)
		{

			if (packet.client_id != Form1::clientId)
			{
				int idButton = (10 - Form1::level) * 4;

				HBITMAP hBitmap;

				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(packet.bitmapId1));
				SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

				idButton++;
				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(packet.bitmapId2));
				SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

				idButton++;
				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(packet.bitmapId3));
				SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

				idButton++;
				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(packet.bitmapId4));
				SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
			}

			black = packet.black;
			white = packet.white;

			int level = Form1::level;

			int idButton = (10 - level) * 4;

			HBITMAP hBitmap;
			int idBitmap = IDB_BITMAP9;

			while (white > 0)
			{
				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
				SendMessage(hResultButtons[idButton], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				white--;
				idButton++;

			}

			idBitmap = IDB_BITMAP8;

			while (black > 0)
			{
				hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
				SendMessage(hResultButtons[idButton], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				black--;
				idButton++;
			}

			if (packet.black == 4)
			{

				DisableGameLevel(Form1::level, gameButtons);
				Form1::level++;
				SetInactiveFields(Form1::level, gameButtons);

				if (packet.client_id != Form1::clientId)
				{
					MessageBox(hForm1, "End game.Your opponent win!", "Information", MB_OK);
				}
				else
				{
					MessageBox(hForm1, "End game.You win !", "Information", MB_OK);

				}
			}
			else
			{
				DisableGameLevel(Form1::level, gameButtons);
				Form1::level++;
				if (packet.client_id != Form1::clientId)
				{
					ActiveGameLevel(Form1::level, gameButtons);
				}
				else
				{
					SetInactiveFields(Form1::level, gameButtons);
				}
			}
		}

		else if (packet.packet_type == MESSAGE_EVENT)
		{
			int messageLength = strlen(packet.message);
			char *msg = (char *)malloc(1 + messageLength);
			int k = 0;

			for (k; k < messageLength; k++)
			{
				msg[k] = packet.message[k];
			}
			msg[k] = '\0';

			AddMessageToTextView(hTextView, msg, packet.client_id);
		}
		else if (packet.packet_type == START_EVENT)
		{
			MessageBox(hForm1, "You can start the game.", "Information", MB_OK);
			Form1::isGameStart = true;

			if (Form1::clientId == packet.client_id)
			{
				ActiveGameLevel(Form1::level, gameButtons);
			}
			else
			{
				SetInactiveFields(Form1::level, gameButtons);
			}

		}
		else if (packet.packet_type == INIT_CONNECTION)
		{
			Form1::clientId = packet.client_id;
		}
		else if (packet.packet_type == EMPTY_PACKET)
		{

		}
		else
		{
			MessageBox::Show("Error in packet types", "Error");
		}
	}
}

void AddMessageToTextView(HWND hTextView, char * message, int clientId)
{
	PSTR content;
	int contentLength;

	contentLength = GetWindowTextLength(hTextView);
	content = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(contentLength + 1), MEM_COMMIT, PAGE_READWRITE);
	GetWindowTextA(hTextView, content, contentLength + 1);

	PSTR newContent;
	if (Form1::clientId == clientId)
	{
		newContent = (char *)malloc(1 + contentLength + strlen(message) + strlen("\r\nYou >> "));
		strcpy(newContent, "You >> ");
		strcat(newContent, message);
		strcat(newContent, "\r\n");
		strcat(newContent, content);
	}
	else
	{
		newContent = (char *)malloc(1 + contentLength + strlen(message) + strlen("\r\nYour friend >> "));
		strcpy(newContent, "Your friend >> ");
		strcat(newContent, message);
		strcat(newContent, "\r\n");
		strcat(newContent, content);
	}

	SetWindowText(hTextView, newContent);

	free(newContent);
	VirtualFree(content, 0, MEM_RELEASE);
}

void ActiveGameLevel(int n, ImageButton** gameButtons)
{
	int idButton = (10 - n) * 4;
	int idButtonMax = idButton + 4;

	HBITMAP hBitmap;
	int idBitmap = IDB_BITMAP1;

	for (idButton; idButton < idButtonMax; idButton++)
	{
		hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
		SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		gameButtons[idButton]->BitmapId = idBitmap;
	}
}

void DisableGameLevel(int n, ImageButton** gameButtons)
{
	int idButton = (10 - n) * 4;
	int idButtonMax = idButton + 4;
	for (idButton; idButton < idButtonMax; idButton++)
	{
		gameButtons[idButton]->BitmapId = 0;
	}
}

void SetInactiveFields(int n, ImageButton** gameButtons)
{
	int idButton = (10 - n) * 4;
	int idButtonMax = idButton + 4;

	HBITMAP hBitmap;
	int idBitmap = IDB_BITMAP10;

	for (idButton; idButton < idButtonMax; idButton++)
	{
		hBitmap = LoadBitmap(Application::hInstance, MAKEINTRESOURCE(idBitmap));
		SendMessage(gameButtons[idButton]->hWnd, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
		gameButtons[idButton]->BitmapId = idBitmap;
	}
}
