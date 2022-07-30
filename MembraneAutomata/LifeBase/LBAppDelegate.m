//
//  LBAppDelegate.m
//  AL001
//
//  Created by Mitsuyoshi Yamazaki on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "LBAppDelegate.h"
#import "LBLifeViewController.h"

@interface LBAppDelegate ()

@property (nonatomic, readonly) LBLifeViewController *lifeViewController;

@end


@implementation LBAppDelegate

@synthesize window;
@synthesize lifeViewController = _lifeViewController;

#pragma mark - Behavior

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	_lifeViewController = [[LBLifeViewController alloc] initWithNibName:@"LBLifeViewController" bundle:nil];
	
	[self.window setContentView:self.lifeViewController.view];
	
	[self.lifeViewController initializeLifeView];
}


- (void)dealloc
{
	[_lifeViewController release], _lifeViewController = nil;
	
    [super dealloc];
}

@end
