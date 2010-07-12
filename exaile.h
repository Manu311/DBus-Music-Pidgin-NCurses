#ifndef EXAILE_H
#define EXAILE_H

#include "exaile-glue.h"

#include "music.h"

int cur_pos;

void *elapse_thread ( void * ptr ) //Designed for Threading
{
	while (true)
	{
		int mins, secs;
		::cur_pos++;
		mins = (int) ((float) cur_pos / 60);
		secs = cur_pos - mins * 60;
		
		mvwprintw(Music_win, TIME_LINE, col/2 - 2, "%02i:%02i", mins, secs);
		wattron(Music_win, COLOR_PAIR(1));

		float percent ((float)::cur_pos / (float)::duration);

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
		sleep(1);
	}
	
	return NULL;
}

class Exaile_Client
: public org::exaile::Exaile_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:
	void TrackChanged() 
	{
		std::string uuml = ""; uuml += (char) -61; uuml += (char) -69;

		std::string
		Title = GetTrackAttr("title"),
		Artist = GetTrackAttr("artist");
		int mins, secs;
		
		clear_Music_win ( EMPTY_WIN );

		wattron(Music_win, COLOR_PAIR(2));
		mvwprintw(Music_win, ARTIST_LINE,(col-strlen(Artist.c_str()) + 8)/2,"%s",Artist.c_str());

		mvwprintw(Music_win, TITLE_LINE,(col-strlen(Title.c_str()) + 8)/2,"%s",Title.c_str());

		duration = atoi ( GetTrackAttr("__length").c_str() );
		
		mins = duration / 60;
		secs = duration - mins * 60;
		
		mvwprintw(Music_win, TIME_LINE, col/2 + 6, "%02i:%02i", mins, secs);

		wattron(Music_win, COLOR_PAIR(1));

		clear_Music_win ( INIT_WIN );
		
		std::string temp2 = CurrentPosition();
		int temp = temp2.find(":");
		mins = atoi ( temp2.substr(0, temp).c_str() );
		secs = atoi ( temp2.substr(temp+1, temp + 3).c_str() );
		
		::cur_pos = mins * 60 + secs;
		
		pthread_create( &elapse_T, NULL, ::elapse_thread, (void*) NULL);
	}
	
	 void StateChanged()
	{
		std::string cur_state = GetState();
		if (cur_state == "playing")
		{
			screen_saver = false;
			
		}
		else if (cur_state == "paused")
		{
			screen_saver = true;
			clear_Music_win ( INIT_WIN );
			pthread_create( &saver_T, NULL, ::screensaver_thread, (void*) NULL);
		}
		else if (cur_state == "stopped")
		{
			screen_saver = true;
			::cur_pos = 0;
		}
		else
		{
			std::cout << "unknown state:" << std::endl;
			std::cout << cur_state << std::endl;
		}
	}
	

	Exaile_Client ( DBus::Connection &conn, const char *path, const char *name )
                : DBus::ObjectProxy(conn, path, name)
	{
		std::string cur_state = GetState();
		if (cur_state == "playing")
		{
			TrackChanged();
			screen_saver = false;
		}
		else if (cur_state == "paused")
		{
			screen_saver = true;
			clear_Music_win ( INIT_WIN );
			pthread_create( &saver_T, NULL, ::screensaver_thread, (void*) NULL);
		}
	}
	

	
private:
	pthread_t saver_T;
	pthread_t elapse_T;
};
#endif