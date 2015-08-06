#include "ControlCollection.h"
#include "Control.h"

ControlCollection::ControlCollection(Control *owner)
{
	this->owner = owner;
}

void ControlCollection::Add(Control *control)
{
	control->parent = this->owner;
	push_back(control);
}

