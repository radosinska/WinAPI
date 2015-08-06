#ifndef ControlCollection_H
#define ControlCollection_H

#include <list>

class Control;

class ControlCollection : public std::list<Control*>
{
private:
	Control* owner;
public:
	ControlCollection(Control *owner);
	void Add(Control *control);
};

#endif