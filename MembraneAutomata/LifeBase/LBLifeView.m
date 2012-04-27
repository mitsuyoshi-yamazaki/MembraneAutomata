//
//  LBLifeView.m
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "LBLifeView.h"

@interface LBLifeView ()

@end

@implementation LBLifeView

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
			
			switch (map.currentCells[position]) {
				case MMAWater:
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.3f, 0.3f, 1.0f, 0.8f));
					break;
					
				case MMAOil:
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 0.3f, 0.3f, 0.8f));
					break;
					
				case MMAWaterFamilier:
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.1f, 1.0f, 0.4f, 0.8f));
					break;
					
				case MMAOilFamilier:
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.8f, 0.8f, 0.1f, 0.8f));
					break;
					
				default:
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.0f, 0.0f, 1.0f));
					break;
			}
			
			CGContextFillEllipseInRect(context, CGRectMake(x * gridSize, y * gridSize, gridSize, gridSize));
		}
	}
}


- (void)initializeCells:(NSUInteger)size
{
	NSUInteger height = (NSUInteger)((self.frame.size.height / self.frame.size.width) * size);
	
	MMAMap aMap;
	
	map = aMap;
	MMAMapInitialize(&map, MMASizeMake(size, height));
	randomizeMap(&map, 5, 5, 2, 2);
	
	[self setNeedsDisplay:YES];
}


#pragma mark - Execution
- (void)clearCells {
	clearMap(&map);
}

- (void)randomizeCells:(NSUInteger)rate {
	randomizeMap(&map, 5, 5, 2, 2);
}

- (void)calculateNextPattern {
	step(&map);
}


@end
