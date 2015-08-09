#ifndef FORM1_H
#define FORM1_H

#define _WINSOCKAPI_ 

#include "Form.h"
#include "Button.h"
#include "TextBox.h"
#include "EventArgs.h"
#include "MessageBox.h"
#include "TextView.h"
#include "ImageButton.h"
#include "resource.h"

class Form1 : public Form
{
public:
	Form1();
	~Form1();

private:
	void InitializeComponent();

private:
	Button *button1;
	TextBox *textBox1;
	TextView *textView1;
	ImageButton *imageButton1;

private:
	void button1_Click(void* sender, EventArgs* e);

	void Form1_FormClosing(void* sender, EventArgs* e);
	void Form1_FormClosed(void* sender, EventArgs* e);

private:
	void RefreshTextView(PSTR,int);
	//void updateLoop(void *);
};

#endif