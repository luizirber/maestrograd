#include "xfcapp.ui"
#include <xfc/gtk/accelgroup.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/menubar.hh>
#include <xfc/gtk/stock.hh>
#include <xfc/gtk/toolbar.hh>
#include <xfc/glib/error.hh>
#include <iostream>

XfcApp::XfcApp()
{
    // Set the window title and default size    
    set_title("XfcApp");
    set_default_size(500, 500);
    
    // Create the action group and add the actions
    action_group = new Gtk::ActionGroup("XfcAppActions");
    add_actions();    
    
    // Create the user interface manager and insert the action group    
    manager = new Gtk::UIManager;
    manager->insert_action_group(*action_group);
    
    // Associate the user interface manager's AccelGroup with the window
    add_accel_group(manager->get_accel_group());
    
    // Create main vertical box and add to window    
    Gtk::VBox *main_vbox = new Gtk::VBox;
    add(*main_vbox);
    
    // Load XML description of the menus and toolbar from the definition string.
    G::Error error;    
    if (!manager->add_ui_from_string(ui_info, -1, &error))
    {
        std::cout << "building menus and toolbar failed: << " << error.message() << std::endl;
    }

    // Get a pointer to the menubar and pack it into main_vbox    
    Gtk::Widget *menubar = manager->get_widget("/MenuBar");
    main_vbox->pack_start(*menubar, false);    
    menubar->show();
    
    // Get a pointer to the toolbar and pack it into main_vbox    
    Gtk::Toolbar *toolbar = static_cast<Gtk::Toolbar*>(manager->get_widget("/ToolBar"));
    toolbar->set_tooltips(true);
    main_vbox->pack_start(*toolbar, false)    ;
    toolbar->show();
    // Show main_vbox so it's visible    
    main_vbox->show();
}

XfcApp::~XfcApp()
{
}

void
XfcApp::add_actions()
{
    using namespace Gtk;
    using namespace sigc;
    
    action_group->add("FileMenu", "_File");
    action_group->add("EditMenu", "_Edit");
    action_group->add("HelpMenu", "_Help");

    Action *action = action_group->add("New", "_New", StockId::NEW, AccelKey("<control>N"), "Create a new file");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_new));
    action = action_group->add("Open", "_Open", StockId::OPEN, AccelKey("<control>O"), "Open a file");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_open));
    action = action_group->add("Save", "_Save", StockId::SAVE, AccelKey("<control>S"), "Save current file");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_save));
    action = action_group->add("SaveAs", "Save _As...", StockId::SAVE, "Save to a file");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_save_as));
    action = action_group->add("Quit", "_Quit", StockId::QUIT, AccelKey("<control>Q"), "Quit");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_file_quit));
    action = action_group->add("Cut", "C_ut", StockId::CUT, AccelKey("<control>X"), "Cut the selection");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_cut));
    action = action_group->add("Copy", "_Copy", StockId::COPY, AccelKey("<control>C"), "Copy the selection");
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_copy));
    action = action_group->add("Paste", "_Paste", StockId::PASTE, AccelKey("<control>V"), "Paste the clipboard");
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_paste));
    action = action_group->add("Clear", "C_lear", StockId::CLEAR, "Clear the selection");
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_clear));
    action = action_group->add("Preferences", "Prefere_nces", StockId::PREFERENCES, "Configure the application");
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_edit_preferences));
    action = action_group->add("About", "_About", AccelKey("<control>A"), "About");    
    action->signal_activate().connect(mem_fun(this, &XfcApp::on_help_about));
}

void
XfcApp::on_file_new()
{
    std::cout << "You activated action: New" << std::endl;
}

void
XfcApp::on_file_open()
{
    std::cout << "You activated action: Open" << std::endl;
}

void
XfcApp::on_file_save()
{
    std::cout << "You activated action: Save" << std::endl;
}

void
XfcApp::on_file_save_as()
{
    std::cout << "You activated action: SaveAs" << std::endl;
}

void
XfcApp::on_file_quit()
{
    dispose();
}

void
XfcApp::on_edit_cut()
{
    std::cout << "You activated action: Cut" << std::endl;
}

void
XfcApp::on_edit_copy()
{
    std::cout << "You activated action: Copy" << std::endl;
}

void
XfcApp::on_edit_paste()
{
    std::cout << "You activated action: Paste" << std::endl;
}

void
XfcApp::on_edit_clear()
{
    std::cout << "You activated action: Clear" << std::endl;
}

void
XfcApp::on_edit_preferences()
{
    std::cout << "You activated action: Preferences" << std::endl;
}

void
XfcApp::on_help_about()
{
    std::cout << "You activated action: About" << std::endl;
}

int main (int argc, char *argv[])
{
    using namespace Main;

    init(&argc, &argv);

    XfcApp window;
    window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
    window.show();

    run();
    return 0;
}
