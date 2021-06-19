#include"GameStruct.h"

car::car(unsigned short widthTrackP)
{
	xPos = widthTrackP / 2;
	xPosPrevious = xPos;
	widthTrack = widthTrackP;
}

unsigned short car::GetX_Pos()
{
	return xPos;
}

unsigned short car::GetX_PosPrevious()
{
	return xPosPrevious;
}

void car::changeX_Pos(short axisX)
{
	xPosPrevious = xPos;
	if (xPos + axisX > width / 2 + 1 && xPos + axisX < widthTrack - width / 2 - 1)
	{
		xPos += axisX;
	}
	else if (axisX < 0)
	{
		xPos = width / 2 + 1;
	}
	else
	{
		xPos = widthTrack - width / 2 - 1;
	}
}

track::track()
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

gameField::gameField()
{
	for (short i = 0; i < height; i++)
		for (short j = 0; j < width; j++)		
			characterCells[i][j] = ' ';
}