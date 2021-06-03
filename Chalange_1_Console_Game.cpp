#include<iostream>
#include<Windows.h>
using namespace std;
/*
typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
	COORD dwSize;
	COORD dwCursorPosition;
	WORD wAttributes;
	SMALL_RECT srWindow;
	COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO;
*/

int nScreenWidth = 120;	
int nScreenHeight = 40;


int main()
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	wchar_t* screnSpace = new wchar_t[nScreenHeight * nScreenWidth];


	while (true)
	{
		GetConsoleScreenBufferInfo(hConsoleOutput, &lpConsoleScreenBufferInfo);
		cout << lpConsoleScreenBufferInfo.dwSize.X << endl;
		cout << lpConsoleScreenBufferInfo.dwSize.Y << endl << endl;

		cout << lpConsoleScreenBufferInfo.dwMaximumWindowSize.X << endl;
		cout << lpConsoleScreenBufferInfo.dwMaximumWindowSize.Y << endl << endl;

		Sleep(2000);
	}



	return 0;

}