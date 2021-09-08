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

typedef struct {
    int64_t offsetX;
    int64_t offsetY;
    int64_t width;
    int64_t height;
} Area;

typedef struct {
    const void * _Nonnull camera;
    bool errorFlag;
    char stringBuffer[256];
} PylonGrabber;

void CPylonInitialize(void) CF_SWIFT_NAME(PylonInitialize());
void CPylonTerminate(void) CF_SWIFT_NAME(PylonTerminate());

PylonGrabber CPylonCreateCamera(void) CF_SWIFT_NAME(PylonGrabber.init());
void CPylonAttachDevice(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.AttachDevice(self:));
char * _Nonnull CPylonGetString(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(getter:PylonGrabber.getString(self:));
void CPylonExecuteSoftwareTrigger(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.ExecuteSoftwareTrigger(self:));
void CPylonDestroyDevice(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.DestroyDevice(self:));
void CPylonReleaseCamera(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.ReleaseCamera(self:));
void CPylonPrintParams(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.PrintParams(self:));
void CPylonGrabStop(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.GrabStop(self:));
void CPylonCameraStart(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.cameraStart(self:));
void CPylonCameraStop(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.cameraStop(self:));

void CPylonGrabFrames(PylonGrabber  * _Nonnull frameGrabber,
                      const void * _Nonnull object,
                      int bufferCount,
                      int timeout,
                      GrabCallback _Nonnull grabCallback) CF_SWIFT_NAME(PylonGrabber.GrabFrames(self:object:bufferCount:timeout:callBack:));
int64_t CPylonIntParameter(PylonGrabber  * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.IntParameter(self:name:));
double CPylonFloatParameter(PylonGrabber  * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.FloatParameter(self:name:));
const char * _Nonnull CPylonStringParameter(PylonGrabber  * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.StringParameter(self:name:));
Area CPylonGetAOI(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getAOI(self:));
Area CPylonGetAutoAOI(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getAutoAOI(self:));
void CPylonSetAOI(PylonGrabber  * _Nonnull frameGrabber, Area area) CF_SWIFT_NAME(PylonGrabber.setAOI(self:area:));
void CPylonSetAutoAOI(PylonGrabber  * _Nonnull frameGrabber, Area area) CF_SWIFT_NAME(PylonGrabber.setAutoAOI(self:area:));
Area CPylonGetMaxArea(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getMaxArea(self:));

bool CPylonIsPylonDeviceAttached(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.IsPylonDeviceAttached(self:));
bool CPylonIsCameraDeviceRemoved(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.IsCameraDeviceRemoved(self:));
bool CPylonHasOwnership(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.HasOwnership(self:));
bool CPylonIsOpen(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.IsOpen(self:));
bool CPylonIsGrabbing(PylonGrabber  * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.IsGrabbing(self:));

#ifdef __cplusplus
}
#endif
#pragma clang assume_nonnull end
