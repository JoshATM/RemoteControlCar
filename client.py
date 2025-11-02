import socket
import time
import keyboard

arduino_ip = "192.168.1.156"
arduino_port = 80

connection = None
last_command = None

def connect():
    global connection
    try:
        connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        connection.connect((arduino_ip, arduino_port))
        return True
    except:
        return False

def send(command):
    global last_command
    
    if command == last_command:
        return
    
    last_command = command
    
    try:
        connection.send(f"{command}\n".encode())
        connection.recv(1024)
        if command == "FORWARD":
            print("forward")
        elif command == "BACKWARD":
            print("backward")
        elif command == "LEFT":
            print("left")
        elif command == "RIGHT":
            print("right")
    except:
        pass

def cleanup():
    global connection
    if connection:
        try:
            send("STOP")
        except:
            pass
        connection.close()

if not connect():
    exit()

try:
    while True:
        if keyboard.is_pressed('esc'):
            break
        
        if keyboard.is_pressed('w') or keyboard.is_pressed('up'):
            send("FORWARD")
        elif keyboard.is_pressed('s') or keyboard.is_pressed('down'):
            send("BACKWARD")
        elif keyboard.is_pressed('a') or keyboard.is_pressed('left'):
            send("LEFT")
        elif keyboard.is_pressed('d') or keyboard.is_pressed('right'):
            send("RIGHT")
        else:
            send("STOP")
        
        time.sleep(0.05)

except KeyboardInterrupt:
    pass
finally:
    cleanup()
