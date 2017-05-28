#include "objectivec.h"
#include <QObject>
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <CoreData/CoreData.h>
#import <Foundation/NSUserNotification.h>
#import <Foundation/NSString.h>
#include <QDebug>
#include <QToolButton>



void ObjectiveC::Display(WId id)
{
    NSView* parentNSView = reinterpret_cast<NSView*>(id);
    NSWindow *mainWindow = [parentNSView window];
    mainWindow.titlebarAppearsTransparent = true;
    mainWindow.backgroundColor =  NSColor.whiteColor;




    /*
    NSButton *closeButton = [mainWindow standardWindowButton:NSWindowCloseButton];
    [closeButton setHidden:YES];
    NSUserNotification* userNotification = [[[NSUserNotification alloc] init] autorelease];
    userNotification.title = @"Cancion Actual";
    userNotification.informativeText = @"Strawberry Fields Forever";
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];
    */


}


void ObjectiveC::HideWindow()
{
    [NSApp hide:nil];
}


