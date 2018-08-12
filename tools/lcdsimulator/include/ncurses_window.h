#ifndef CCALCLCDSIM_SRC_NCURSES_H_
#define CCALCLCDSIM_SRC_NCURSES_H_

#include <ncurses.h>
#include "graphics/pixelsurface.h"
#include "input.h"
#include "graphics/scene.h"

void ncurses_init();

void ncurses_loop(G_Scene * scene);

void ncurses_input(G_Scene * scene);

#endif
