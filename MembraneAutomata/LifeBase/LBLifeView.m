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
		
	CGSize gridSize = CGSizeMake(self.bounds.size.width / map.size.width,);
	CGFloat margin = kLBLifeViewCellMargin * gridSize.width;
	CGSize cellSize = CGSizeMake(gridSize.width - margin, gridSize.height - margin);
	
	height++;
	
//	NSLog(@"w : %lu, h : %lu", width, height);
//	NSLog(@"w * h : %lu, size : %lu", width * height, self.memorySize);
	
	if (width * height > self.memorySize) {
//		return;
	}


	CGContextSetStrokeColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.0f, 0.0f, 1.0f));
	
	NSUInteger position;
	
	for (NSUInteger y = 0; y < height; y++) {
		for (NSUInteger x = 0; x < width; x++) {
			position = x + y * width;
			if (position < self.memorySize) {
				if (memory[position] != 0x00) {
					//				CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1 - ((float)memory[x + y * width] / 0x1c), ((float)(memory[x + y * width] % 5) / 6), ((float)(memory[x + y * width] % 10) / 10), 1.0f));
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 1 - ((float)memory[x + y * width] / 0x1c), 1.0f, 1.0f));
				}
				else {
					CGContextSetFillColorWithColor(context, CGColorCreateGenericRGB(1.0f, 1.0f, 1.0f, 1.0f));
				}
				CGContextFillRect(context, CGRectMake(x * gridSize.width + margin, y * gridSize.height + margin, cellSize.width, cellSize.height));
				
				if (self.previousPointer == position) {
					CGContextStrokeRect(context, CGRectMake(x * gridSize.width, y * gridSize.height, gridSize.width, gridSize.height));
				}
			}
		}
	}
	
	
	CGContextSetStrokeColorWithColor(context, CGColorCreateGenericRGB(0.0f, 0.0f, 1.0f, 1.0f));
	
	for (NSString *rangeString in self.referedPointers) {
		NSRange range = NSRangeFromString(rangeString);
		
		if (range.length) {			
			NSUInteger i = range.location % width;
			NSUInteger j = range.location / width;
			
			CGContextStrokeRect(context, CGRectMake(i * gridSize.width + margin, j * gridSize.height + margin, cellSize.width * range.length, cellSize.height));
		}
	}
}


- (void)initializeCells:(NSUInteger)size
{
	NSUInteger height = (NSUInteger)((self.frame.size.height / self.frame.size.width) * size);
	
	MMAMap aMap;
	
	map = aMap;
	MMAMapInitialize(&map, MMASizeMake(size, height));
	
	[self setNeedsDisplay:YES];
}


#pragma mark - Execution
- (void)clearCells {
	
}

- (void)randomizeCells:(NSUInteger)rate {
	
}

- (void)calculateNextPattern {
	
}


@end
