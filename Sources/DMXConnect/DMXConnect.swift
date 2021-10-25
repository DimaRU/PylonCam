//
//  DMXConnect.swift
//  
//
//  Created by Dmitriy Borovikov on 23.09.2021.
//

import Foundation
import Logging
import Socket
import DMXWrapper

public struct DMXCodeBox {
	public let x,xx: Int32
	public let y,yy: Int32
	public var code: String?
}
public protocol DMXConnectDelegate: AnyObject {
	func detectedDMX(boxes: [DMXCodeBox])
	func waitingStartDMX()
}


final public class DMXConnect {
    private let logger = Logger(label: String(describing: DMXConnect.self))
    private let socket: Socket
    private let listenQueue = DispatchQueue(label: "dmx_listen", qos: .userInitiated)
    private let sendQueue = DispatchQueue(label: "dmx_send", qos: .userInitiated)
    private let requestSignature: Socket.Signature
    private let requestPath: String, replyPath: String
    private var listening = true
    private var listenBuffer: UnsafeMutablePointer<Int8>
    private var listenBufferSize: Int
	var frameId: UInt64 = 0
	public weak var delegate: DMXConnectDelegate?
	var detectedBoxes: [DMXCodeBox] = []


    public init() {
        listenBufferSize = (MemoryLayout<DMXCode>.stride * Int(MaxDMXCodes) + MemoryLayout<DMXCodeDetectionReply>.stride + 0xfff) & ~0xfff
        requestPath = FileManager.default.temporaryDirectory.appendingPathComponent("dmx_request").path
        replyPath = FileManager.default.temporaryDirectory.appendingPathComponent("dmx_reply").path
        do {
            requestSignature = try Socket.Signature.init(socketType: .datagram, proto: .unix, path: requestPath)!
            socket = try Socket.create(family: .unix, type: .datagram, proto: .unix)
            socket.readBufferSize = listenBufferSize
            listenBuffer = UnsafeMutablePointer<Int8>.allocate(capacity: listenBufferSize)
            try socket.bind(on: replyPath)
            return
        } catch let error as Socket.Error {
            logger.critical("code: \(error.errorCode), \(error.errorReason ?? "")")
            fatalError("\(error)")
        } catch {
            fatalError("\(error)")
        }
    }

    /// DMX codes detection rquest to nn_dmx
    /// - Parameters:
    ///   - num: frame buffer number
    ///   - width: frame width
    ///   - height: frame height
    ///   - frameId: frame id
    public func request(num: Int, width: Int, height: Int, frameId: UInt64) {
		sendQueue.async { [self] in
			do {
				self.frameId = frameId
                var request = BoxDetectionRequest(frameId: frameId, width: UInt64(width), height: UInt64(height), bufferNum: Int32(num))
				let size = MemoryLayout.size(ofValue: request)
				let _ = try withUnsafePointer(to: &request) { requestPtr in
					try socket.write(from: requestPtr, bufSize: size, to: requestSignature.address!)
				}
			} catch let error as Socket.Error  {
				if error.errorCode == -9980 {
					logger.info("DMX decoder not stated")
					delegate?.waitingStartDMX()
				} else {
					logger.error("Request error: \(error)")
				}
			} catch {
				fatalError("\(error)")
			}
		}
    }

    public func startListenReply() {
		listening = true
        listenQueue.async { [self] in
            while(listening) {
                do {
					let replySize = try socket.read(into: listenBuffer, bufSize: listenBufferSize)
					listenBuffer.withMemoryRebound(to: DMXReplyHeader.self, capacity: 1) { replyHeader in
						parseReply(header: replyHeader.pointee, size: replySize)
					}
                } catch {
                    if listening {
                        logger.error("listener error: \(error)")
                    }
                }
            }
        }
    }

	public func stop() {
		listening = false
		socket.close()
	}

	private func parseReply(header: DMXReplyHeader, size: Int) {
		guard MemoryLayout.stride(ofValue: header) <= size else {
			logger.error("Reply size too small \(size)")
			return
		}
		guard header.frameId == frameId else {
			logger.error("Frame id not in sync: \(header.frameId), \(frameId)")
			return
		}
		if header.replyType == 0 {
			listenBuffer.withMemoryRebound(to: DMXBoxDetectionReply.self, capacity: 1) {
				parseBox(reply: $0.pointee, size: size)
			}
		} else if header.replyType == 1 {
			listenBuffer.withMemoryRebound(to: DMXCodeDetectionReply.self, capacity: 1) {
				parseCode(reply: $0.pointee, size: size)
			}
		} else {
			logger.error("Wrong reply type \(header.replyType)")
		}
	}

	private func parseBox(reply: DMXBoxDetectionReply, size: Int) {
        let detectedCount = Int(reply.detectedCount)
		detectedBoxes = []
		guard detectedCount != 0 else {
			delegate?.detectedDMX(boxes: [])
			return
		}
		guard MemoryLayout<DMXBoxDetectionReply>.stride + MemoryLayout<DMXBox>.stride * detectedCount <= size else {
			logger.error("Box detection reply size too small \(size)")
			return
		}
		(listenBuffer + MemoryLayout<DMXBoxDetectionReply>.stride).withMemoryRebound(to: DMXBox.self, capacity: detectedCount) { ptr in
			detectedBoxes.reserveCapacity(detectedCount)
			for i in 0..<detectedCount {
				let detectedBox = DMXCodeBox(x: Int32(ptr[i].x), xx: Int32(ptr[i].xx), y: Int32(ptr[i].y), yy: Int32(ptr[i].yy), code: nil)
				detectedBoxes.append(detectedBox)
			}
		}
	}

	private func parseCode(reply: DMXCodeDetectionReply, size: Int) {
		guard MemoryLayout<DMXCodeDetectionReply>.stride + MemoryLayout<DMXBox>.stride * detectedBoxes.count <= size else {
			logger.error("Box detection reply size too small \(size)")
			return
		}
		(listenBuffer + MemoryLayout<DMXCodeDetectionReply>.stride).withMemoryRebound(to: DMXCode.self, capacity: detectedBoxes.count) { ptr in
			for i in 0..<detectedBoxes.count {
                let len = Int(ptr[i].len)
				guard len != 0, len <= MaxDMXCodeLen else { continue }
				detectedBoxes[i].code = String(unsafeUninitializedCapacity: len) {
					memcpy($0.baseAddress!, &ptr[i].code, len)
					return Int(len)
				}
			}
		}
        delegate?.detectedDMX(boxes: detectedBoxes)
	}

    deinit {
        print("Deinit:", String(describing: Self.self))
		listening = false
		socket.close()
        unlink(replyPath)
		listenBuffer.deallocate()
    }
}
