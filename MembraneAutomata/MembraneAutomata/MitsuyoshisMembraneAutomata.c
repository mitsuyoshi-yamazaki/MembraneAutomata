//
//  MitsuyoshisMembraneAutomata.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "MitsuyoshisMembraneAutomata.h"

#pragma mark - Initializer
MMASize MMASizeMake(unsigned long x, unsigned long y) {
	MMASize size;
	
	size.x = x;
	size.y = y;
	return size;
}

MMAMap MMAMapMake(byte rule, MMASize size) {
	MMAMap map;
	
	map.rule = rule;
	map.size = size;
	return map;
}

#pragma mark - Execution
void step(MMAMap *map) {
	
}