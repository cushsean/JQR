import socket
import sys
import time

print("Hello World")

if len(sys.argv) != 3:
    print("Expected arguments: ip and port")
    sys.exit()

try:
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("Socket Created")
except:
    print("Failed to create socket.")
    sys.exit()

ip = sys.argv[1]
port = int(sys.argv[2])

print(ip)
print(port)

print("host: " + socket.gethostname())

try:
    sockfd.bind((ip, port))
    print("Bound successfully to: " + ip + ":" + str(port))
except:
    print("Failed to bind.")
    sockfd.close()
    sys.exit()

try:
    sockfd.listen(20)
    print("listening")
except:
    print("Failed to listen")
    sockfd.close()
    sys.exit()

while True:
    client, addr = sockfd.accept()
    print("Connection accepted from " + str(addr))
    client.send(('Welcome to Sockets in Python. Good Bye.').encode('utf-8'))
    client.close()
    break

sockfd.close()

print("SOCK_STREAM CLOSED. STARTING DATAGRAM.")

try:
    sockdg = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sockdg.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("Socket Created")
except:
    print("Failed to create Datagram")
    sys.exit()

time.sleep(2)

try:
    sockdg.sendto(('Here is a quick DGRAM').encode('utf-8'), (ip, port))
    print("DGRAM sent")
except:
    print("Failed to send DGRAM. Terminating Connection.")
    sockdg.close()
    sys.exit()

print("End of Transmission")
sockdg.close()