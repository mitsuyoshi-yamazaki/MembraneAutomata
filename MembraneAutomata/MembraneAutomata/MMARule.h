//
//  MMARule.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MMADefinition.h"

char* ruleName(MMARule);
char* ruleDescription(MMARule);
char* ruleNameOfMap(MMAMap *);
char* ruleDescriptionOfMap(MMAMap *);

void stepInRuleExchanging(MMAMap *);
void stepInRuleAutomata(MMAMap *);
