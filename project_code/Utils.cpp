#include <Windows.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "Utils.h"

int getValidInteger(const std::string message) {
    //ensures the user has correctly entered an integer, and returns this
    int input;
    bool valid_input = false;
    while (!valid_input) {
        std::cout << message;
        std::string strinput;
        std::getline(std::cin, strinput);
        std::stringstream ss(strinput);
        if (ss >> input) { //this fails if ss attempts to assign a non integer to input
            valid_input = true;  
        }
        else {
            std::cout << "\nInvalid input. Please enter a valid integer." << std::endl;
        }
    }
    return input;
}

std::string getValidString(const std::string message) {
    //gets valid string data
    std::string input;
    bool valid_input = false;
    while (!valid_input) {
        std::cout << message;
        std::getline(std::cin, input);
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "\nError parsing input data. Please try again." << std::endl;
        }
        valid_input = true;
    }
    return input;
}

void printLineSep() {
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}

void clearScreen() {
   std::cout << "\033[2J\033[1;1H";
}

void pause() {
    std::cin.get();
}

void setConsoleTheme() {
    // Set console colors
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX consoleInfo;
    consoleInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &consoleInfo);
    consoleInfo.ColorTable[0] = RGB(20, 15, 75);
    SetConsoleScreenBufferInfoEx(hConsole, &consoleInfo);

    // Set console font
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    fontInfo.dwFontSize.X = 14;
    fontInfo.dwFontSize.Y = 18;
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

