//
//  CPylonImageEventHandler.h
//  
//
//  Created by Dmitriy Borovikov on 25.09.2021.
//

#pragma once
using namespace Pylon;

class CPylonImageEventHandler: public CImageEventHandler
{
private:
    const void *object;
    GrabCallback grabCallback;
public:
    CPylonImageEventHandler(const void * object, GrabCallback grabCallback);
    virtual void OnImagesSkipped( CInstantCamera& camera, size_t countOfSkippedImages );
    virtual void OnImageGrabbed( CInstantCamera& camera, const CGrabResultPtr& ptrGrabResult );
};
