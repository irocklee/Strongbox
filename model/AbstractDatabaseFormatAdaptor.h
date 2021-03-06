//
//  AbstractPasswordDatabase.h
//  Strongbox
//
//  Created by Mark on 07/11/2017.
//  Copyright © 2017 Mark McGuill. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Node.h"
#import "DatabaseAttachment.h"
#import "StrongboxDatabase.h"
#import "CompositeKeyFactors.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^OpenCompletionBlock)(BOOL userCancelled, StrongboxDatabase*_Nullable database, NSError*_Nullable error);
typedef void (^SaveCompletionBlock)(BOOL userCancelled, NSData*_Nullable data, NSString*_Nullable debugXml, NSError*_Nullable error);

@protocol AbstractDatabaseFormatAdaptor <NSObject>

+ (BOOL)isValidDatabase:(nullable NSData *)prefix error:(NSError**)error;

+ (NSString *)fileExtension;

- (StrongboxDatabase*)create:(CompositeKeyFactors*)ckf;

- (void)read:(NSInputStream*)stream
         ckf:(CompositeKeyFactors*)ckf
  completion:(OpenCompletionBlock)completion;

- (void)read:(NSInputStream*)stream
         ckf:(CompositeKeyFactors*)ckf
xmlDumpStream:(NSOutputStream*_Nullable)xmlDumpStream
sanityCheckInnerStream:(BOOL)sanityCheckInnerStream
  completion:(OpenCompletionBlock)completion;

- (void)save:(StrongboxDatabase*)database completion:(SaveCompletionBlock)completion;

@property (nonatomic, readonly) DatabaseFormat format;
@property (nonatomic, readonly) NSString* fileExtension;

@end

NS_ASSUME_NONNULL_END
