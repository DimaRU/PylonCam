//
//  main.c
//  PylonCam
//
//  Created by Dmitriy Borovikov on 30.08.2021.
//

// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#include "GetLabplacian.hpp"

using namespace Pylon;
using namespace GenApi;
using namespace std;

int main( int /*argc*/, char* /*argv*/[] )
{
    // The exit code of the sample application.
    int exitCode = 0;

    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();

    try
    {
        // Create an instant camera object with the camera device found first.
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice() );

        INodeMap& nodemap = camera.GetNodeMap();
        camera.Open();

        cout << "Camera Device Information" << endl
            << "=========================" << endl;
        cout << "Vendor           : "
            << CStringParameter( nodemap, "DeviceVendorName" ).GetValue() << endl;
        cout << "Model            : "
            << CStringParameter( nodemap, "DeviceModelName" ).GetValue() << endl;
        cout << "Firmware version : "
            << CStringParameter( nodemap, "DeviceFirmwareVersion" ).GetValue() << endl << endl;
        // Get the integer nodes describing the AOI.
        CIntegerParameter offsetX( nodemap, "OffsetX" );
        CIntegerParameter offsetY( nodemap, "OffsetY" );
        CIntegerParameter width( nodemap, "Width" );
        CIntegerParameter height( nodemap, "Height" );

        cout << "OffsetX:OffsetY " << offsetX.GetValue() << ":" << offsetY.GetValue() << endl;
        cout << "Width:Height " << width.GetValue() << ":" << height.GetValue() << endl;

        // Print the model name of the camera.
        cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
        // Get camera device information.
        camera.Close();

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 5;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
//        camera.StartGrabbing( c_countOfImagesToGrab );
        camera.StartGrabbing( GrabStrategy_LatestImages );

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while (camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException );

            // Image grabbed successfully?
            if (!ptrGrabResult->GrabSucceeded())
            {
                cout << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " " << ptrGrabResult->GetErrorDescription() << endl;
                continue;
            }



            CImageFormatConverter formatConverter;
            formatConverter.OutputPixelFormat = PixelType_BGR8packed;
            CPylonImage pylonImage;

            // Access the image data.
            int width = ptrGrabResult->GetWidth();
            int height = ptrGrabResult->GetHeight();
//            const uint8_t* pImageBuffer = (uint8_t*) ptrGrabResult->GetBuffer();

//            formatConverter.Convert(pylonImage, ptrGrabResult);
            cout << "WxH: " << width << "x" << height << endl;
            cout << "Buffer Size: " << ptrGrabResult->GetBufferSize() << " n:" << endl; //<< pylonImage.GetAllocatedBufferSize()  << endl;
            //            cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl;
            GetLabplacian(height, width, ptrGrabResult->GetBuffer());
        }
    }
    catch (const GenericException& e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
            << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
//    cerr << endl << "Press enter to exit." << endl;
//    while (cin.get() != '\n');

    // Releases all pylon resources.
    PylonTerminate();

    return exitCode;
}
