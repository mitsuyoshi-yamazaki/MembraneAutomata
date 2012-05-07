//
//  LBLifeViewController.h
//  LifeBase
//
//  Created by Mitsuyoshi Yamazaki on 9/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define kLBLifeViewControllerRefreshTimeInterval	0.0f
#define kLBLifeViewControllerRefreshPerCaliculation	5

#define kLBLifeViewControllerDefaultMapSize		400

#define kLBLifeViewControllerStopAfterNSteps	0
#define kLBLifeViewControllerSteps				100

@class LBLifeView;

@interface LBLifeViewController : NSViewController {
	LBLifeView *lifeView;
	
	NSButton *startButton;
	NSTextFieldCell *rangeField;
	NSTextFieldCell *ruleField;
	NSTextFieldCell *stepField;
	NSTextFieldCell *idField;
	
	BOOL running;
	
	NSUInteger steps;
}

@property (nonatomic, retain) IBOutlet LBLifeView *lifeView;
@property (nonatomic, retain) IBOutlet NSButton *startButton;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *rangeField;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *ruleField;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *stepField;
@property (nonatomic, retain) IBOutlet NSTextFieldCell *idField;

- (void)redrawLifeView;
- (void)repeat;

- (void)initializeLifeView;

- (IBAction)redraw:(id)sender;
- (IBAction)clearCells:(id)sender;
- (IBAction)randomizeCells:(id)sender;
- (IBAction)startPause:(id)sender;
- (IBAction)step:(id)sender;
- (IBAction)print:(id)sender;

@end
