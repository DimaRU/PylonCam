//
//  FrameGrabber.h
//  
//
//  Created by Dmitriy Borovikov on 03.09.2021.
//

#pragma once
#include "SwiftDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const void * _Nonnull camera;
} FrameGrabber;

typedef void (*GrabCallbackPtr)(int width, int height, unsigned char * _Nonnull ptr);

void CPylonInitialize(void);
void CPylonTerminate(void);

void * _Nonnull  CPylonCreateCamera(void) CF_SWIFT_NAME(FrameGrabber.init());
void CPylonReleaseCamera(void * _Nonnull camera) CF_SWIFT_NAME(FrameGrabber.PylonReleaseCamera(self:));
void CPylonPrintParams(void * _Nonnull camera) CF_SWIFT_NAME(FrameGrabber.PylonPrintParams(self:));
void CPylonGrabStop(void * _Nonnull camera) CF_SWIFT_NAME(FrameGrabber.PylonGrabStop(self:));
void CPylonGrabFrames(void * _Nonnull camera, int bufferCount, int timeout, GrabCallbackPtr  _Nonnull grabCallbackPtr) CF_SWIFT_NAME(FrameGrabber.CPylonGrabFrames(self:bufferCount:timeout:callBack:));
int CPylonIntParameter(void * _Nonnull camera, const char * _Nonnull name) CF_SWIFT_NAME(FrameGrabber.PylonIntParameter(self:name:));
double CPylonFloatParameter(void * _Nonnull camera, const char * _Nonnull name) CF_SWIFT_NAME(FrameGrabber.PylonFloatParameter(self:name:));
const char * _Nonnull CPylonStringParameter(void * _Nonnull camera, const char * _Nonnull name) CF_SWIFT_NAME(FrameGrabber.PylonStringParameter(self:name:));

#ifdef __cplusplus
}
#endif
