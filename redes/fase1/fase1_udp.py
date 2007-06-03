import socket
import select
import sys

class conexao(object):
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.conn_pool = {}
        self.counter = 0
        self.mode = 'server'

    def to_physical_layer(self, key, msg):
        if self.mode == 'server':
            self.conn_pool[str(key)].send(msg)
        elif self.mode == 'client':
            self.sock.send(msg)

    def from_physical_layer(self, key):
        if self.mode == 'server':
            return self.conn_pool[key].recv(1024)
        elif self.mode == 'client':
            return self.sock.recv(1024)

    def start_client(self, addr, port):
        self.sock.connect((str(addr), int(port)))
        self.sock.setblocking(0)
        self.mode = 'client'

    def start_server(self, port):
        self.sock.bind((socket.gethostname(), int(port)))
        self.sock.listen(1)
        self.mode = 'server'
        conn, addr = self.sock.accept()
        self.conn_pool[str(self.counter)] = conn
        self.sock.setblocking(0)
        self.conn_pool[str(self.counter)].setblocking(0)
        self.counter += 1

    def run(self):
        while(1):
            if self.mode == 'server':
                read, write, err = select.select([self.conn_pool[str(0)]],
                                                 [self.conn_pool[str(0)]],
                                                 [self.conn_pool[(str(0))]])
                if read:
                    print "mensagem recebida: ", self.from_physical_layer("0")
                elif write:
                    msg = raw_input("DESTINO|mensagem : ")
                    try:
                        who, msg = msg.split("|")
                    except ValueError:
                        print "mensagem no formato errado"
                    finally:
                        self.to_physical_layer(who, msg)
            elif self.mode == 'client':
                read, write, err = select.select([self.sock],
                                                 [self.sock],
                                                 [self.sock])
                if read:
                    print "mensagem recebida: ", self.from_physical_layer(0)
                elif write:
                    msg = raw_input("mensagem : ")
                    self.to_physical_layer(0, msg)
