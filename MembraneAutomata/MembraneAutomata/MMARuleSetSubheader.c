//
//  MMARuleSetSubheader.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "MMARuleSetSubheader.h"

byte isComposed(int, MMAAmount *, byte);
byte decompose(int, MMAAmount *, byte);

byte isComposedInVariableRule(MMAAmount *, MMAReactionRule *, byte);
byte decomposeInVariableRule(MMAAmount *, MMAAtomSet *, byte);

byte react(MMAReactionRule, MMAAmount *);

#pragma mark - 
MMAReactionRule MMAReactionRuleMake(byte object, byte subtracter, byte result, int minimum, int maximum) {
	
	MMAReactionRule rule;
	
	rule.object = object;
	rule.subtracter = subtracter;
	rule.minimum = minimum;
	rule.maximum = maximum;
	rule.result = result;
	
	return rule;
}

MMAReactionRule MMAReactionRuleDummy() {
	MMAReactionRule rule;
	return rule;
}

void MMAAtomDefaultInitializer(MMAAtomSet *atom) {
	
	byte water = 1;
	byte oil = 2;
	byte membrane = 3;
	
	MMAReactionRule waterDecomposeRule = MMAReactionRuleMake(oil, 0, oil, 26, MMARuleMaximum);
	MMAReactionRule oilDecomposeRule = MMAReactionRuleMake(water, 0, water, 26, MMARuleMaximum);
	MMAReactionRule membraneComposeRule0 = MMAReactionRuleMake(membrane, 0, membrane, 0, 10);
	MMAReactionRule membraneComposeRule1 = MMAReactionRuleMake(oil, water, membrane, -6, 6);
	MMAReactionRule membraneDecomposeRule0 = MMAReactionRuleMake(oil, water, oil, -1, MMARuleMaximum);
	MMAReactionRule membraneDecomposeRule1 = MMAReactionRuleMake(water, oil, water, -1, MMARuleMaximum);
	
	(*atom).ruleSet = (MMAReactionRule *)malloc(sizeof(MMAReactionRule) * 6);
//	(*atom).ruleSet[0] = MMAReactionRuleDummy();
	(*atom).ruleSet[0] = waterDecomposeRule;
	(*atom).ruleSet[1] = oilDecomposeRule;
	(*atom).ruleSet[2] = membraneComposeRule0;
	(*atom).ruleSet[3] = membraneComposeRule1;
	(*atom).ruleSet[4] = membraneDecomposeRule0;
	(*atom).ruleSet[5] = membraneDecomposeRule1;
	
	(*atom).atomCount = 4; // actual count + 1(Null substance)
	
	(*atom).attributes = (byte *)malloc(sizeof(byte) * (*atom).atomCount);
	(*atom).attributes[0] = 0x00;	// Null Substance
	(*atom).attributes[1] = 0x01;
	(*atom).attributes[2] = 0x02;
	(*atom).attributes[3] = 0x04;
	
	(*atom).composeRules = (byte *)malloc(sizeof(byte) * (*atom).atomCount);
	(*atom).composeRules[0] = 0x00;
	(*atom).composeRules[1] = 0x00;
	(*atom).composeRules[2] = 0x00;
	(*atom).composeRules[3] = 0x0c;
	
	(*atom).decomposeRules = (byte *)malloc(sizeof(byte) * (*atom).atomCount);
	(*atom).decomposeRules[0] = 0x00;
	(*atom).decomposeRules[1] = 0x01;
	(*atom).decomposeRules[2] = 0x02;
	(*atom).decomposeRules[3] = 0x30;
	
	(*atom).substanceCount = 4; // actual count + 1(Null substance)
	(*atom).supposedRange = 3;
}


#pragma mark - 
void initializeSetAsDefault(MMAAmount *set) {

	int numberOfSubstances = 7;
	
	(*set).amount = (int *)malloc(sizeof(int) * numberOfSubstances);
	(*set).ruleCount = numberOfSubstances;

	resetAmount(set);	
}

void initializeAmount(MMAAmount *set, int atomCount) {
	
	(*set).amount = (int *)malloc(sizeof(int) * atomCount);
	(*set).ruleCount = atomCount;
	
	resetAmount(set);	
}

void resetAmount(MMAAmount *set) {
	
	for (int i = 0; i < (*set).ruleCount; i++) {
		(*set).amount[i] = 0;
	}
}

byte nextSubstance(int range, MMAAmount *set, byte target) {

	int max = (*set).ruleCount;
	int i;
	
	for (i = 0; i < max; i++) {
		if (isComposed(range, set, i)) {
			return i;
		}
	}
	return decompose(range, set, target);
}


#pragma mark - Rules
byte isComposed(int range, MMAAmount *set, byte substance) {
	
	switch (substance) {
		case 0:		// water
			return 0;
			
		case 1:		// oil
			return 0;
			
		case 2: {	// membrane
			
			int waterCount = (*set).amount[0];
			int oilCount = (*set).amount[1];
			int membraneCount = (*set).amount[2] + (*set).amount[4];
			
			int membraneMaximum = range * 3 + 1;
			int membraneThreshold = range * 2;
			
			if ((*set).amount[2] > 0 && membraneCount < membraneMaximum && abs(waterCount - (oilCount  + (*set).amount[3])) <= membraneThreshold) {
				return 1;
			}
			return 0;
		}
			
		case 3: {
			int wMax = range * (range * 2 + 1) + range;
			int maximum = range * range;
			int membraneCount = (*set).amount[2] + (*set).amount[4] + (*set).amount[6];
			
			if (membraneCount > 0 && (*set).amount[3] > 0 && (*set).amount[3] < maximum && membraneCount < range * 2 + 1 && (*set).amount[0] > 0 && (*set).amount[0] < wMax) {
				return 1;
			}
			return 0;
		}
			
		case 4: {
			
			int waterCount = (*set).amount[0];
			int oilCount = (*set).amount[1];
			int membraneCount = (*set).amount[2] + (*set).amount[4];
			
			int maximum = (range * 3 + 1) * 2;
			int threshold = waterCount - (oilCount  + (*set).amount[3]);
			
			if ((*set).amount[4] > 0 && membraneCount < maximum && threshold > 0 && threshold < 20 && (*set).amount[6] == 0) {
				return 1;
			}

			return 0;
		}
			
		case 5: {
			int maximum = range * range * 3;
			if ((*set).amount[5] < maximum && (*set).amount[3] > 0 && (*set).amount[3] < 10 && (*set).amount[0] == 0) {//(*set).amount[5] > 0 && 
				return 1;
			}
			return 0;
		}
			
		case 6: {
			
			int waterCount = (*set).amount[0];
			int oilCount = (*set).amount[1];
			int membraneCount = (*set).amount[2] + (*set).amount[4];// + (*set).amount[6];
			
			int maximum = (range * 3 + 1) * 2;
			int threshold = (oilCount + (*set).amount[3]) - (waterCount);
			
			if ((*set).amount[6] > 0 && membraneCount < maximum && threshold > 0 && threshold < 14 && (*set).amount[4] < 3) {
				return 1;
			}
			
			return 0;
		}
			
		default:
			return 0;
	}
}

byte decompose(int range, MMAAmount *set, byte target) {
		
	int waterCount = (*set).amount[0] + (*set).amount[6];
	int oilCount = (*set).amount[1] + (*set).amount[3];
//	int membraneCount = (*set).amount[2];
	
	int changeThreshold = (range * (range * 2 + 1)) + (range * 2);

	switch (target) {
		case 0:		// water
			if (oilCount >= changeThreshold) {
				return 1;
			}
			break;
			
		case 1:		// oil
			if (waterCount >= changeThreshold) {
				return 0;
			}
			break;
			
		case 2: 	// membrane
			if (waterCount > oilCount) {
				return 0;
			}
			else {
				return 1;
			}
			break;
			
		case 3:
			if (waterCount == 0 || waterCount >= changeThreshold) {
				return 1;
			}
			break;
			
		case 4:
			if (waterCount > oilCount) {
				return 0;
			}
			else {
				return 1;
			}
			break;

		case 5:
			return 0;
			break;
			
		case 6:
			if (waterCount > oilCount) {
				return 0;
			}
			else {
				return 1;
			}
			break;
			
		default:
			break;
	}

	return target;
}


#pragma mark - In Variable Rule
byte nextSubstanceInVariableRule(MMAAtomSet *atom, MMAAmount *amount, byte target) {
	
	int iMax = (*atom).substanceCount;
	
	for (int i = 0; i < iMax; i++) {
		if (isComposedInVariableRule(amount, (*atom).ruleSet, (*atom).composeRules[i])) {
			return i;
		}
	}
	
	return decomposeInVariableRule(amount, atom, target);
}

byte isComposedInVariableRule(MMAAmount *amount, MMAReactionRule *rules, byte theRule) {

	if (!theRule) {
		return 0;
	}
	
	byte mask = 0x01;
	int i = 0;
	
	while (theRule != 0) {
		if (theRule & mask) {
			if (!react(rules[i], amount)) {
				return 0;
			}
		}
		
		theRule = theRule >> 1;
		i++;
	}
	
	return 1;
}

byte decomposeInVariableRule(MMAAmount *amount, MMAAtomSet *atom, byte target) {
	
	byte theRule = (*atom).decomposeRules[target];
	const byte mask = 0x01;
	byte result = 0;
	int i = 0;
	
	while (theRule != 0) {
		if (theRule & mask) {
			result = react((*atom).ruleSet[i], amount);
			if (result) {
				return result;
			}
		}
		theRule = theRule >> 1;
		i++;
	}
	
	return target;
}

byte react(MMAReactionRule rule, MMAAmount *amount) {
	
	int value = (*amount).amount[rule.object] - (*amount).amount[rule.subtracter];
	
	if (value > rule.minimum && value < rule.maximum) {
		return rule.result;
	}
	return 0;
}

void countAmount(MMAAmount *amount, byte attribute) {
	
	const byte mask = 0x01;
	int i = 1;
	
	while (attribute != 0) {
		if (attribute & mask) {
			(*amount).amount[i]++;
		}
		
		attribute = attribute >> 1;
		i++;
	}
}

