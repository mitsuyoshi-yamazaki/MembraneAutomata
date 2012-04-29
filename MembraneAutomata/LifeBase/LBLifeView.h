//
//  LBLifeView.h
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "MitsuyoshisMembraneAutomata.h"

@interface LBLifeView : NSView {
	MMAMap map;
}

- (void)clearCells;
- (void)randomizeCells:(NSUInteger)rate;
- (void)calculateNextPattern;

- (void)initializeCells:(NSUInteger)size;

- (void)print;

- (NSString *)rule;
- (NSUInteger)range;

@end
