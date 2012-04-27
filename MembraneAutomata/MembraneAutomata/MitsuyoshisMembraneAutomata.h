//
//  MembraneAutomata.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define MMAWater	0x00
#define MMAOil		0x01
#define MMAWaterFamilier	0x02
#define MMAOilFamilier		0x03

#define MMAUnstableMax	8

typedef unsigned char byte;

struct MMASize {
	int width;
	int height;
};
typedef struct MMASize MMASize;

struct MMACell {

};
typedef struct MMACell MMACell;

struct MMAMap {
	MMASize size;
	byte *currentCells;
//	byte *previousCells;
};
typedef struct MMAMap MMAMap;

MMASize MMASizeMake(int, int);
void MMAMapInitialize(MMAMap *, MMASize);
void MMAMapDelete(MMAMap *);

void clearMap(MMAMap *);
void randomizeMap(MMAMap *, unsigned int, unsigned int, unsigned int, unsigned int);

void stepMap(MMAMap *);
void stepCell(MMAMap *, int);
void printMap(MMAMap *);
void countSubstances(MMAMap *);