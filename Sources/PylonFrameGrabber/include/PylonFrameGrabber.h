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
#include <unistd.h>

#pragma clang assume_nonnull begin

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int64_t offsetX;
    int64_t offsetY;
    int64_t width;
    int64_t height;
} Area;

typedef struct _PylonGrabber {
    const void * _Nonnull camera;
    bool errorFlag;
    char stringBuffer[256];
} PylonGrabber;

typedef NS_CLOSED_ENUM(int, GetParameterType) {
    value,
    min,
    max,
    step
};

typedef NS_CLOSED_ENUM(int, PylonCameraEvent) {
    cameraAttach,
    cameraAttached,
    cameraOpen,
    cameraOpened,
    cameraGrabStart,
    cameraGrabStarted,
    cameraGrabStop,
    cameraGrabStopped,
    cameraClose,
    cameraClosed,
    cameraDestroy,
    cameraDestroyed,
    cameraDetach,
    cameraDetached,
    cameraGrabError,
    cameraDeviceRemoved
};

typedef void (*GrabCallback)(const void *object, int width, int height, void * _Nullable frame, int context);
typedef void (*EventCallback)(const void *object, PylonCameraEvent event, const char * _Nullable errorMessage);

void CPylonInitialize(void) CF_SWIFT_NAME(PylonInitialize());
void CPylonTerminate(void) CF_SWIFT_NAME(PylonTerminate());

PylonGrabber CPylonCreateCamera(void) CF_SWIFT_NAME(PylonGrabber.init());
void CPylonAttachDevice(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.attachDevice(self:));
char * _Nonnull CPylonGetString(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(getter:PylonGrabber.getString(self:));
void CPylonExecuteSoftwareTrigger(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.executeSoftwareTrigger(self:));
void CPylonDestroyDevice(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.destroyDevice(self:));
void CPylonReleaseCamera(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.releaseCamera(self:));
void CPylonPrintParams(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.printParams(self:));
void CPylonGrabStop(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.grabStop(self:));
void CPylonCameraStart(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.cameraStart(self:));
void CPylonCameraStop(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.cameraStop(self:));
void CPylonGrabFrames(PylonGrabber * _Nonnull frameGrabber,
                      const void * _Nonnull object,
                      int timeout,
                      GrabCallback _Nonnull grabCallback) CF_SWIFT_NAME(PylonGrabber.grabFrames(self:object:timeout:callBack:));
int64_t CPylonIntParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, GetParameterType type) CF_SWIFT_NAME(PylonGrabber.intParameter(self:name:type:));
void CPylonSetIntParameter(PylonGrabber *frameGrabber, const char *name, int64_t value) CF_SWIFT_NAME(PylonGrabber.setIntParameter(self:name:value:));
double CPylonFloatParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, GetParameterType type) CF_SWIFT_NAME(PylonGrabber.floatParameter(self:name:type:));
void CPylonSetFloatParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, double value) CF_SWIFT_NAME(PylonGrabber.setFloatParameter(self:name:value:));
const char * _Nonnull CPylonStringParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.stringParameter(self:name:));
void CPylonSetStringParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, const char * _Nonnull value) CF_SWIFT_NAME(PylonGrabber.setStringParameter(self:name:value:));
const char * _Nonnull CPylonEnumParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.enumParameter(self:name:));
void CPylonSetEnumParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, const char * _Nonnull value) CF_SWIFT_NAME(PylonGrabber.setEnumParameter(self:name:value:));
bool CPylonBoolParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name) CF_SWIFT_NAME(PylonGrabber.boolParameter(self:name:));
void CPylonSetBoolParameter(PylonGrabber * _Nonnull frameGrabber, const char * _Nonnull name, bool value) CF_SWIFT_NAME(PylonGrabber.setBoolParameter(self:name:value:));

Area CPylonGetAOI(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getAOI(self:));
Area CPylonGetAutoAOI(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getAutoAOI(self:));
void CPylonSetAOI(PylonGrabber * _Nonnull frameGrabber, Area area) CF_SWIFT_NAME(PylonGrabber.setAOI(self:area:));
void CPylonSetAutoAOI(PylonGrabber * _Nonnull frameGrabber, Area area) CF_SWIFT_NAME(PylonGrabber.setAutoAOI(self:area:));
Area CPylonGetMaxArea(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.getMaxArea(self:));
bool CPylonIsPylonDeviceAttached(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.isPylonDeviceAttached(self:));
bool CPylonIsCameraDeviceRemoved(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.isCameraDeviceRemoved(self:));
bool CPylonHasOwnership(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.hasOwnership(self:));
bool CPylonIsOpen(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.isOpen(self:));
bool CPylonIsGrabbing(PylonGrabber * _Nonnull frameGrabber) CF_SWIFT_NAME(PylonGrabber.isGrabbing(self:));
void CPylonSetBufferAllocator(PylonGrabber * _Nonnull frameGrabber,
                              void * frameBuffer,
                              size_t frameBufferSize,
                              int bufferCount) CF_SWIFT_NAME(PylonGrabber.setBufferAllocator(self:frameBuffer:frameBufferSize:bufferCount:));
void CPylonSetSoftwareTrigger(PylonGrabber *frameGrabber,
                              const void * _Nonnull object,
                              GrabCallback _Nonnull grabCallback) CF_SWIFT_NAME(PylonGrabber.setSoftwareTrigger(self:object:callBack:));
bool CPylonWaitForFrameTriggerReady(PylonGrabber *frameGrabber, int timeout) CF_SWIFT_NAME(PylonGrabber.waitForFrameTriggerReady(self:timeout:));
void CPylonSetEventCallback(PylonGrabber * _Nonnull frameGrabber,
                            const void * _Nonnull object,
                            EventCallback _Nullable eventCallback) CF_SWIFT_NAME(PylonGrabber.setEventCallback(self:object:callBack:));

#ifdef __cplusplus
}
#endif
#pragma clang assume_nonnull end
