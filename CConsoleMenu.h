#pragma once

#include <iostream>
#include <conio.h>

#define UP 72
#define DOWN 80
#define ESC 27
#define ENTER 13

class ConsoleMenu
{
	HANDLE hStdOut;
	COORD GetConsoleCursorPosition(HANDLE);

	int size_of_menu;
	int active_item;

	void setSizeOfMenu(int size_of_menu) { this->size_of_menu = size_of_menu; }
	void setActiveItem() { this->active_item = 0; }

	void moveUpOrDown(char);
	void changeActiveItem(int, int);
	void drawMenuItems(const char* []);
	int getActiveItem(const char* []);

	void goToXY(short, short);
	void cleanMenu();

public:
	ConsoleMenu(int);
	~ConsoleMenu() {}
	void activate(const char* [], bool (*main_menu_items_func[])());
};
