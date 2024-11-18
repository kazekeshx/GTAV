#include <iostream>
#include "Menu.h"
using namespace System;
using namespace std;

int main()
{
    Console::CursorVisible = false;

    Menu menu;
    menu.mostrarMenu();

    return 0;
}