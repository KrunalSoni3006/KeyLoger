
#include "stdafx.h"

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
#define _WIN32_WINNT 0x050

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			//if (fEatKeystroke = (p->vkCode == 0x41)) {     //redirect a to b
			//	printf("Hello a\n");
			//	keybd_event('B', 0, 0, 0);
			//	keybd_event('B', 0, KEYEVENTF_KEYUP, 0);}
			if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN)) // Keydown
			{
				char dt[26];
				time_t result = time(NULL);

				string f_str = to_string(p->vkCode);
				//f_str = f_str + to_string(ctime_s(dt, sizeof dt, &result)); +"/n";
				std::string::size_type sz;
				char temp = stoi(f_str, &sz);
				cout << temp << endl;
				break;
			}
			break;

		}
	}
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

int main()
{
	// Install the low-level keyboard & mouse hooks
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);

	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(hhkLowLevelKybd);

	return(0);
}