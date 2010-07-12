
#if true
#include <string.h>    
#include <signal.h>
#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <dbus-c++/dbus.h>
#include <pthread.h>

#define LINE_PLACEHOLDER " "
int col;
WINDOW *Music_win, *Pidgin_win;
DBus::BusDispatcher dispatcher;

#include "rhythmbox.h"
#include "pidgin.h"
#include "exaile.h"
#include "amarok.h"

void init_ncurses()
{
	initscr();
	
	curs_set(0); //disables cursor
	
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);

	int row;
	getmaxyx(stdscr,row,col);
	
	Music_win = newwin(4, col, 0, 0);
	Pidgin_win = newwin(row-6, col, 5, 0);
	
	wattron(Music_win, COLOR_PAIR(1));
	wattron(Pidgin_win, COLOR_PAIR(1));
	
	std::string placeholder;
	for (int i=0; i<col; i+=2)
	{
		placeholder += "- ";
	}
	
	mvprintw(4, 0, "%s", placeholder.c_str());
	
	scrollok(Pidgin_win, true);
	
	
	refresh();
}

void quit ( int sig )
{
	endwin();
	dispatcher.leave();
	exit(1);
}

int main(int argc, char *argv[])
//int main()
{
	signal(SIGTERM, quit);
	signal(SIGINT, quit);
	

	init_ncurses();
		
	DBus::default_dispatcher = &dispatcher;
	
	DBus::_init_threading();
	
        DBus::Connection conn = DBus::Connection::SessionBus();

	std::string argument;
	
	for ( int i=0; i<argc; i++ )
	{
		argument = argv[i];
		if ( argument == "--help" || argument == "-h" || argc == 1 )
		{
			endwin();
			std::cout << "dbus-listener [OPTION]..."
			<< std::endl << std::endl << "Options: "
			<< std::endl << "	-h,	--help				this help"
			<< std::endl << "	-RB,	--with-Rhythmbox		enable Rhythmbox Support"
			<< std::endl << "	-purp,	--with-Pidgin			enable Pidgin Support"
			<< std::endl << "	-exa,	--with-Exaile			enable Exaile Support"
			<< std::endl << "	-ama,	--with-Amarok			enable Amarok Support"
			<< std::endl << std::endl;
			exit(1);
		}
		
		else if ( argument == "-purp" || argument == "--with-Pidgin" )
		{
			//Pidgin_Client Pidgin_Conn ( conn, "/im/pidgin/purple/PurpleObject", "im.pidgin.purple.PurpleService" );
		}
		else if ( argument == "-RB" || argument == "--with-Rhythmbox" )
		{
#ifdef RHYTHMBOX_H
			RB_Shell RBS_Conn ( conn, "/org/gnome/Rhythmbox/Shell", "org.gnome.Rhythmbox" );

			RB_Client RB_Conn ( conn, "/org/gnome/Rhythmbox/Player", "org.gnome.Rhythmbox", RBS_Conn );
#endif
		}
		else if ( argument == "-exa" || argument == "--with-Exaile" )
		{
#ifdef EXAILE_H
			Exaile_Client Exaile_Conn (conn, "/org/exaile/Exaile", "org.exaile.Exaile" );
#endif
		}
		else if ( argument == "-ama" || argument == "--with-Amarok" )
		{
#ifdef AMAROK_H
			Amarok_Client Amarok_Conn (conn, "/Player", "org.kde.amarok" );
#endif
		}
	}

	Pidgin_Client Pidgin_Conn ( conn, "/im/pidgin/purple/PurpleObject", "im.pidgin.purple.PurpleService" );

	dispatcher.enter();

	quit(1);

	return 0;
}

#endif