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
@synthesize rangeField;
@synthesize ruleField;
@synthesize stepField;
@synthesize idField;


#pragma mark - behavior

- (void)redrawLifeView
{
	for (NSUInteger i = 0; i < kLBLifeViewControllerRefreshPerCaliculation; i++) {
		[self.lifeView calculateNextPattern];
	}
	
	self.stepField.title = [NSString stringWithFormat:@"Steps: %d", self.lifeView.steps];
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

	self.rangeField.title = [NSString stringWithFormat:@"Range: %d", self.lifeView.range];
	self.ruleField.title = [NSString stringWithFormat:@"Rule: %@", self.lifeView.rule];
	self.stepField.title = [NSString stringWithFormat:@"Steps: %d", self.lifeView.steps];
	self.idField.title = [NSString stringWithFormat:@"Map ID: %d", self.lifeView.mapId];
	
	self.running = NO;
	
	if (self.isRunning) {
		self.startButton.title = @"Pause";
	}
	else {
		self.startButton.title = @"Start";
	}
	
	
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
		
	[self.lifeView clearCells];
	self.idField.title = [NSString stringWithFormat:@"Map ID: %d", self.lifeView.mapId];
	[self redraw:self];
}


- (IBAction)randomizeCells:(id)sender
{
	[self.lifeView clearCells];
	[self.lifeView randomizeCells:50];
	
	self.idField.title = [NSString stringWithFormat:@"Map ID: %d", self.lifeView.mapId];
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
	self.stepField.title = [NSString stringWithFormat:@"Steps: %d", self.lifeView.steps];
	
	[self.lifeView setNeedsDisplay:YES];
}

- (IBAction)print:(id)sender {
	[self.lifeView print];
}

- (IBAction)store:(id)sender {
	[self.lifeView storeMap];
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
	
	self.rangeField = nil;
	self.ruleField = nil;
	self.stepField = nil;
	self.idField = nil;
	
    [super dealloc];
}

@end
