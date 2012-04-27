//
//  MembraneAutomata.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

typedef unsigned char byte;

typedef enum {
	MMAWater,
	MMAOil,
	MMAWaterFamilier,
	MMAOilFamilier,
}MMASubstance;

struct MMASize {
	unsigned long x;
	unsigned long y;
};
typedef struct MMASize MMASize;

struct MMACell {
	byte substance;
};
typedef struct MMACell MMACell;

struct MMAMap {
	byte rule;
	MMASize size;
	MMACell *currentCells;
	MMACell *previousCells;
};
typedef struct MMAMap MMAMap;

MMASize MMASizeMake(unsigned long, unsigned long);
MMAMap MMAMapMake(byte, MMASize);

void step(MMAMap *);