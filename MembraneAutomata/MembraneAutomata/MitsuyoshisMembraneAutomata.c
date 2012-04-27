//
//  MitsuyoshisMembraneAutomata.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MitsuyoshisMembraneAutomata.h"

MMASize suitableSize(MMASize);

int unstabilityBetween(byte, byte);
//int unstabilityBetween(byte, byte);

MMASize suitableSize(MMASize size) {
	MMASize newSize;
	
	newSize.width = ((unsigned long)(size.width / 2)) * 2;
	newSize.height = ((unsigned long)(size.height / 2)) * 2;
	
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


#pragma mark - Map Initializer
MMASize MMASizeMake(int x, int y) {
	MMASize size;
	
	size.width = x;
	size.height = y;
	return size;
}

void MMAMapInitialize(MMAMap *map, MMASize size) {	
	
	(*map).size = suitableSize(size);

//	(*map).previousCells = (byte *)malloc(sizeof(byte) * (*map).size.x * (*map).size.y);
	(*map).currentCells = (byte *)malloc(sizeof(byte) * (*map).size.width * (*map).size.height);
	
	clearMap(map);
}

void MMAMapDelete(MMAMap *map) {
	free((*map).currentCells);
}


#pragma mark - Cell Initializer
void clearMap(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
//			(*map).previousCells[position] = MMAWater;
			(*map).currentCells[position] = MMAWater;
		}
	}
}

void randomizeMap(MMAMap *map, unsigned int water, unsigned int oil, unsigned int wFamilier, unsigned int oFamilier) {
	
	srand(time(NULL));
	srand(rand());
	
	int position = 0;
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int maximum = water + oil + wFamilier + oFamilier;
	int randomValue = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			
			randomValue = rand() % maximum;
			
			if (randomValue < water) {
				(*map).currentCells[position] = MMAWater;
			}
			else if (randomValue < water + oil) {
				(*map).currentCells[position] = MMAOil;
			}
			else if (randomValue < water + oil + wFamilier) {
				(*map).currentCells[position] = MMAWaterFamilier;
			}
			else {
				(*map).currentCells[position] = MMAOilFamilier;
			}
		}
	}
}


#pragma mark - Execution
void step(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
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


#pragma mark - Print
void printMap(MMAMap *map) {
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;

	printf("\nPrint map\n");
	
	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			position = x + y * xMax;
			
			printf("%d ", (*map).currentCells[position]);
		}
		printf("\n");
	}
}


