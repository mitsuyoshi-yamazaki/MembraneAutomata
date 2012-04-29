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

byte isComposed(int, MMARuleSet, byte);
byte decompose(int, MMARuleSet, byte);

#pragma mark - 
MMARuleSet defaultSet() {
	
	MMARuleSet set;
	int numberOfSubstances = 3;
	
	MMASubstance substances[numberOfSubstances];
	
	substances[0].code = MMAWater;
	substances[1].code = MMAOil;
	substances[2].code = MMAMembrane;
	
	int amount[numberOfSubstances];
	
//	amount[0] = 0;
//	amount[1] = 0;
//	amount[2] = 0;
	
//	set.rules = substances;
	set.amount = amount;
	set.ruleCount = numberOfSubstances;

	resetAmount(&set);
	
	return set;
}

void resetAmount(MMARuleSet *set) {
	
	for (int i = 0; i < (*set).ruleCount; i++) {
		(*set).amount[i] = 0;
	}
}

byte nextSubstance(int range, MMARuleSet set, byte target) {

	int max = set.ruleCount;
	int i;
	
	for (i = 0; i < max; i++) {
		if (isComposed(range, set, i)) {
			return i;
		}
	}
	return decompose(range, set, target);
}


#pragma mark - Rules
byte isComposed(int range, MMARuleSet set, byte substance) {
	
	switch (substance) {
		case 0:		// water
			return 0;
			
		case 1:		// oil
			return 0;
			
		case 2: {	// membrane
			
			int waterCount = set.amount[0];
			int oilCount = set.amount[1];
			int membraneCount = set.amount[2];
			
			int membraneMaximum = range * 3 + 1;
			int membraneThreshold = range * 2;
			
			if (membraneCount > 0 && membraneCount < membraneMaximum && abs(waterCount - oilCount) <= membraneThreshold) {
				return 1;
			}
			return 0;
		}
			
		default:
			return 0;
	}
}

byte decompose(int range, MMARuleSet set, byte target) {
		
	int waterCount = set.amount[0];
	int oilCount = set.amount[1];
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
			
		default:
			break;
	}

	return target;
}

