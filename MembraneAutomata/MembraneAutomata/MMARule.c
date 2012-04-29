//
//  MMARule.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MMARule.h"

#define MMARuleNameExchange	"Exchange"
#define MMARuleNameAutomata	"Automata"
#define MMARuleNameRuleSet	"Rule Set"

#define MMARuleDescriptionExchange	"It exchanges cell statuses as like real world. Amount of each substances never change. Not very succeeded."
#define MMARuleDescriptionAutomata	"It changes cell statuses like cellular automata. Oil drops and membrane appear. Works well"
#define MMARuleDescriptionRuleSet	"It changes cell statuses like cellular automata. Automata rules are created from combination of small rules. Now working"

void copyCells(MMAMap *);

#pragma mark - Rule Name and Description
char* ruleName(MMARule rule) {
	
	switch (rule) {
		case MMARuleExchange:
			return MMARuleNameExchange;
			
		case MMARuleAutomata:
			return MMARuleNameAutomata;
			
		case MMARuleRuleSet:
			return MMARuleNameRuleSet;
			
		default:
			return NULL;
	}
}

char* ruleDescription(MMARule rule) {
	
	switch (rule) {
		case MMARuleExchange:
			return MMARuleDescriptionExchange;
			
		case MMARuleAutomata:
			return MMARuleDescriptionAutomata;
			
		case MMARuleRuleSet:
			return MMARuleDescriptionRuleSet;
			
		default:
			return NULL;
	}
}

char* ruleNameOfMap(MMAMap *map) {
	return ruleName((*map).rule);
}

char* ruleDescriptionOfMap(MMAMap *map) {
	return ruleDescription((*map).rule);
}


#pragma mark - Execution
void copyCells(MMAMap *map) {
	memcpy((*map).previousCells, (*map).currentCells, (*map).size.width * (*map).size.height * sizeof(byte));
}

void stepMap(MMAMap *map) {
	
	switch ((*map).rule) {
		case MMARuleExchange:
			stepInRuleExchanging(map);
			break;
			
		case MMARuleAutomata:
			copyCells(map);
			stepInRuleAutomata(map);
			break;
			
		case MMARuleRuleSet:
			copyCells(map);
			stepInRuleRuleSet(map);
			break;
			
		default:
			break;
	}
}


#pragma mark - Rules
void stepInRuleExchanging(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	int subPosition = 0;
	int mostStablePosition = 0;
	int mostStableUnstability;
	int subUnstability;
	byte currentSubstance;
	
	int minimumRange = 0 - (*map).range;
	int maxRange = (*map).range + 1;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			currentSubstance = (*map).currentCells[position];
			
			if (1) {//(currentSubstance != MMANull) {
				mostStablePosition = position;
				mostStableUnstability = MMAUnstableMax;
				
				for (int i = minimumRange; i < maxRange; i++) {
					for (int j = minimumRange; j < maxRange; j++) {
						subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;
						subUnstability = unstabilityInThePosition(map, currentSubstance, subPosition);
						
						if (subUnstability < mostStableUnstability) {
							mostStableUnstability = subUnstability;
							mostStablePosition = subPosition;
						}
					}
				}
				
				(*map).currentCells[position] = (*map).currentCells[mostStablePosition];
				(*map).currentCells[mostStablePosition] = currentSubstance;
			}
		}
	}
}

void stepInRuleAutomata(MMAMap *map) {
		
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	int subPosition = 0;
	
	int range = (*map).range;
	
	int waterCount = 0;
	int oilCount = 0;
	int membraneCount = 0;
	int oFamilCount = 0;
	
	int changeThreshold = (range * (range * 2 + 1)) + (range * 2);
	
	int membraneMaximum = range * 3 + 1;
	int membraneThreshold = range * 2;
	
	int oFamilMaximum = range * 2;
	int oFamilThreshold = (int)((range * 2 + 1) * (range * 2 + 1) * 0.6);
	
	int minimumRange = 0 - range;
	int maxRange = range + 1;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			waterCount = 0;
			oilCount = 0;
			membraneCount = 0;
			oFamilCount = 0;
			
			for (int i = minimumRange; i < maxRange; i++) {
				for (int j = minimumRange; j < maxRange; j++) {
					subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;
					
					switch ((*map).previousCells[subPosition]) {
						case MMAWater:
							waterCount++;
							break;
							
						case MMAOil:
							oilCount++;
							break;
							
						case MMAMembrane:
							membraneCount++;
							break;
							
						case MMAOilFamilier:
							oFamilCount++;
							break;
							
						default:
							break;
					}
				}
			}
			
			if (membraneCount > 0 && membraneCount < membraneMaximum && abs(waterCount - (oilCount + oFamilCount)) <= membraneThreshold) {
				(*map).currentCells[position] = MMAMembrane;
			}
			else if (oFamilCount > 0 && oFamilCount < oFamilMaximum && oilCount > oFamilThreshold) {
				(*map).currentCells[position] = MMAOilFamilier;
			}
			else {
				switch ((*map).previousCells[position]) {
					case MMAWater:
						if ((oilCount + oFamilCount) >= changeThreshold) {
							(*map).currentCells[position] = MMAOil;
						}
						break;
						
					case MMAOil:
						if (waterCount >= changeThreshold) {
							(*map).currentCells[position] = MMAWater;
						}
						break;
						
					case MMAMembrane:
						if (waterCount > (oilCount + oFamilCount)) {
							(*map).currentCells[position] = MMAWater;
						}
						else {
							(*map).currentCells[position] = MMAOil;
						}
						break;
						
					case MMAOilFamilier:
						(*map).currentCells[position] = MMAOil;
						break;
						
					default:
						break;
				}
			}
		}
	}
}

void stepInRuleRuleSet(MMAMap *map) {
	
	int xMax = (*map).size.width;
	int yMax = (*map).size.height;
	int position = 0;
	int subPosition = 0;

	int range = (*map).range;
	int minimumRange = 0 - range;
	int maxRange = range + 1;
	
	MMARuleSet set;
	initializeSetAsDefault(&set);

	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			position = x + y * xMax;
			resetAmount(&set);
			
			for (int i = minimumRange; i < maxRange; i++) {
				for (int j = minimumRange; j < maxRange; j++) {
					subPosition = ((x + i + xMax) % xMax) + ((y + j + yMax) % yMax) * xMax;
					
					set.amount[(*map).previousCells[subPosition]]++;
				}
			}

			(*map).currentCells[position] = nextSubstance(range, &set, (*map).previousCells[position]);
		}
	}
}


