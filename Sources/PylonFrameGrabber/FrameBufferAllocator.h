//
//  FrameBufferAllocator.h
//  PylonCam
//
//  Created by Dmitriy Borovikov on 12.09.2021.
//

#pragma once
#include <pylon/PylonIncludes.h>

class FrameBufferAllocator : public Pylon::IBufferFactory
{
public:
    FrameBufferAllocator(void * frameBuffer, size_t frameBufferSize);
    virtual ~FrameBufferAllocator();
    virtual void AllocateBuffer( size_t bufferSize, void** pCreatedBuffer, intptr_t& bufferContext );
    virtual void FreeBuffer( void* pCreatedBuffer, intptr_t bufferContext );
    virtual void DestroyBufferFactory();

protected:
    void *  frameBuffer;
    size_t  frameBufferSize;
    int     context;
};
