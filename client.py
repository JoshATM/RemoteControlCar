import socket

class WiFiClient:
    def __init__(self):
        self.ip_address = '192.168.1.156' 
        self.port = 80
        self.timeout = 2

    def send_command(self, command):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(self.timeout)
            sock.connect((self.ip_address, self.port))
            sock.send((command + '\n').encode())
            sock.close()
            return True
        except:
            return False
