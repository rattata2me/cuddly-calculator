#ifndef CCALCLCDSIM_SRC_NCURSES_H_
#define CCALCLCDSIM_SRC_NCURSES_H_

#include <ncurses.h>
#include "graphics/pixelsurface.h"

void ncurses_init();

void ncurses_loop(G_Surface * buffer);

#endif
