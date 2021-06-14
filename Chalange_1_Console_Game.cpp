#include<iostream>
#include<Windows.h>
#include <stdio.h>
#include <chrono>

using namespace std;

typedef struct car
{
	static const unsigned short height = 4;
	static const unsigned short width = 6;
	const wchar_t carCells[height][width] = {
		{0x0020, 0x0020, 0x2588, 0x2588, 0x0020, 0x0020}
		,{0x2588, 0x2588, 0x2588, 0x2588, 0x2588, 0x2588}
		,{0x0020, 0x0020, 0x2588, 0x2588, 0x0020, 0x0020}
		,{0x2588, 0x2588, 0x0020, 0x0020, 0x2588, 0x2588}
	};
	const wchar_t carEndLineCells[width] = {
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020
	};
	unsigned short xPos;
	const float speedLevel[6] = { 0.f, 1.f, 1.5f, 2.f, 2.5f, 10.f };
	const short acceleration = 2;
	car(unsigned short xPosP)
	{
		xPos = xPosP;
	}
} Car;

typedef struct track
{
	static const unsigned short width = 20;
	static const unsigned short height = 28;
	const wchar_t startLine[width] = { 
		0x255A, 0x2550, 0x2550, 0x2550, 0x2550,
		0x2550, 0x2550, 0x2550, 0x2550, 0x2550,
		0x2550, 0x2550, 0x2550, 0x2550, 0x2550,
		0x2550, 0x2550, 0x2550, 0x2550, 0x255D
	};
	const wchar_t middlePart[width] = { 
		0x2551, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x2551
	};
	const wchar_t emptyPart[width] = {  
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020,
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020
	};
	wchar_t trackField[height][width];// = { {' '} };
	unsigned short partLineNumber[height];
	bool NeedRefreshScreen = false;
	track()
	{
		for (short i = 0; i < height; i++)
		{
			for (short j = 0; j < width; j++)
			{
				trackField[i][j] = ' ';
			}
			partLineNumber[i] = i;
		}
	}
} Track;

typedef struct gameField
{
	static const unsigned short height = 35;
	static const unsigned short width = 45;
	static const unsigned short startPosWidthTrack = 2;
	static const unsigned short startPosHeightTrack = 2;

	static const unsigned short delayForStart = 1;

	wchar_t characterCells[height][width];// = { {' '} };
	bool needRefreshScreen = false;
	gameField()
	{
		for (short i = 0; i < height; i++)		
			for (short j = 0; j < width; j++)
			{
				characterCells[i][j] = ' ';
			}
		
	}
} GameField;



void addNextLine(bool isFirst, Track &currTrack)
{
	currTrack.NeedRefreshScreen = true;
	for (short i = 0; i < currTrack.height; i++)
	{
		if (!isFirst && i < currTrack.height - 1)
		{
			wmemcpy(currTrack.trackField[i], currTrack.trackField[i + 1], currTrack.width);
			currTrack.partLineNumber[i] = currTrack.partLineNumber[i + 1];
		}
		else if (i != 0)
		{
			currTrack.partLineNumber[i] = currTrack.partLineNumber[i - 1] + 1;
			if (currTrack.partLineNumber[i] > 1 && currTrack.partLineNumber[i] < 6)
			{
				wmemcpy(currTrack.trackField[i], currTrack.middlePart, currTrack.width);
			}
			else
			{
				wmemcpy(currTrack.trackField[i], currTrack.emptyPart, currTrack.width);
				if (currTrack.partLineNumber[i] > 2) currTrack.partLineNumber[i] = 0;
			}			
		}
		else
		{
			wmemcpy(currTrack.trackField[i], currTrack.startLine, currTrack.width);
			currTrack.partLineNumber[i] = 5;
		}
	}
}

void pastTrackOnTheGameField(Track &currTrack, GameField &currGameField)
{
	currGameField.needRefreshScreen = true;
	for (int i = 0; i < currTrack.height; i++)
	{
		unsigned short heightIndex = i + (currGameField.height - currTrack.height) - currGameField.startPosHeightTrack;
		copy(begin(currTrack.trackField[i]), end(currTrack.trackField[i]), currGameField.characterCells[heightIndex] + currGameField.startPosWidthTrack);
		//wmemcpy(currGameField.characterCells[heightIndex], currTrack.trackField[i], currTrack.widthTrack);
	}
}

void pastCarOnTheTrack(Car &car, Track &track, bool startFlag)
{
	unsigned short heightIndex = 0;
	unsigned short widthIndex = car.xPos - car.width / 2;
	if (!startFlag) copy(begin(car.carEndLineCells), end(car.carEndLineCells), track.trackField[heightIndex] + widthIndex);
	for (size_t i = 0; i < car.height; i++)
	{		
		heightIndex = i + 1;
		copy(begin(car.carCells[car.height - 1 - i]), end(car.carCells[car.height - 1 - i]), track.trackField[heightIndex] + widthIndex);
	}
}

int main()
{
	//HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	//wchar_t* screnSpace = new wchar_t[nScreenHeight * nScreenWidth];

	//wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	Track newTrack;
	Car newCar(newTrack.width / 2);
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