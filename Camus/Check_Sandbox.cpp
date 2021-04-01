#include "Check_Sandbox.h"
#include <windows.h>
#include <iostream>


#pragma comment(lib, "user32.lib")


void Mouse_Movement()
{
    std::cout << "[+] Checking Mouse Movement     [In Progress]" << std::endl;

	HMODULE dllhandle;
	dllhandle = LoadLibrary(TEXT("User32.dll"));
	char GetCursorPos[] = { 'G','e','t','C','u','r','s','o','r','P','o','s', 0 };
	using GetCursorPosPrototype = BOOL(WINAPI*)(LPPOINT);
	GetCursorPosPrototype hGetCursorPos = (GetCursorPosPrototype)GetProcAddress(dllhandle, GetCursorPos);

	POINT lpPoint1, lpPoint2;
	hGetCursorPos(&lpPoint1);
	Sleep(10000);
	hGetCursorPos(&lpPoint2);
    if ((lpPoint1.x == lpPoint2.x) && (lpPoint1.y == lpPoint2.y))
    {
        std::cout << "[-] Mouse Movement Check    [ERROR]" << std::endl;
        std::cout << "[-] Exiting Program" << std::endl;
        abort();
    }


    else
    {
        std::cout << "[-] Mouse Movement Check    [OK]" << std::endl;

    }

		
}
