import serial
import pyautogui
import time

# Configure the UART
bluetooth_port = 'COM13'  # Adjust this as your system
baud_rate = 9600
ser = serial.Serial(bluetooth_port, baud_rate)

print("Waiting for gestures...")

while True:
    if ser.in_waiting > 0:
        gesture = ser.readline().decode('utf-8').strip()  # Read the gesture

        if gesture == "Right Swipe":#Read from Bluetooth Terminal
            pyautogui.press('right')  # Move to the next slide
            print("Right Swipe detected. Moving to next slide.")
        
        elif gesture == "Left Swipe":#Read from Bluetooth Terminal
            pyautogui.press('left')  # Move to the previous slide
            print("Left Swipe detected. Moving to previous slide.")

    time.sleep(0.1)  # Check every 100ms for new gesture data