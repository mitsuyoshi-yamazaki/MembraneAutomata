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

int unstabilityBetween(byte, byte);
int unstabilityInThePosition(MMAMap *, byte, int);

#pragma mark - Calculate Stability
int unstabilityBetween(byte substanceA, byte substanceB) {
	
	if (substanceA == MMANull || substanceB == MMANull) {
		return 0;
	}
	
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

int unstabilityInThePosition(MMAMap *map, byte substance, int position) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int x = position % xMax;
	int y = position / xMax;

	int subPosition;
	int unstability = 0;
	
	int minimumRange = 0 - (*map).range;
	int maxRange = (*map).range + 1;
	
	for (int i = minimumRange; i < maxRange; i++) {
		for (int j = minimumRange; j < maxRange; j++) {
			subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;

			unstability += unstabilityBetween(substance, (*map).currentCells[subPosition]);
		}
	}

	return unstability;
}


#pragma mark - Map Initializer
MMASize MMASizeMake(int x, int y) {
	MMASize size;
	
	size.width = x;
	size.height = y;
	return size;
}

void MMAMapInitialize(MMAMap *map, MMASize size) {	
	
	(*map).range = 1;
	(*map).size = size;

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

void randomizeMap(MMAMap *map, int *rate) {
	
	srand(time(NULL));
	srand(rand());
	
	int position = 0;
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int maximum = rate[MMANull] + rate[MMAWater] + rate[MMAOil] + rate[MMAWaterFamilier] + rate[MMAOilFamilier];
	int randomValue = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			
			randomValue = rand() % maximum;
			
			if (randomValue < rate[MMAWater]) {
				(*map).currentCells[position] = MMAWater;
			}
			else if (randomValue < rate[MMAWater] + rate[MMAOil]) {
				(*map).currentCells[position] = MMAOil;
			}
			else if (randomValue < rate[MMAWater] + rate[MMAOil] + rate[MMAWaterFamilier]) {
				(*map).currentCells[position] = MMAWaterFamilier;
			}
			else if (randomValue < rate[MMAWater] + rate[MMAOil] + rate[MMAWaterFamilier] + rate[MMAOilFamilier]) {
				(*map).currentCells[position] = MMAOilFamilier;
			}
			else {
				(*map).currentCells[position] = MMANull;
			}
		}
	}
}


#pragma mark - Execution
void stepMap(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	int subPosition = 0;
	int mostStablePosition = 0;
	int mostStableUnstability;
	int subUnstability;
	byte currentSubstance;

	int minimumRange = 0 - (*map).range;
	int maxRange = (*map).range + 1;

	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			currentSubstance = (*map).currentCells[position];

			if (1) {//(currentSubstance != MMANull) {
				mostStablePosition = position;
				mostStableUnstability = MMAUnstableMax;
				
				for (int i = minimumRange; i < maxRange; i++) {
					for (int j = minimumRange; j < maxRange; j++) {
						subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;
						subUnstability = unstabilityInThePosition(map, currentSubstance, subPosition);
						
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
}
/*
void stepCell(MMAMap *map, int position) {

	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int x = position % xMax;
	int y = position / xMax;
	
	int mostStablePosition = position;
	int mostStableUnstability = MMAUnstableMax;
	byte currentSubstance = (*map).currentCells[position];
	int subPosition = 0;
	int subUnstability;

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
*/

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

void countSubstances(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	
	int water	= 0;
	int oil		= 0; 
	int wFamilier = 0;
	int oFamilier = 0;
	
	printf("\nCount substances\n");
	
	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			position = x + y * xMax;
			
			switch ((*map).currentCells[position]) {
				case MMAWater:	water++;	break;
				case MMAOil:	oil++;		break;
				case MMAWaterFamilier:	wFamilier++;	break;
				case MMAOilFamilier:	oFamilier++;	break;
				default:	break;
			}
		}
	}

	printf("Water  : %5d\n", water);
	printf("Oil    : %5d\n", oil);
	printf("wFamil : %5d\n", wFamilier);
	printf("oFamil : %5d\n", oFamilier);
}

