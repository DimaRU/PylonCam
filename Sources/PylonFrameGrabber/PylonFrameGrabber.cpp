//
//  PylonFrameGrabber.c
//  PylonCam
//
//  Created by Dmitriy Borovikov on 30.08.2021.
//

#include <pylon/PylonIncludes.h>
#include "PylonFrameGrabber.h"
#include "FrameBufferAllocator.h"

using namespace Pylon;
using namespace GenApi;
using namespace std;

void CPylonInitialize(void) {
    PylonInitialize();
}

void CPylonTerminate(void) {
    PylonTerminate();
}

void CPylonReleaseCamera(PylonGrabber *frameGrabber) {
    delete (CInstantCamera *)frameGrabber->camera;
}

static void storeString(PylonGrabber *frameGrabber, const char *string) {
    strcpy(frameGrabber->stringBuffer, string);
    frameGrabber->errorFlag = true;
}

char * _Nonnull CPylonGetString(PylonGrabber  *frameGrabber) {
    return frameGrabber->stringBuffer;
}

PylonGrabber CPylonCreateCamera(void) {
    PylonGrabber frameGrabber;
    frameGrabber.camera = new CInstantCamera();
    frameGrabber.errorFlag = false;
    return frameGrabber;
}

void CPylonAttachDevice(PylonGrabber *frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    try
    {
        IPylonDevice* device = CTlFactory::GetInstance().CreateFirstDevice();
        std::cout << device->GetDeviceInfo().GetModelName() << std::endl;
        camera->Attach(device);
    }
    catch (const GenericException& e)
    {
        storeString(frameGrabber, e.GetDescription());
    }
}

void CPylonCameraStart(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    try
    {
        camera->Open();
    }
    catch (const GenericException& e)
    {
        storeString(frameGrabber, e.GetDescription());
    }
}

void CPylonCameraStop(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    try
    {
        camera->Close();
    }
    catch (const GenericException& e)
    {
        storeString(frameGrabber, e.GetDescription());
    }
}

void CPylonExecuteSoftwareTrigger(PylonGrabber *frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber;
    frameGrabber->errorFlag = false;
    camera->ExecuteSoftwareTrigger();
}

void CPylonDestroyDevice(PylonGrabber *frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    camera->DestroyDevice();
 }

int64_t CPylonIntParameter(PylonGrabber *frameGrabber, const char *name, GetParameterType type)
{
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    switch (type) {
        case GetParameterType::value: return CIntegerParameter( nodemap, name ).GetValue();
        case GetParameterType::min:   return CIntegerParameter( nodemap, name ).GetMin();
        case GetParameterType::max:   return CIntegerParameter( nodemap, name ).GetMax();
        case GetParameterType::step:  return CIntegerParameter( nodemap, name ).GetInc();
    }
}

void CPylonSetIntParameter(PylonGrabber *frameGrabber, const char *name, int64_t value)
{
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    CIntegerParameter( nodemap, name ).SetValue(value);
}

double CPylonFloatParameter(PylonGrabber *frameGrabber, const char *name, GetParameterType type)
{
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    switch (type) {
        case GetParameterType::value: return CFloatParameter( nodemap, name ).GetValue();
        case GetParameterType::min:   return CFloatParameter( nodemap, name ).GetMin();
        case GetParameterType::max:   return CFloatParameter( nodemap, name ).GetMax();
        case GetParameterType::step:  return CFloatParameter( nodemap, name ).GetInc();
    }
}

void CPylonSetFloatParameter(PylonGrabber *frameGrabber, const char *name, double value)
{
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    CFloatParameter( nodemap, name ).SetValue(value);
}

const char *CPylonStringParameter(PylonGrabber *frameGrabber, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    storeString(frameGrabber, CStringParameter( nodemap, name ).GetValue().c_str());
    return frameGrabber->stringBuffer;
}

void CPylonPrintParams(PylonGrabber *frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;

    try
    {
        INodeMap& nodemap = camera->GetNodeMap();

        cout << "Camera Device Information" << endl
            << "=========================" << endl;
        cout << "Vendor           : " << CStringParameter( nodemap, "DeviceVendorName" ).GetValue() << endl;
        cout << "Model            : " << CStringParameter( nodemap, "DeviceModelName" ).GetValue() << endl;
        cout << "Firmware version : " << CStringParameter( nodemap, "DeviceFirmwareVersion" ).GetValue() << endl << endl;
    }
    catch (const GenericException& e)
    {
        cerr << "CPylon Error: " << e.GetDescription() << endl;
    }
}

void CPylonGrabStop(PylonGrabber *frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    camera->StopGrabbing();
}

void CPylonGrabFrames(PylonGrabber *frameGrabber,
                      const void * _Nonnull object,
                      int bufferCount,
                      int timeout,
                      GrabCallback _Nonnull grabCallback) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;

    try
    {
        camera->MaxNumBuffer = bufferCount;
        camera->StartGrabbing( GrabStrategy_LatestImages );
        CGrabResultPtr ptrGrabResult;

        while (camera->IsGrabbing())
        {
            camera->RetrieveResult( timeout, ptrGrabResult, TimeoutHandling_ThrowException );

            if (!ptrGrabResult->GrabSucceeded())
            {
                cerr << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " " << ptrGrabResult->GetErrorDescription() << endl;
                continue;
            }

            int width = ptrGrabResult->GetWidth();
            int height = ptrGrabResult->GetHeight();
            auto pImageBuffer = ptrGrabResult->GetBuffer();

            grabCallback(object, width, height, pImageBuffer);
        }
    }
    catch (const GenericException& e)
    {
        if (!camera->IsGrabbing()) return;
        storeString(frameGrabber, e.GetDescription());
    }
}

Area CPylonGetAOI(PylonGrabber *frameGrabber) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    INodeMap& nodemap = camera->GetNodeMap();
    area.width = CIntegerParameter( nodemap, "Width" ).GetValue();
    area.height = CIntegerParameter( nodemap, "Height" ).GetValue();
    area.offsetX = CIntegerParameter( nodemap, "OffsetX" ).GetValue();
    area.offsetY = CIntegerParameter( nodemap, "OffsetY" ).GetValue();
    return area;
}

Area CPylonGetAutoAOI(PylonGrabber *frameGrabber) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    INodeMap& nodemap = camera->GetNodeMap();
    CEnumParameter(nodemap, "AutoFunctionAOISelector").SetValue("AOI1");
    area.width = CIntegerParameter( nodemap, "AutoFunctionAOIWidth" ).GetValue();
    area.height = CIntegerParameter( nodemap, "AutoFunctionAOIHeight" ).GetValue();
    area.offsetX = CIntegerParameter( nodemap, "AutoFunctionAOIOffsetX" ).GetValue();
    area.offsetY = CIntegerParameter( nodemap, "AutoFunctionAOIOffsetY" ).GetValue();
    return area;
}

void CPylonSetAOI(PylonGrabber *frameGrabber, Area area) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;

    try {
        INodeMap& nodemap = camera->GetNodeMap();
        CIntegerParameter( nodemap, "Width" ).SetValue(area.width);
        CIntegerParameter( nodemap, "Height" ).SetValue(area.height);
        CIntegerParameter( nodemap, "OffsetX" ).SetValue(area.offsetX);
        CIntegerParameter( nodemap, "OffsetY" ).SetValue(area.offsetY);
    } catch (const GenericException& e)
    {
        storeString(frameGrabber, e.GetDescription());
    }
}

void CPylonSetAutoAOI(PylonGrabber *frameGrabber, Area area) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;

    try {
        INodeMap& nodemap = camera->GetNodeMap();
        CEnumParameter(nodemap, "AutoFunctionAOISelector").SetValue("AOI1");
        CIntegerParameter( nodemap, "AutoFunctionAOIWidth" ).SetValue(area.width);
        CIntegerParameter( nodemap, "AutoFunctionAOIHeight" ).SetValue(area.height);
        CIntegerParameter( nodemap, "AutoFunctionAOIOffsetX" ).SetValue(area.offsetX);
        CIntegerParameter( nodemap, "AutoFunctionAOIOffsetY" ).SetValue(area.offsetY);
    } catch (const GenericException& e)
    {
        storeString(frameGrabber, e.GetDescription());
    }
}

Area CPylonGetMaxArea(PylonGrabber *frameGrabber) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    frameGrabber->errorFlag = false;
    INodeMap& nodemap = camera->GetNodeMap();
    area.offsetX = 0;
    area.offsetY = 0;
    area.width = CIntegerParameter( nodemap, "WidthMax" ).GetValue();
    area.height = CIntegerParameter( nodemap, "HeightMax" ).GetValue();
    return area;
}

bool CPylonIsPylonDeviceAttached(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    return camera->IsPylonDeviceAttached();
}

bool CPylonIsCameraDeviceRemoved(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    return camera->IsCameraDeviceRemoved();
}

bool CPylonHasOwnership(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    return camera->HasOwnership();
}

bool CPylonIsOpen(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    return camera->IsOpen();
}

bool CPylonIsGrabbing(PylonGrabber  * _Nonnull frameGrabber) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    return camera->IsGrabbing();
}

void CPylonSetBufferAllocator(PylonGrabber * _Nonnull frameGrabber, void * frameBuffer, size_t frameBufferSize) {
    CInstantCamera *camera = (CInstantCamera *)frameGrabber->camera;
    FrameBufferAllocator * allocator = new FrameBufferAllocator(frameBuffer, frameBufferSize);
    camera->SetBufferFactory(allocator);
}
