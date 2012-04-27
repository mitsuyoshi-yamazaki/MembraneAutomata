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

typedef unsigned char byte;

struct MMASize {
	unsigned long x;
	unsigned long y;
};
typedef struct MMASize MMASize;

struct MMACell {

};
typedef struct MMACell MMACell;

struct MMAMap {
	MMASize size;
	byte *currentCells;
	byte *previousCells;
};
typedef struct MMAMap MMAMap;

MMASize MMASizeMake(unsigned long, unsigned long);
void MMAMapInitialize(MMAMap *, MMASize);

void step(MMAMap *);
void clearMap(MMAMap *);
