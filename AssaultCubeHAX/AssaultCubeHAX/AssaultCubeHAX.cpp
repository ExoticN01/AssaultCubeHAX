#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>

#include "Process.h"
#include "OffSet.h"
#include "ConsoleColor.h"
#include "Fonctions.h"
#include "AntiBan.h"

using namespace std;

DWORD ASHDebug = false;

//Var/Strings/Char/int
int HealthValue = 0;
int AmmoValue = 0;

void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

int main()
{
    SetConsoleTitle("AssaultCubeHAX | Initalizing");
    cout << "Getting Process ID...";
    int pid = GetProcessID("ac_client.exe");
    if (pid == NULL)
    {
        cout << endl << red <<"ERROR: No Process Found!" << white <<endl;
        cin.ignore();
        exit(1);
    }
    cout << green << " Sucess!" << white << endl;
    cout << "Process ID: " << pid << endl;
    cout << white <<"Creating Handle on Process";
    HANDLE HandleCreate = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
    cout << green << " Sucess!" << endl;
    cout << white <<"Getting ModuleBase Adresses";
    uintptr_t ModuleBase = GetModuleBaseAddress(pid, "ac_client.exe");
    cout << green << " Sucess!" << endl;
    cout << white <<"Getting PlayerStructure Offset";
    uintptr_t PlayerStructure = 0;
    ReadProcessMemory(HandleCreate, (BYTE*)ModuleBase + Player_Adress, &PlayerStructure, sizeof(PlayerStructure), nullptr);
    cout << green << " Sucess!" << endl;
    cout << white <<"Loading Functions";
    cout << green << " Sucess!" << endl;
    cout << white <<"Finishes Inializing, Loading Menu" << endl;
    Sleep(2000);
    SetConsoleTitle("AssaultCubeHAXX | Menu");
    clear();
    cout << "AssaultCubeHAXX v0.1" << endl;
    cout << endl;
    cout << endl;
    for (; ;)
    {
        cout << "HAXX->";
        string input;
        getline(cin, input);
        if (input == "sethealth")
        {
            cout << "What Number Of Health Do you Want?" << endl;
            int NewHealth;
            cin >> NewHealth;
            if (NewHealth == NULL || NewHealth == 0)
            {
                cout << red << "ERROR: Please enter Number Upper 1!" << white << endl;
            }
            else
            {
                uintptr_t Health_Addr = PlayerStructure + Health_Offset;
                WriteProcessMemory(HandleCreate, (BYTE*)Health_Addr, &NewHealth, sizeof(NewHealth), nullptr);
                ReadProcessMemory(HandleCreate, (BYTE*)Health_Addr, &HealthValue, sizeof(HealthValue), nullptr);
                cout << "Current health is: " << dec << HealthValue << endl;
            }
        }
        else if (input == "help")
        {
            cout << "Command List:" << endl;
            cout << " sethealth <Number>" << endl;
            cout << " setammo <number>" << endl;
            cout << " infjump" << endl;
            cout << " nocooldown" << endl;
            cout << " invisible" << endl;
            cout << " speed <number>" << endl;
            cout << " kill" << endl;
            cout << " admin" << endl;
            cout << " rapidfire" << endl;
            cout << " " << endl;
        }
        else if (input == "setammo")
        {
            cout << "What Number Of Ammo Do you Want?" << endl;
            int NewAmmo;
            cin >> NewAmmo;
            if (NewAmmo == NULL || NewAmmo == 0)
            {
                cout << red << "ERROR: Please enter Number Upper 1!" << white << endl;
            }
            else
            {
                uintptr_t Ammo_Addr = PlayerStructure + M4Ammo_Offset;
                WriteProcessMemory(HandleCreate, (BYTE*)Ammo_Addr, &NewAmmo, sizeof(NewAmmo), nullptr);
            }
        }
        else if (input == "infjump")
        {
            if (infjumpParameter == false)
            {
                infjumpParameter = true;
                uintptr_t Jump_Adress = PlayerStructure + JumpCool_Offset;
                thread JumpInstance(InfinityJump, HandleCreate, Jump_Adress);
                JumpInstance.detach();
                cout << green <<"InfinityJump Activated!" << white <<endl;
            }
            else
            {
                infjumpParameter = false;
                cout << "InfinityJump Desactivated!" <<endl;
            }
        }
        else if (input == "invisible")
        {
            if (InvisibleParameter == false)
            {
                thread InvisibleInstance(Invisible, HandleCreate, PlayerStructure);
                InvisibleInstance.detach();
                InvisibleParameter = true;
                cout << green << "Invisible Activated!" << white << endl;
            }
            else
            {
                InvisibleParameter = false;
                cout << "Invisible Desactivated!" << endl;
            }

        }
        else if (input == "admin")
        {
            if (AdminMode == false)
            {
                int AdminActivate = 1;
                uintptr_t AdminAdress = PlayerStructure + Admin_Offset;
                WriteProcessMemory(HandleCreate, (BYTE*)AdminAdress, &AdminActivate, sizeof(AdminActivate), nullptr);
                cout << green << "Admin Activated!" << white << endl;
            }
            else
            {
                int AdminDesactivate = 0;
                uintptr_t InvAdress = PlayerStructure + Admin_Offset;
                WriteProcessMemory(HandleCreate, (BYTE*)InvAdress, &AdminDesactivate, sizeof(AdminDesactivate), nullptr);
                cout << "Admin Desactivated!" << endl;
            }

        }
        else if (input == "kill")
        {
            int Dead = 1;
            uintptr_t InvAdress = PlayerStructure + Invisible_Offset;
            WriteProcessMemory(HandleCreate, (BYTE*)InvAdress, &Dead, sizeof(Dead), nullptr);
        }
        else if (input == "speed")
        {
            cout << "What Number Of Speed Do you Want?" << endl;
            int NewSpeed;
            cin >> NewSpeed;
            if (NewSpeed == NULL || NewSpeed == 0)
            {
                cout << red << "ERROR: Please enter Number Upper 1!" << white << endl;
            }
            else
            {
                uintptr_t Speed_Addr = PlayerStructure + Speed_Offset;
                WriteProcessMemory(HandleCreate, (BYTE*)Speed_Addr, &NewSpeed, sizeof(NewSpeed), nullptr);
            }
        }
        else if (input == "rapidfire")
        {
            RapidFAct = !RapidFAct;
            thread RapidInstance(RapidFire, HandleCreate, PlayerStructure);
            RapidInstance.detach();
            cout << "RapidFire: " << RapidFAct << endl;
        }
        else
        {
            cout << red << "ERROR: Invalid Command!" << white <<endl;
        }
    }



    //TESTING
    //GetModuleBaseAddress
    uintptr_t Health_Addr = PlayerStructure + 0xF8;
    int HealthValue = 0;
    ReadProcessMemory(HandleCreate, (BYTE*)Health_Addr, &HealthValue, sizeof(HealthValue), nullptr);
    cout << "Current health is: " << dec << HealthValue << endl;
    cout << "Press Any For Change Health" << endl;
    cin.ignore();
    int NewHealth = 9999;
    WriteProcessMemory(HandleCreate, (BYTE*)Health_Addr, &NewHealth, sizeof(NewHealth), nullptr);
    ReadProcessMemory(HandleCreate, (BYTE*)Health_Addr, &HealthValue, sizeof(HealthValue), nullptr);
    cout << "Current health is: " << dec << HealthValue << endl;
    cin.ignore();
}

