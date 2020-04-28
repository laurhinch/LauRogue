#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <conio.h>

#include "Player.h"
#include "RNG.h"

Player player;

#include "Map.h"

#define STARTINGPOINTS 14

using std::cout;
using std::cin;
using std::string;

Map map;

//helper functions
//fontSize() sets fontsize in console to a ratio of a:b
void fontSize(int a, int b) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = a;
    lpConsoleCurrentFontEx->dwFontSize.Y = b;
    SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}

int clamp(const int& val, const int& lo, const int& hi)
{
    return min(max(val, lo), hi);
}

string selectedItem(string val, bool isSelected) {
    if (isSelected) {
        return "[" + val + "]";
    }
    else {
        return " " + val + " ";
    }
}

//input functions
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

//game processes

/*
    updateGame()

    Performs all main functions associated with gameplay including updating the screen and calculating game events.
    Returns -1 if game is lost.
    Returns 0 if game is won.
    Returns a seed if game is neither won nor lost but rather saved and exited.
*/
int updateGame() {
    char key;
    while (1) {
        system("cls");
        //check if player is dead
        if (player.getHealth() <= 0) {
            return -1; // death code
        }
        //draw HUD elements


        //draw map
        map.player = player;
        map.drawMap();


        //handle input
        key = getKey();
        switch (key) {
        case 'w':
            player.setY(player.getY() - 1);
            break;
        case 's':
            player.setY(player.getY() + 1);
            break;
        case 'a':
            player.setX(player.getX() - 1);
            break;
        case 'd':
            player.setX(player.getX() + 1);
            break;
        }
    }
}

void updateGameScreen() {

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

        cout << "\n\n\tPress \'w\' or \'s\' keys to change selection." << "\n";
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

Player newGame() {
    char key;
    int pointsUsed = 0;
    int pointsLeft = STARTINGPOINTS;
    int fortitude = 1, strength = 1, dexterity = 1, speed = 1, luck = 1;
    bool cursor[6][2];
    int curX = 1;
    int curY = 0;
    while (1) {
        int health = fortitude * 40;
        int damage = dexterity * strength;
        system("cls");
        //build menu elements
        cout << "LauRogue Character Creator\t" << "[" << std::to_string(pointsUsed) << " out of " << STARTINGPOINTS << "]\n" << "\n";
        for (int i = 0; i < 6; i++) {
            cursor[i][0] = false;
            cursor[i][1] = false;
        }
        cursor[curY][curX] = true;
        cout << "\tFortitude\t[" << std::to_string(fortitude) << "/10]\t" << selectedItem("-", cursor[0][0]) << "|" << selectedItem("+", cursor[0][1]) << "\n";
        cout << "\tStrength\t[" << std::to_string(strength) << "/10]\t" << selectedItem("-", cursor[1][0]) << "|" << selectedItem("+", cursor[1][1]) << "\n";
        cout << "\tDexterity\t[" << std::to_string(dexterity) << "/10]\t" << selectedItem("-", cursor[2][0]) << "|" << selectedItem("+", cursor[2][1]) << "\n";
        cout << "\tSpeed\t\t[" << std::to_string(speed) << "/10]\t" << selectedItem("-", cursor[3][0]) << "|" << selectedItem("+", cursor[3][1]) << "\n";
        cout << "\tLuck\t\t[" << std::to_string(luck) << "/10]\t" << selectedItem("-", cursor[4][0]) << "|" << selectedItem("+", cursor[4][1]) << "\n";
        cout << "\n";
        cout << "(Max Health: " << std::to_string(health) << ")\t(Damage: " << std::to_string(damage) << ")" << "\n";
        cout << "\n";
        cout << "\t" << selectedItem("RESET STATS", cursor[5][0]) << "\t" << selectedItem("FINALIZE", cursor[5][1]) << "\n";
        key = getKey();
        switch (key) {
        case 'w':
            curY--;
            break;
        case 's':
            curY++;
            break;
        case 'a':
            curX--;
            break;
        case 'd':
            curX++;
            break;
        case 'z':
            //reset or finalize
            if (curY == 5) {
                switch (curX) {
                    //reset
                case 0:
                    fortitude = 1;
                    strength = 1;
                    dexterity = 1;
                    speed = 1;
                    luck = 1;
                    pointsUsed = 0;
                    pointsLeft = STARTINGPOINTS;
                    break;
                case 1:
                    if (pointsUsed <= STARTINGPOINTS) {
                        return Player(health, fortitude, strength, dexterity, speed, luck);
                    }
                    else {
                        cout << "Too many points allocated!" << "\n";
                        getKey();
                    }
                    break;
                }
            }
            //if not = 5, must not be bottom row
            else {
                //increment
                if (curX == 1) {
                    switch (curY) {
                        //fortitude
                    case 0:
                        fortitude++;
                        pointsUsed++;
                        if (fortitude > 10) {
                            fortitude = 10;
                            pointsUsed--;
                        }
                        break;
                        //strength
                    case 1:
                        strength++;
                        pointsUsed++;
                        if (strength > 10) {
                            strength = 10;
                            pointsUsed--;
                        }
                        break;
                        //dexterity
                    case 2:
                        dexterity++;
                        pointsUsed++;
                        if (dexterity > 10) {
                            dexterity = 10;
                            pointsUsed--;
                        }
                        break;
                        //speed
                    case 3:
                        speed++;
                        pointsUsed++;
                        if (speed > 10) {
                            speed = 10;
                            pointsUsed--;
                        }
                        break;
                        //luck
                    case 4:
                        luck++;
                        pointsUsed++;
                        if (luck > 10) {
                            luck = 10;
                            pointsUsed--;
                        }
                        break;
                    }
                }
                //decrement
                else {
                    switch (curY) {
                        //fortitude
                    case 0:
                        fortitude--;
                        pointsUsed--;
                        if (fortitude < 1) {
                            fortitude = 1;
                            pointsUsed++;
                        }
                        break;
                        //strength
                    case 1:
                        strength--;
                        pointsUsed--;
                        if (strength < 1) {
                            strength = 1;
                            pointsUsed++;
                        }
                        break;
                        //dexterity
                    case 2:
                        dexterity--;
                        pointsUsed--;
                        if (dexterity < 1) {
                            dexterity = 1;
                            pointsUsed++;
                        }
                        break;
                        //speed
                    case 3:
                        speed--;
                        pointsUsed--;
                        if (speed < 1) {
                            speed = 1;
                            pointsUsed++;
                        }
                        break;
                        //luck
                    case 4:
                        luck--;
                        pointsUsed--;
                        if (luck < 1) {
                            luck = 1;
                            pointsUsed++;
                        }
                        break;
                    }
                }
                
            }
            break;
        }
        curY = clamp(curY, 0, 5);
        curX = clamp(curX, 0, 1);
        pointsLeft = STARTINGPOINTS - pointsUsed;
    }
}

void loadGame() {
    char key;
    while (1) {
        system("cls");
        key = getKey();
        break;

    }
}

void optionsMenu() {
    char key;
    while (1) {
        system("cls");
        key = getKey();
        break;

    }
}

int main()
{
    //increase speed of cin/cout streams
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //initialize important objects
    RNG rand = *new RNG(1);
    HANDLE hstdin;
    DWORD mode;
    CONSOLE_CURSOR_INFO cursorInfo;

    //configure input buffer
    hstdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hstdin, &mode);
    SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
    GetConsoleCursorInfo(hstdin, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hstdin, &cursorInfo);
    fontSize(24, 32);

    //get main menu interaction
    int index = mainMenu();

    switch (index) {
        case 0:
            //new player menu
            player = newGame();
            map = Map(player);
            updateGame();
            break;
        case 1:
            //load player menu
            loadGame();
            break;
        case 2:
            //options menu
            optionsMenu();
            break;
        case 3:
            //exit game
            return 0;
    }



    SetConsoleMode(hstdin, mode);
    return 0;
}