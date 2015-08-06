#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Event.h"
#include "EventArgs.h"

typedef Event<void, void*, EventArgs*> EventHandler;

#endif
