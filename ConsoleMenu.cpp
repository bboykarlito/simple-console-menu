#include "pch.h"
#include "CConsoleMenu.h"

ConsoleMenu::ConsoleMenu(int size_of_menu)
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	setSizeOfMenu(size_of_menu);
	setActiveItem();
}

void ConsoleMenu::activate(const char* menu_items[], bool (*main_menu_items_func[])())
{
	while (1)
	{
		if (main_menu_items_func[getActiveItem(menu_items)]()) continue;
		break;
	}
}

int ConsoleMenu::getActiveItem(const char* menu_items[])
{
	std::cout << "\n\n\n";
	drawMenuItems(menu_items);
	char button = _getch();
	while (button != ENTER)
	{
		moveUpOrDown(button);
		cleanMenu();
	    drawMenuItems(menu_items);
		button = _getch();
		if (button == -32) button = _getch();
	}
    return active_item;
}

void ConsoleMenu::drawMenuItems(const char* menu_items[])
{
	for (int item = 0; item < size_of_menu; item++)
	{
		item == active_item ? std::cout << "-> " : std::cout << "   ";
		std::cout << menu_items[item] << std::endl;
	}
}

void ConsoleMenu::moveUpOrDown(char button)
{
	int first_menu_item = 0;
	int last_menu_item = size_of_menu - 1;

	switch (button)
	{
	case UP: changeActiveItem(first_menu_item, last_menu_item); break;
	case DOWN: changeActiveItem(last_menu_item, first_menu_item); break;
	}
}

void ConsoleMenu::changeActiveItem(int menu_peak, int opposite_menu_peak)
{
	if (active_item == menu_peak) active_item = opposite_menu_peak;
	else if (menu_peak > opposite_menu_peak) active_item++;
	else active_item--;
}

void ConsoleMenu::cleanMenu()
{
	COORD position = GetConsoleCursorPosition(hStdOut);
	short X = position.X, Y = position.Y;
	goToXY(X, Y - size_of_menu);
	for (int i = 0; i < size_of_menu; i++) printf("                                             \n");
	goToXY(X, Y - size_of_menu);
}

void ConsoleMenu::goToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

COORD ConsoleMenu::GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
