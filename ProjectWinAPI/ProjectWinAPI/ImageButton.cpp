#include "ImageButton.h"

ImageButton::ImageButton()
{
	this->className = "Button";
	this->style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT | BS_DEFPUSHBUTTON | BS_BITMAP;
}

ImageButton::~ImageButton()
{
}
