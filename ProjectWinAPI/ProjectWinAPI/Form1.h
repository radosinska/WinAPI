#ifndef FORM1_H
#define FORM1_H

#define _WINSOCKAPI_ 

#include "Form.h"
#include "Button.h"
#include "TextBox.h"
#include "EventArgs.h"
#include "MessageBox.h"
#include "TextView.h"

class Form1 : public Form
{
//public:
//	static Form1& getInstance()
//	{
//		static Form1 instance;
//		return instance;
//	}
//private:
//	Form1();
//	Form1(Form1 const&); //Don't implement
//	void operator=(Form1 const&); //Don't implement
//
public:
	Form1();
	~Form1();

//public:
//	static TextView& GetTextView();

private:
	void InitializeComponent();
private:
	Button *button1;
	TextBox *textBox1;
	TextView *textView1;

private:
	void button1_Click(void* sender, EventArgs* e);

	void Form1_FormClosing(void* sender, EventArgs* e);
	void Form1_FormClosed(void* sender, EventArgs* e);

private:
	void RefreshTextView(PSTR,int);
	//void updateLoop(void *);
};

#endif