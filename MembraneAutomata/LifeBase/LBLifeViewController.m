//
//  LBLifeViewController.m
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "LBLifeViewController.h"

#import "LBLifeView.h"

@interface LBLifeViewController ()

@property (nonatomic, getter = isRunning) BOOL running;

@end



@implementation LBLifeViewController

@synthesize lifeView;
@synthesize startButton;
@synthesize running;
@synthesize pointerFieldCell;
@synthesize registerFieldCell;
@synthesize executionFlagFieldCell;
@synthesize errorFlagFieldCell;
@synthesize opcodeFieldCell;


#pragma mark - behavior

- (void)redrawLifeView
{
	for (NSUInteger i = 0; i < kLBLifeViewControllerRefreshPerCaliculation; i++) {
		[self.lifeView calculateNextPattern];
		steps++;
		
		if (kLBLifeViewControllerStopAfterNSteps && steps > kLBLifeViewControllerSteps) {
			self.running = NO;
			[self.lifeView setNeedsDisplay:YES];
			break;
		}
	}
	
	[self.lifeView setNeedsDisplay:YES];
}


- (void)repeat
{	
	if (!self.isRunning) {
		return;
	}
	
	[self redrawLifeView];
	
	[self performSelector:@selector(repeat) withObject:nil afterDelay:kLBLifeViewControllerRefreshTimeInterval];
}


- (void)initializeLifeView
{
	[self.lifeView initializeCells:kLBLifeViewControllerDefaultMapSize];
	
	self.running = NO;
	
	if (self.isRunning) {
		self.startButton.title = @"Pause";
	}
	else {
		self.startButton.title = @"Start";
	}
	
	steps = 0;
	
	//	[self repeat];
	//	[self performSelector:@selector(repeat) withObject:nil afterDelay:2.0f];
}



#pragma IBAction

- (IBAction)redraw:(id)sender
{
	[self.lifeView setNeedsDisplay:YES];
}


- (IBAction)clearCells:(id)sender
{
	if (self.isRunning) {
		self.running = NO;
		self.startButton.title = @"Start";
	}
	
	steps = 0;
	
	[self.lifeView clearCells];
	[self redraw:self];
}


- (IBAction)randomizeCells:(id)sender
{
	[self.lifeView clearCells];
	[self.lifeView randomizeCells:50];
	
	steps = 0;

	[self redraw:self];
}


- (IBAction)startPause:(id)sender
{	
	if (self.isRunning) {
		self.running = NO;
		self.startButton.title = @"Start";
	}
	else {
		self.running = YES;
		self.startButton.title = @"Pause";
		[self repeat];
	}
}


- (IBAction)step:(id)sender
{
	if (self.isRunning) {
		self.running = NO;
		self.startButton.title = @"Start";
	}
	
	[self.lifeView calculateNextPattern];
	
	
	[self.lifeView setNeedsDisplay:YES];
}



#pragma mark - Lifecycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc 
{
	self.lifeView = nil;
	self.startButton = nil;
    self.pointerFieldCell = nil;
	self.registerFieldCell = nil;
	self.executionFlagFieldCell = nil;
	self.errorFlagFieldCell = nil;
	self.opcodeFieldCell = nil;
	
    [super dealloc];
}

@end
