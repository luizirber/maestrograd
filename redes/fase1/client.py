# Echo client program
import socket

HOST = ''    # The remote host
PORT = 50007 # The same port as used by the server
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
while(1):
    try:
        msg = raw_input("entre com a string a ser enviada: ")
    except KeyboardInterrupt:
        print
        s.close()
        break
    s.send(msg)
    data = s.recv(1024)
    print 'Received', repr(data)
