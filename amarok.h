#ifndef AMAROK_H
#define AMAROK_H


#include "amarok-glue.h"
#include "music.h"

class Amarok_Client
	: public org::freedesktop::MediaPlayer_proxy,
	public DBus::IntrospectableProxy,
	public DBus::ObjectProxy
{
public:
	int Playing_State;
	int duration; //in msec
	int cur_pos;

	Amarok_Client ( DBus::Connection &conn, const char *path, const char *name );
	void TrackChange(const std::map< std::string, ::DBus::Variant >& argin0);
	void StatusChange(const ::DBus::Struct< int32_t, int32_t, int32_t, int32_t >& argin0);
	void CapsChange(const int32_t& argin0);

private:
	pthread_t test_T;
};

void *Secound_Thread ( void * ptr )
{
	Amarok_Client *AmaCom = (Amarok_Client*) ptr;
	int middle = (col - 10) / 2,
	screensaver_Int = 0,
	statuscheck_int = 0;
	while (true)
	{
		if (AmaCom->Playing_State == 0) //Playing
		{
			if (AmaCom->cur_pos > AmaCom->duration)
				AmaCom->cur_pos = AmaCom->PositionGet();
			int sleep_time = AmaCom->cur_pos - ((AmaCom->cur_pos / 1000) * 1000);
			int mins = (int) ((float) AmaCom->cur_pos / 60000);
			int secs = (AmaCom->cur_pos - mins * 60000)/1000;
		
			mvwprintw(Music_win, TIME_LINE, col/2 - 2, "%02i:%02i", mins, secs);
			
			wattron(Music_win, COLOR_PAIR(1));

			float percent ((float)AmaCom->cur_pos / (float)AmaCom->duration);

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
			AmaCom->cur_pos += (1000 - sleep_time);
			usleep( (1000 - sleep_time) * 1000 );
		}else{ //Screensaver
			if ( screensaver_Int >= 0 )
			{
				screensaver_Int++;
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - screensaver_Int, LINE_PLACEHOLDER);
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + screensaver_Int - 1, LINE_PLACEHOLDER);

				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - screensaver_Int - 1, "<");
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + screensaver_Int, ">");

				if ( screensaver_Int > middle - 1 )
					screensaver_Int = screensaver_Int * -1;
			}else {
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + screensaver_Int - 1, LINE_PLACEHOLDER);
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - screensaver_Int, LINE_PLACEHOLDER);

				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + screensaver_Int, ">");
				mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - screensaver_Int - 1, "<");
				screensaver_Int++;
			}
		wrefresh(Music_win);
		usleep( 100 * 1000 );
		}
		if (statuscheck_int > 10) //caches 
		{
			statuscheck_int = 0;
			AmaCom->StatusChange(AmaCom->GetStatus());
		} else
			statuscheck_int++;
	}
}



Amarok_Client::Amarok_Client ( DBus::Connection &conn, const char *path, const char *name )
	: DBus::ObjectProxy(conn, path, name)
{
	StatusChange(GetStatus());
	TrackChange(GetMetadata());
	pthread_create( &test_T, NULL, ::Secound_Thread, (void*) this);
}

void Amarok_Client::TrackChange(const std::map< std::string, ::DBus::Variant >& argin0)
{
	std::map< std::string, ::DBus::Variant > Track_Data;
	Track_Data = argin0;
	clear_Music_win ( EMPTY_WIN );

	std::string mesg;
	mesg = Track_Data["artist"].reader().get_string();
	
	wattron(Music_win, COLOR_PAIR(2));
	mvwprintw(Music_win, ARTIST_LINE,(col-strlen(mesg.c_str()) + 8)/2,"%s",mesg.c_str());

	mesg = Track_Data["title"].reader().get_string();
	
	mvwprintw(Music_win, TITLE_LINE,(col-strlen(mesg.c_str()) + 8)/2,"%s",mesg.c_str());

	wattron(Music_win, COLOR_PAIR(3));
	
	duration = Track_Data["mtime"].reader().get_int64();
	int mins = duration/60000;
	int secs = (duration - mins*60000) / 1000;
	mvwprintw(Music_win, TIME_LINE, col/2 + 6, "%02i:%02i", mins, secs);

	wattron(Music_win, COLOR_PAIR(1));

	clear_Music_win ( INIT_WIN );
}

void Amarok_Client::StatusChange(const ::DBus::Struct< int32_t, int32_t, int32_t, int32_t >& argin0)
{
	Playing_State = argin0._1;
	clear_Music_win ( EMPTY_PROGBAR );
	cur_pos = PositionGet();
}

void Amarok_Client::CapsChange(const int32_t& argin0)
{
	//std::cout << "Caps" << argin0 << std::endl;
}
#endif