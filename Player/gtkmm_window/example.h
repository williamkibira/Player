#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class PlayerWindow : public Gtk::Window
{
public:
  PlayerWindow();
  virtual ~PlayerWindow();

protected:

  //Child widgets:
  Gtk::Frame m_Frame;
};

#endif //GTKMM_EXAMPLEWINDOW_H
