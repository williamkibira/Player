#include <stdio.h>
 #include <stdlib.h>
 #include <vlc/vlc.h>
 #include <SDL/SDL.h>
 int main(int argc, char* argv[])
 {
     libvlc_instance_t * inst;
     libvlc_media_player_t *mp;
     libvlc_media_t *m;
     
     /* Load the VLC engine */
     inst = libvlc_new (0, NULL);
  
     /* Create a new item */
     //m = libvlc_media_new_path (inst, "http://mycool.movie.com/test.mov");
       m = libvlc_media_new_path (inst, "/home/william/Videos/manup.FLV"); 
     /* Create a media player playing environement */
     mp = libvlc_media_player_new_from_media (m);
     
     /* No need to keep the media now */
     libvlc_media_release (m);
 
 #if 0
     /* This is a non working code that show how to hooks into a window,
      * if we have a window around */
      libvlc_media_player_set_xdrawable (mp, xdrawable);
     /* or on windows */
      libvlc_media_player_set_hwnd (mp, hwnd);
     /* or on mac os */
      libvlc_media_player_set_nsobject (mp, view);
  #endif
 

//Set parent window
	SDL_SysWMinfo xwin;
	SDL_VERSION (&xwin.version);
	SDL_GetWMInfo (&xwin);


       libvlc_video_set_parent (inst, (libvlc_drawable_t)xwin.info.x11.window);







     /* play the media_player */
     libvlc_media_player_play (mp);
    
     sleep (1000); /* Let it play a bit */
    
     /* Stop playing */
     libvlc_media_player_stop (mp);
 
     /* Free the media_player */
     libvlc_media_player_release (mp);
 
     libvlc_release (inst);
 
     return 0;
 }
