#pragma once

typedef struct car
{
private:
	unsigned short xPos;
	unsigned short xPosPrevious;
	unsigned short widthTrack;
public:
	static const unsigned short height = 4;
	static const unsigned short width = 6;
	const wchar_t carCells[height][width] = {
		{0x0020, 0x0020, 0x2588, 0x2588, 0x0020, 0x0020}
		,{0x2588, 0x2588, 0x2588, 0x2588, 0x2588, 0x2588}
		,{0x0020, 0x0020, 0x2588, 0x2588, 0x0020, 0x0020}
		,{0x2588, 0x2588, 0x0020, 0x0020, 0x2588, 0x2588}
	};	
	const wchar_t carCellsErasure[height][width] = {
		{0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020}
		,{0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020}
		,{0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020}
		,{0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020}
	};
	const wchar_t carEndLineCells[width] = {
		0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020
	};

	const float speedLevel[6] = { 0.f, 1.f, 1.5f, 2.f, 2.5f, 10.f };
	const short acceleration = 2;
	float offsetX = 0;

	car(unsigned short widthTrackP);	
	unsigned short GetX_Pos();
	unsigned short GetX_PosPrevious();
	void changeX_Pos(short axisX);
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
	wchar_t trackField[height][width];
	unsigned short partLineNumber[height];
	bool NeedRefreshScreen = false;
	track();	
} Track;

typedef struct gameField
{
	static const unsigned short height = 35;
	static const unsigned short width = 45;
	static const unsigned short startPosWidthTrack = 2;
	static const unsigned short startPosHeightTrack = 2;

	static const unsigned short delayForStart = 1;

	wchar_t characterCells[height][width];
	bool needRefreshScreen = false;
	gameField();	
} GameField;

