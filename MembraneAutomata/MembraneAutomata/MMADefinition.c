//
//  MMADefinition.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "MMADefinition.h"
#include "json.h"

void filenameCreateWithId(char *,unsigned int);

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
MMAPoint MMAPointMake(int x, int y) {
	MMAPoint point;
	
	point.x = x;
	point.y = y;
	return point;
}

MMASize MMASizeMake(int x, int y) {
	MMASize size;
	
	size.width = x;
	size.height = y;
	return size;
}

MMARange MMARangeMake(int x, int y, int width, int height) {
	MMARange range;
	
	range.origin.x = x;
	range.origin.y = y;
	range.size.width = width;
	range.size.height = height;
	return range;
}

MMARange MMARangeFromPoints(MMAPoint pointA, MMAPoint pointB) {
	
	MMAPoint patternFrom = pointA;
	MMAPoint patternTo = pointB;
	
	if (pointA.x > pointB.x) {
		patternFrom.x = pointB.x;
		patternTo.x = pointA.x;
	}
	if (pointA.y > pointB.y) {
		patternFrom.y = pointB.y;
		patternTo.y = pointA.y;
	}

	return MMARangeMake(patternFrom.x, patternFrom.y, patternTo.x - patternFrom.x, patternTo.y - patternFrom.y);
}

void printRange(MMARange range) {
	printf("Range origin : (%d,%d), size : (%d,%d)\n", range.origin.x, range.origin.y, range.size.width, range.size.height);
}

void MMAPatternInitialize(MMAPattern *pattern, MMASize size, MMARule rule, int range) {
	
	(*pattern).rule = rule;
	(*pattern).range = range;
	(*pattern).origin = MMAPointMake(0, 0);
	(*pattern).size = size;
	(*pattern).identifier = 0;
	
	(*pattern).cells = (byte *)malloc(sizeof(byte) * (*pattern).size.width * (*pattern).size.height);
}

void MMAPatternDelete(MMAPattern *pattern) {
	free((*pattern).cells);
}

void MMAMapInitialize(MMAMap *map, MMASize size) {	
	
	(*map).range = 1;
	(*map).size = size;
	(*map).rule = MMARuleAutomata;
	(*map).identifier = 0;
	
	(*map).previousCells = (byte *)malloc(sizeof(byte) * (*map).size.width * (*map).size.height);
	(*map).currentCells = (byte *)malloc(sizeof(byte) * (*map).size.width * (*map).size.height);
	
	clearMap(map);
}

void MMAMapDelete(MMAMap *map) {
	free((*map).currentCells);
	free((*map).previousCells);
}


#pragma mark - Cell Initializer
void clearMap(MMAMap *map) {
	fillMapWith(map, 0);
}

void fillMapWith(MMAMap *map, byte substance) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			(*map).previousCells[position] = substance;
			(*map).currentCells[position] = substance;
		}
	}
}

void randomizeMap(MMAMap *map, int *rate, int count) {
	MMARange range = MMARangeMake(0, 0, (*map).size.width, (*map).size.height);
	
	randomizeRange(map, range, rate, count);
}

void frameWith(MMAMap *map, byte substance, int margin) {
	
	int position = 0;
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			
			if (x < margin || x > (xMax - margin) || y < margin || y > (yMax - margin)) {
				(*map).currentCells[position] = substance;
				(*map).previousCells[position] = substance;
			}
		}
	}
}

void clearRange(MMAMap *map, MMARange range) {
	fillRangeWith(map, range, 0);
}

void fillRangeWith(MMAMap *map, MMARange range, byte substance) {
	
	int xMax = range.origin.x + range.size.width;
	int yMax = range.origin.y + range.size.height;
	int width = (*map).size.width;
	
	if (xMax > (*map).size.width) {
		xMax = (*map).size.width;
	}
	if (yMax > (*map).size.height) {
		yMax = (*map).size.height;
	}
	
	int xMin = range.origin.x;
	int yMin = range.origin.y;
	
	if (xMin < 0) {
		xMin = 0;
	}
	if (yMin < 0) {
		yMin = 0;
	}
	
	int position = 0;
	
	for (int x = xMin; x < xMax; x++) {
		for (int y = yMin; y < yMax; y++) {
			position = x + y * width;
			(*map).previousCells[position] = substance;
			(*map).currentCells[position] = substance;
		}
	}
}

void randomizeRange(MMAMap *map, MMARange range, int *rate, int count) {
	
	srand(time(NULL));
	srand(rand());
	
	int maximum = 0;
	int until[count];
	
	for (int i = 0; i < count; i++) {
		maximum += rate[i];
		until[i] = maximum;
	}
	
	int xMax = range.origin.x + range.size.width;
	int yMax = range.origin.y + range.size.height;
	int width = (*map).size.width;
	
	if (xMax > (*map).size.width) {
		xMax = (*map).size.width;
	}
	if (yMax > (*map).size.height) {
		yMax = (*map).size.height;
	}
	
	int xMin = range.origin.x;
	int yMin = range.origin.y;
	
	if (xMin < 0) {
		xMin = 0;
	}
	if (yMin < 0) {
		yMin = 0;
	}
		
	int position = 0;
	int randomValue = 0;
	
	for (int x = xMin; x < xMax; x++) {
		for (int y = yMin; y < yMax; y++) {
			position = x + y * width;

			randomValue = rand() % maximum;
			
			for (int j = 0; j < count; j++) {
				if (randomValue < until[j]) {
					(*map).currentCells[position] = j;
					(*map).previousCells[position] = j;
					break;
				}
			}
		}
	}
}


#pragma mark - Pattern Extraction
void patternIn(MMAMap *map, MMAPattern *pattern, MMAPoint fromPoint, MMAPoint toPoint) {
	// 余白切り取り未実装

	MMAPoint patternFrom = fromPoint;
	MMAPoint patternTo = toPoint;

	if (fromPoint.x > toPoint.x) {
		patternFrom.x = toPoint.x;
		patternTo.x = fromPoint.x;
	}
	if (fromPoint.y > toPoint.y) {
		patternFrom.y = toPoint.y;
		patternTo.y = fromPoint.y;
	}
	
	if (fromPoint.x < 0) {
		fromPoint.x = 0;
	}
	if (fromPoint.y < 0) {
		fromPoint.y = 0;
	}
	
	if (toPoint.x > (*map).size.width) {
		toPoint.x = (*map).size.width;
	}
	if (toPoint.y > (*map).size.height) {
		toPoint.y = (*map).size.height;
	}
	
	MMASize size = MMASizeMake(patternTo.x - patternFrom.x, patternTo.y - patternFrom.y);
	MMAPatternInitialize(pattern, size, (*map).rule, (*map).range);

	int x, y;
	int mapWidth = (*map).size.width;
	int patternWidth = (*pattern).size.width;
	int mapPosition;
	int patternPosition;
	
	for (x = patternFrom.x; x < patternTo.x; x++) {
		for (y = patternFrom.y; y < patternTo.y; y++) {
			mapPosition = x + y * mapWidth;
			patternPosition = (x - patternFrom.x) + (y - patternFrom.y) * patternWidth;
			
			(*pattern).cells[patternPosition] = (*map).currentCells[mapPosition];
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

void countSubstances(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	
	int water	= 0;
	int oil		= 0; 
	int wFamilier = 0;
	int oFamilier = 0;
	int membrane = 0;
	
	printf("\nCount substances\n");
	
	for (int y = 0; y < yMax; y++) {
		for (int x = 0; x < xMax; x++) {
			position = x + y * xMax;
			
			switch ((*map).currentCells[position]) {
				case MMAWater:	water++;	break;
				case MMAOil:	oil++;		break;
				case MMAWaterFamilier:	wFamilier++;	break;
				case MMAOilFamilier:	oFamilier++;	break;
				case MMAMembrane:		membrane++;		break;
				default:	break;
			}
		}
	}
	
	printf("Water  : %5d\n", water);
	printf("Oil    : %5d\n", oil);
	printf("wFamil : %5d\n", wFamilier);
	printf("oFamil : %5d\n", oFamilier);
	printf("Membra : %5d\n", membrane);
}


#pragma mark - File
void filenameCreateWithId(char *filename, unsigned int anIdentifier) {
	sprintf(filename, "MMAMapFile%d", anIdentifier);
}

int storeMap(MMAMap *map) {
	MMAPattern pattern;
	MMAPatternInitialize(&pattern, (*map).size, (*map).rule, (*map).range);
	pattern.cells = (*map).currentCells;
	pattern.identifier = (*map).identifier;
	
	int succeeded = storePattern(&pattern);
	
	MMAPatternDelete(&pattern);
	
	return succeeded;
}

int restoreMap(MMAMap *map, unsigned int anIdentifier) {

}

int storePattern(MMAPattern *pattern) {
	
	char filename[30];
	filenameCreateWithId(filename, (*pattern).identifier);
	
	char identifierKey[] = "identifier";
	char rangeKey[] = "range";
	char ruleKey[] = "rule";
//	char originKey[] = "origin";
	char sizeKey[] = "size";
	char cellsFileKey[] = "cells_file";
	
	char cellsFilename[30];
	sprintf(cellsFilename, "%s%d", cellsFileKey, (*pattern).identifier);
	
	
	struct json_object *identifierObject, *rangeObject, *ruleObject, *sizeObject, *cellsFileObject;
	char identifier[30], range[30], rule[30], size[30], cellsFile[30];
	
	sprintf(identifier, "%s:%d", identifierKey, (*pattern).identifier);
	identifierObject = json_tokener_parse(identifier);
	
//	sprintf(size, )
	
	struct json_object *json;
	json = json_tokener_parse("");
//	json_object_object_add(json, cellsFileKey, cellsObject);
	
	return json_object_to_file(filename, json);
}

int restorePattern(MMAPattern *pattern, unsigned int anIdentifier) {
	
}

