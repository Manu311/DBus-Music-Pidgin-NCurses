#include "pidgin-glue.h"

std::map < std::string, std::string > Buddy_Aliases;

class Pidgin_Client
: public im::pidgin::purple::PurpleInterface_proxy,
public DBus::IntrospectableProxy,
public DBus::ObjectProxy
{
public:

	Pidgin_Client ( DBus::Connection &conn, const char *path, const char *name )
		: DBus::ObjectProxy(conn, path, name)
	{
		int temp;
		getmaxyx(Pidgin_win, row, temp);
		cur_rows = 0;
		
#if false
		test_Incoming_Message();
#endif
	}

	void ReceivedImMsg(const int32_t& argin0, const std::string& argin1, const std::string& argin2, const int32_t& argin3, const uint32_t& argin4)
	{
		wattron(Pidgin_win, COLOR_PAIR(2));
		if (Buddy_Aliases.count(argin1) < 1)
			Buddy_Aliases[argin1] = PurpleBuddyGetContactAlias(PurpleFindBuddy(argin0, argin1));
		mvwprintw(Pidgin_win, cur_rows, 0, "%s:", Buddy_Aliases[argin1].c_str());
		
		wattron(Pidgin_win, COLOR_PAIR(1));

		std::string text = format_html_string(argin2);
		int line_length;
		while (text.size() > 0)
		{
			line_length = col - 15;
			if (line_length > text.size())
				line_length = text.size();
			mvwprintw(Pidgin_win, cur_rows, 15, "%s", text.substr(0, line_length).c_str());
			text = text.substr(line_length);
			cur_rows++;

			if (cur_rows >= row)
			{
				scroll(Pidgin_win);
				cur_rows--;
			}
			
		}
		
		wrefresh(Pidgin_win);
	}

#if false
	void test_Incoming_Message()
	{
		const int32_t test = 3477; //Account-ID (ICQ)
		const std::string test2 = "366457560"; ///Buddy-Id (Leoni's ICQ)
		const std::string test3 = "testnachricht";
		const uint32_t test4 = 2;
		ReceivedImMsg(test, test2, test3, test, test4);
		
	}
#endif
	
private:
	int row, cur_rows;

	std::string format_html_string(std::string text)
	{
		std::string result = "";
		std::string rest, rest2;
		int pos1 = text.find('<');
		result += text.substr(0, pos1);
		rest2 = text;
		while (pos1 < rest2.size())
		{
			rest = rest2.substr(pos1+1);
			int pos2 = rest.find('>');
			if (pos2 >= rest.size())
				pos2 = rest.size() - 1;
			rest2 = rest.substr(pos2+1);
			pos1 = rest2.find('<');
			result += rest2.substr(0,pos1);
		}
		//int pos2 = rest.find('>');
		//rest = rest.substr(pos2);
		
		
		return result;
	}

};
