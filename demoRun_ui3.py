# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'demoRun.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import sys # add necessary import
import glob, os # add necessary import
import serial
import serial.tools.list_ports 


class Ui_demoRun(object):
    def setupUi(self, demoRun):
        demoRun.setObjectName("demoRun")
        demoRun.resize(1217, 1128)
        self.centralwidget = QtWidgets.QWidget(demoRun)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setObjectName("label")
        self.gridLayout_2.addWidget(self.label, 0, 0, 1, 1)
        self.importCSV = QtWidgets.QPushButton(self.centralwidget)
        self.importCSV.setObjectName("importCSV")
        self.gridLayout_2.addWidget(self.importCSV, 1, 0, 1, 1)
        self.listCSV = QtWidgets.QListWidget(self.centralwidget)
        self.listCSV.setObjectName("listCSV")
        self.gridLayout_2.addWidget(self.listCSV, 1, 1, 2, 2)
        self.chooseCSV = QtWidgets.QPushButton(self.centralwidget)
        self.chooseCSV.setObjectName("chooseCSV")
        self.gridLayout_2.addWidget(self.chooseCSV, 2, 0, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(1170, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_2.addItem(spacerItem, 3, 0, 1, 3)
        self.groupBox_3 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_3.setObjectName("groupBox_3")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox_3)
        self.gridLayout.setObjectName("gridLayout")
        self.serialWindow = QtWidgets.QListWidget(self.groupBox_3)
        self.serialWindow.setObjectName("serialWindow")
        self.gridLayout.addWidget(self.serialWindow, 0, 0, 1, 1)
        self.serialConnect = QtWidgets.QPushButton(self.groupBox_3)
        self.serialConnect.setObjectName("serialConnect")
        self.gridLayout.addWidget(self.serialConnect, 1, 0, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox_3, 4, 0, 1, 1)
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
        self.gridLayout_2.addWidget(self.groupBox_2, 4, 1, 1, 1)
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
        self.gridLayout_2.addWidget(self.groupBox, 4, 2, 1, 1)
        spacerItem1 = QtWidgets.QSpacerItem(1170, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_2.addItem(spacerItem1, 5, 0, 1, 3)
        self.groupBox_5 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_5.setObjectName("groupBox_5")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.groupBox_5)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.progressBar = QtWidgets.QProgressBar(self.groupBox_5)
        self.progressBar.setProperty("value", 24)
        self.progressBar.setObjectName("progressBar")
        self.gridLayout_4.addWidget(self.progressBar, 0, 0, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox_5, 6, 0, 1, 1)
        self.groupBox_4 = QtWidgets.QGroupBox(self.centralwidget)
        self.groupBox_4.setObjectName("groupBox_4")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.groupBox_4)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.servoDataWindow = QtWidgets.QListView(self.groupBox_4)
        self.servoDataWindow.setObjectName("servoDataWindow")
        self.gridLayout_3.addWidget(self.servoDataWindow, 0, 0, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox_4, 6, 1, 1, 2)
        demoRun.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(demoRun)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1217, 47))
        self.menubar.setObjectName("menubar")
        demoRun.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(demoRun)
        self.statusbar.setObjectName("statusbar")
        demoRun.setStatusBar(self.statusbar)

        self.retranslateUi(demoRun)
        QtCore.QMetaObject.connectSlotsByName(demoRun)

    def retranslateUi(self, demoRun):
        _translate = QtCore.QCoreApplication.translate
        demoRun.setWindowTitle(_translate("demoRun", "MainWindow"))
        self.label.setText(_translate("demoRun", "Motion Profiles"))
        self.importCSV.setText(_translate("demoRun", "Import"))
        self.chooseCSV.setText(_translate("demoRun", "Select"))
        self.groupBox_3.setTitle(_translate("demoRun", "Com Port"))
        self.serialConnect.setText(_translate("demoRun", "Connect"))
        self.groupBox_2.setTitle(_translate("demoRun", "Speed"))
        self.speedSelect.setText(_translate("demoRun", "Select"))
        self.groupBox.setTitle(_translate("demoRun", "Operation"))
        self.startRun.setText(_translate("demoRun", "Start"))
        self.pauseRun.setText(_translate("demoRun", "Pause"))
        self.stopRun.setText(_translate("demoRun", "Stop"))
        self.resetSystem.setText(_translate("demoRun", "Reset"))
        self.groupBox_5.setTitle(_translate("demoRun", "Run Progress"))
        self.groupBox_4.setTitle(_translate("demoRun", "Servo Data"))
        self.importCSV.clicked.connect(self.displayCSV)
        self.chooseCSV.clicked.connect(self.selectCSVFile)
        self.ser_port =  None # default serial port
        self.refreshSerial() # load serial with avaible ports upon initialization
        self.servoData = [] # stores all servo data points from csv file as 6 X N matrix  
        self.serialConnect.clicked.connect(self.chooseSerial)


    
    def chooseSerial(self):
        '''choose the highlighted serial communication port'''
        '''Initialize the serial port before everything else'''

        if(self.ser_port == None): #ser_port initial setup

            try: # try to connect to specified serial port from drop down menu
            # Initialize the serial port before everything else
                self.ser_port = serial.Serial (self.serialWindow.currentText(), 115200, timeout = 0.2)
                self.ser_port.close() # default close port to protect from errors if port was left open
                self.ser_port.open()
                print("Connecting")
                print(self.ser_port.is_open)
                '''Change the color of the connect button to green when the serial connects'''
                palette = self.serialConnect.palette()
                role = self.serialConnect.backgroundRole() #choose whatever you like
                palette.setColor(role, QtGui.QColor('green'))
                self.serialConnect.setPalette(palette)
                self.serialConnect.setAutoFillBackground(True)


            except Exception as e:
                print("Failed to connect to device")
                print(str(e))

        elif(self.ser_port.is_open == False): # if program is running, but ser_port has been physically disconnected, reconnect

            try: # try to connect to specified serial port from drop down menu
                self.ser_port = serial.Serial (self.serialWindow.currentText(), 115200, timeout = 0.2)
                self.ser_port.open()
                print("Connecting")
                print(self.ser_port.is_open)
                '''Change the color of the connect button to green when the serial connects'''
                palette = self.serialConnect.palette()
                role = self.serialConnect.backgroundRole() #choose whatever you like
                palette.setColor(role, QtGui.QColor('green'))
                self.serialConnect.setPalette(palette)
                self.serialConnect.setAutoFillBackground(True)


            except Exception as e:
                print("Failed to reconnect to device")
                print(str(e))

        else: # if the serial port is already open, close it
            print("Disconnecting serial")
            self.ser_port.close()
            '''Change the color of the connect button back to grey when the serial disconnects'''
            palette = self.serialConnect.palette()
            role = self.serialConnect.backgroundRole() #choose whatever you like
            palette.setColor(role, QtGui.QColor('grey'))
            self.serialConnect.setPalette(palette)
            self.serialConnect.setAutoFillBackground(True)
            print(self.ser_port.is_open)
            self.ser_port = None
    
    
    def refreshSerial(self):
        '''refresh serial port device availible list for user to select from'''
        self.serialWindow.clear()
        list_of_avail_ports = (list(serial.tools.list_ports.comports()))
        for port in list_of_avail_ports:
            #self.serialDropDown.addItem(str(port).replace(' - n/a', ''))
            self.serialWindow.addItem(str(port)[:(str(port).find(' '))]) # remove extra stuff in port name string    
    
    
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
    ui = Ui_demoRun()
    ui.setupUi(window)
    window.show()
    sys.exit(app.exec_())

