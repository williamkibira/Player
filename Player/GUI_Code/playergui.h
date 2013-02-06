/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef PLAYERGUI_H
#define PLAYERGUI_H
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/scale.h>
#include <gtkmm-3.0/gtkmm/window.h>

#include <gdk/gdkx.h>
//#include <gdkmm/gdkmm.h>

#include "playlistview.h"
#include"../uri_mechanism.h"
#include"../playerengine.h"
#include"../medialist.h"
#include"../mediastore.h"
#include<string>
class Player_ControlsGUI : public Gtk::Window
{
public:
  Player_ControlsGUI();
  virtual ~Player_ControlsGUI();
 void set_xwindows_id(gulong player_window_id);
protected:
  void deliver_CodecInfo();
  Glib::RefPtr<Gtk::Adjustment> m_adjustment1,m_adjustmentVol; // new adjustments for progress bar and seek bar
  Glib::RefPtr<Gtk::TextBuffer> m_codecdata; // the text buffers for codec information
  //Signal handlers:
  void on_button_clicked();
  
  void on_adjustment_value_changed();
  //Child widgets:
  Gtk::Label m_progressLabel;
  Gtk::Box m_VBox_Main, m_VBox;
  Gtk::Box m_HBox,m_SHBox,m_SHBox2;
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Alignment m_Alignment,m_AlignmentVol,m_AlignmentSeek;
  Gtk::ProgressBar m_ProgressBar; // the progress bar
  Gtk::HScale seeker,vol; // the seek bar
  Gtk::ScrolledWindow m_PlaylistView;
  Gtk::TextView m_CodecInfoArea;
  Gtk::DrawingArea video_area;
  Gtk::Button m_playbutton, m_pausebutton, m_previousbutton,m_nextbutton,m_openbutton,m_stopbutton;
  sigc::connection m_timeout_connection;
  std::string data;
  PlaylistViewer playlist;
// now to handle the signals for the progress bar , label and slider

void set_screen_resize(int width_value,  int height_value);



bool on_value_changed_progressBar(double value);
bool on_value_changed_seeker(Gtk::ScrollType,double value);
bool on_value_changed_vol(Gtk::ScrollType, double value);
void on_update_Label(gint64 pos, gint64 len);
std::string media_uri;
double test_seeker; // test value
int index;
// the signal handlers for the buttons :)
gulong player_window_id;
		 
void on_video_window_realize();
void on_playbutton_pressed();
void on_pausebutton_pressed();
void on_previousbutton_pressed();
void on_nextbutton_pressed();
void on_openbutton_pressed();
void on_stopbutton_pressed();
void load_list();

bool update();
 URI_Mechanism uri;
 MediaList list;
 PlayerEngine_vlc engine;
 MediaStore store;
};


#endif // PLAYERGUI_H
