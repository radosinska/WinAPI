#ifndef MESSAGE_H
#define MESSAGE_H

#define _WINSOCKAPI_

#include <windows.h>

typedef struct Message
{
public:
	HWND hWnd;
	UINT Msg;
	WPARAM WParam;
	LPARAM LParam;

	static Message Create(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		Message message;
		message.hWnd = hWnd;
		message.Msg = msg;
		message.WParam = wparam;
		message.LParam = lparam;
		return message;
	}
} Message;

#endif