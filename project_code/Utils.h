/*EE273 Group Project
Name: Utils.h
Program: Project Allocation
Authors: Ross Cathcart & Kishan Maharaj
Last Updated: 18/03/2023
*/

#pragma once
#include <string>
#include <stdlib.h>   

int getValidInteger(std::string message);

std::string getValidString(const std::string message);

void printLineSep();

void clearScreen();

void pause();

void setConsoleTheme();
