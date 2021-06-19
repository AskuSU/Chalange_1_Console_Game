#pragma once
#include<iostream>
#include"GameStruct.h"

void addNextLine(bool isFirst, Track& currTrack);
void pastTrackOnTheGameField(Track& currTrack, GameField& currGameField);
void pastCarOnTheTrack(Car& car, Track& track, bool startFlag);