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

byte isComposed(int, MMARuleSet *, byte);
byte decompose(int, MMARuleSet *, byte);

#pragma mark - 
void initializeSetAsDefault(MMARuleSet *set) {

	int numberOfSubstances = 7;
	
	(*set).amount = (int *)malloc(sizeof(int) * numberOfSubstances);
	(*set).ruleCount = numberOfSubstances;

	resetAmount(set);	
}

void resetAmount(MMARuleSet *set) {
	
	for (int i = 0; i < (*set).ruleCount; i++) {
		(*set).amount[i] = 0;
	}
}

byte nextSubstance(int range, MMARuleSet *set, byte target) {

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
byte isComposed(int range, MMARuleSet *set, byte substance) {
	
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
			if ((*set).amount[2] > 0 && (*set).amount[3] > 0 && (*set).amount[3] < maximum && (*set).amount[2] < range * 2 + 1 && (*set).amount[0] > 0 && (*set).amount[0] < wMax) {
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
			
			if ((*set).amount[4] > 0 && membraneCount < maximum && threshold > 0 && threshold < 14) {
				return 1;
			}

			return 0;
		}
			
		case 5: {
			int maximum = range * range;
			if ((*set).amount[5] < maximum && (*set).amount[3] > 0 && (*set).amount[3] < 10 && (*set).amount[0] == 0) {//(*set).amount[5] > 0 && 
				return 1;
			}
			return 0;
		}
			
		case 6: {
			
			int waterCount = (*set).amount[0];
			int oilCount = (*set).amount[1];
			int membraneCount = (*set).amount[2] + (*set).amount[4] + (*set).amount[6];
			
			int maximum = (range * 3 + 1) * 2;
			int threshold = oilCount - (waterCount  + (*set).amount[3]);
			
			if ((*set).amount[6] > 0 && membraneCount < maximum && threshold > 0 && threshold < 14) {
				return 1;
			}
			
			return 0;
		}
			
		default:
			return 0;
	}
}

byte decompose(int range, MMARuleSet *set, byte target) {
		
	int waterCount = (*set).amount[0];
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
			if (waterCount > oilCount) {
				return 0;
			}
			else {
				return 1;
			}
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

