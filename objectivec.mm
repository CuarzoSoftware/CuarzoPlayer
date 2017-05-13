#include "objectivec.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <CoreData/CoreData.h>
#import <Foundation/NSUserNotification.h>
#import <Foundation/NSString.h>
#include <QDebug>



void ObjectiveC::Display(PlayerWindow *app)
{
    NSView* parentNSView = reinterpret_cast<NSView*>(app->winId());
    NSWindow *mainWindow = [parentNSView window];
    mainWindow.titlebarAppearsTransparent = true;
    mainWindow.backgroundColor =  NSColor.whiteColor;

    /*
    NSUserNotification* userNotification = [[[NSUserNotification alloc] init] autorelease];
    userNotification.title = @"Cancion Actual";
    userNotification.informativeText = @"Strawberry Fields Forever";
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:userNotification];
    */


}


