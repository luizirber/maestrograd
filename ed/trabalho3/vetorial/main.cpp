#include "janela.h"
#include <xfc/gdk/window.hh>

int main (int argc, char *argv[])
{
    using namespace Main;

    init(&argc, &argv);

    JanelaPrincipal window;
    window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
    window.show();

    run();
    return 0;
}
