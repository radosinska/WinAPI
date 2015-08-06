#ifndef FORM1_H
#define FORM1_H

#include "Form.h"
#include "Button.h"
#include "TextBox.h"
#include "EventArgs.h"
#include "MessageBox.h"

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
private:
	void button1_Click(void* sender, EventArgs* e);

	void Form1_FormClosing(void* sender, EventArgs* e);
	void Form1_FormClosed(void* sender, EventArgs* e);
};

#endif