#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#define playlistwidth 50
#define playlistwidth_nat 70

#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/scale.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gdk/gdkx.h>

#include"playlistview.h"
#include"../uri_mechanism.h"
#include"../playerengine.h"
#include"../medialist.h"
#include"../mediastore.h"


#include<iostream>
#include <iomanip>
#include<string>
#include<stdint.h>




class PlayerGUI : public Gtk::Window
{	
	

	public:
	PlayerGUI();
virtual ~PlayerGUI();
	
        
	 
	 
	protected:
	// Defining new GUI elements 

	// The positioning , framing and packing

	Gtk::Frame Horizontal_Frame,Vertical_Frame;
	Gtk::Box Vert_Box_main,video_Box,HBox1,HBox2,mini_HBox;
	Gtk::ScrolledWindow playlistwindow;
	Gtk::ButtonBox* controlbox;	
	Gtk::Alignment align_vol;
	// Interactive and Visual Elements of GUI
	
	Gtk::HScale seeker;
	Gtk::VScale volume;
	Gtk::Label m_Timer,Label_Volume;
	Gtk::Button m_play,m_pause,m_previous,m_next, m_stop, m_open_media;
	Gtk::ProgressBar progressbar;
	Gtk::DrawingArea video_area;
	PlaylistViewer playlist;

	// The Signal handlers for the window Class are below
	void on_button_clicked();
	bool on_value_changed_seeker(Gtk::ScrollType,double value);
        bool on_value_changed_vol(Gtk::ScrollType, double value);
        void on_video_window_realize();
	void on_playbutton_pressed();
	void on_pausebutton_pressed();
	void on_previousbutton_pressed();
	void on_nextbutton_pressed();
	void on_openbutton_pressed();
	void on_stopbutton_pressed();
	void on_update_Label(int64_t pos, int64_t len);
        bool update();
	// The setters of window properties
	void set_screen_resize(int width_value,  int height_value);	
	void set_background_color();
  
	// Class instances 
         URI_Mechanism uri;
	 MediaList list;
	 PlayerEngine_vlc engine;
	 MediaStore store;      
         gulong player_window_id;
	 std::string media_uri;

	private:
   
	// Variables like signals and stuff here		

        sigc::connection m_timeout_connection;
	Gdk::RGBA m_Color;
        int index;
	
};
#endif // PLAYERWINDOW_H
