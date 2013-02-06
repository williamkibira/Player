
#include"PlayerWindow.h"

				

PlayerGUI::PlayerGUI() 
:
/* Decibing the Boxes Orientation */   Vert_Box_main(Gtk::ORIENTATION_VERTICAL,20),
		        	       video_Box(Gtk::ORIENTATION_HORIZONTAL,10),
			               HBox1(Gtk::ORIENTATION_HORIZONTAL,20),
			               mini_HBox(Gtk::ORIENTATION_HORIZONTAL,10),
/* Decribe the labels out look*/       m_Timer("000:00:00 / 000:00:00"),

/* Define the buttons and there Icons */ m_play(Gtk::Stock::MEDIA_PLAY),
					 m_pause(Gtk::Stock::MEDIA_PAUSE),
					 m_previous(Gtk::Stock::MEDIA_PREVIOUS),
					 m_next(Gtk::Stock::MEDIA_NEXT),
					 m_stop(Gtk::Stock::MEDIA_STOP),
					 m_open_media(Gtk::Stock::OPEN),
/* Then we do an alignment for one component [ Volume]*/ align_vol(0.5,0.5,1,1),
/* The label for the volume */ 		 Label_Volume("Vol:")
	  
{
	// Initialize all GUI elements in the Constructor
set_default_size(780, 480); // default size of the window
set_title("Will-Tanium Player");

add(Vert_Box_main); // added main box to the window

/* Defining the box properties by frame placements follows */

Vert_Box_main.pack_start(video_Box); // pack a box into a box
video_Box.pack_start(video_area); // pack the video area inside the box
video_area.set_size_request(640, 480);
set_background_color();
video_Box.pack_end(playlistwindow); // pack the playlist window

playlistwindow.add(playlist);


/* Place the slider and the */

Vert_Box_main.pack_start(seeker);
seeker.set_range(0,100);
seeker.set_draw_value(false);
seeker.set_value(0);
/* The timer label placement */


Vert_Box_main.pack_start(m_Timer);
m_Timer.set_alignment(Gtk::ALIGN_CENTER);

Vert_Box_main.pack_start(mini_HBox);
mini_HBox.pack_start(Horizontal_Frame,Gtk::PACK_EXPAND_PADDING,4);

Horizontal_Frame.add(HBox1);


/* now pack the buttons in a button box layout*/

/*Define the specifications for the button box*/
controlbox = 0;
controlbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL) );
/* Pack into the main box */

HBox1.pack_start(*controlbox,Gtk::PACK_SHRINK,2);








controlbox->set_spacing(1.5);
controlbox->set_layout(Gtk::BUTTONBOX_START);

/* Add the buttons */
// set the size of button


controlbox->add(m_play);
controlbox->add(m_pause);
controlbox->add(m_previous);
controlbox->add(m_next);
controlbox->add(m_stop);
controlbox->add(m_open_media);

// now we go ahead and pack the volume

 volume.set_range(0,100);
 volume.set_draw_value(false);
 volume.set_value(0);
 volume.set_inverted();
 HBox1.pack_start(Label_Volume,Gtk::PACK_EXPAND_PADDING);
 HBox1.pack_end(align_vol,Gtk::PACK_EXPAND_WIDGET); // Volume packaging in UI
 align_vol.add(volume);
 volume.set_value(80);

  /* Everything that comes after this has to do with the signals of the player */

  m_play.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_playbutton_pressed));
  m_pause.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_pausebutton_pressed));
  m_previous.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_previousbutton_pressed));
  m_next.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_nextbutton_pressed));
  m_open_media.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_openbutton_pressed));
  m_stop.signal_clicked().connect(sigc::mem_fun(*this,&PlayerGUI::on_stopbutton_pressed));
  volume.signal_change_value().connect(sigc::mem_fun(*this,&PlayerGUI::on_value_changed_vol));
  video_area.signal_realize().connect(sigc::mem_fun(*this,&PlayerGUI::on_video_window_realize));
  seeker.signal_change_value().connect(sigc::mem_fun(*this,&PlayerGUI::on_value_changed_seeker));   	
  /*The End of the player , this is cleanly followed by cleaning UP memory*/

  // Button presets on window initialization 

  m_play.set_sensitive(false);
  m_pause.set_sensitive(false);
  m_previous.set_sensitive(false);
  m_next.set_sensitive(false);
  m_open_media.set_sensitive();
  m_stop.set_sensitive(false);	
  m_play.show();
  m_pause.hide();





 show_all_children();
}





void PlayerGUI::on_button_clicked()
{
 	 hide();
} 


bool PlayerGUI::on_value_changed_seeker(Gtk::ScrollType, double value)
{
 
  engine.seekState(value);

}


bool PlayerGUI::on_value_changed_vol(Gtk::ScrollType, double value)
{

  engine.setVol(value);
  
}


void PlayerGUI::on_update_Label(int64_t pos, int64_t len)
{     
	std::ostringstream timerActive (std::ostringstream::out);
        std::ostringstream timerStatic (std::ostringstream::out);

        timerActive << std::right << std::setfill('0') << 
        std::setw(3) << pos/1000/60/60 << ":" <<
        std::setw(2) << pos/1000/60 << ":" <<
        std::setw(2) << std::left << pos/1000%60;

        timerStatic << std::right << std::setfill('0') <<
        std::setw(3) << len/1000/60/60 << ":" <<
        std::setw(2) << len/1000/60 << ":" <<
        std::setw(2) << std::left << len/1000%60;

	

        // and now we create the label for the time with changes
	m_Timer.set_text(timerActive.str()+ "/" +timerStatic.str());

	
}



void PlayerGUI::on_playbutton_pressed(){

  // The UI changes :)
  
  m_play.set_sensitive(false);
  m_pause.set_sensitive();
  m_previous.set_sensitive();
  m_next.set_sensitive();
  m_open_media.set_sensitive(false);
  m_stop.set_sensitive();	
  m_play.hide();
  m_pause.show();
// then call up the list
// and place the uri into the engine

//engine.get_File(list.find_item(index));

//then engage the play state
 media_uri = list.find_item(index);
 std::cout<< "Test for linked list out put !!!"<<std::endl;
 std::cout<< media_uri<<std::endl;
 
 //engine.set_winID(player_window_id);

//engine.stopState();
  engine.get_File(media_uri);
  engine.set_winID(player_window_id);
  set_screen_resize(640,480);

 engine.playState();

// clear the string after use
 

 m_timeout_connection = Glib::signal_timeout().connect(
 sigc::mem_fun(*this, &PlayerGUI::update), 200);
 
}



void PlayerGUI::on_pausebutton_pressed(){
  // UI inits on button press

  m_play.set_sensitive();
  m_pause.set_sensitive(false);
  m_play.show();
  m_pause.hide();
  engine.playState();
  
}





void PlayerGUI::on_previousbutton_pressed(){



if(index <= 1 ){
 on_stopbutton_pressed();
}else{

// Button settings 

  
 on_stopbutton_pressed();
 seeker.set_value(0);

 media_uri = list.find_prev_item(index);
 engine.get_File(media_uri);
 engine.set_winID(player_window_id);
  set_screen_resize(640,480);
 
 engine.playState();
 
  m_play.set_sensitive(false);
  m_pause.set_sensitive();
  m_previous.set_sensitive();
  m_next.set_sensitive();
  m_open_media.set_sensitive(false);
  m_stop.set_sensitive();	
  m_play.hide();
  m_pause.show();
 


 m_timeout_connection = Glib::signal_timeout().connect(
 sigc::mem_fun(*this, &PlayerGUI::update), 200);
 
}
}



void PlayerGUI::on_nextbutton_pressed(){


  
 on_stopbutton_pressed();
 seeker.set_value(0);

 media_uri=list.find_next_item(index);
 
 engine.get_File(media_uri);
 engine.set_winID(player_window_id);
 set_screen_resize(640,480);
 engine.playState();

//Button Presets for next button
  m_play.set_sensitive(false);
  m_pause.set_sensitive();
  m_previous.set_sensitive();
  m_next.set_sensitive();
  m_open_media.set_sensitive(false);
  m_stop.set_sensitive();	
  m_play.hide();
  m_pause.show();
  


  m_timeout_connection = Glib::signal_timeout().connect(
 sigc::mem_fun(*this, &PlayerGUI::update), 200);
 index++; 
}


void PlayerGUI::on_openbutton_pressed(){

 // The point to call intance of the URI mechanism
	uri.folderchoose();
 // Ok then fill up the playlist view with Data and also fill up the 
 // the Linked list here with data
 store.readToDB();
 std::vector<MediaStore::playlistdata> media_list=store.sendData();
 // then iterate through the vector to push data into list 
 // create a test to see if data is worth using or is garbage

 for(std::vector<MediaStore::playlistdata>::iterator iter = media_list.begin(); iter != media_list.end();
 ++iter){
 // then we check the data

 std::cout<< iter->track<<std::endl;
 std::cout<< iter->name<<std::endl;
 std::cout<< iter->path<<std::endl;
 // then dump the data in the playlist

 // then load up the playlist Data structure :)

 list.pushIn(iter->track,iter->path,iter->name);

}
 playlist.fill_Playlist();

 m_play.set_sensitive();
 m_pause.set_sensitive(false);
 m_previous.set_sensitive();
 m_next.set_sensitive();
 m_open_media.set_sensitive(false);
 m_stop.set_sensitive();
 m_pause.hide();

 index = 1;
}



void PlayerGUI::on_stopbutton_pressed(){



  m_play.set_sensitive();
  m_pause.set_sensitive(false);
  m_previous.set_sensitive(false);
  m_next.set_sensitive(false);
  m_open_media.set_sensitive();
  m_stop.set_sensitive(false);

  m_pause.hide();
  m_play.show();
  m_Timer.set_text("000:00:00 / 000:00:00");
  engine.stopState();
  m_timeout_connection.disconnect();
  seeker.set_value(0);
  
 }  



bool PlayerGUI::update()
{

/* Update of the seekers position */
 seeker.set_value(engine.getSliderPOS());
 on_update_Label(engine.get_media_time(),engine.get_media_length());
 if(engine.end_state()== stream_ended){
        on_stopbutton_pressed();
        seeker.set_value(0);
	index++;
 // Button Presets for next sequence

  m_play.set_sensitive(false);
  m_pause.set_sensitive();
  m_previous.set_sensitive();
  m_next.set_sensitive();
  m_open_media.set_sensitive(false);
  m_stop.set_sensitive();	
  m_play.hide();
  m_pause.show(); 


 media_uri=list.find_next_item(index);
 
 engine.get_File(media_uri);
 engine.set_winID(player_window_id);
 set_screen_resize(640,480);
 engine.playState();
 m_timeout_connection = Glib::signal_timeout().connect(
 sigc::mem_fun(*this, &PlayerGUI::update), 200);
 	

}
return true;
}



void PlayerGUI::set_screen_resize(int width_value,  int height_value)
{

// We Resize the window to suit our viewing :)

video_area.set_size_request(width_value, height_value);
resize(1,1);
check_resize();

}

void PlayerGUI::set_background_color()
{
 //Set start color:
  m_Color.set_red(0.0);
  m_Color.set_green(0.0);
  m_Color.set_blue(0.0);
  m_Color.set_alpha(0.0); //opaque


 video_area.override_background_color(m_Color);

}


void PlayerGUI::on_video_window_realize()
{
// now we aquire the x windows ID

player_window_id = GDK_WINDOW_XID(video_area.get_window()->gobj());

// yes the X windows ID has been aquired ../../../
}



PlayerGUI::~PlayerGUI()
{


}
