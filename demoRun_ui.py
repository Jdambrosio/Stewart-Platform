# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'demoRun.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import sys # add necessary import
import glob, os # add necessary import

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1217, 1128)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout.setObjectName("gridLayout")
        spacerItem = QtWidgets.QSpacerItem(1170, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 5, 0, 1, 3)
        spacerItem1 = QtWidgets.QSpacerItem(1170, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem1, 3, 0, 1, 3)
        self.chooseCSV = QtWidgets.QPushButton(self.centralwidget)
        self.chooseCSV.setObjectName("chooseCSV")
        self.gridLayout.addWidget(self.chooseCSV, 2, 0, 1, 1)
        self.listCSV = QtWidgets.QListWidget(self.centralwidget)
        self.listCSV.setObjectName("listCSV")
        self.gridLayout.addWidget(self.listCSV, 1, 1, 2, 2)
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.importCSV = QtWidgets.QPushButton(self.centralwidget)
        self.importCSV.setObjectName("importCSV")
        self.gridLayout.addWidget(self.importCSV, 1, 0, 1, 1)
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout.setObjectName("verticalLayout")
        self.startRun = QtWidgets.QPushButton(self.groupBox)
        self.startRun.setObjectName("startRun")
        self.verticalLayout.addWidget(self.startRun)
        self.pauseRun = QtWidgets.QPushButton(self.groupBox)
        self.pauseRun.setObjectName("pauseRun")
        self.verticalLayout.addWidget(self.pauseRun)
        self.stopRun = QtWidgets.QPushButton(self.groupBox)
        self.stopRun.setObjectName("stopRun")
        self.verticalLayout.addWidget(self.stopRun)
        self.resetSystem = QtWidgets.QPushButton(self.groupBox)
        self.resetSystem.setObjectName("resetSystem")
        self.verticalLayout.addWidget(self.resetSystem)
        self.gridLayout.addWidget(self.groupBox, 4, 2, 1, 1)
        self.groupBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_2.setObjectName("groupBox_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.groupBox_2)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.speedSelectionWindow = QtWidgets.QTextEdit(self.groupBox_2)
        self.speedSelectionWindow.setObjectName("speedSelectionWindow")
        self.verticalLayout_2.addWidget(self.speedSelectionWindow)
        self.speedDial = QtWidgets.QDial(self.groupBox_2)
        self.speedDial.setObjectName("speedDial")
        self.verticalLayout_2.addWidget(self.speedDial)
        self.speedSelect = QtWidgets.QPushButton(self.groupBox_2)
        self.speedSelect.setObjectName("speedSelect")
        self.verticalLayout_2.addWidget(self.speedSelect)
        self.gridLayout.addWidget(self.groupBox_2, 4, 1, 1, 1)
        self.frame = QtWidgets.QFrame(self.centralwidget)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.frame)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.progressBar = QtWidgets.QProgressBar(self.frame)
        self.progressBar.setProperty("value", 24)
        self.progressBar.setObjectName("progressBar")
        self.gridLayout_2.addWidget(self.progressBar, 1, 0, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.frame)
        self.label_2.setObjectName("label_2")
        self.gridLayout_2.addWidget(self.label_2, 0, 0, 1, 1)
        self.gridLayout.addWidget(self.frame, 6, 1, 1, 2)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1217, 47))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.chooseCSV.setText(_translate("MainWindow", "Select"))
        self.label.setText(_translate("MainWindow", "Motion Profiles"))
        self.importCSV.setText(_translate("MainWindow", "Import"))
        self.groupBox.setTitle(_translate("MainWindow", "Operation"))
        self.startRun.setText(_translate("MainWindow", "Start"))
        self.pauseRun.setText(_translate("MainWindow", "Pause"))
        self.stopRun.setText(_translate("MainWindow", "Stop"))
        self.resetSystem.setText(_translate("MainWindow", "Reset"))
        self.groupBox_2.setTitle(_translate("MainWindow", "Speed"))
        self.speedSelect.setText(_translate("MainWindow", "Select"))
        self.label_2.setText(_translate("MainWindow", "Current Progress"))
        self.importCSV.clicked.connect(self.displayCSV)
        self.chooseCSV.clicked.connect(self.selectCSVFile)
        
        
    def displayCSV(self):
        '''refresh file list in drop down menu that can be imported to program'''
        self.listCSV.clear()
        os.chdir(os.getcwd())
        for file in glob.glob("*.csv"):
            self.listCSV.addItem(str(file))    
            
    def selectCSVFile(self):
        '''import a csv file from the current operating directory'''
        with open (self.listCSV.currentText(), 'r') as csvDataInput:
            lines = csvDataInput.readlines()
        for line in lines:
            split_str = line.split(',')  # seperate line entries into three lists
            try:
                 servo1 = float(split_str[0])
                 servo2 = float(split_str[1])
                 servo3 = float(split_str[2])
                 servo4 = float(split_str[3])
                 servo5 = float(split_str[4])
                 servo6 = float(split_str[5])                 

            except (IndexError, ValueError, TypeError):  # ignore invalid entries
                pass
                print("error")
            else:
                self.servoData.append([servo1,servo2,servo3,servo4,servo5,servo6])
                #self.serWindowPrint(self.coordinateData[0][0])
        
if __name__ == '__main__':
    '''main of the GUI, make new UI window, start event loop, and exit when done'''

    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(window)
    window.show()
    sys.exit(app.exec_())
        

