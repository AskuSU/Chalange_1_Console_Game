#include"ScreenOutput.h"

using namespace std;

void addNextLine(bool isFirst, Track& currTrack)
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

void pastTrackOnTheGameField(Track& currTrack, GameField& currGameField)
{
	currGameField.needRefreshScreen = true;
	for (int i = 0; i < currTrack.height; i++)
	{
		unsigned short heightIndex = i + (currGameField.height - currTrack.height) - currGameField.startPosHeightTrack;
		copy(begin(currTrack.trackField[i]), end(currTrack.trackField[i]), currGameField.characterCells[heightIndex] + currGameField.startPosWidthTrack);
	}
}

void pastCarOnTheTrack(Car& car, Track& track, bool startFlag)
{
	unsigned short heightIndex = 0;
	unsigned short widthIndex = car.GetX_Pos() - car.width / 2;
	unsigned short widthIndexPrevious = car.GetX_PosPrevious() - car.width / 2;
	if (!startFlag)
	{	
		copy(begin(car.carEndLineCells), end(car.carEndLineCells), track.trackField[heightIndex] + widthIndex);
		for (unsigned short i = 0; i < car.height; i++)
		{
			heightIndex = i;
			copy(begin(car.carCellsErasure[car.height - 1 - i]), end(car.carCellsErasure[car.height - 1 - i]), track.trackField[heightIndex] + widthIndexPrevious);
		}
	}
	for (unsigned short i = 0; i < car.height; i++)
	{
		heightIndex = i + 1;
		copy(begin(car.carCells[car.height - 1 - i]), end(car.carCells[car.height - 1 - i]), track.trackField[heightIndex] + widthIndex);
	}
}