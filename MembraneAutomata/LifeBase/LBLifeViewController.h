//
//  LBLifeViewController.h
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define kLBLifeViewControllerRefreshTimeInterval	0.1f
#define kLBLifeViewControllerRefreshPerCaliculation	1

#define kLBLifeViewControllerDefaultMapSize		400

#define kLBLifeViewControllerStopAfterNSteps	1
#define kLBLifeViewControllerSteps				100

@class LBLifeView;

@interface LBLifeViewController : NSViewController {
	LBLifeView *lifeView;
	
	NSButton *startButton;
	NSTextFieldCell *pointerFieldCell;
	NSTextFieldCell *registerFieldCell;
	NSTextFieldCell *executionFlagFieldCell;
	NSTextFieldCell *errorFlagFieldCell;
	NSTextFieldCell *opcodeFieldCell;
	
	BOOL running;
	
	NSUInteger steps;
}

@property (nonatomic, retain) IBOutlet LBLifeView *lifeView;
@property (nonatomic, retain) IBOutlet NSButton *startButton;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *pointerFieldCell;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *registerFieldCell;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *executionFlagFieldCell;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *errorFlagFieldCell;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *opcodeFieldCell;

- (void)redrawLifeView;
- (void)repeat;

- (void)initializeLifeView;

- (IBAction)redraw:(id)sender;
- (IBAction)clearCells:(id)sender;
- (IBAction)randomizeCells:(id)sender;
- (IBAction)startPause:(id)sender;
- (IBAction)step:(id)sender;

@end
