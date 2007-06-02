import socket
import select

SERVER = 'localhost'
PORT = 3456

class test_server(object):
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client = socker.socket(socket.AF_INET, socket.SOCK_STREAM)

        _ready = threading.Event()
        _thread = threading.Thread(target=accept_reply)
        _thread.setDaemon(True)
        _thread.start()
        _ready.wait(5)

    def accept_reply(self):
           self._sock.listen(1)
           self._ready.set()
           self._sock.settimeout(5)
           try:
               conn, address = self._sock.accept()
               conn.setblocking(True)
               while not self.received_bytes:
                   self.received_bytes = conn.recv(4096)
           except socket.timeout:
               self._sock.close()


