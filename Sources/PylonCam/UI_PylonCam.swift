/********************************************************************************
** Form generated from reading UI file 'UI_PylonCam.ui'
**
** Created by: Qlift User Interface Compiler version <undefined>
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

import Qlift


class UIMainWindow: QMainWindow {
    var centralwidget: QWidget!
    var verticalLayout: QVBoxLayout!
    var horizontalLayout_3: QHBoxLayout!
    var pageHeaderlabel: QLabel!
    var horizontalSpacer: QSpacerItem!
    var horizontalLayout: QHBoxLayout!
    var lapLabel: QLabel!
    var bestLabel: QLabel!
    var imageLabel: QLabel!
    var frameButtons: QFrame!
    var layoutWidget1: QWidget!
    var horizontalLayout_2: QHBoxLayout!
    var plusButton: QPushButton!
    var minusButton: QPushButton!

    override init(parent: QWidget? = nil, flags: Qt.WindowFlags = .Widget) {
        super.init(parent: parent, flags: flags)
        self.geometry = QRect(x: 0, y: 0, width: 1043, height: 787)
        self.minimumSize = QSize(width: 520, height: 410)
        self.windowTitle = "MainWindow"
        self.styleSheet = """
background: #284465;
"""
        centralwidget = QWidget(parent: self)
        centralwidget.name = "centralwidget"
        verticalLayout = QVBoxLayout(parent: centralwidget)
        verticalLayout.contentsMargins = QMargins(left: 20, top: 20, right: 20, bottom: 2)
        verticalLayout.spacing = 5
        horizontalLayout_3 = QHBoxLayout(parent: nil)
        horizontalLayout_3.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
        pageHeaderlabel = QLabel(parent: centralwidget)
        pageHeaderlabel.name = "pageHeaderlabel"
        pageHeaderlabel.maximumSize = QSize(width: 230, height: 40)
        pageHeaderlabel.styleSheet = """
font-family: Rubik;
font-style: normal;
font-weight: bold;
font-size: 32px;
line-height: 38px;
color: #FFFFFF;

"""
        pageHeaderlabel.text = "Camera focus"
        pageHeaderlabel.alignment = [.AlignLeading, .AlignLeft, .AlignTop]
        horizontalLayout_3.add(widget: pageHeaderlabel)
        horizontalSpacer = QSpacerItem(width: 40, height: 20, horizontalPolicy: .Expanding, verticalPolicy: .Minimum)
        horizontalLayout_3.add(item: horizontalSpacer)
        horizontalLayout = QHBoxLayout(parent: nil)
        horizontalLayout.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
        lapLabel = QLabel(parent: centralwidget)
        lapLabel.name = "lapLabel"
        lapLabel.minimumSize = QSize(width: 194, height: 42)
        lapLabel.maximumSize = QSize(width: 194, height: 42)
        lapLabel.styleSheet = """
font-family: Rubik;
font-style: normal;
font-weight: 500;
font-size: 16px;
color: white;
height: 40px;
width: 192px;
max-width: 192px;
max-height: 40px;
min-height: 40px;
min-width: 192px;
border: 1px solid transparent;
"""
        lapLabel.text = "Laplacian: 0.0"
        lapLabel.alignment = [.AlignLeading, .AlignLeft, .AlignVCenter]
        horizontalLayout.add(widget: lapLabel)
        bestLabel = QLabel(parent: centralwidget)
        bestLabel.name = "bestLabel"
        bestLabel.minimumSize = QSize(width: 194, height: 42)
        bestLabel.maximumSize = QSize(width: 194, height: 42)
        bestLabel.styleSheet = """
font-family: Rubik;
font-style: normal;
font-weight: 500;
font-size: 16px;
color: white;
height: 40px;
width: 192px;
max-width: 192px;
max-height: 40px;
min-height: 40px;
min-width: 192px;
border: 1px solid transparent;
"""
        bestLabel.text = "best: 0"
        bestLabel.alignment = [.AlignLeading, .AlignLeft, .AlignVCenter]
        horizontalLayout.add(widget: bestLabel)
        horizontalLayout_3.add(layout: horizontalLayout)
        verticalLayout.add(layout: horizontalLayout_3)
        imageLabel = QLabel(parent: centralwidget)
        imageLabel.name = "imageLabel"
        imageLabel.text = ""
        verticalLayout.add(widget: imageLabel)
        frameButtons = QFrame(parent: centralwidget)
        frameButtons.name = "frameButtons"
        frameButtons.minimumSize = QSize(width: 174, height: 95)
        frameButtons.maximumSize = QSize(width: 100, height: 95)
        frameButtons.autoFillBackground = false
        frameButtons.styleSheet = """
QFrame {
background: transparent;
}
QPushButton {
font-family: Rubik;
font-style: normal;
font-weight: 500;
font-size: 48px;
opacity: 0.94;
height: 60px;
width: 60px;
max-width: 60px;
max-height: 60px;
min-height: 60px;
min-width: 60px;
}
QPushButton:enabled { 
border: 1px solid #0F9FD6;
border-radius: 8px;
color: #0F9FD6;
background: transparent;
}
QPushButton:disabled { 
border: 1px solid gray;
border-radius: 8px;
color: #0F9FD6;
background: transparent;
}
QPushButton:pressed{ 
border: 1px solid white;
}
QPushButton::checked { 
color: #FFFFFF;
background: #0F9FD6;
border-radius: 8px;
}
"""
        frameButtons.frameShape = .NoFrame
        layoutWidget1 = QWidget(parent: frameButtons)
        layoutWidget1.name = "layoutWidget1"
        layoutWidget1.geometry = QRect(x: 10, y: 10, width: 161, height: 72)
        horizontalLayout_2 = QHBoxLayout(parent: layoutWidget1)
        horizontalLayout_2.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
        horizontalLayout_2.spacing = 0
        plusButton = QPushButton(parent: layoutWidget1)
        plusButton.name = "plusButton"
        plusButton.styleSheet = """
QPushButton:enabled { 
color: #FFFFFF;
background: #0F9FD6;
border-radius: 8px;
}

"""
        plusButton.text = "+"
        plusButton.isFlat = false
        horizontalLayout_2.add(widget: plusButton)
        minusButton = QPushButton(parent: layoutWidget1)
        minusButton.name = "minusButton"
        minusButton.styleSheet = """
QPushButton:enabled { 
color: #FFFFFF;
background: #0F9FD6;
border-radius: 8px;
}

"""
        minusButton.text = "-"
        minusButton.isFlat = false
        horizontalLayout_2.add(widget: minusButton)
        verticalLayout.add(widget: frameButtons)
        self.centralWidget = centralwidget
    }
}
