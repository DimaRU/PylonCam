//
//  MainWindow.swift
//  
//
//  Created by Dmitriy Borovikov on 17.06.2021.
//

import Foundation
import Qlift
import Logging
import PylonFrameGrabber
import FocusMeasure

fileprivate let brigtnessParam = "AutoTargetValue";

class MainWindow: UIMainWindow {
    private let zoomFactor: [Double] = [0.5, 1, 2, 3, 4, 5, 8]
    private let bufferCount: Int32 = 5
    private var zoomLevel = 1 {
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

    private var bestMeasure: Double? = nil
    private var imageWidth = 0
    private var imageHeight = 0
    private var frameGrabber: PylonGrabber
    private let frameGrabberQueue = DispatchQueue(label: "frameGrabber.Queue", qos: .userInitiated)
    private let measureQueue = DispatchQueue(label: "measureFocus.Queue", qos: .userInteractive)
    private var sharedMemory: SharedMemory?
    private var savedAOI: Area = Area()

    init() {
        PylonInitialize()
        frameGrabber = PylonGrabber()
        super.init()
        connectButtons()
    }

    deinit {
        if frameGrabber.IsPylonDeviceAttached() {
            frameGrabber.setAOI(area: savedAOI)
        }
        frameGrabber.ReleaseCamera()
        PylonTerminate()
    }

    private func connectButtons() {
        plusButton.connectClicked { [unowned self] in
            zoomLevel -= 1
            setZoom(zoom: zoomFactor[zoomLevel])
        }
        minusButton.connectClicked { [unowned self] in
            zoomLevel += 1
            setZoom(zoom: zoomFactor[zoomLevel])
        }
        laplacianButton.connectToggled { [unowned self] _ in
            bestMeasure = nil
        }
        sobelButton.connectToggled { [unowned self] _ in
            bestMeasure = nil
        }
        varianceButton.connectToggled { [unowned self] _ in
            bestMeasure = nil
        }

        startStopButton.connectClicked { [unowned self] in startStopButtonClick() }
        centerButton.connectClicked{ [unowned self] in centerButtonClick() }
        startStopButton.text = "Start"
    }

    override func closeEvent(event: QCloseEvent) {
        self.frameGrabber.GrabStop()
    }

    private func setZoom(zoom: Double) {
        let zWidth = Double(imageWidth) / zoom
        let zHeight = Double(imageHeight) / zoom
        imageLabel.resize(width: Int32(zWidth), height: Int32(zHeight))
    }

    private func centerButtonClick() {
        let zWidth = Double(imageWidth) / zoomFactor[zoomLevel] / 2
        let zHeight = Double(imageHeight) / zoomFactor[zoomLevel] / 2
        scrollArea.ensureVisible(x: Int32(zWidth), y: Int32(zHeight))
    }

    private func setFocusParams() {
        let area = frameGrabber.getMaxArea()
        let xPart = (area.width / 3) & ~0xf
        let yPart = (area.height / 3) & ~0xf
        let newWidth = (area.width - xPart * 2) & ~0xf
        let newHeight = (area.height - yPart * 2) & ~0xf
        imageHeight = Int(newHeight)
        imageWidth = Int(newWidth)
        let aoi = Area(offsetX: xPart, offsetY: yPart, width: newWidth, height: newHeight)
        print("Camera capability: \(area.width)x\(area.height)")
        let model = String(cString: frameGrabber.StringParameter(name: "DeviceModelName"), encoding: .utf8)!
        statusBar.showMessage(message: " \(model): \(aoi)")
        frameGrabber.setAOI(area: aoi)
        frameGrabber.setAutoAOI(area: aoi)
        sharedMemory = SharedMemory(width: imageWidth, height: imageHeight, bufferCount: Int(bufferCount))
        if let sharedMemory = sharedMemory {
            frameGrabber.SetBufferAllocator(frameBuffer: sharedMemory.sharedFrameBuffer, frameBufferSize: sharedMemory.bufferSize)
        }
        let scrollSize = scrollArea.size
        let labelWidth = scrollSize.width - 5
        let labelHeight = labelWidth * Int32(imageHeight) / Int32(imageWidth)
        imageLabel.resize(width: labelWidth, height: labelHeight)
    }

    private func tryConnect() -> Bool {
        if !frameGrabber.IsPylonDeviceAttached() {
            frameGrabber.AttachDevice()
            guard !frameGrabber.errorFlag else {
                statusBar.showMessage(message: String(cString: frameGrabber.getString, encoding: .utf8)!)
                return false
            }
        }
        if !frameGrabber.IsOpen() {
            frameGrabber.cameraStart()
            guard !frameGrabber.errorFlag else {
                statusBar.showMessage(message: String(cString: frameGrabber.getString, encoding: .utf8)!)
                return false
            }
        }
        savedAOI = frameGrabber.getAOI()
        frameGrabber.PrintParams()
        setFocusParams()
        setBrigthnessSlider()
        return true
    }

    private func setBrigthnessSlider() {
        brightnessSlider.minimum = Int32(frameGrabber.IntParameter(name: brigtnessParam, type: .min))
        brightnessSlider.maximum = Int32(frameGrabber.IntParameter(name: brigtnessParam, type: .max))
        brightnessSlider.singleStep = Int32(frameGrabber.IntParameter(name: brigtnessParam, type: .step))
        brightnessSlider.pageStep = 1
        let value = Int32(frameGrabber.IntParameter(name: brigtnessParam, type: .value))
        brightnessSlider.value = value;
        self.brightnessLabel.text = "Brightness: \(value)"
        brightnessSlider.connectValueChanged { [unowned self] value in
            self.frameGrabber.SetIntParameter(name: brigtnessParam, value: Int64(value))
            self.brightnessLabel.text = "Brightness: \(value)"
        }
    }

    private func startStopButtonClick() {
        if startStopButton.text == "Start" {
            guard tryConnect() else {
                return
            }
            startStopButton.text = "Stop"
            frameGrabberQueue.async { [unowned self] in
                frameGrabber.GrabFrames(object: Unmanaged.passUnretained(self).toOpaque(), bufferCount: bufferCount, timeout: 500)
                { object, width, height, frame, context in
                    let mySelf = Unmanaged<MainWindow>.fromOpaque(object).takeUnretainedValue()
                    mySelf.drawFrame(frame: frame, width: width, height: height)
                }
            }
        } else {
            startStopButton.text = "Start"
            self.frameGrabber.GrabStop()
            if frameGrabber.IsPylonDeviceAttached() {
                frameGrabber.setAOI(area: savedAOI)
            }
            self.frameGrabber.cameraStop()
            sharedMemory = nil
        }
    }

    private func getMeasureFunc() -> ((_: Int32, _: Int32, _: UnsafeMutableRawPointer) -> Double) {
        if laplacianButton.checked {
            return laplacianMeasure
        } else if sobelButton.checked {
            return sobelMeasure
        } else if varianceButton.checked {
            return varianceMeasure
        }
        return laplacianMeasure
    }

    private func drawFrame(frame: UnsafeMutableRawPointer, width: Int32, height: Int32) {
        measureQueue.async {
            let measureFunc = self.getMeasureFunc()
            let measure = measureFunc(width, height, frame)
            dispatchQt {
                self.lapLabel.text = String(format: "Measure: %.2f", measure)
                if self.laplacianButton.checked {
                    if self.bestMeasure ?? Double.greatestFiniteMagnitude <= measure {
                        return
                    }
                } else {
                    if self.bestMeasure ?? 0 >= measure {
                        return
                    }
                }
                self.bestMeasure = measure
                self.bestLabel.text = String(format: "Best: %.2f", self.bestMeasure!)
            }
        }
        dispatchQt { [weak self] in
            guard let self = self else { return }
            // Draw picture
            let dmxImage = QImage(data: frame, width: Int(width), height: Int(height), format: .Format_Grayscale8)
            self.imageLabel.setImage(dmxImage)
        }
    }
}
