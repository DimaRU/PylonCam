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
    var frameGrabber: PylonFrameGrabber
    let queue = DispatchQueue(label: "frameGrabber.Queue", qos: .userInitiated)

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
    }
    func minusButtonClick() {
    }

    func startStopButtonClick() {
        if startStopButton.text == "Start" {
            startStopButton.text = "Stop"
            queue.async { [self] in
                frameGrabber.AttachDevice()
                frameGrabber.PrintParams()
                frameGrabber.GrabFrames(object: Unmanaged.passUnretained(self).toOpaque(), bufferCount: 5, timeout: 500)
                { object, width, height, frame in
                    let mySelf = Unmanaged<MainWindow>.fromOpaque(object).takeUnretainedValue()
                    mySelf.drawFrame(frame: frame, width: Int(width), height: Int(height))
                }
                print("Stopped")
            }
        } else {
            startStopButton.text = "Start"
            self.frameGrabber.GrabStop()
        }

    }

    func drawFrame(frame: UnsafeRawPointer, width: Int, height: Int) {
        dispatchQt {
            // Draw picture
            print("width:", width)
            let dmxImage = QImage(data: frame, width: width, height: height, format: .Format_Grayscale8)
            self.imageLabel.setImage(dmxImage)
            self.imageLabel.scaledContents = true
        }
    }
}
