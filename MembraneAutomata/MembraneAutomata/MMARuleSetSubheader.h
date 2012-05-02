//
//  MMARuleSetSubheader.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#include "MMADefinition.h"

#define MMARuleMinimum		-1000
#define MMARuleMaximum		1000

typedef unsigned char byte;

struct MMAReactionRule {
	byte object;
	byte subtracter;
	byte result;
	int minimum;
	int maximum;
};
typedef struct MMAReactionRule MMAReactionRule;

struct MMAAtomSet {
	MMAReactionRule *ruleSet;
	byte *attributes;
	byte *composeRules;
	byte *decomposeRules;
	int atomCount;
	int substanceCount;
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

struct MMAAmount {
	int *amount;
	int ruleCount;
};
typedef struct MMAAmount MMAAmount;

void initializeSetAsDefault(MMAAmount *);
void initializeAmount(MMAAmount *, int);
void resetAmount(MMAAmount *);

MMAReactionRule MMAReactionRuleDummy();
MMAReactionRule MMAReactionRuleMake(byte, byte, byte, int, int);

void MMAAtomDefaultInitializer(MMAAtomSet *);

byte nextSubstance(int, MMAAmount *, byte);
byte nextSubstanceInVariableRule(MMAAtomSet *,MMAAmount *, byte);

void countAmount(MMAAmount *, byte);
