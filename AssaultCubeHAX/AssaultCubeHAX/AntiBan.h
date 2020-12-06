#include <Windows.h>
#include <string>

#include "OffSet.h"

using namespace std;

void ChangeNickname(HANDLE handle, DWORD ModuleAdress)
{
	while (true)
	{
		Sleep(1000);
		string Nickname = randomString();
		uintptr_t Health_Addr = ModuleAdress + Name_Offset;
		WriteProcessMemory(handle, (BYTE*)Health_Addr, Nickname.c_str(), sizeof(Nickname), nullptr);
	}
}

void ClientNumberBypass(HANDLE handle, DWORD ModuleAdress)
{
}

void PermissionHIGH()
{
}