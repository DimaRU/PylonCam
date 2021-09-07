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
    var groupBox: QGroupBox!
    var verticalLayout_2: QVBoxLayout!
    var laplacianButton: QRadioButton!
    var sobelButton: QRadioButton!
    var varianceButton: QRadioButton!
    var scrollArea: QScrollArea!
    var imageLabel: QLabel!
    var frameButtons: QFrame!
    var layoutWidget1: QWidget!
    var horizontalLayoutButtons: QHBoxLayout!
    var startStopButton: QPushButton!
    var horizontalSpacer_3: QSpacerItem!
    var centerButton: QPushButton!
    var horizontalSpacer_2: QSpacerItem!
    var plusButton: QPushButton!
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
        verticalLayout = QVBoxLayout(parent: centralwidget)
        verticalLayout.contentsMargins = QMargins(left: 20, top: 10, right: 20, bottom: 2)
        verticalLayout.spacing = 8
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
        bestLabel.text = "best: 0"
        bestLabel.alignment = [.AlignLeading, .AlignLeft, .AlignVCenter]
        horizontalLayout.add(widget: bestLabel)
        horizontalLayout_3.add(layout: horizontalLayout)
        groupBox = QGroupBox(parent: centralwidget)
        groupBox.name = "groupBox"
        groupBox.styleSheet = """
QRadioButton {
  font-family: Rubik;
  font-style: normal;
  font-weight: 500;  color: white;
}
QRadioButton::indicator {
  color: white;

//  width:               10px;
//  height:              10px;
//   border-radius: 7px;
}
QRadioButton::indicator:checked {
  color: white;
   background-color: white;
// ;   border:                 2px solid white;
}
QRadioButton::indicator:unchecked {
   background-color:  white;
// ;   border:                 2px solid white;
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
        verticalLayout_2.contentsMargins = QMargins(left: 0, top: 0, right: 0, bottom: 0)
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
        horizontalLayout_3.add(widget: groupBox)
        verticalLayout.add(layout: horizontalLayout_3)
        scrollArea = QScrollArea(parent: centralwidget)
        scrollArea.name = "scrollArea"
        scrollArea.widgetResizable = false
        imageLabel = QLabel()
        imageLabel.name = "imageLabel"
        imageLabel.geometry = QRect(x: 0, y: 0, width: 1001, height: 612)
        imageLabel.sizePolicy = QSizePolicy(horizontal: .Ignored, vertical: .Ignored)
        imageLabel.scaledContents = true
        scrollArea.setWidget(imageLabel)
        verticalLayout.add(widget: scrollArea)
        frameButtons = QFrame(parent: centralwidget)
        frameButtons.name = "frameButtons"
        frameButtons.sizePolicy = QSizePolicy(horizontal: .Minimum, vertical: .Minimum)
        frameButtons.minimumSize = QSize(width: 174, height: 95)
        frameButtons.maximumSize = QSize(width: 16777215, height: 95)
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
        layoutWidget1.geometry = QRect(x: 10, y: 10, width: 1001, height: 72)
        horizontalLayoutButtons = QHBoxLayout(parent: layoutWidget1)
        horizontalLayoutButtons.contentsMargins = QMargins(left: -1, top: -1, right: 10, bottom: -1)
        horizontalLayoutButtons.spacing = 30
        startStopButton = QPushButton(parent: layoutWidget1)
        startStopButton.name = "startStopButton"
        startStopButton.minimumSize = QSize(width: 162, height: 62)
        startStopButton.maximumSize = QSize(width: 62, height: 62)
        startStopButton.styleSheet = """
QPushButton {
opacity: 0.94;
max-width: 160px;
max-height: 60px;
min-width: 160px;
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
        horizontalLayoutButtons.add(widget: startStopButton)
        horizontalSpacer_3 = QSpacerItem(width: 40, height: 20, horizontalPolicy: .Expanding, verticalPolicy: .Minimum)
        horizontalLayoutButtons.add(item: horizontalSpacer_3)
        centerButton = QPushButton(parent: layoutWidget1)
        centerButton.name = "centerButton"
        centerButton.minimumSize = QSize(width: 162, height: 62)
        centerButton.maximumSize = QSize(width: 62, height: 62)
        centerButton.styleSheet = """
QPushButton {
opacity: 0.94;
max-width: 160px;
max-height: 60px;
min-width: 160px;
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
        horizontalLayoutButtons.add(widget: centerButton)
        horizontalSpacer_2 = QSpacerItem(width: 40, height: 20, horizontalPolicy: .Expanding, verticalPolicy: .Minimum)
        horizontalLayoutButtons.add(item: horizontalSpacer_2)
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
        horizontalLayoutButtons.add(widget: plusButton)
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
        horizontalLayoutButtons.add(widget: minusButton)
        verticalLayout.add(widget: frameButtons)
        self.centralWidget = centralwidget
    }
}
