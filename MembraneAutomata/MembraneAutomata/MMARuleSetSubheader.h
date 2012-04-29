//
//  MMARuleSetSubheader.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MMADefinition.h"

struct MMASubstance {
	byte code;
//	byte composeRule;
//	byte decomposeRule;
};
typedef struct MMASubstance MMASubstance;

struct MMARuleSet {
	int *amount;
	int ruleCount;
};
typedef struct MMARuleSet MMARuleSet;


MMARuleSet defaultSet();
void resetAmount(MMARuleSet *);

byte nextSubstance(int, MMARuleSet, byte);
