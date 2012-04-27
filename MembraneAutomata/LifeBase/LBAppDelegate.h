//
//  LBAppDelegate.h
//  AL001
//
//  Created by Mitsuyoshi Yamazaki on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class LBLifeViewController;

@interface LBAppDelegate : NSObject <NSApplicationDelegate> {
	NSWindow *window;
	
	LBLifeViewController *_lifeViewController;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)save:(id)sender;
- (IBAction)export:(id)sender;
- (IBAction)showSource:(id)sender;

@end
