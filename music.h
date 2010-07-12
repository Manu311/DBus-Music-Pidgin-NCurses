#ifndef MUSIC_H
#define MUSIC_H

#define ARTIST_LINE 0
#define TITLE_LINE 1
#define TIME_LINE 3
#define PROGBAR_LINE 2

int duration;
std::string trackuri;
bool screen_saver;

//options:
#define EMPTY_WIN 1
#define INIT_WIN 2
#define EMPTY_PROGBAR 4


void clear_Music_win( int options )
{
	if ( EMPTY_WIN & options )
	{
		std::string placeholder = "";
		for (int i=0; i<col; i++)
			placeholder += LINE_PLACEHOLDER;
		
		mvwprintw(Music_win, ARTIST_LINE, 0, "%s", placeholder.c_str());
		mvwprintw(Music_win, TITLE_LINE, 0, "%s", placeholder.c_str());
		mvwprintw(Music_win, PROGBAR_LINE, 0, "%s", placeholder.c_str());
	}
	if ( EMPTY_PROGBAR & options )
	{
		std::string placeholder = "";
		for (int i=1; i<col-7; i++)
			placeholder += LINE_PLACEHOLDER;
		mvwprintw(Music_win, PROGBAR_LINE, 1, placeholder.c_str());
	}
	if ( INIT_WIN & options )
	{
		wattron(Music_win, COLOR_PAIR(1));
		mvwprintw(Music_win, ARTIST_LINE, 0, "Artist:");
		mvwprintw(Music_win, TITLE_LINE, 0, "Title: ");
		mvwprintw(Music_win, TIME_LINE, 0, "Duration:");

		mvwprintw(Music_win, TIME_LINE, col/2 + 4, "/");
		mvwprintw(Music_win, PROGBAR_LINE, col - 7, "]");
		mvwprintw(Music_win, PROGBAR_LINE, 0, "[");
	}
	
	wrefresh(Music_win);
	
}

void *screensaver_thread ( void * ptr )
{
	int middle = (col - 10) / 2,
	i = 0;
	sleep ( 1 ); //wait for any drawing progress to finish
	clear_Music_win ( EMPTY_PROGBAR );
	while ( screen_saver )
	{
		if ( i >= 0 )
		{
			i++;
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - i, LINE_PLACEHOLDER);
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + i - 1, LINE_PLACEHOLDER);

			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - i - 1, "<");
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + i, ">");

			if ( i > middle - 1 )
				i = i * -1;
		}else {
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + i - 1, LINE_PLACEHOLDER);
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - i, LINE_PLACEHOLDER);

			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle + i, ">");
			mvwprintw(Music_win, PROGBAR_LINE, 2 + middle - i - 1, "<");
			i++;
		}
		
		wrefresh(Music_win);
		usleep ( 100000 );
	}
	clear_Music_win ( EMPTY_PROGBAR );
	return NULL;
}

#endif