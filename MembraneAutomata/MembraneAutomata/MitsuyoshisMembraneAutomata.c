//
//  MitsuyoshisMembraneAutomata.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "MitsuyoshisMembraneAutomata.h"

MMASize suitableSize(MMASize);

int unstabilityBetween(byte, byte);
//int unstabilityBetween(byte, byte);

MMASize suitableSize(MMASize size) {
	MMASize newSize;
	
	newSize.x = ((unsigned long)(size.x / 2)) * 2;
	newSize.y = ((unsigned long)(size.y / 2)) * 2;
	
	return newSize;
}

#pragma mark - Calculate Stability
int unstabilityBetween(byte substanceA, byte substanceB) {
	
	switch (substanceA) {
		case MMAWater:
			switch (substanceB) {
				case MMAWater:	return 0;
				case MMAOil:	return 1;
				case MMAWaterFamilier:	return 0;
				case MMAOilFamilier:	return 1;
			}
			break;
			
		case MMAOil:
			switch (substanceB) {
				case MMAWater:	return 1;
				case MMAOil:	return 0;
				case MMAWaterFamilier:	return 1;
				case MMAOilFamilier:	return 0;
			}
			break;
			
		case MMAWaterFamilier:
			switch (substanceB) {
				case MMAWater:	return 0;
				case MMAOil:	return 1;
				case MMAWaterFamilier:	return -1;
				case MMAOilFamilier:	return -1;
			}
			break;
			
		case MMAOilFamilier:
			switch (substanceB) {
				case MMAWater:	return 1;
				case MMAOil:	return 0;
				case MMAWaterFamilier:	return -1;
				case MMAOilFamilier:	return -1;
			}
			break;
			
		default:
			break;
	}
	
	return 0;
}
/*
int unstabilityBetween(byte substanceA, byte substanceB) {
	
}
*/


#pragma mark - Initializer
MMASize MMASizeMake(int x, int y) {
	MMASize size;
	
	size.x = x;
	size.y = y;
	return size;
}

void MMAMapInitialize(MMAMap *map, MMASize size) {	
	
	(*map).size = suitableSize(size);

//	(*map).previousCells = (byte *)malloc(sizeof(byte) * (*map).size.x * (*map).size.y);
	(*map).currentCells = (byte *)malloc(sizeof(byte) * (*map).size.x * (*map).size.y);
	
	clearMap(map);
}


void clearMap(MMAMap *map) {
	
	int xMax = (*map).size.x;
	int yMax = (*map).size.y;
	int position = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
//			(*map).previousCells[position] = MMAWater;
			(*map).currentCells[position] = MMAWater;
		}
	}
}

void MMAMapDelete(MMAMap *map) {
	free((*map).currentCells);
}

#pragma mark - Execution
void step(MMAMap *map) {
	
	int xMax = (*map).size.x;
	int yMax = (*map).size.y;
	int position = 0;
	int subPosition = 0;
	int mostStablePosition = 0;
	int mostStableUnstability;
	int subUnstability;
	byte currentSubstance;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			mostStablePosition = position;
			mostStableUnstability = MMAUnstableMax;
			currentSubstance = (*map).currentCells[position];
			
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;
					subUnstability = unstabilityBetween(currentSubstance, (*map).currentCells[subPosition]);
					
					if (subUnstability < mostStableUnstability) {
						mostStableUnstability = subUnstability;
						mostStablePosition = subPosition;
					}
				}
			}
			
			(*map).currentCells[position] = (*map).currentCells[mostStablePosition];
			(*map).currentCells[mostStablePosition] = currentSubstance;
		}
	}
}

