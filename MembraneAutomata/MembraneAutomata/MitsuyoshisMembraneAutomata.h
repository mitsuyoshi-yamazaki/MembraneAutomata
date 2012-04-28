//
//  MembraneAutomata.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define MMANull		0x00
#define MMAWater	0x01
#define MMAOil		0x02
#define MMAWaterFamilier	0x03
#define MMAOilFamilier		0x04

#define MMAUnstableMax	8

#define MMARuleExchange	"Exchange"
#define MMARuleAutomata	"Automata"

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
	int range;
	MMASize size;
	byte *currentCells;
	byte *previousCells;
};
typedef struct MMAMap MMAMap;

MMASize MMASizeMake(int, int);
void MMAMapInitialize(MMAMap *, MMASize);
void MMAMapDelete(MMAMap *);

void clearMap(MMAMap *);
void randomizeMap(MMAMap *, int *);

void stepMap(MMAMap *);
//void stepCell(MMAMap *, int);
void printMap(MMAMap *);
void countSubstances(MMAMap *);

char* ruleName();