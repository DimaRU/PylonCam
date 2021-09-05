//
//  MainWindow.swift
//  
//
//  Created by Dmitriy Borovikov on 17.06.2021.
//

import Foundation
import Qlift
import Logging
import PylonLib

class MainWindow: UIMainWindow {
    let zoom: [Float] = [0.5, 1, 2, 3, 4, 5, 8]
    var zoomLevel = 1 {
        didSet {
            if zoomLevel == 0 {
                plusButton.enabled = false
            } else if zoomLevel == zoom.count - 1 {
                minusButton.enabled = false
            } else {
                minusButton.enabled = true
                plusButton.enabled = true
            }
        }
    }
    var frameGrabber: PylonFrameGrabber
    let frameGrabberQueue = DispatchQueue(label: "frameGrabber.Queue", qos: .userInitiated)
    let measureQueue = DispatchQueue(label: "measureFocus.Queue", qos: .userInteractive)

    init() {
        PylonInitialize()
        frameGrabber = PylonFrameGrabber()
        super.init()
        connectButtons()
    }

    deinit {
        frameGrabber.ReleaseCamera()
        PylonTerminate()
    }

    private func connectButtons() {
        plusButton.connectClicked(to: plusButtonClick)
        minusButton.connectClicked(to: minusButtonClick)
        startStopButton.connectClicked(to: startStopButtonClick)
        startStopButton.text = "Start"
    }

    func plusButtonClick() {
        zoomLevel -= 1
    }
    func minusButtonClick() {
        zoomLevel += 1
    }

    func startStopButtonClick() {
        if startStopButton.text == "Start" {
            startStopButton.text = "Stop"
            frameGrabberQueue.async { [self] in
                frameGrabber.AttachDevice()
                frameGrabber.PrintParams()
                frameGrabber.GrabFrames(object: Unmanaged.passUnretained(self).toOpaque(), bufferCount: 5, timeout: 500)
                { object, width, height, frame in
                    let mySelf = Unmanaged<MainWindow>.fromOpaque(object).takeUnretainedValue()
                    mySelf.drawFrame(frame: frame, width: width, height: height)
                }
                print("Stopped")
            }
        } else {
            startStopButton.text = "Start"
            self.frameGrabber.GrabStop()
        }

    }

    func drawFrame(frame: UnsafeRawPointer, width: Int32, height: Int32) {
        measureQueue.async {
            let measure = LaplacianMeasure(height: height, width: width, imageBuffer: frame)
            dispatchQt { [self] in
                lapLabel.text = String(measure)
            }
        }
        dispatchQt { [self] in
            // Draw picture
            let dmxImage = QImage(data: frame, width: Int(width), height: Int(height), format: .Format_Grayscale8)
            self.imageLabel.setImage(dmxImage.scaled(
                                        w: Int32(Float(width) / zoom[zoomLevel]),
                                        h: Int32(Float(height) / zoom[zoomLevel]),
                                        aspectMode: .KeepAspectRatio,
                                        mode: .SmoothTransformation))
        }
    }
}
