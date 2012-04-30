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
	MMARuleRuleSet,
	MMARuleVariableRuleSet,
}MMARule;

struct MMAPoint {
	int x;
	int y;
};
typedef struct MMAPoint MMAPoint;

struct MMASize {
	int width;
	int height;
};
typedef struct MMASize MMASize;

struct MMARange {
	MMAPoint origin;
	MMASize size;
};
typedef struct MMARange MMARange;

struct MMACell {
	
};
typedef struct MMACell MMACell;

struct MMAPattern {
	int identifier;
	MMARule rule;
	int range;
	MMAPoint origin;
	MMASize size;
	byte *cells;
};
typedef struct MMAPattern MMAPattern;

struct MMAMap {
	int identifier;
	MMARule rule;
	int range;
	MMASize size;
	byte *currentCells;
	byte *previousCells;
};
typedef struct MMAMap MMAMap;

MMAPoint MMAPointMake(int, int);
MMASize MMASizeMake(int, int);
MMARange MMARangeMake(int, int, int, int);
MMARange MMARangeFromPoints(MMAPoint, MMAPoint);
void printRange(MMARange);
void MMAPatternInitialize(MMAPattern *, MMASize, MMARule, int);
void MMAPatternDelete(MMAPattern *);
void MMAMapInitialize(MMAMap *, MMASize);
void MMAMapDelete(MMAMap *);

int unstabilityBetween(byte, byte);
int unstabilityInThePosition(MMAMap *, byte, int);

void clearMap(MMAMap *);
void fillMapWith(MMAMap *, byte);
void randomizeMap(MMAMap *, int *, int);
void frameWith(MMAMap *, byte, int);
void clearRange(MMAMap *, MMARange);
void fillRangeWith(MMAMap *, MMARange, byte);
void randomizeRange(MMAMap *, MMARange, int *, int);

void patternIn(MMAMap *, MMAPattern *, MMAPoint, MMAPoint);
void printMap(MMAMap *);
void countSubstances(MMAMap *);

int storeMap(MMAMap *, char *);
int restoreMap(MMAMap *, char *);
int storePattern(MMAPattern *, char *);
int restorePattern(MMAPattern *, char *);

