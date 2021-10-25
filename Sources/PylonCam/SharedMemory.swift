//
//  SharedMemory.swift
//
//
//  Created by Dmitriy Borovikov on 12.09.2021.
//

import Foundation
import DMXWrapper

final class SharedMemory {
    public let sharedFrameBuffer: UnsafeMutableRawPointer
    public let bufferSize: Int

    init(frameSize: Int, bufferCount: Int, sharedFileName: String) {
        bufferSize = frameSize * bufferCount
        sharedFrameBuffer = SharedMemory.makeSharedFrameBuffer(size: bufferSize, sharedFileName: sharedFileName)
    }

    deinit {
        munmap(sharedFrameBuffer, bufferSize)
    }

    static func makeSharedFrameBuffer(size: Int, sharedFileName: String) -> UnsafeMutableRawPointer {
        let sharedFile = shmOpen(sharedFileName, O_RDWR|O_CREAT, UInt16(S_IRUSR|S_IWUSR))
        guard
            sharedFile != -1 else {
                perror(nil)
                fatalError("Can't open shared frame_buffer file")
            }

        var statBuf: stat = stat()
        let _ = fstat(sharedFile, &statBuf)
        let fileSize = Int(statBuf.st_size)
        print(fileSize)
        if size > fileSize {
#if os(Linux)
            ftruncate(sharedFile, size)
#else
            ftruncate(sharedFile, Int64(size))
#endif
        }

        guard
            let buffer = mmap(nil, size, PROT_READ|PROT_WRITE, MAP_SHARED, sharedFile, 0),
            buffer != UnsafeMutableRawPointer(bitPattern: -1) else {
                perror(nil)
                fatalError("Can't map frame_buffer")
            }
        close(sharedFile)
        return buffer
    }
}
