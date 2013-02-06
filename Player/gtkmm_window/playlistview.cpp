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


#include "playlistview.h"

#include "playlistview.h"
#include <iostream>
#include <string>
#include <vector>
#include "../mediastore.h"
PlaylistViewer::PlaylistViewer()
{
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  set_model(m_refTreeModel);

 // Fill the TreeView's model
 // Gtk::TreeModel::Row row = *(m_refTreeModel->append());
/*
  row[m_Columns.m_col_trackNum] = 1;
  row[m_Columns.m_col_trackName] = "right-click on this";
  row[m_Columns.m_col_trackPath] = "right-click on this";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_trackNum]= 2;
  row[m_Columns.m_col_trackName] = "or this";
  row[m_Columns.m_col_trackPath] = "right-click on this";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_trackNum] = 3;
  row[m_Columns.m_col_trackName] = "or this, for a popup context menu";
  row[m_Columns.m_col_trackPath] = "right-click on this";
*/

// master plan is to run through a vector to populate values


 
  //Add the TreeView's view columns:
  append_column("Track", m_Columns.m_col_trackNum);
  append_column("Name", m_Columns.m_col_trackName);
  append_column("Path", m_Columns.m_col_trackPath);

  //Fill popup menu:
  Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem("_Play", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &PlaylistViewer::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);
    
  item = Gtk::manage(new Gtk::MenuItem("_Queue", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &PlaylistViewer::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);
    
  item = Gtk::manage(new Gtk::MenuItem("_Info", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &PlaylistViewer::on_menu_file_popup_generic) );
  m_Menu_Popup.append(*item);

  m_Menu_Popup.accelerate(*this);
  m_Menu_Popup.show_all(); //Show all menu items when the menu pops up

#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  signal_button_press_event()
    .connect(sigc::mem_fun(*this, &PlaylistViewer::on_button_press_event), false);
#endif
}

PlaylistViewer::~PlaylistViewer()
{
}

bool PlaylistViewer::on_button_press_event(GdkEventButton* event)
{
  bool return_value = false;

  //Call base class, to allow normal handling,
  //such as allowing the row to be selected by the right-click:
  return_value = TreeView::on_button_press_event(event);

  //Then do our custom stuff:
  if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
  {
    m_Menu_Popup.popup(event->button, event->time);
  }

  return return_value;
}

void PlaylistViewer::on_menu_file_popup_generic()
{
  std::cout << "A popup menu item was selected." << std::endl;

  Glib::RefPtr<Gtk::TreeView::Selection> refSelection = get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      int number = (*iter)[m_Columns.m_col_trackNum];
     // std::string name = (*iter)[m_Columns.m_col_trackPath];
      //std::string path = (*iter)[m_Columns.m_col_trackPath]
      //we can also get the path of the track
      std::cout << "  Selected number =" << number << std::endl;
      //std::cout << "  Selected Name"<< name    <<std::endl;
    }
  }
}

void PlaylistViewer::get_media_data( int track, char *path,char *name)
{
	 Data mediadata = {track, std::string(path), std::string(name)};
	media_data.push_back(mediadata);
}
void PlaylistViewer::fill_Playlist()
{
 Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	MediaStore store;
	store.readToDB();
std::vector<MediaStore::playlistdata> media_list=store.sendData();
 for(std::vector<MediaStore::playlistdata>::iterator iter = media_list.begin(); iter != media_list.end();
++iter){


  //row = *(m_refTreeModel->append());



  row[m_Columns.m_col_trackNum] = iter->track;
  row[m_Columns.m_col_trackName] = iter->name;
  row[m_Columns.m_col_trackPath] = iter->path;
  row = *(m_refTreeModel->append());
}
}
