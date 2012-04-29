//
//  LBLifeView.m
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "LBLifeView.h"

@interface LBLifeView ()

- (void)randomizeAsDefault;

@end

@implementation LBLifeView

- (void)randomizeAsDefault {
//	int rate[MMANumberOfSubstance] = {0,1000,1000,0,2,1};	// Rule Automata用
	int rate[MMANumberOfSubstance] = {1000,1000,1,2,0,0};	// Rule Rule Set用
	randomizeMap(&map, rate);
	frameWith(&map, MMAWater, map.size.width * 0.01);
}


#pragma mark - Lifecycle
- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (void)dealloc 
{
    
    [super dealloc];
}


- (void)drawRect:(NSRect)dirtyRect
{
	CGContextRef context = [[NSGraphicsContext currentContext] graphicsPort];
		
	NSUInteger width = map.size.width;
	NSUInteger height = map.size.height;
	
	CGFloat gridSize = self.bounds.size.width / width;	
	
	NSUInteger position;

	for (NSUInteger y = 0; y < height; y++) {
		for (NSUInteger x = 0; x < width; x++) {
			position = x + y * width;
						
			if (map.currentCells[position] != MMANull) {
				switch (map.currentCells[position]) {
						//				case MMANull:
						//					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 1.0f, 1.0f, 0.8f));	// White
						//					break;
						
					case MMAWater:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.3f, 0.3f, 1.0f, 0.8f));	// Blue
						break;
						
					case MMAOil:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 0.3f, 0.3f, 0.8f));	// Red
						break;
						
					case MMAWaterFamilier:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.1f, 1.0f, 0.4f, 0.8f));	// Green
						break;
						
					case MMAOilFamilier:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.8f, 0.8f, 0.1f, 0.8f));	// Yellow
						break;
						
					default:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.0f, 0.0f, 1.0f));
						break;
				}

				if (gridSize > 1.0f) {
					CGContextFillEllipseInRect(context, CGRectMake(x * gridSize, y * gridSize, gridSize, gridSize));
				}
				else {
					CGContextFillRect(context, CGRectMake(x * gridSize, y * gridSize, gridSize, gridSize));
				}
			}
		}
	}
}


- (void)initializeCells:(NSUInteger)size
{
	NSUInteger height = (NSUInteger)((self.frame.size.height / self.frame.size.width) * size);
	
	MMAMap aMap;
	
	map = aMap;
	
	MMAMapInitialize(&map, MMASizeMake(size, height));
	
	map.rule = MMARuleRuleSet;
	map.range = 4;
	[self randomizeAsDefault];
	
/*	
	[self clearCells];
	
	int xMax = map.size.width;
	int yMax = map.size.height;
	
	for (int x = 0; x < xMax; x++) {
		for (int y = 0; y < yMax; y++) {
			map.currentCells[x + y * xMax] = 0;
			if (y >= yMax / 2) {
				map.currentCells[x + y * xMax] = 1;
			}
		}
	}
	
	int centerPosition = xMax / 2 + ((yMax / 2) - 1) * xMax;
	map.currentCells[centerPosition - 1] = 2;
	map.currentCells[centerPosition + 0] = 2;
	map.currentCells[centerPosition + 1] = 2;
	*/
	[self setNeedsDisplay:YES];
}


#pragma mark - Execution
- (void)clearCells {
	clearMap(&map);
}

- (void)randomizeCells:(NSUInteger)aRate {
	[self randomizeAsDefault];
}

- (void)calculateNextPattern {
//	countSubstances(&map);
	stepMap(&map);
}


#pragma mark - Behavior
- (NSString *)rule {
	return [NSString stringWithCString:ruleNameOfMap(&map) encoding:NSUTF8StringEncoding];
}

- (NSUInteger)range {
	return map.range;
}


@end
