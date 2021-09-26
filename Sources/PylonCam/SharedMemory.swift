//
//  SharedMemory.swift
//
//
//  Created by Dmitriy Borovikov on 12.09.2021.
//

import Foundation
#if canImport(Darwin)
import Darwin
#elseif canImport(Glibc)
import Glibc
#else
#error("Unsupported platform")
#endif
import CameraSharedMem

fileprivate let sharedFileName = "/frame_buffer"

class SharedMemory {
    public let sharedFrameBuffer: UnsafeMutableRawPointer!
    public let headerSize: Int
    public let bufferSize: Int
    public let bufferCount: Int

    init(width: Int, height: Int, bufferCount: Int) {
        self.bufferCount = bufferCount
        headerSize = (MemoryLayout<CameraSharedMem>.size + MemoryLayout<UnsafeRawPointer>.size * bufferCount + 0xff) & ~0xff
        let size = width * height * bufferCount + headerSize
        bufferSize = (size + 0xfff) & ~0xfff
        sharedFrameBuffer = SharedMemory.makeShareFrameBuffer(size: bufferSize)
        let cameraSharedMemPtr = sharedFrameBuffer.bindMemory(to: CameraSharedMem.self, capacity: 1)
        cameraSharedMemPtr.pointee.width = UInt64(width)
        cameraSharedMemPtr.pointee.height = UInt64(height)
        let frameBufferPtr = (sharedFrameBuffer + MemoryLayout<CameraSharedMem>.size).bindMemory(to: UnsafeMutableRawPointer.self, capacity: 0)
        frameBufferPtr[0] = sharedFrameBuffer + headerSize
    }

    deinit {
        destroyShareFrameBuffer(size: bufferSize)
    }

    static func makeShareFrameBuffer(size: Int) -> UnsafeMutableRawPointer {
        shm_unlink(sharedFileName)
        let sharedFile = shmOpen(sharedFileName, O_RDWR|O_CREAT, 0)
        guard
            sharedFile != -1 else {
                perror(nil)
                fatalError("Can't open shared frame_buffer file")
        }

        #if os(Linux)
        ftruncate(sharedFile, size)
        #else
        ftruncate(sharedFile, Int64(size))
        #endif
        guard
            let buffer = mmap(nil, size, PROT_READ|PROT_WRITE, MAP_SHARED, sharedFile, 0),
            buffer != UnsafeMutableRawPointer(bitPattern: -1) else {
                shm_unlink(sharedFileName)
                perror(nil)
                fatalError("Can't map frame_buffer")
        }
        close(sharedFile)
        return buffer
    }

    func destroyShareFrameBuffer(size: Int) {
        munmap(sharedFrameBuffer, size)
        shm_unlink(sharedFileName)
    }
}
