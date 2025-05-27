#include <iostream>
#include "../mapper/intel_driver.hpp"
#include "../mapper/kdmapper.hpp"
#include <Windows.h>
#include <conio.h> 
#include "../driver/driver.h"
// hello, this is just a simple "spoofer" well its not really a spoofer its just spoofs disk when u load the driver from the bytes 
// the driver from this is the first one i found on random server so its not ud and u will be banned after like 30min lol
// this has 0 protection, which means its easy asf to crack but its better than download file a and stuff like that. have fun.

#define COM1_PORT   0x03f8
#define COM2_PORT   0x02f8
#define COM3_PORT   0x03e8
#define COM4_PORT   0x02e8

void centerwind(int posx, int posy)
{
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);

}

namespace driver
{
    bool load_driver = false;
}

BOOL load_driver()
{
    Sleep(2000);
    system("cls");


    HANDLE device_handle = intel_driver::Load();
    Sleep(200);

    if (!device_handle || device_handle == INVALID_HANDLE_VALUE)
    {
        printf("Couldn't Map Driver");
        return false;
    }

    if (!kdmapper::MapDriver(device_handle, rawData))
    {
        printf("Couldn't Map Driver");
        intel_driver::Unload(device_handle);
        return false;
    }

    Sleep(500);
    intel_driver::Unload(device_handle);


    unsigned char rawData[6240] = { 0 };

    return true;
}

int main()
{
    centerwind(430, 300);
    SetConsoleTitleA("Spoofer Ultra Detected Price 30$");
    while (true) {
        system("cls");  
        std::cout << ("\n\n [1] Load Driver\n [2] Check Your Disk Serial\n");
        std::cout << "\n  > ";
        int option;
        std::cin >> option;
        switch (option)
        {
        case 1:
            system("cls");
            driver::load_driver = load_driver();
            if (!driver::load_driver)
            {
                printf("\n Failed to load driver \n");
                Sleep(5000);
            }
            break;
        case 2:
            system("cls");
            system("wmic diskdrive get serialnumber\n");
            std::cout << "Press Any Key To Go Back.";
            _getch(); 
            break;
        default:
            std::cout << ("dumbass detected.");
            Sleep(1000);
            break;
        }

    }
   

    return 0;
}

