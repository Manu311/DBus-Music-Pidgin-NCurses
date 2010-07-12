#ifndef RHYTHMBOX_H
#define RHYTHMBOX_H

#include "RB-glue.h"
#include "RBS-glue.h"

#include "music.h"

class RB_Shell
: public org::gnome::Rhythmbox::Shell_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:
	RB_Shell ( DBus::Connection &conn, const char *path, const char *name )
                : DBus::ObjectProxy(conn, path, name)
	{
	}
	
	void visibilityChanged(const bool& argin0) { }
	
	int update_track()
	{
		std::map< std::string, ::DBus::Variant > Properties_Dict = getSongProperties(::trackuri);
		
		clear_Music_win ( EMPTY_WIN );

		std::string mesg;
		mesg = Properties_Dict["artist"].reader().get_string();
		
		wattron(Music_win, COLOR_PAIR(2));
		mvwprintw(Music_win, ARTIST_LINE,(col-strlen(mesg.c_str()) + 8)/2,"%s",mesg.c_str());

		mesg = Properties_Dict["title"].reader().get_string();
		
		mvwprintw(Music_win, TITLE_LINE,(col-strlen(mesg.c_str()) + 8)/2,"%s",mesg.c_str());

		wattron(Music_win, COLOR_PAIR(3));
		
		int dur = Properties_Dict["duration"].reader().get_uint32();
		int mins = dur/60;
		int secs = dur - mins*60;
		mvwprintw(Music_win, TIME_LINE, col/2 + 6, "%02i:%02i", mins, secs);

		wattron(Music_win, COLOR_PAIR(1));

		clear_Music_win ( INIT_WIN );

		return dur;
	}

};


void *init_update_track ( void * ptr ) //Designed for Threading
{
	try {
		RB_Shell *RBS_Conn = (RB_Shell *) ptr;
		::duration = RBS_Conn->update_track();
	}
	catch (...)
	{
		//if Rhythmbox quit, we caught an execption here
		clear_Music_win ( EMPTY_WIN | EMPTY_PROGBAR );
	}
	
	return NULL;
}

class RB_Client
: public org::gnome::Rhythmbox::Player_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:
	RB_Client ( DBus::Connection &conn, const char *path, const char *name, RB_Shell &RBS_Conn_in )
                : DBus::ObjectProxy(conn, path, name)
	{
		RBS_Conn = &RBS_Conn_in;

		if (getPlaying())
		{
			screen_saver = false;
			::trackuri = getPlayingUri();
			::init_update_track( RBS_Conn );
		}else{
			screen_saver = true;
			clear_Music_win ( INIT_WIN );
			pthread_create( &thread2, NULL, ::screensaver_thread, (void*) NULL);
		}
	}

	void playingSongPropertyChanged(const std::string& argin0, const std::string& argin1, const ::DBus::Variant& argin2, const ::DBus::Variant& argin3)
	{
	}
	
	void elapsedChanged(const uint32_t& argin0)
	{
		if (screen_saver)
			return;

		int mins = argin0/60;
		int secs = argin0 - mins*60;
		wattron(Music_win, COLOR_PAIR(4));
		mvwprintw(Music_win, TIME_LINE, col/2 - 2, "%02i:%02i", mins, secs);
		wattron(Music_win, COLOR_PAIR(1));

		float percent ((float)argin0 / (float)::duration);
		
		mvwprintw(Music_win, PROGBAR_LINE, col - 7, "] %2i %%", (int)(percent * 100));
		
		mvwprintw(Music_win, PROGBAR_LINE, 0, "[");
		
		std::string progbar = "";
		
		for (int i=0; i < percent * (col - 9); i++)
			progbar += "=";

		wattron(Music_win, COLOR_PAIR(2));
		mvwprintw(Music_win, PROGBAR_LINE, 1, "%s", progbar.c_str());
		wattron(Music_win, COLOR_PAIR(3));
		
		mvwprintw(Music_win, PROGBAR_LINE, 1 + percent * (col - 8), ">");
		wattron(Music_win, COLOR_PAIR(1));
		
		wrefresh(Music_win);
		
		/*if (argin0 == 1) //ugly bugfix, updates Track-Info at first Track-Second
			duration = RBS_Conn->update_track(getPlayingUri());*/
	}

	void playingUriChanged(const std::string& argin0)
	{
		::trackuri = argin0;
		pthread_create( &thread1, NULL, ::init_update_track, (void*) RBS_Conn);
	}
	void playingChanged(const bool& argin0) 
	{
		if (argin0)
		{
			screen_saver = false;
			clear_Music_win ( EMPTY_PROGBAR );
			pthread_cancel ( thread2 );

			::trackuri = getPlayingUri();
			::init_update_track( RBS_Conn );
		}else{
			screen_saver = true;
			pthread_create( &thread2, NULL, ::screensaver_thread, (void*) NULL);
		}			
	}
	  
private:
	RB_Shell *RBS_Conn;
	pthread_t thread1;
	pthread_t thread2;
};
#endif