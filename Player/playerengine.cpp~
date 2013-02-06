/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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


#include "playerengine.h"
#include <gtkmm-3.0/gtkmm.h>
//#include "SDL_Window/SDL_Window.h"
#include"GUI_Code/playergui.h"
PlayerEngine_vlc::PlayerEngine_vlc(){
	vlcPlayer = NULL;
	 /* Initialize libVLC */
    	vlcInstance = libvlc_new(0, NULL);
	
	/* Complain in case of broken installation */
   if (vlcInstance == NULL) {
        // Report that libVLC could not be initialized
		
		message =  "Error : libVLC failed to Init";
        exit(1);
    }



 

  //Shows the window and returns when it is closed.
  
  // now create the signal ID
  

// Here is where we call up the Display window for viewwing the full Video
// I will USE SDL for my final Video Out put. 

//libvlc_video_set_callbacks(vlcPlayer, lock, unlock, display, &ctx);
//libvlc_video_set_format(vlcPlayer, "RV16", VIDEOWIDTH, VIDEOHEIGHT, VIDEOWIDTH*2);


}
void PlayerEngine_vlc::get_File(std::string uri){
 /* Stop if something is playing */
    if (vlcPlayer && libvlc_media_player_is_playing(vlcPlayer))
        stopState();
    message =  "Status : Loading";
    
     /* Create a new Media */
    libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance,&uri[0]/*uri.c_str()*/);
    if (!vlcMedia)
     { 
       message =  "Error : failed to create media";
        return;
    }
    
     /* Create a new libvlc player */
    vlcPlayer = libvlc_media_player_new_from_media (vlcMedia);

    //gulong window_id;
  //libvlc_media_player_set_xwindow(vlcPlayer,window_id);
  
  //Player_ControlsGUI win;

  //win.set_xwindows_id(window_id);    





    /* Release the media */
    libvlc_media_release(vlcMedia);

    /* And start playback */
     /*
    libvlc_media_player_play (vlcPlayer);
    message =  "Status : Playing";
      */


// catch the exception from here

    


}
void PlayerEngine_vlc::playState(){

	  if (!vlcPlayer)
        return;

    if (libvlc_media_player_is_playing(vlcPlayer))
    {
        /* Pause */
        libvlc_media_player_pause(vlcPlayer);
       
    }
    else
    {
        /* Play again */
        libvlc_media_player_play(vlcPlayer);
     
    }

}
void PlayerEngine_vlc::pauseState(){

	libvlc_media_player_pause(vlcPlayer);
	message =  "Status : Pause";
}
void PlayerEngine_vlc::seekState(double position){
	if (vlcPlayer)
        libvlc_media_player_set_position(vlcPlayer, (float)position/100.0);
}
void PlayerEngine_vlc::setVol(double volume_level){
	if (vlcPlayer)
        libvlc_audio_set_volume (vlcPlayer,(int)volume_level);

}
void PlayerEngine_vlc::stopState(){

 if(vlcPlayer) {
        /* stop the media player */
        libvlc_media_player_stop(vlcPlayer);

        /* release the media player */
        libvlc_media_player_release(vlcPlayer);

        /* Reset application values */
        vlcPlayer = NULL;
       }
}



int64_t PlayerEngine_vlc::get_media_length(){
	
  // type cast to gint64 and return media length

 return (int64_t)libvlc_media_player_get_length(vlcPlayer); 
}




int64_t PlayerEngine_vlc::get_media_time(){

if (!vlcPlayer)
        return 0;

    /* update the timeline */
    
    return (int64_t)libvlc_media_player_get_time (vlcPlayer);

    /* Stop the media */
    if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
        this->stopState();

}

double PlayerEngine_vlc::getSliderPOS(){

float pos = libvlc_media_player_get_position(vlcPlayer);

return (double)pos*100.0;
/*
  if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
 */       this->stopState();

}



PlayerEngine_vlc::~PlayerEngine_vlc(){

if (vlcInstance)
        libvlc_release(vlcInstance);
}


std::string PlayerEngine_vlc::report(){

// Just to report the players current status :)

return message;

}
int PlayerEngine_vlc::end_state()
{
if (libvlc_media_player_get_state(vlcPlayer) == libvlc_Ended)
return 1;
}
// now lets set up the video ID setting

void PlayerEngine_vlc::set_winID(gulong player_window_id)
{
  
  libvlc_media_player_set_xwindow(vlcPlayer,player_window_id);
  
  }


