//
//  PylonFrameGrabber.h
//  
//
//  Created by Dmitriy Borovikov on 03.09.2021.
//

#pragma once
#include "SwiftDefs.h"
#include <stdbool.h>
#include <stdint.h>

#pragma clang assume_nonnull begin

typedef void (*GrabCallback)(const void *object, int width, int height, void * _Nonnull frame);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _area {
    int64_t offsetX;
    int64_t offsetY;
    int64_t width;
    int64_t height;
} Area;

typedef struct {
    const void * _Nonnull cameraPointer;
} PylonFrameGrabber;

void CPylonInitialize(void) CF_SWIFT_NAME(PylonInitialize());
void CPylonTerminate(void) CF_SWIFT_NAME(PylonTerminate());

const void * _Nonnull CPylonCreateCamera(void) CF_SWIFT_NAME(PylonFrameGrabber.init());
bool CPylonAttachDevice(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.AttachDevice(self:));
void CPylonExecuteSoftwareTrigger(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.ExecuteSoftwareTrigger(self:));
void CPylonDestroyDevice(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.DestroyDevice(self:));
void CPylonReleaseCamera(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.ReleaseCamera(self:));
void CPylonPrintParams(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.PrintParams(self:));
void CPylonGrabStop(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.GrabStop(self:));
void CPylonGrabFrames(const void * _Nonnull cameraPtr,
                      const void * _Nonnull object,
                      int bufferCount,
                      int timeout,
                      GrabCallback _Nonnull grabCallback) CF_SWIFT_NAME(PylonFrameGrabber.GrabFrames(self:object:bufferCount:timeout:callBack:));
int64_t CPylonIntParameter(const void * _Nonnull cameraPtr, const char * _Nonnull name) CF_SWIFT_NAME(PylonFrameGrabber.IntParameter(self:name:));
double CPylonFloatParameter(const void * _Nonnull cameraPtr, const char * _Nonnull name) CF_SWIFT_NAME(PylonFrameGrabber.FloatParameter(self:name:));
const char * _Nonnull CPylonStringParameter(const void * _Nonnull cameraPtr, const char * _Nonnull name) CF_SWIFT_NAME(PylonFrameGrabber.StringParameter(self:name:));
Area CPylonGetAOI(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.getAOI(self:));
Area CPylonGetAutoAOI(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.getAutoAOI(self:));
void CPylonSetAOI(const void * _Nonnull cameraPtr, Area area) CF_SWIFT_NAME(PylonFrameGrabber.setAOI(self:area:));
void CPylonSetAutoAOI(const void * _Nonnull cameraPtr, Area area) CF_SWIFT_NAME(PylonFrameGrabber.setAutoAOI(self:area:));
Area CPylonGetMaxArea(const void * _Nonnull cameraPtr) CF_SWIFT_NAME(PylonFrameGrabber.getMaxArea(self:));

#ifdef __cplusplus
}
#endif
#pragma clang assume_nonnull end
