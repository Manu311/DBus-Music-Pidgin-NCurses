  cmake_minimum_required(VERSION 2.6)
  PROJECT(dbus-listener)
 
  INCLUDE_DIRECTORIES(
	/usr/local/include/glib-2.0/
	/usr/local/lib/glib-2.0/include/
	/usr/local/include/dbus-1.0/
	/usr/local/lib/dbus-1.0/include/
	/usr/local/include/dbus-c++-1/
	)
  
 FILE(GLOB SRCS *.cpp)
 FILE(GLOB HDRS *.h)
 
  ADD_EXECUTABLE(dbus-listener 
 	${SRCS}
 	${HDRS}
  )
 
  TARGET_LINK_LIBRARIES(dbus-listener
	dbus-c++-1
	ncurses
	glib-2.0
  )
