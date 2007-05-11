#include <xfc/main.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/widgetsignals.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class DrawingArea : public Gtk::DrawingArea, protected Gtk::WidgetSignals
{
    Gdk::Pixmap *pixmap;

    void draw_brush(double x, double y);

protected:
    virtual bool on_expose_event(const Gdk::EventExpose& event);
    virtual bool on_configure_event(const Gdk::EventConfigure& event);
    virtual bool on_button_press_event(const Gdk::EventButton& event);
    virtual bool on_motion_notify_event(const Gdk::EventMotion& event);

public:
    DrawingArea();
    virtual ~DrawingArea();
};

class JanelaPrincipal : public Gtk::Window
{
public:
    JanelaPrincipal();
    virtual ~JanelaPrincipal();

    void on_file_new();
    void on_file_open();
    void on_file_save();
    void on_file_save_as();
    void on_file_quit();
    void on_edit_cut();
    void on_edit_copy();
    void on_edit_paste();
    void on_edit_clear();
    void on_edit_preferences();
    void on_help_about();
};
