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
	int rate[MMANumberOfSubstance] = {0,50,50,0,0,1};
	randomizeMap(&map, rate);
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

				CGContextFillEllipseInRect(context, CGRectMake(x * gridSize, y * gridSize, gridSize, gridSize));
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
	
	map.range = 1;
	[self randomizeAsDefault];
	
/*	
	map.currentCells[50 + 500] = MMANull;
	map.currentCells[51 + 500] = MMANull;
	map.currentCells[52 + 500] = MMANull;
	map.currentCells[53 + 500] = MMANull;
	map.currentCells[54 + 500] = MMANull;
	map.currentCells[55 + 500] = MMANull;
	map.currentCells[56 + 500] = MMANull;
	map.currentCells[50 + 600] = MMANull;
	map.currentCells[51 + 600] = MMANull;
	map.currentCells[52 + 600] = MMANull;
	map.currentCells[53 + 600] = MMANull;
	map.currentCells[54 + 600] = MMANull;
	map.currentCells[55 + 600] = MMANull;
	map.currentCells[56 + 600] = MMANull;
	map.currentCells[50 + 700] = MMANull;
	map.currentCells[51 + 700] = MMANull;
	map.currentCells[52 + 700] = MMANull;
	map.currentCells[53 + 700] = MMANull;
	map.currentCells[54 + 700] = MMANull;
	map.currentCells[55 + 700] = MMANull;
	map.currentCells[56 + 700] = MMANull;
	map.currentCells[50 + 800] = MMANull;
	map.currentCells[51 + 503] = MMANull;
	map.currentCells[52 + 503] = MMANull;
	map.currentCells[53 + 503] = MMANull;
	map.currentCells[54 + 503] = MMANull;
	map.currentCells[55 + 503] = MMANull;
	map.currentCells[56 + 503] = MMANull;
	map.currentCells[50 + 900] = MMANull;
	map.currentCells[51 + 900] = MMANull;
	map.currentCells[52 + 900] = MMANull;
	map.currentCells[53 + 900] = MMANull;
	map.currentCells[54 + 900] = MMANull;
	map.currentCells[55 + 900] = MMANull;
	map.currentCells[56 + 900] = MMANull;
	map.currentCells[50 + 1000] = MMANull;
	map.currentCells[51 + 1000] = MMANull;
	map.currentCells[52 + 1000] = MMANull;
	map.currentCells[53 + 1000] = MMANull;
	map.currentCells[54 + 1000] = MMANull;
	map.currentCells[55 + 1000] = MMANull;
	map.currentCells[56 + 1000] = MMANull;
	map.currentCells[50 + 1100] = MMANull;
	map.currentCells[51 + 1100] = MMANull;
	map.currentCells[52 + 1100] = MMANull;
	map.currentCells[53 + 1100] = MMANull;
	map.currentCells[54 + 1100] = MMANull;
	map.currentCells[55 + 1100] = MMANull;
	map.currentCells[56 + 1100] = MMANull;
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
	countSubstances(&map);
	stepMap(&map);
}


#pragma mark - Behavior
- (NSString *)rule {
	return [NSString stringWithCString:ruleName() encoding:NSUTF8StringEncoding];
}

- (NSUInteger)range {
	return map.range;
}


@end
