#ifndef ControlCollection_H
#define ControlCollection_H

#include "Control.h"
#include <list>

class ControlCollection : public std::list<Control*>
{
private:
	Control *owner;
public:
	ControlCollection(Control *owner);
	void Add(Control *control);
};

#endif