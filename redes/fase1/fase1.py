import socket

class programa(object):
    def __init__(self):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.conn_pool = {}
        self.counter = 0

    def to_physical_layer(self, key, msg):
        self.conn_pool[key].send(msg)

    def from_physical_layer(self):
        return self.client.recv(1024)

    def main(self):
        port = raw_input("Insira a porta a ser usada pelo servidor: ")
        try:
            self.server.bind((socket.gethostname(), int(port)))
        except:
            print "nao foi possivel iniciar o servidor"

        self.server.listen(1)
        conn, addr = self.server.accept()
        self.conn_pool[str(self.counter)] = conn
        self.counter += 1
        while(1):
            print "escreva mensagem no formato"
            msg = raw_input("DESTINO|mensagem : ")
            try:
                who, msg = msg.split("|")
            except ValueError:
                print "mensagem no formato errado"
            finally:
                self.to_physical_layer(who, msg)
                print
            print "mensagens recebidas: ", self.conn_pool[str(0)].recv(1024)

if __name__ == "__main__":
    p = programa()
    p.main()
