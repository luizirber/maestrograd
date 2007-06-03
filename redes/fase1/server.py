# Echo server program
import socket

HOST = '10.0.0.3'                 # Symbolic name meaning the local host
PORT = 5007              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
conn, addr = s.accept()
conn.setblocking(1)
print 'Connected by', addr, "in port", PORT
while (1):
    data = conn.recv(1024)
    if not data: break
    #conn.send(data)
    print 'recebeu: ', data
