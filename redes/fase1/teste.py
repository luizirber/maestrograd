import socket
import threading
import sys

SERVER = 'localhost'
CLIENT = 'localhost'
PORT = 22654

class application(object):
    def __init__(self):
        self._ready = threading.Event()

        print 'DEBUG: inicializando sender'
        self.sender = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sender.bind((SERVER, PORT))
        self.sender.setblocking(0)
        sender_thread = threading.Thread(name="sender", target=self.to_physical_layer)
        sender_thread.setDaemon(True)

        self._ready.wait(5)

        print 'DEBUG: inicializando receiver'
        self.receiver = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.receiver.setblocking(0)
        receiver_thread = threading.Thread(name="receiver", target=self.from_physical_layer)

        sender_thread.start()
        receiver_thread.start()

    def from_physical_layer(self):
        print 'DEBUG: servidor recebendo mensagem'
        self.sender.listen(1)
        self._ready.set()
        conn, addr = self.sender.accept()
        conn.setblocking(True)
        msg = conn.recv(1024)

        return msg

    def to_physical_layer(self):
        while (1):
            msg = raw_input("String: ")
            self.sender.connect((CLIENT, PORT))
            msg = self.sender.send(msg)

if __name__ == "__main__":
    s = application()
