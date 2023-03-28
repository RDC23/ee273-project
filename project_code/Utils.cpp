/*EE273 Group Project
Name: Utils.cpp
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/


#include <Windows.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "Utils.h"

int getValidInteger(const std::string message) {
    //returns a valid integer and handles exceptions when creating this
    int input;
    bool valid_input = false;
    //loop until valid input
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
    //returns a valid string and handles exceptions when creating this 
    std::string input;
    bool valid_input = false;
    //loop until valid input
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
    //prints a pattern to act as a divider in the terminal
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}

void clearScreen() {
    //text code to clear the console 
   std::cout << "\033[2J\033[1;1H";
}

void pause() {
    //stalls the code and waits for "enter" press before continuing code execution
    std::cin.get();
}

void setConsoleTheme() {
    //uses the <windows.h> API and classes provided to set console attributes
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    //set console colours
    CONSOLE_SCREEN_BUFFER_INFOEX consoleInfo;
    consoleInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(console, &consoleInfo);
    consoleInfo.ColorTable[0] = RGB(20, 15, 75);
    SetConsoleScreenBufferInfoEx(console, &consoleInfo);

    //set console font
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(console, FALSE, &fontInfo);
    fontInfo.dwFontSize.X = 14;
    fontInfo.dwFontSize.Y = 18;
    wcscpy_s(fontInfo.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(console, FALSE, &fontInfo);
}

