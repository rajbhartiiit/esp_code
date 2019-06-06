import socket
import sys
from time import sleep

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# server_address = ('192.168.0.102', 8080)
server_address = ('192.168.1.107', 8080)
message = "Hi"

while True:
    print message
    sent = sock.sendto(message, server_address)
    sock.settimeout(25)
    print >>sys.stderr, 'waiting to receive'
    data, server = sock.recvfrom(4096)
    print data

    sleep(1)