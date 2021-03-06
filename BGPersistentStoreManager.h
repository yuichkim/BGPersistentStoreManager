//
//  BGPersistentStoreManager.h
//  BGPersistentStoreManager
//
//  Created by Ben Guild on 7/16/15.
//  Copyright (c) 2015-2018+ Ben Guild. All rights reserved.
//

#import <Foundation/Foundation.h>

@import CoreData;

@interface BGPersistentStoreManager : NSObject

@property (readonly, assign, nonatomic) BOOL dataStoreWasResetOrCreatedOnLoad;

+ (instancetype)sharedManager;

- (NSManagedObjectContext *)managedObjectContext;

- (void)handleSaveError:(NSError *)error;
// This method can be subclassed.

- (void)cleanUpOldObjects;
// This method can be subclassed. It's useful for cleaning up old objects on save.

- (NSError *)performBlockOnChildContext:(void (^)(NSManagedObjectContext *context,
                                                  NSString *loggingDescriptor))block
                  withLoggingDescriptor:(NSString *)loggingDescriptor;

#pragma mark - Advanced methods

- (void)performContextSaveOperationAndOptionallyCleanUpOldObjects:(BOOL)cleanUpOldObjects;
// NOTE: This is already called automatically on backgrounding/termination, but you can also call it manually.
//  Useful, for example, when completing a background operation, as the app is already in the background then.
//  Also useful for after a cache loss occurs to force re-save persisted data immediately that was restored from another source.

@end
