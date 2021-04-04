#ifndef _CONST_H_
#define _CONST_H_

/* these define the map dimensions not the console itself */
#define ROWS 34 /* one less because of the status bar at the top */
#define COLS 98

#define CONSOLE_ROWS 35
#define CONSOLE_COLS 98

#define INITIAL_PROBABILITY 45
#define STAY_WALL_LIMIT 4
#define BECOME_WALL_LIMIT 5

#define WALL '#'
#define PB_WALL '%'
#define FLOOR '.'
#define PLAYER '@'
#define ENEMY 'X'
#define EXIT '>'
#define COIN 'o'
#define CHEST '?'
#define ORE '*'

static char* main_menu_text[26] = {
  "\n                             ____   _             _         _ \n",
  "                            |  _ \\ (_) ___   ___ (_) _ __  | |  ___\n",
  "                            | | | || |/ __| / __|| || '_ \\ | | / _ \\\n",
  "                            | |_| || |\\__ \\| (__ | || |_) || ||  __/\n",
  "                            |____/ |_||___/ \\___||_|| .__/ |_| \\___|\n",
  "                                                    |_|\n",
  "                                           ___    __\n",
  "                                          / _ \\  / _|\n",
  "                                         | | | || |_\n",
  "                                         | |_| ||  _|\n",
  "                                          \\___/ |_|\n\n",
  "                                    ____             _\n",
  "                                   / ___|  ___    __| | ___\n",
  "                                  | |  _  / _ \\  / _` |/ __|\n",
  "                                  | |_| || (_) || (_| |\\__ \\\n",
  "                                   \\____| \\___/  \\__,_||___/\n \n \n \n \n",
  "                                  /------------------------\\\n",
  "                                  |                        |\n",
  "                                  |        1. Play         |\n",
  "                                  |                        |\n",
  "                                  \\------------------------/\n",
  "                                  /------------------------\\\n",
  "                                  |                        |\n",
  "                                  |        2. Quit         |\n",
  "                                  |                        |\n",
  "                                  \\------------------------/\n \n \n \n",
};

#endif