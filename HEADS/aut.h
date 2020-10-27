#ifndef  _AUT_H_
#define  _AUT_H_

#include "struct.h"
void aut(MAP map, Battleinfo* batinfo);
void aut_move(MAP map, OFF_POS opos, int visit[7][7]);
int aut_attack(MAP map, OFF_POS opos, int visit[7][7], Arminfo info);
void ATTACK(OFF_POS to, Arminfo info, int Stay_pos, MAP map);
#endif