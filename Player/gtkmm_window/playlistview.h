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


#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <gtkmm.h>
#include <string>
class PlaylistViewer : public Gtk::TreeView
{
public:

	struct Data{
	int track;
	std::string path;
	std::string name;
};
	void fill_Playlist();
	void get_media_data( int track, char *path,char *name);
  PlaylistViewer();
  virtual ~PlaylistViewer();

protected:
  // Override Signal handler:
  // Alternatively, use signal_button_press_event().connect_notify()
  virtual bool on_button_press_event(GdkEventButton *ev);

  //Signal handler for popup menu items:
  void on_menu_file_popup_generic();

  
  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_trackNum); add(m_col_trackName); add(m_col_trackPath); }

    Gtk::TreeModelColumn<unsigned int> m_col_trackNum;
    Gtk::TreeModelColumn<Glib::ustring> m_col_trackName;
    Gtk::TreeModelColumn<Glib::ustring> m_col_trackPath;
  
  };
  
  ModelColumns m_Columns;

  //The Tree model:
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  
  // A function that will populate the table for us

  

  Gtk::Menu m_Menu_Popup;
	std::vector<Data> media_data;
  //Gtk::TreeModel::Row row;
};

#endif // PLAYLISTVIEW_H
