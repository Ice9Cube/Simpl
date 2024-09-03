#include <iostream>
#include <fstream>
#include <string>   // For string manipulations
#include <unistd.h> // For sleep on UNIX-like systems
#include <limits>   // For system()
#include <unistd.h> // For sleep()
#include "Bank.h"

int main() {
    std::system("clear");

    Bank bank;

    bank.PanelMenu();

    return 0;
}