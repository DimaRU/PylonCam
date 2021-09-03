//
//  FrameGrabber.c
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


void CPylonReleaseCamera(void *camera) {
    delete (CInstantCamera *)camera;
}

void *CPylonCreateCamera(void) {
    try
    {
        IPylonDevice* device = CTlFactory::GetInstance().CreateFirstDevice();
        CInstantCamera *camera = new CInstantCamera(device);
        return camera;
    }
    catch (const GenericException& e)
    {
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
        return nullptr;
    }
}

int CPylonIntParameter(void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    int value = CIntegerParameter( nodemap, name ).GetValue();
    camera->Close();
    return value;
}

double CPylonFloatParameter(void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    double value = CFloatParameter( nodemap, name ).GetValue();
    camera->Close();
    return value;
}

const char *CPylonStringParameter(void *cameraPtr, const char *name)
{
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    INodeMap& nodemap = camera->GetNodeMap();
    camera->Open();
    auto value = CStringParameter( nodemap, name ).GetValue().c_str();
    camera->Close();
    return value;
}

void CPylonPrintParams(void *cameraPtr) {
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
        // Get the integer nodes describing the AOI.
        CIntegerParameter offsetX( nodemap, "OffsetX" );
        CIntegerParameter offsetY( nodemap, "OffsetY" );
        CIntegerParameter width( nodemap, "Width" );
        CIntegerParameter height( nodemap, "Height" );

        cout << "OffsetX:OffsetY " << offsetX.GetValue() << ":" << offsetY.GetValue() << endl;
        cout << "Width:Height " << width.GetValue() << ":" << height.GetValue() << endl;

        cout << "Using device " << camera->GetDeviceInfo().GetModelName() << endl;
        camera->Close();
    }
    catch (const GenericException& e)
    {
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
    }
}

void CPylonGrabStop(void *cameraPtr) {
    CInstantCamera *camera = (CInstantCamera *)cameraPtr;
    camera->StopGrabbing();
}

void CPylonGrabFrames(void *cameraPtr, int bufferCount, int timeout, GrabCallbackPtr grabCallbackPtr) {
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
            uint8_t* pImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();

            grabCallbackPtr(width, height, pImageBuffer);
        }
    }
    catch (const GenericException& e)
    {
        cerr << "An exception occurred." << endl
            << e.GetDescription() << endl;
    }
}

