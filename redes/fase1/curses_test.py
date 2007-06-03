import curses
import curses.ascii
import time

from fase1 import conexao

class persistent_data(object):
    def __init__(self, size=4):
        self.conn_buffer = []
        self.current_buffer = []
        self.show_size = size

    def append(self, string):
        self.conn_buffer.append(string)
        if len(self.conn_buffer) > self.show_size:
            self.current_buffer = self.conn_buffer[len(self.conn_buffer) \
                                                   - self.show_size:]
        else:
            self.current_buffer = self.conn_buffer

    def set_show_size(self, new_size):
        self.show_size = new_size

def main(stdscr):
    curses.echo()
    connection = conexao()
    data = persistent_data()

    stdscr_y, stdscr_x = stdscr.getmaxyx()
    read = stdscr.subwin(stdscr_y - 3, stdscr_x, 0, 0)
    read.box()
    read.refresh()

    write = stdscr.subwin(3, stdscr_x, stdscr_y - 3, 0)
    write.box()

    valid_option = False
    while not valid_option:
        write.clear()
        write.box()
        msg = 'Este sera o servidor? S/N : '
        write.addstr(1, 2, msg)
        result = write.getstr(1, 2 + len(msg))
        if result == 'S':
            write.clear()
            write.box()
            msg = 'Entre com a porta a ser usada: '
            write.addstr(1, 2, msg)
            port = write.getstr(1, 2 + len(msg))
            connection.start_server(port)
            valid_option = True
        elif result == 'N':
            write.clear()
            write.box()
            msg = 'Entre com o ENDERECO:PORTA | '
            write.addstr(1, 2, msg)
            location = write.getstr(1, 2 + len(msg))
            addr, port = location.split(":")
            connection.start_client(addr, port)
            valid_option = True

    while(1):
        write.clear()
        write.box()

        read.clear()
        read.box()
        data.set_show_size(stdscr_y - 5)

        i = 1
        for string in data.current_buffer:
            read.addstr(i, 2, string)
            i += 1
        read.refresh()

        msg = ''
        send = False
        i = 1;
        while not send:
            c = write.getch(1, i + 1)
            c = chr(c)
            if c in '\n':
                data.append("LOCAL: " + msg)
                connection.to_physical_layer(0, msg)
                send = True
            elif curses.ascii.isalnum(c):
                msg += curses.ascii.unctrl(c)
                i += 1


#        msg = write.getstr(1, 2)
#        data.append(msg)

if __name__ == '__main__':
    curses.wrapper(main)
