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
import DMXWrapper


fileprivate let sharedFileName = "/frame_buffer"

class SharedMemory {
    public var sharedFrameBuffer: UnsafeMutableRawPointer!
    let bufferSize: Int

    init(size: Int) {
        bufferSize = (size + 0xfff) & ~0xfff
        sharedFrameBuffer = makeShareFrameBuffer(size: bufferSize)
    }

    deinit {
        destroyShareFrameBuffer(size: bufferSize)
    }

    func makeShareFrameBuffer(size: Int) -> UnsafeMutableRawPointer {
        shm_unlink(sharedFileName)
        let sharedFile = shmOpen(sharedFileName, O_RDWR|O_CREAT, 0)
        guard
            sharedFile != -1 else {
                perror(nil)
                print("Can't open shared frame_buffer file")
                fatalError()
        }

        #if os(Linux)
        ftruncate(sharedFile, size)
        #else
        ftruncate(sharedFile, Int64(size))
        #endif
        guard
            let buffer = mmap(nil, size, PROT_READ|PROT_WRITE, MAP_SHARED, sharedFile, 0),
            buffer != UnsafeMutableRawPointer(bitPattern: -1) else {
                perror(nil)
                shm_unlink(sharedFileName)
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
