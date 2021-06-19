//#include<iostream>
#include<Windows.h>
//#include <stdio.h>
#include <chrono>

#include"GameStruct.h"
#include"ScreenOutput.h"

using namespace std;

int main()
{
	//HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	//wchar_t* screnSpace = new wchar_t[nScreenHeight * nScreenWidth];

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	Track newTrack;
	Car newCar(newTrack.width);
	GameField _GameField;
	
	addNextLine(true, newTrack);
	pastCarOnTheTrack(newCar, newTrack, true);
	pastTrackOnTheGameField(newTrack, _GameField);
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	float V, TimeFromStart = 0;
	long double S = 0;
	int S_total = 0;
	V = newCar.speedLevel[5];

	while (1) {
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		TimeFromStart += fElapsedTime;
		if (!(TimeFromStart < _GameField.delayForStart))
		{
			S += V * static_cast<long double>(fElapsedTime);
			if (S > S_total)
			{
				S_total++;
				addNextLine(false, newTrack);
				pastCarOnTheTrack(newCar, newTrack, false);
				pastTrackOnTheGameField(newTrack, _GameField);
			}
		}		
		if (newTrack.NeedRefreshScreen)
		{
			for (short i = 0; i < _GameField.height; i++)
			{
				//swprintf_s(newTrack.trackField[newTrack.heightTrack - 1], newTrack.widthTrack - 4, L"FPS=%4.3f", TimeFromStart);//1.0f / fElapsedTime);
				//short invert = newTrack.heightTrack - i - 1;
				//WriteConsoleOutputCharacter(hConsole, newTrack.trackField[i], newTrack.widthTrack, { 0, invert }, &dwBytesWritten);

				short invert = _GameField.height - i - 1;
				WriteConsoleOutputCharacter(hConsole, _GameField.characterCells[i], _GameField.width, { 0, invert }, &dwBytesWritten);
			}
			newTrack.NeedRefreshScreen = false;
		}

		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		{
			if (newCar.offsetX > 0) newCar.offsetX = 0;
			newCar.offsetX -= 10.0f * fElapsedTime;
		}
		
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		{
			if (newCar.offsetX < 0) newCar.offsetX = 0;
			newCar.offsetX += 10.0f * fElapsedTime;
		}

		if (newCar.offsetX > 1)
		{
			newCar.changeX_Pos(1);
			newCar.offsetX -= 1;
		}
		else if (newCar.offsetX < -1)
		{
			newCar.changeX_Pos(-1);
			newCar.offsetX += 1;
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