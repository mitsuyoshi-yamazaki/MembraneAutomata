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
	MMAPoint clickedPoint;
	MMAPoint draggedPoint;
	
	BOOL dragging;
	BOOL selecting;
	
	NSUInteger patternId;
}

- (void)clearCells;
- (void)randomizeCells:(NSUInteger)rate;
- (void)calculateNextPattern;

- (void)initializeCells:(NSUInteger)size;

- (void)print;
- (void)storeMap;

- (NSString *)rule;
- (NSUInteger)range;
- (NSUInteger)mapId;
- (NSUInteger)steps;

@end
