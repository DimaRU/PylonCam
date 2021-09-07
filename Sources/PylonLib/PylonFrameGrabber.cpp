//
//  PylonFrameGrabber.c
//  PylonCam
//
//  Created by Dmitriy Borovikov on 30.08.2021.
//

#include <pylon/PylonIncludes.h>
#include "PylonLib.h"

using namespace Pylon;
using namespace GenApi;
using namespace std;

void CPylonInitialize(void) {
    PylonInitialize();
}

void CPylonTerminate(void) {
    PylonTerminate();
}

void CPylonReleaseCamera(const void *camera) {
    delete (CInstantCamera *)camera;
}

const void * CPylonCreateCamera(void) {
    auto camera = new CInstantCamera();
    return camera;
}

bool CPylonAttachDevice(const void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    try
    {
        IPylonDevice* device = CTlFactory::GetInstance().CreateFirstDevice();
        camera->Attach(device);
        return true;
    }
    catch (const GenericException& e)
    {
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
        return false;
    }
}

void CPylonExecuteSoftwareTrigger(const void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->ExecuteSoftwareTrigger();
}

void CPylonDestroyDevice(const void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->DestroyDevice();
 }



int64_t CPylonIntParameter(const void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    int64_t value = CIntegerParameter( nodemap, name ).GetValue();
    camera->Close();
    return value;
}

double CPylonFloatParameter(const void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    double value = CFloatParameter( nodemap, name ).GetValue();
    camera->Close();
    return value;
}

const char *CPylonStringParameter(const void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    auto value = CStringParameter( nodemap, name ).GetValue().c_str();
    camera->Close();
    return value;
}

void CPylonPrintParams(const void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    try
    {
        INodeMap& nodemap = camera->GetNodeMap();
        camera->Open();

        cout << "Camera Device Information" << endl
            << "=========================" << endl;
        cout << "Vendor           : " << CStringParameter( nodemap, "DeviceVendorName" ).GetValue() << endl;
        cout << "Model            : " << CStringParameter( nodemap, "DeviceModelName" ).GetValue() << endl;
        cout << "Firmware version : " << CStringParameter( nodemap, "DeviceFirmwareVersion" ).GetValue() << endl << endl;
        camera->Close();
    }
    catch (const GenericException& e)
    {
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
    }
}

void CPylonGrabStop(const void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->StopGrabbing();
}

void CPylonGrabFrames(const void * _Nonnull cameraPtr,
                      const void * _Nonnull object,
                      int bufferCount,
                      int timeout,
                      GrabCallback _Nonnull grabCallback) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
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
        cerr << "An exception occurred." << endl
            << e.GetDescription() << endl;
    }
}

Area CPylonGetAOI(const void * cameraPtr) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->Open();
    INodeMap& nodemap = camera->GetNodeMap();
    area.width = CIntegerParameter( nodemap, "Width" ).GetValue();
    area.height = CIntegerParameter( nodemap, "Height" ).GetValue();
    area.offsetX = CIntegerParameter( nodemap, "OffsetX" ).GetValue();
    area.offsetY = CIntegerParameter( nodemap, "OffsetY" ).GetValue();
    camera->Close();
    return area;
}

Area CPylonGetAutoAOI(const void * cameraPtr) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->Open();
    INodeMap& nodemap = camera->GetNodeMap();
    CEnumParameter(nodemap, "AutoFunctionAOISelector").SetValue("AOI1");
    area.width = CIntegerParameter( nodemap, "AutoFunctionAOIWidth" ).GetValue();
    area.height = CIntegerParameter( nodemap, "AutoFunctionAOIHeight" ).GetValue();
    area.offsetX = CIntegerParameter( nodemap, "AutoFunctionAOIOffsetX" ).GetValue();
    area.offsetY = CIntegerParameter( nodemap, "AutoFunctionAOIOffsetY" ).GetValue();
    camera->Close();
    return area;
}

void CPylonSetAOI(const void * cameraPtr, Area area) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    try {
        camera->Open();
        INodeMap& nodemap = camera->GetNodeMap();
        CIntegerParameter( nodemap, "Width" ).SetValue(area.width);
        CIntegerParameter( nodemap, "Height" ).SetValue(area.height);
        CIntegerParameter( nodemap, "OffsetX" ).SetValue(area.offsetX);
        CIntegerParameter( nodemap, "OffsetY" ).SetValue(area.offsetY);
    } catch (const GenericException& e)
    {
        cerr << "CPylon Error: " << e.GetDescription() << endl;
    }
    camera->Close();
}

void CPylonSetAutoAOI(const void * cameraPtr, Area area) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    try {
        camera->Open();
        INodeMap& nodemap = camera->GetNodeMap();
        CEnumParameter(nodemap, "AutoFunctionAOISelector").SetValue("AOI1");
        CIntegerParameter( nodemap, "AutoFunctionAOIWidth" ).SetValue(area.width);
        CIntegerParameter( nodemap, "AutoFunctionAOIHeight" ).SetValue(area.height);
        CIntegerParameter( nodemap, "AutoFunctionAOIOffsetX" ).SetValue(area.offsetX);
        CIntegerParameter( nodemap, "AutoFunctionAOIOffsetY" ).SetValue(area.offsetY);
    } catch (const GenericException& e)
    {
        cerr << "CPylon Error: " << e.GetDescription() << endl;
    }
    camera->Close();
}

Area CPylonGetMaxArea(const void * cameraPtr) {
    Area area;
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->Open();
    INodeMap& nodemap = camera->GetNodeMap();
    area.offsetX = 0;
    area.offsetY = 0;
    area.width = CIntegerParameter( nodemap, "WidthMax" ).GetValue();
    area.height = CIntegerParameter( nodemap, "HeightMax" ).GetValue();
    camera->Close();
    return area;
}
