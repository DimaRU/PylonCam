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
    var verticalLayout_3: QVBoxLayout!
    var horizontalLayout_3: QHBoxLayout!
    var pageHeaderlabel: QLabel!
    var horizontalSpacer: QSpacerItem!
    var horizontalLayout: QHBoxLayout!
    var lapLabel: QLabel!
    var bestLabel: QLabel!
    var horizontalLayout_4: QHBoxLayout!
    var scrollArea: QScrollArea!
    var imageLabel: QLabel!
    var frameButtons: QFrame!
    var verticalLayout: QVBoxLayout!
    var groupBox: QGroupBox!
    var verticalLayout_2: QVBoxLayout!
    var laplacianButton: QRadioButton!
    var sobelButton: QRadioButton!
    var varianceButton: QRadioButton!
    var verticalSpacer_2: QSpacerItem!
    var startStopButton: QPushButton!
    var verticalSpacer_3: QSpacerItem!
    var centerButton: QPushButton!
    var verticalSpacer: QSpacerItem!
    var horizontalLayout_2: QHBoxLayout!
    var plusButton: QPushButton!
    var horizontalSpacer_2: QSpacerItem!
    var minusButton: QPushButton!

    override init(parent: QWidget? = nil, flags: Qt.WindowFlags = .Widget) {
        super.init(parent: parent, flags: flags)
        self.geometry = QRect(x: 0, y: 0, width: 1043, height: 845)
        self.minimumSize = QSize(width: 520, height: 410)
        self.windowTitle = "MainWindow"
        self.styleSheet = """
background: #284465;
"""
        centralwidget = QWidget(parent: self)
        centralwidget.name = "centralwidget"
        verticalLayout_3 = QVBoxLayout(parent: centralwidget)
        verticalLayout_3.contentsMargins = QMargins(left: 20, top: 20, right: 0, bottom: 0)
        verticalLayout_3.spacing = 20
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
        lapLabel.text = "meashure: 0.0"
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
        bestLabel.text = "best: "
        bestLabel.alignment = [.AlignLeading, .AlignLeft, .AlignVCenter]
        horizontalLayout.add(widget: bestLabel)
        horizontalLayout_3.add(layout: horizontalLayout)
        verticalLayout_3.add(layout: horizontalLayout_3)
        horizontalLayout_4 = QHBoxLayout(parent: nil)
        horizontalLayout_4.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
        horizontalLayout_4.spacing = 0
        scrollArea = QScrollArea(parent: centralwidget)
        scrollArea.name = "scrollArea"
        scrollArea.widgetResizable = false
        imageLabel = QLabel()
        imageLabel.name = "imageLabel"
        imageLabel.geometry = QRect(x: 0, y: 0, width: 8, height: 16)
        imageLabel.sizePolicy = QSizePolicy(horizontal: .Ignored, vertical: .Ignored)
        imageLabel.scaledContents = true
        scrollArea.setWidget(imageLabel)
        horizontalLayout_4.add(widget: scrollArea)
        frameButtons = QFrame(parent: centralwidget)
        frameButtons.name = "frameButtons"
        frameButtons.minimumSize = QSize(width: 200, height: 0)
        frameButtons.maximumSize = QSize(width: 200, height: 16777215)
        frameButtons.autoFillBackground = false
        frameButtons.styleSheet = """
QFrame {
background: transparent;
}
QPushButton {
font-family: Rubik;
font-style: normal;
font-weight: 500;
font-size: 32px;
opacity: 0.94;
height: 60px;
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
        verticalLayout = QVBoxLayout(parent: frameButtons)
        verticalLayout.contentsMargins = QMargins(left: 10, top: 20, right: 20, bottom: 20)
        verticalLayout.spacing = 0
        groupBox = QGroupBox(parent: frameButtons)
        groupBox.name = "groupBox"
        groupBox.sizePolicy = QSizePolicy(horizontal: .Expanding, vertical: .Expanding)
        groupBox.minimumSize = QSize(width: 0, height: 0)
        groupBox.styleSheet = """
QGroupBox {
  border:  0px solid transparent;
  background-color: transparent;
}

QRadioButton {
  font-family: Rubik;
  font-style: normal;
  font-size: 30px;
  color: white;
  border:    4px solid transparent;
}
QRadioButton::indicator {
  color: white;
//  width:               20px;
//  height:              20px;
//   border-radius: 7px;
}
QRadioButton::indicator:checked {
  color: white;
   background-color: white;
//   border:                 2px solid white;
}
QRadioButton::indicator:unchecked {
   background-color:  white;
//    border:                 2px solid white;
}
QRadioButton:checked{
    background-color: gray;
}

QRadioButton:unchecked{
//   background-color: black;
}
"""
        groupBox.title = ""
        verticalLayout_2 = QVBoxLayout(parent: groupBox)
        verticalLayout_2.contentsMargins = QMargins(left: 10, top: 0, right: 0, bottom: 0)
        verticalLayout_2.spacing = 15
        laplacianButton = QRadioButton(parent: groupBox)
        laplacianButton.name = "laplacianButton"
        laplacianButton.text = "Laplacian"
        laplacianButton.checked = true
        verticalLayout_2.add(widget: laplacianButton)
        sobelButton = QRadioButton(parent: groupBox)
        sobelButton.name = "sobelButton"
        sobelButton.text = "Sobel"
        verticalLayout_2.add(widget: sobelButton)
        varianceButton = QRadioButton(parent: groupBox)
        varianceButton.name = "varianceButton"
        varianceButton.text = "Variance"
        verticalLayout_2.add(widget: varianceButton)
        verticalLayout.add(widget: groupBox)
        verticalSpacer_2 = QSpacerItem(width: 20, height: 40, horizontalPolicy: .Minimum, verticalPolicy: .Expanding)
        verticalLayout.add(item: verticalSpacer_2)
        startStopButton = QPushButton(parent: frameButtons)
        startStopButton.name = "startStopButton"
        startStopButton.minimumSize = QSize(width: 62, height: 62)
        startStopButton.styleSheet = """
QPushButton {
opacity: 0.94;
max-height: 60px;
min-height: 60px;
}
QPushButton:enabled { 
color: #FFFFFF;
background: #0F9FD6;
border-radius: 8px;
}

"""
        startStopButton.text = "Start"
        startStopButton.isFlat = false
        verticalLayout.add(widget: startStopButton)
        verticalSpacer_3 = QSpacerItem(width: 20, height: 40, horizontalPolicy: .Minimum, verticalPolicy: .Fixed)
        verticalLayout.add(item: verticalSpacer_3)
        centerButton = QPushButton(parent: frameButtons)
        centerButton.name = "centerButton"
        centerButton.sizePolicy = QSizePolicy(horizontal: .Expanding, vertical: .Fixed)
        centerButton.minimumSize = QSize(width: 62, height: 62)
        centerButton.styleSheet = """
QPushButton {
opacity: 0.94;
max-height: 60px;
min-height: 60px;
}
QPushButton:enabled { 
color: #FFFFFF;
background: #0F9FD6;
border-radius: 8px;
}

"""
        centerButton.text = "Center"
        centerButton.isFlat = false
        verticalLayout.add(widget: centerButton)
        verticalSpacer = QSpacerItem(width: 20, height: 40, horizontalPolicy: .Minimum, verticalPolicy: .Expanding)
        verticalLayout.add(item: verticalSpacer)
        horizontalLayout_2 = QHBoxLayout(parent: nil)
        horizontalLayout_2.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
        horizontalLayout_2.spacing = 0
        plusButton = QPushButton(parent: frameButtons)
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
        horizontalSpacer_2 = QSpacerItem(width: 40, height: 20, horizontalPolicy: .Expanding, verticalPolicy: .Minimum)
        horizontalLayout_2.add(item: horizontalSpacer_2)
        minusButton = QPushButton(parent: frameButtons)
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
        verticalLayout.add(layout: horizontalLayout_2)
        horizontalLayout_4.add(widget: frameButtons)
        verticalLayout_3.add(layout: horizontalLayout_4)
        self.centralWidget = centralwidget
        statusBar = QStatusBar(parent: self)
        statusBar.name = "statusBar"
        statusBar.styleSheet = """
font-family: Rubik;
font-style: normal;
font-weight: 500;
font-size: 14px;
color: white;
"""
    }
}
