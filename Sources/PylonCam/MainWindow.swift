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
    let zoomFactor: [Double] = [0.5, 1, 2, 3, 4, 5, 8]
    var zoomLevel = 1 {
        didSet {
            if zoomLevel == 0 {
                plusButton.enabled = false
            } else if zoomLevel == zoomFactor.count - 1 {
                minusButton.enabled = false
            } else {
                minusButton.enabled = true
                plusButton.enabled = true
            }
        }
    }
    var imageWidth = 0
    var imageHeight = 0
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
        centerButton.connectClicked(to: centerButtonClick)
        startStopButton.text = "Start"
    }

    private func plusButtonClick() {
        zoomLevel -= 1
        setZoom(zoom: zoomFactor[zoomLevel])
    }
    private func minusButtonClick() {
        zoomLevel += 1
        setZoom(zoom: zoomFactor[zoomLevel])
    }

    private func setZoom(zoom: Double) {
        let zWidth = Double(imageWidth) / zoom
        let zHeight = Double(imageHeight) / zoom
        print(zWidth, zHeight, zoom)
        imageLabel.resize(width: Int32(zWidth), height: Int32(zHeight))
    }

    func centerButtonClick() {
        let zWidth = Double(imageWidth) / zoomFactor[zoomLevel] / 2
        let zHeight = Double(imageHeight) / zoomFactor[zoomLevel] / 2
        scrollArea.ensureVisible(x: Int32(zWidth), y: Int32(zHeight))
    }

    func setFocusParams() {
        let area = frameGrabber.getMaxArea()
        let xPart = (area.width / 3) & ~0xf
        let yPart = (area.height) / 3 & ~0xf
        let newWidth = (area.width - xPart * 2) & ~0xf
        let newHeight = (area.height - yPart * 2) & ~0xf
        let roiArea = frameGrabber.getAutoAOI()
        print("Auto AOI:", roiArea)
        imageHeight = Int(newHeight)
        imageWidth = Int(newWidth)
        let aoi = Area(offsetX: xPart, offsetY: yPart, width: newWidth, height: newHeight)
        print("Camera: \(area.width)x\(area.height)")
        print(aoi)
        frameGrabber.setAOI(area: aoi)
        frameGrabber.setAutoAOI(area: aoi)
    }

    func startStopButtonClick() {
        if startStopButton.text == "Start" {
            startStopButton.text = "Stop"
            frameGrabberQueue.async { [self] in
                frameGrabber.AttachDevice()
                frameGrabber.PrintParams()
                setFocusParams()
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

    func getMeasureFunc() -> ((_: Int32, _: Int32, _: UnsafeMutableRawPointer) -> Double) {
        if laplacianButton.checked {
            return laplacianMeasure
        } else if sobelButton.checked {
            return sobelMeasure
        } else if varianceButton.checked {
            return varianceMeasure
        }
        return laplacianMeasure
    }

    func drawFrame(frame: UnsafeMutableRawPointer, width: Int32, height: Int32) {
        measureQueue.async {
            let measureFunc = self.getMeasureFunc()
            let measure = measureFunc(width, height, frame)
            dispatchQt {
                self.lapLabel.text = String(measure)
            }
        }
        dispatchQt { [self] in
            // Draw picture
            let dmxImage = QImage(data: frame, width: Int(width), height: Int(height), format: .Format_Grayscale8)
            self.imageLabel.setImage(dmxImage)
        }
    }
}
