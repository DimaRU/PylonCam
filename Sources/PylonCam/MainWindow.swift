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

    init() {
        super.init()
        connectButtons()
    }

    private func connectButtons() {
        plusButton.connectClicked(to: plusButtonClick)
        minusButton.connectClicked(to: minusButtonClick)
    }

    func plusButtonClick() {
    }
    func minusButtonClick() {
    }


//    func showMessageBox(error: SwiftyModbus.ModbusError) {
//        dispatchQt {
//            let messageBox = QMessageBox(parent: self)
//            messageBox.text = error.localizedDescription
//            messageBox.icon = .Critical
//            let _: QMessageBox.StandardButton = messageBox.exec()
//        }
//    }
}
