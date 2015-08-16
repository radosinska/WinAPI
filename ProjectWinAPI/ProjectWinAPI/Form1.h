#ifndef FORM1_H
#define FORM1_H

#define _WINSOCKAPI_ 

#define ARRAY_LENGTH 40
#define ROW_LENGTH 4
#define VECTOR_LENGTH 7

#include "Form.h"
#include "Button.h"
#include "TextBox.h"
#include "EventArgs.h"
#include "MessageBox.h"
#include "TextView.h"
#include "ImageButton.h"
#include "DataToPass.h"
#include "resource.h"

class Form1 : public Form
{
public:
	Form1();
	~Form1();

private:
	void WaitingForOponent();
	void InitializeComponent();

private:
	TextView * infoBox;
	TextView *messagesView;
	TextBox *messageBox;
	Button *sendButton;

	Button *checkButton;

	ImageButton **gameButtonArray;
	ImageButton **resultButtonArray;
	ImageButton **buttonVector;

public:
	//static DataToPass * data;

	static int clientId;
	static int level;
	
private:
	void sendButton_Click(void* sender, EventArgs* e);

	void gameButton_Click(void* sender, EventArgs* e);
	void checkButton_Click(void * sender, EventArgs* e);

	void Form1_FormClosing(void* sender, EventArgs* e);
	void Form1_FormClosed(void* sender, EventArgs* e);
};

#endif