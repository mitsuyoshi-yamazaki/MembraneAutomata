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

#pragma mark - Initializer
MMASize MMASizeMake(unsigned long x, unsigned long y) {
	MMASize size;
	
	size.x = x;
	size.y = y;
	return size;
}

void MMAMapInitialize(MMAMap *map, MMASize size) {	
	
	(*map).size = size;

	(*map).previousCells = (byte *)malloc(sizeof(byte) * (*map).size.x * (*map).size.y);
	(*map).currentCells = (byte *)malloc(sizeof(byte) * (*map).size.x * (*map).size.y);
}

#pragma mark - Execution
void step(MMAMap *map) {
	
	int xMax = (*map).size.x;
	int yMax = (*map).size.y;
	int position = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;

		}
	}
}

void clearMap(MMAMap *map) {
	
	int xMax = (*map).size.x;
	int yMax = (*map).size.y;
	int position = 0;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			(*map).previousCells[position] = MMAWater;
			(*map).currentCells[position] = MMAWater;
		}
	}
}