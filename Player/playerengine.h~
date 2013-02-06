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


#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H

// this will be the new class for a libVLC based engine that i will implement in my player

// Reasons being that it is readily available at the time of the project.
#include<vlc/vlc.h>
#include <gtkmm-3.0/gtkmm.h>
#include <string>
#include <stdint.h>
#define stream_ended 1
//#include "SDL_Window/sdl_videoout.h"
class PlayerEngine_vlc{
	
	public:
		PlayerEngine_vlc();
	virtual ~PlayerEngine_vlc();
		void playState();
		void pauseState();
		void seekState(double position);
		void setVol(double volume_level);
		void stopState();
		int64_t get_media_length();
 		int64_t get_media_time();
		void get_File(std::string uri);
		void get_DVD_URI();
		double getSliderPOS();
		std::string report();
 		int end_state();
		void set_winID(gulong player_window_id);
	private:

		libvlc_instance_t *vlcInstance;
               libvlc_media_player_t *vlcPlayer;
		std::string message;
		//SDL_videoout video;

};

#endif // PLAYERENGINE_H
