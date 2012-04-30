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
	int rate[7] = {10000,8800,0,100,10,0,20};	// Rule Rule Set用
	int count = 7;
	
	if (selecting) {
		randomizeRange(&map, MMARangeFromPoints(clickedPoint, draggedPoint), rate, count);
	}
	else {
		randomizeMap(&map, rate, 7);
		frameWith(&map, 0, map.size.width * 0.01);		
	}
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
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 0.5f, 0.3f, 0.8f));	// Red
						break;
						
					case MMAWaterFamilier:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.1f, 1.0f, 0.4f, 0.8f));	// Green
						break;
						
					case MMAOilFamilier:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 0.1f, 0.8f, 0.8f));	// Purple
						break;
						
					case 5:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.2f, 0.2f, 0.4f, 0.8f));
						break;
						
					case 6:
						CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.8f, 1.0f, 0.8f));
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
	
	if (dragging) {
		
		MMAPoint patternFrom = clickedPoint;
		MMAPoint patternTo = draggedPoint;
		
		if (clickedPoint.x > draggedPoint.x) {
			patternFrom.x = draggedPoint.x;
			patternTo.x = clickedPoint.x;
		}
		if (clickedPoint.y > draggedPoint.y) {
			patternFrom.y = draggedPoint.y;
			patternTo.y = clickedPoint.y;
		}

		MMASize size = MMASizeMake(patternTo.x - patternFrom.x, patternTo.y - patternFrom.y);
		
		CGContextSetLineWidth(context, 0.2f);
		CGContextSetStrokeColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.0f, 0.0f, 0.8f));
		
		CGContextStrokeRect(context, CGRectMake(patternFrom.x * gridSize, patternFrom.y * gridSize, size.width * gridSize, size.height * gridSize));
	}
}


- (void)initializeCells:(NSUInteger)size
{
	dragging = NO;
	selecting = NO;
	
	NSUInteger height = (NSUInteger)((self.frame.size.height / self.frame.size.width) * size);
	
	clickedPoint = MMAPointMake(0, 0);
	draggedPoint = MMAPointMake(0, 0);
	MMAMap aMap;
	
	map = aMap;
	
	MMAMapInitialize(&map, MMASizeMake(size, height));
	
	map.rule = MMARuleRuleSet;
	map.range = 3;
	[self randomizeAsDefault];
	
//	fillMapWith(&map, 1);
//	frameWith(&map, 0, map.size.width * 0.1);
//	map.currentCells[(int)(map.size.width * 0.1) + (int)(map.size.height * 0.5) * map.size.width] = 4;
//	map.currentCells[(int)(map.size.width * 0.9) + (int)(map.size.height * 0.5) * map.size.width] = 6;
	
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
	if (selecting) {
		clearRange(&map, MMARangeFromPoints(clickedPoint, draggedPoint));
	}
	else {
		clearMap(&map);
	}
}

- (void)randomizeCells:(NSUInteger)aRate {
	[self randomizeAsDefault];
}

- (void)calculateNextPattern {
//	countSubstances(&map);
	selecting = NO;
	stepMap(&map);
}


#pragma mark - Behavior
- (NSString *)rule {
	return [NSString stringWithCString:ruleNameOfMap(&map) encoding:NSUTF8StringEncoding];
}

- (NSUInteger)range {
	return map.range;
}

- (void)print {
	printMap(&(map));
}


#pragma mark - NSControl

- (void)mouseDown:(NSEvent *)theEvent
{
	NSPoint locationInWindow = [theEvent locationInWindow];
    NSPoint location = [self convertPoint:locationInWindow fromView:nil];
	
//	NSLog(@"clicked point : (%f,%f)", location.x, location.y);
	
	NSUInteger width = map.size.width;	
	CGFloat gridSize = self.bounds.size.width / width;	

	clickedPoint = MMAPointMake(location.x / gridSize, location.y / gridSize);
	
	dragging = YES;
}

- (void)mouseDragged:(NSEvent *)theEvent {
	
	NSPoint locationInWindow = [theEvent locationInWindow];
    NSPoint location = [self convertPoint:locationInWindow fromView:nil];
		
	NSUInteger width = map.size.width;	
	CGFloat gridSize = self.bounds.size.width / width;	
	
	draggedPoint = MMAPointMake(location.x / gridSize, location.y / gridSize);

	[self setNeedsDisplay:YES];
}

- (void)mouseUp:(NSEvent *)theEvent {
	
	dragging = NO;
	selecting = YES;
	
	NSPoint locationInWindow = [theEvent locationInWindow];
    NSPoint location = [self convertPoint:locationInWindow fromView:nil];
	
//	NSLog(@"unclicked point : (%f,%f)", location.x, location.y);
	
	NSUInteger width = map.size.width;	
	CGFloat gridSize = self.bounds.size.width / width;	
	
	draggedPoint = MMAPointMake(location.x / gridSize, location.y / gridSize);
	
	MMAPattern pattern;
	patternIn(&map, &pattern, clickedPoint, draggedPoint);
	
	/*
	printf("\nPattern is ...\n");
	
	for (int y = 0; y < pattern.size.height; y++) {
		for (int x = 0; x < pattern.size.width; x++) {
			printf("%01d ", pattern.cells[x + y * pattern.size.width]);
		}
		printf("\n");
	}*/
}

@end
