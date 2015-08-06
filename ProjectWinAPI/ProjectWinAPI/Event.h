#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include "EventArgs.h"

template <typename Return, typename Arg1, typename Arg2>
class Event
{
private:
	class Handler
	{
	public:
		virtual ~Handler() { };
		virtual Return operator()(Arg1, Arg2) = 0;
	};

public:
	template <typename Class>
	class New : public Handler
	{
		typedef Return(Class::*Func)(Arg1, Arg2);

	private:
		Class* mThis;
		Func   mFunc;

	public:
		New(Class* aThis, Func aFunc) : mThis(aThis), mFunc(aFunc) { }

		virtual Return operator()(Arg1 arg1, Arg2 arg2)
		{
			return (mThis->*mFunc)(arg1, arg2);
		}
	};

private:
	std::vector<Handler*> mPtrs;

private:
	Event(const Event&);
	Event& operator=(const Event&);

public:
	Event() { }
	~Event()
	{
		typename std::vector<Handler*>::iterator i;
		for (i = mPtrs.begin(); i != mPtrs.end(); i++)
		{
			delete (*i);
		}
	}

	Event& operator+=(Handler* aPtr)
	{
		mPtrs.push_back(aPtr);
		return *this;
	}

	Return operator()(Arg1 arg1, Arg2 arg2)
	{
		for (typename std::vector<Handler*>::iterator i = mPtrs.begin(); i != mPtrs.end(); i++)
		{
			/*return */ (*(*i))(arg1, arg2);
		}
	}
};

#endif