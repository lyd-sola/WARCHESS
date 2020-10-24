#ifndef  _ACT_H_
#define  _ACT_H_


void move(DBL_POS From, MAP map, int able);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);
void delarm(DBL_POS dpos, MAP map);
void nxt_round(MAP map, Battleinfo* info, int* pside);
#endif