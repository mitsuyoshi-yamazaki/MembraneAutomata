//
//  MMARule.h
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

typedef enum rule {
	MMARuleExchange,
	MMARuleAutomata,
	MMARuleAtomSet,
}MMARule;

char* ruleName(MMARule);
char* ruleDescription(MMARule);
