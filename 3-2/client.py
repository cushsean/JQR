import socket
import sys

print("This is a client")

if len(sys.argv) != 3:
    print("ERROR: Expected arguments: ip and port")
    sys.exit()

try:
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("Sock created successfully")
except:
    print("ERROR: Failed to create socket. Terminating connection.")
    sys.exit()

ip = sys.argv[1]
port = int(sys.argv[2])

print("address " + ip + ":" + str(port))

try:
    sockfd.connect((ip, port))
    print("Connected to " + ip + ":" + str(port))
except:
    print("ERROR: Failed to create connection. Terminating connection.")
    sys.exit()

print((sockfd.recv(128)).decode('utf-8'))

sockfd.close()

print("Socket closed. Starting DATAGRAM.")

try:
    sockdg = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sockdg.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("Datagram socket created.")
except:
    print("Failed to create datagram socket. Terminating connection.")
    sys.exit()

try:
    sockdg.bind((ip, port))
    print("Bound successfully to: " + ip + ":" + str(port))
except:
    print("Failed to bind datagram")
    sockdg.close()
    sys.exit()

try:
    buf, (ip, port) = sockdg.recvfrom(128)

except:
    print("Failed to recv. Terminating connection.")
    sockdg.close()
    sys.exit()

msg = buf.decode('utf-8')
print("Received message from: " + ip + ":" + str(port))
print(msg)

print("End of Transmission")
sockdg.close()