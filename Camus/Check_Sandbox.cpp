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
        std::cout << "--------------------------------" << std::endl;


    }

		
}


void Hardware_Check()
{
    std::cout << "[+] Checking Hardware Resources     [In Progress]" << std::endl;

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    DWORD numberOfProcessors = systemInfo.dwNumberOfProcessors;
    if (numberOfProcessors < 2)
    {
        std::cout << "[-] CPU Resource Check   [ERROR]" << std::endl;
        std::cout << "[-] Description: CPU is less than 2 Core   [ERROR]" << std::endl;
        std::cout << "[-] Exiting Program" << std::endl;
        abort();
    }
    else
    {
        std::cout << "[-] CPU Resource Check   [OK]" << std::endl;;

    }
        

    // check RAM
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    DWORD RAMMB = memoryStatus.ullTotalPhys / 1024 / 1024;
    if (RAMMB < 2048)
    {
        std::cout << "[-] RAM Resource Check    [ERROR]" << std::endl;
        std::cout << "[-] Description: RAM capacity is less than 2048   [ERROR]" << std::endl;
        std::cout << "[-] Exiting Program" << std::endl;
        abort();
    }
    else
    {
        std::cout << "[-] RAM Resource Check   [OK]" << std::endl;
        std::cout << "--------------------------------" << std::endl;

    }


}