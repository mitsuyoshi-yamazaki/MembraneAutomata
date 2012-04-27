//
//  LBLifeViewController.m
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "LBLifeViewController.h"

#import "LBLifeView.h"

#define kLBLifeViewControllerLabelPointer	@"Pointer"
#define kLBLifeViewControllerLabelRegister	@"Register"
#define kLBLifeViewControllerLabelExecution	@"Will execute"
#define kLBLifeViewControllerLabelError		@"Error"
#define kLBLifeViewControllerLabelOpcode	@"Code"

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

- (void)save
{
	[self.lifeView save];
}

- (void)export
{
	[self.lifeView export];
}

- (void)showSource
{
	[self.lifeView showSource];
}


- (void)redrawLifeView
{
	for (NSUInteger i = 0; i < kLBLifeViewControllerRefreshPerCaliculation; i++) {
		[self.lifeView calculateNextPattern];
	}
	
	self.pointerFieldCell.title = [NSString stringWithFormat:@"%@: %lu", kLBLifeViewControllerLabelPointer, self.lifeView.previousPointer];
	self.registerFieldCell.title = [NSString stringWithFormat:@"%@: %lu", kLBLifeViewControllerLabelRegister, self.lifeView.mainRegister];
	self.executionFlagFieldCell.title = [NSString stringWithFormat:@"%@: %d", kLBLifeViewControllerLabelExecution, self.lifeView.previousWillExecute];
	self.errorFlagFieldCell.title = [NSString stringWithFormat:@"%@: %d", kLBLifeViewControllerLabelError, self.lifeView.previousError];
	
	if (self.lifeView.previousWillExecute) {
		self.opcodeFieldCell.title = [NSString stringWithFormat:@"%@: %@", kLBLifeViewControllerLabelOpcode, [self.lifeView currentCode]];
	}
	else {
		self.opcodeFieldCell.title = [NSString stringWithFormat:@"%@: (%@)", kLBLifeViewControllerLabelOpcode, [self.lifeView currentCode]];
	}
	
	if (self.lifeView.previousError) {
//		NSLog(@"error");
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
	[self.lifeView initializeCells:kLBLifeViewControllerCellPerLine];
	
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
}


- (IBAction)randomizeCells:(id)sender
{
	[self.lifeView clearCells];
	[self.lifeView randomizeCells:50];
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
	
	self.pointerFieldCell.title = [NSString stringWithFormat:@"%@: %lu", kLBLifeViewControllerLabelPointer, self.lifeView.previousPointer];
	self.registerFieldCell.title = [NSString stringWithFormat:@"%@: %lu", kLBLifeViewControllerLabelRegister, self.lifeView.mainRegister];
	self.executionFlagFieldCell.title = [NSString stringWithFormat:@"%@: %d", kLBLifeViewControllerLabelExecution, self.lifeView.previousWillExecute];
	self.errorFlagFieldCell.title = [NSString stringWithFormat:@"%@: %d", kLBLifeViewControllerLabelError, self.lifeView.previousError];
	
	if (self.lifeView.previousWillExecute) {
		self.opcodeFieldCell.title = [NSString stringWithFormat:@"%@: %@", kLBLifeViewControllerLabelOpcode, [self.lifeView currentCode]];
	}
	else {
		self.opcodeFieldCell.title = [NSString stringWithFormat:@"%@: (%@)", kLBLifeViewControllerLabelOpcode, [self.lifeView currentCode]];
	}
	
	if (self.lifeView.previousError) {
		//		NSLog(@"error");
	}	
	
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
