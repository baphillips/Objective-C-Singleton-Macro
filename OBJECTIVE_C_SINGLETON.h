//
//  OBJECTIVE_C_SINGLETON.h
//
//  Created by Brandon Phillips on 5/16/12.
//  Copyright (c) 2012 Brandon Phillips. All rights reserved.
//

#ifndef LexDK_OBJECTIVE_C_SINGLETON_h
#define LexDK_OBJECTIVE_C_SINGLETON_h

/// This macro implements the various methods needed to make a safe singleton.
/// Sample usage:
/// OBJECTIVE_C_SINGLETON_(SomeUsefulManager, sharedSomeUsefulManager)
/// (with no trailing semicolon)
#if __has_feature(objc_arc)

#define OBJECTIVE_C_SINGLETON(_object_name_, _shared_obj_name_)                         \
																						\
+ (_object_name_ *) _shared_obj_name_                                                   \
{                                                                                       \
	static _object_name_ *z##_shared_obj_name_;											\
																						\
	static dispatch_once_t done;														\
																						\
	dispatch_once(&done, ^{z##_shared_obj_name_ = [_object_name_ new]; });				\
																						\
	return z##_shared_obj_name_;                                                        \
}																						\


#else

#define OBJECTIVE_C_SINGLETON(_object_name_, _shared_obj_name_)                         \
																						\
static _object_name_ *z##_shared_obj_name_ = nil;                                       \
																						\
+ (_object_name_ *) _shared_obj_name_                                                   \
{                                                                                       \
	if (z##_shared_obj_name_ == nil) {                                                  \
		z##_shared_obj_name_ = [NSAllocateObject([self class], 0, NULL) init];			\
	}                                                                                   \
																						\
	return z##_shared_obj_name_;                                                        \
}                                                                                       \
																						\
+ (id) allocWithZone:(NSZone *)zone                                                     \
{                                                                                       \
	return [[self _shared_obj_name_] retain];											\
}                                                                                       \
																						\
- (id) copyWithZone:(NSZone *)zone                                                      \
{                                                                                       \
return self;																			\
}                                                                                       \
																						\
- (id) retain                                                                           \
{                                                                                       \
	return self;                                                                        \
}                                                                                       \
																						\
- (NSUInteger) retainCount                                                              \
{                                                                                       \
	return NSUIntegerMax;  /* so the singleton object cannot be released */             \
}                                                                                       \
																						\
- (oneway void) release                                                                 \
{                                                                                       \
																						\
}                                                                                       \
																						\
- (id) autorelease                                                                      \
{                                                                                       \
	return self;                                                                        \
}                                                                                       \


#endif


#endif
