import serial
import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt
from PyQt5.QtGui import *
from PyQt5 import *


# Top-left - motor controls
# Top-right - arm controls
# Bottom - sensors/cameras
# on and off for motors and arm
# buttons and keyboard control for motor and arms


commPort = "/dev/ttyACM0"
serMotor = serial.Serial(commPort, baudrate=115200)


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.UI()

    def UI(self):
        self.setWindowTitle("URC Gui")
        self.setGeometry(1600, 0, 1200, 900)

        main_layout = QVBoxLayout()
        top_layout = QHBoxLayout()
        top_left_layout = QGridLayout()
        top_right_layout = QGridLayout()
        bottom_layout = QGridLayout()

        forward_button = QPushButton("Forward\nW")
        forward_button.clicked.connect(self.forwardButton)
        left_button = QPushButton("Left\nA")
        left_button.clicked.connect(self.leftButton)
        backwards_button = QPushButton("Backwards\nS")
        backwards_button.clicked.connect(self.backwardsButton)
        right_button = QPushButton("Right\nD")
        right_button.clicked.connect(self.rightButton)
        speed_up_button = QPushButton("Speed Up\nShift")
        speed_up_button.clicked.connect(self.speedupButton)
        stop_button = QPushButton("Stop\nEsc")
        stop_button.clicked.connect(self.stopButton)
        enable_button = QPushButton("Enable")
        disable_button = QPushButton("Disable")

        top_left_layout.addWidget(forward_button, 0, 1)
        top_left_layout.addWidget(left_button, 1, 0)
        top_left_layout.addWidget(backwards_button, 1, 1)
        top_left_layout.addWidget(right_button, 1, 2)
        top_left_layout.addWidget(speed_up_button, 2, 0)
        top_left_layout.addWidget(stop_button, 3, 0)
        top_left_layout.addWidget(enable_button, 2, 2)
        top_left_layout.addWidget(disable_button, 3, 2)
        top_right_layout.addWidget(QLabel("arm controls here"), 0, 0)
        bottom_layout.addWidget(QLabel("cameras/sensors here"), 0, 0)

        top_layout.addLayout(top_left_layout)
        top_layout.addLayout(top_right_layout)
        main_layout.addLayout(top_layout)
        main_layout.addLayout(bottom_layout)

        self.setLayout(main_layout)

    def forwardButton(self, event):
        self.motorEvent("W")

    def leftButton(self, event):
        self.motorEvent("A")

    def backwardsButton(self, event):
        self.motorEvent("S")

    def rightButton(self, event):
        self.motorEvent("D")

    def speedupButton(self, event):
        self.motorEvent("shift")

    def stopButton(self, event):
        self.motorEvent("esc")

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_W:
            self.motorEvent("W")
        if event.key() == Qt.Key_S:
            self.motorEvent("S")
        if event.key() == Qt.Key_A:
            self.motorEvent("A")
        if event.key() == Qt.Key_D:
            self.motorEvent("D")
        if event.key() == Qt.Key_Shift:
            self.motorEvent("shift")
        if event.key() == Qt.Key_Escape:
            self.motorEvent("esc")

    def motorEvent(self, keyEvent):
        if keyEvent == "W":
            print("Foward")
            self.foward()
        if keyEvent == "S":
            print("backwards")
            self.backward()
        if keyEvent == "A":
            print("Left")
            self.right()
        if keyEvent == "D":
            print("Right")
            self.left()
        if keyEvent == "shift":
            print("Speed Up")
            self.speed_up()
        if keyEvent == "esc":
            print("stop")
            self.stop()

    def foward(self):
        serMotor.write("1".encode())

    def backward(self):
        serMotor.write("2".encode())

    def left(self):
        serMotor.write("3".encode())

    def right(self):
        serMotor.write("4".encode())

    def speed_up(self):
        serMotor.write("5".encode())

    def stop(self):
        serMotor.write("6".encode())


"""
# commPort2 = '/dev/ttyACM1'
# serArm = serial.Serial(commPort2, baudrate = 115200)
class ArmWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.UI_Arm()

    def UI_Arm(self):
        self.setWindowTitle("Arm Control")
        self.setGeometry(1600, 950, 600, 350)

        self.text = QLabel("Claw Opened = X || Claw Closed = C", self)
        self.text2 = QLabel("Base Shift Right = D || Base Shift Left = A", self)
        self.text3 = QLabel("Fowards:", self)
        self.text4 = QLabel(
            "Bottom Joint = U || Middle Joint = I || Top Joint = O", self
        )
        self.text5 = QLabel("Backwards: ", self)
        self.text6 = QLabel(
            "Bottom Joint = J || Middle Joint = K || Top Joint = L", self
        )
        self.text7 = QLabel("Wrist Clockwise = Y || Wrist Counterclockwise = H", self)
        self.text8 = QLabel("Stop All = Escape", self)

        self.text.setFont(QFont("Arial", 15))
        self.text.move(50, 25)
        self.text2.setFont(QFont("Arial", 15))
        self.text2.move(50, 75)
        self.text3.setFont(QFont("Arial", 15))
        self.text3.move(50, 120)
        self.text4.setFont(QFont("Arial", 13))
        self.text4.move(50, 140)
        self.text5.setFont(QFont("Arial", 15))
        self.text5.move(50, 170)
        self.text6.setFont(QFont("Arial", 13))
        self.text6.move(50, 190)
        self.text7.setFont(QFont("Arial", 15))
        self.text7.move(50, 230)
        self.text8.setFont(QFont("Arial", 15))
        self.text8.move(50, 260)

        closeButton = QPushButton("Close", self)
        closeButton.clicked.connect(self.close_on_click)
        closeButton.resize(150, 50)
        closeButton.move(225, 275)

    def close_on_click(self):
        self.close()

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_0:
            print("Claw Opened")
            # self.claw_open()
        if event.key() == Qt.Key_9:
            print("Claw Closed")
            # self.claw_closed()
        if event.key() == Qt.Key_M:
            print("Base Shift Right")
            # self.base_right()
        if event.key() == Qt.Key_N:
            print("Bace Shift Left")
            # self.base_left()
        if event.key() == Qt.Key_U:
            print("Bottom Joint Foward")
            # self.bottom_joint_foward()
        if event.key() == Qt.Key_J:
            print("Bottom Joint Backwards")
            # self.bottom_joint_backwards()
        if event.key() == Qt.Key_I:
            print("Middle Joint Foward")
            # self.middle_joint_foward()
        if event.key() == Qt.Key_K:
            print("Middle Joint Backwards")
            # self.middle_joint_backwards()
        if event.key() == Qt.Key_O:
            print("Middle Joint Foward")
            # self.top_joint_foward()
        if event.key() == Qt.Key_L:
            print("Middle Joint Backwards")
            # self.top_joint_backwards()
        if event.key() == Qt.Key_Y:
            print("Wrist Clockwise")
            # self.wrist_clockwise()
        if event.key() == Qt.Key_H:
            print("Wrist Counterclockwise")
            # self.wrist_counterclockwise()
        if event.key() == Qt.Key_Escape:
            print("Stop All")
            # self.stop_all()

    def claw_open(self):
        serArm.write("Claw Open".encode())
    
    def claw_closed(self):
        serArm.write("Claw Closed".encode)
    
    def base_right(self):
        serArm.write("Base Shift Right".encode)
    
    def base_left(self):
        serArm.write("Base Shift Left".encode)
    
    def bottom_joint_foward(self):
        serArm.write("Bottom Joint Foward".encode)

    def bottom_joint_backwards(self):
        serArm.write("Bottom Joint Backwards".encode)

    def middle_joint_foward(self):
        serArm.write("Middle Joint Foward".encode)

    def middle_joint_backwards(self):
        serArm.write("Middle Joint Backwards".encode)

    def top_joint_foward(self):
        serArm.write("Top Joint Foward".encode)

    def top_joint_backwards(self):
        serArm.write("Top Joint Backwards".encode)
    
    def stop_all(self):
        serArm.write("Stop All".encode)

    def wrist_clockwise():
        serArm.write("Wrist Clockwise".encode)

    def wrist_counterclockwise():
        serArm.write("Wrist Counterclockwise".encode)
"""


if __name__ == "__main__":
    app = QApplication(sys.argv)

    main = MainWindow()
    main.show()

    sys.exit(app.exec())
