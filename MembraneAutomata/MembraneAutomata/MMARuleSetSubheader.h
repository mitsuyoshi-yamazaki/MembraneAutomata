//
//  MMARuleSetSubheader.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MMADefinition.h"

#define MMASubtracterNull	0xff

struct MMAReactionRule {
	byte object;
	byte subtracter;
	int minimum;
	int maximum;
};
typedef struct MMAReactionRule MMAReactionRule;

struct MMAAtomSet {
	byte *attributes;
	MMAReactionRule *composeRules;
	MMAReactionRule *decomposeRules;
	int count;
	int supposedRange;
};
typedef struct MMAAtomSet MMAAtomSet;

struct MMASubstance {
	byte identifier;
	char *description;
	unsigned int attributesMask;
	unsigned int composeRulesMask;
	unsigned int decomposeRulesMask;
};
typedef struct MMASubstance MMASubstance;

struct MMARuleSet {
	int *amount;
	int ruleCount;
};
typedef struct MMARuleSet MMARuleSet;

void initializeSetAsDefault(MMARuleSet *);
void resetAmount(MMARuleSet *);

void MMAAtomDefaultInitializer(MMAAtomSet *);

byte nextSubstance(int, MMARuleSet *, byte);
