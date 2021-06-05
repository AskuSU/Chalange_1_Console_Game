#include<iostream>
#include<Windows.h>
#include <stdio.h>
#include <chrono>

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

typedef struct car
{
	const wchar_t mas[2][3] = {
		{0x2584, 0x2588, 0x2584}
		,{0x2584, 0x2580, 0x2584}
	};
} Car;

typedef struct track
{
	static const short widthTrack = 12;
	static const short heightTrack = 14;
	const wchar_t startLine[widthTrack] = { 0x255A, 0x2550, 0x2550,
											0x2550, 0x2550, 0x2550,
											0x2550, 0x2550, 0x2550,
											0x2550, 0x2550, 0x255D
	};
	const wchar_t middlePart[widthTrack] = { 0x2551, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x2551
	};
	const wchar_t emptyPart[widthTrack] = {  0x0020, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x0020,
											 0x0020, 0x0020, 0x0020
	};
	wchar_t trackField[heightTrack][widthTrack] = { {' '} };
} Track;


int nScreenWidth = 120;	
int nScreenHeight = 40;


int main()
{
	//HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	//wchar_t* screnSpace = new wchar_t[nScreenHeight * nScreenWidth];

	//wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	Car newCar;
	Track newTrack;
	
	for (short i = 0; i < newTrack.heightTrack; i++)
	{
		if (i != 0)
		{
			static short ctn = 3;
			if (ctn < 3)
			{
				wmemcpy(newTrack.trackField[i], newTrack.middlePart, newTrack.widthTrack);
				ctn++;
			}
			else
			{
				wmemcpy(newTrack.trackField[i], newTrack.emptyPart, newTrack.widthTrack);
				ctn = 1;
			}
		}
		else wmemcpy(newTrack.trackField[i], newTrack.startLine, newTrack.widthTrack);
				
	}

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (1) {
		for (short i = 0; i < newTrack.heightTrack; i++)
		{
			tp2 = chrono::system_clock::now();
			chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();
			
			short invert = newTrack.heightTrack - i - 1;
			WriteConsoleOutputCharacter(hConsole, newTrack.trackField[i], newTrack.widthTrack, { 0, invert }, &dwBytesWritten);
		}
		//WriteConsoleOutputCharacter(hConsole, newCar.mas[0], 3, { 0,0 }, &dwBytesWritten);
		//WriteConsoleOutputCharacter(hConsole, newCar.mas[1], 3, { 0,1 }, &dwBytesWritten);
		//WriteConsoleOutputCharacter(hConsole, newTrack.middlePart, 12, { 0,2 }, &dwBytesWritten);
		//WriteConsoleOutputCharacter(hConsole, newTrack.emptyPart, 12, { 0,3 }, &dwBytesWritten);
		//WriteConsoleOutputCharacter(hConsole, newTrack.startLine, 12, { 0,4 }, &dwBytesWritten);
	}
	/*
	while (true)
	{
		GetConsoleScreenBufferInfo(hConsoleOutput, &lpConsoleScreenBufferInfo);
		cout << lpConsoleScreenBufferInfo.dwSize.X << endl;
		cout << lpConsoleScreenBufferInfo.dwSize.Y << endl << endl;

		cout << lpConsoleScreenBufferInfo.dwMaximumWindowSize.X << endl;
		cout << lpConsoleScreenBufferInfo.dwMaximumWindowSize.Y << endl << endl;

		Sleep(2000);
	}
	*/


	return 0;

}