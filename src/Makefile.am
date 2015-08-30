AM_CPPFLAGS = -I$(top_srcdir)/src/libWhistGame
AM_CPPFLAGS += -I$(top_srcdir)/src/AI
LDFLAGS = `pkg-config --libs gtk+-2.0`
CFLAGS += -std=c99 -g -Wall `pkg-config --cflags gtk+-2.0`

lib_LTLIBRARIES = libWhistGame.la libWhistGameAI.la
bin_PROGRAMS = Whist

Whist_SOURCES = WhistGameGUI/main.c WhistGameGUI/gui.c
Whist_LDADD = libWhistGame.la libWhistGameAI.la

libWhistGameAI_la_SOURCES = AI/robot.c

libWhistGame_la_SOURCES = libWhistGame/deck.c \
                          libWhistGame/player.c \
                          libWhistGame/hand.c \
                          libWhistGame/round.c \
                          libWhistGame/game.c
