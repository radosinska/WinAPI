#include "Form1.h"

//#include "Point.h"
#include "Size.h"

Form1::Form1()
{
	InitializeComponent();
}

void Form1::InitializeComponent()
{
	//this->button1 = new Button();
	//this->button2 = new Button();
	
	////this.SuspendLayout();
	
	// 
	// button1
	// 
	//this->button1->Location = new Point(33, 26);
	//this->button1->Name = "button1";
	//this->button1->Size = new Drawing::Size(75, 23);
	//////this.button1.TabIndex = 0;
	//this->button1->Text = "button1";
	//////this.button1.UseVisualStyleBackColor = true;

	// 
	// button2
	// 
	//this->button2->Location = new Point(33, 56);
	//this->button2->Name = "button2";
	//this->button2->Size = new Drawing::Size(75, 23);
	//this->button2->Text = "button2";

	// 
	// MainForm
	// 
	////this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
	////this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
	this->ClientSize = new Drawing::Size(504, 302); //Size from namespace: Drawing
	//this->Controls->Add(this->button1);
	//this->Controls->Add(this->button2);
	this->Name = "MainForm";
	this->Text = "Nazwa aplikacji";
	this->ResumeLayout(false);
}