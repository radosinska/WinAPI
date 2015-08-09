#include "ImageButton.h"

ImageButton::ImageButton()
{
	this->className = "Button";
	this->style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP;
}

ImageButton::~ImageButton()
{
}
