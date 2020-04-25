#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "Player.h"
#include "RNG.h"

using std::cout;
using std::cin;
using std::string;

Player player;

int clamp(const int& val, const int& lo, const int& hi)
{
    return min(max(val, lo), hi);
}

char getKey()
{
    DWORD        mode;
    HANDLE       hstdin;
    INPUT_RECORD inrec;
    DWORD        count;
    char         result = '\0';
    hstdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hstdin == INVALID_HANDLE_VALUE
        || !GetConsoleMode(hstdin, &mode)
        || !SetConsoleMode(hstdin, 0))
        return result;
    FlushConsoleInputBuffer(hstdin);
    do ReadConsoleInput(hstdin, &inrec, 1, &count);
    while ((inrec.EventType != KEY_EVENT) || !inrec.Event.KeyEvent.bKeyDown);
    result = inrec.Event.KeyEvent.uChar.AsciiChar;
    do ReadConsoleInput(hstdin, &inrec, 1, &count);
    while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);
    SetConsoleMode(hstdin, mode);
    
    return result;
}

int mainMenu() {
    string sMenu[4] = { "NEW GAME", "LOAD SAVE", "OPTIONS", "EXIT GAME" };
    char key_press;
    int index = 0;
    while (1) {
        system("cls");
        cout << "     _                ______   \n"
            << "    | |               | ___ \\   \n"
            << "    | |     __ _ _   _| |_/ /___   __ _ _   _  ___  \n"
            << "    | |    / _` | | | |    // _ \\ / _` | | | |/ _ \\  \n"
            << "    | |___| (_| | |_| | |\\ \\ (_) | (_| | |_| |  __/  \n"
            << "    \\_____/\\__,_|\\__,_\\_ |\\_\\___/ \\__, |\\__,_|\\___|  \n"
            << "                                   __/ |  \n"
            << "                                 |___ /  \n";

        for (int i = 0; i < 4; i++) {
            if (i == index) {
                cout << "\t\t" << sMenu[i] << " <-\n";
            }
            else {
                cout << "\t\t" << sMenu[i] << "\n";
            }
        }

        cout << "\n\n\tPress \'w\' or \'s\' keys to change selection." << std::endl;
        cout << "\tPress \'z\' key to select.\n";

        key_press = getKey();
        switch (key_press) {
        case 'w':
            index--;
            break;
        case 's':
            index++;
            break;
        case 'z':
            index = clamp(index, 0, 3);
            return index;
        }
        index = clamp(index, 0, 3);
    }
}

int main()
{
    //initialize important objects
    RNG rand = *new RNG(1);
    HANDLE hstdin;
    DWORD mode;

    //configure input buffer
    hstdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin, &mode);
    SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

    //get main menu interaction
    int index = mainMenu();

    switch (index) {
        case 0:
            //new player menu
            player = Player();
            break;
        case 1:
            //load player menu
            player = Player(1);
            break;
        case 2:
            //options menu

            break;
        case 3:
            //exit game
            return 0;
    }



    SetConsoleMode(hstdin, mode);
    return 0;
}