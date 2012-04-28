//
//  MMARule.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "MMARule.h"

#define MMARuleNameExchange	"Exchange"
#define MMARuleNameAutomata	"Automata"
#define MMARuleNameAtomSet	"Atom Set"

#define MMARuleDescriptionExchange	"It exchanges cell statuses as like real world. Amount of each substances never change. Not very succeeded."
#define MMARuleDescriptionAutomata	"It changes cell statuses like cellular automata. Oil drops and membrane appear."
#define MMARuleDescriptionAtomSet	"Now working"

char* ruleName(MMARule rule) {
	
	switch (rule) {
		case MMARuleExchange:
			return MMARuleNameExchange;
			
		case MMARuleAutomata:
			return MMARuleNameAutomata;
			
		case MMARuleAtomSet:
			return MMARuleNameAtomSet;
			
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
			
		case MMARuleAtomSet:
			return MMARuleDescriptionAtomSet;
			
		default:
			return NULL;
	}
}
