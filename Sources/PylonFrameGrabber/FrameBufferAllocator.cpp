//
//  FrameBufferAllocator.cpp
//  PylonFrameGrabber
//
//  Created by Dmitriy Borovikov on 12.09.2021.
//

#include <pylon/PylonIncludes.h>
#include "FrameBufferAllocator.h"

using namespace Pylon;

FrameBufferAllocator::FrameBufferAllocator(void * frameBuffer, size_t frameBufferSize)
{
    this->frameBuffer = frameBuffer;
    this->frameBufferSize = frameBufferSize;
    this->context = 0;
}

FrameBufferAllocator::~FrameBufferAllocator()
{
}
// Will be called when the Instant Camera object needs to allocate a buffer.
// Return the buffer and context data in the output parameters.
// Warning: This method can be called by different threads.
void FrameBufferAllocator::AllocateBuffer( size_t bufferSize, void** pCreatedBuffer, intptr_t& bufferContext )
{
    size_t *frameBufferOffset = (size_t *)frameBuffer;
    // Allocate buffer for pixel data.
    *pCreatedBuffer = (uint8_t *)frameBuffer + frameBufferOffset[context];
    // The context information is never changed by the Instant Camera and can be used
    // by the buffer factory to manage the buffers.
    // The context information can be retrieved from a grab result by calling
    bufferContext = context;
    context++;
    frameBufferOffset[context] = frameBufferOffset[context - 1] + bufferSize;
    if ( frameBufferOffset[context] > frameBufferSize) {
        *pCreatedBuffer = NULL;
    }
}

// Frees a previously allocated buffer.
// Warning: This method can be called by different threads.
void FrameBufferAllocator::FreeBuffer( void* pCreatedBuffer, intptr_t bufferContext )
{
    uint8_t* p = reinterpret_cast<uint8_t*>(pCreatedBuffer);
}
// Destroys the buffer factory.
void FrameBufferAllocator::DestroyBufferFactory()
{
    delete this;
}
