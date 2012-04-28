//
//  MMADefinition.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define MMANull		0x00
#define MMAWater	0x01
#define MMAOil		0x02
#define MMAWaterFamilier	0x03
#define MMAOilFamilier		0x04
#define MMAMembrane			0x05

#define MMANumberOfSubstance	6

#define MMAUnstableMax	8


typedef unsigned char byte;

typedef enum rule {
	MMARuleExchange,
	MMARuleAutomata,
	MMARuleAtomSet,
}MMARule;

struct MMASize {
	int width;
	int height;
};
typedef struct MMASize MMASize;

struct MMACell {
	
};
typedef struct MMACell MMACell;

struct MMAMap {
	MMARule rule;
	int range;
	MMASize size;
	byte *currentCells;
	byte *previousCells;
};
typedef struct MMAMap MMAMap;

MMASize MMASizeMake(int, int);
void MMAMapInitialize(MMAMap *, MMASize);
void MMAMapDelete(MMAMap *);

int unstabilityBetween(byte, byte);
int unstabilityInThePosition(MMAMap *, byte, int);

void clearMap(MMAMap *);
void randomizeMap(MMAMap *, int *);
void frameWith(MMAMap *, byte, int);

void stepMap(MMAMap *);
//void stepCell(MMAMap *, int);
void printMap(MMAMap *);
void countSubstances(MMAMap *);

