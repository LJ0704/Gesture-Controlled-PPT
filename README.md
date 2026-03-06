[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/M-vWKnx0)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=21935782&assignment_repo_type=AssignmentRepo)
# final-project-f25

Folder Structure: 

python_script : Python script for gesture controlled PPT 
Video_Image : Images and Video of Testing
Src: Bluetooth_JDY31.c
     Gesture_sensor.c
     UART2_Init.c
     main.c
README file

Code Credits: 
Dean's Book

Reference:

STM32F091RC Reference Manual
STM32F091RC Data Sheet
STM32F091RC User Manual
XYZ Interactive Technologies, ZX SparkFun Sensor Datasheet
GestureSense XZ01 Sensor I2C Register Map
JDY-31 Bluetooth Module Data Sheet

Setup Information:

Connections:

JDY31 Module Connection
PA9 - JDY31 RX
PA10 - JDY31 TX
3.3V - VCC
GND - GND

ZX Gesture Sensor I2C Connections 
PA0 - DR Data Ready
PB8 - SCL
PB9 - SDA
5V - VCC
GND - GND

Test Information:
There is an #define for Running Test Cases: #define TEST_CODE
For checking if Bluetooth is connected 
For checking if the ZX Gesture Sensor is working and returns right version information and register version
Screen shots of the results are added in the github repository


Information for Controlling the PPT(pyhton script setup):
You need to install pyserial and pyautogui libraries to run the automatic PPT controller using gesture.

Run this in your command prompt:
pip install pyserial
pip install pyautogui

And then to run the Python script you will need to run 
py ppt_controller.py

You might need to change the COM PORT Number in Python Script ppt_controller.py 
Need to change in this
# Configure the UART
bluetooth_port = 'COM13'  # Adjust this as your system