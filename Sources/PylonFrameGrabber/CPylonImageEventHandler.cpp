//
//  CPylonImageEventHandler.cpp
//  
//
//  Created by Dmitriy Borovikov on 25.09.2021.
//

#include <pylon/PylonIncludes.h>
#include "PylonFrameGrabber.h"
#include "CPylonImageEventHandler.h"

using namespace Pylon;

CPylonImageEventHandler::CPylonImageEventHandler(const void * object, GrabCallback grabCallback) {
    this->object = object;
    this->grabCallback = grabCallback;
}

void CPylonImageEventHandler::OnImagesSkipped( CInstantCamera& camera, size_t countOfSkippedImages )
{
    grabCallback(object, 0, 0, nullptr, countOfSkippedImages);
}

void CPylonImageEventHandler::OnImageGrabbed( CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult )
{
    if (!ptrGrabResult->GrabSucceeded())
    {
        grabCallback(object, 1, 0, nullptr, ptrGrabResult->GetErrorCode());
        std::cerr << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " " << ptrGrabResult->GetErrorDescription() << std::endl;
        return;
    }
    int width = ptrGrabResult->GetWidth();
    int height = ptrGrabResult->GetHeight();
    auto pImageBuffer = ptrGrabResult->GetBuffer();
    int context = ptrGrabResult->GetBufferContext();

    grabCallback(object, width, height, pImageBuffer, context);
}
