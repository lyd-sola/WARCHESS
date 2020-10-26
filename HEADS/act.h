#ifndef  _ACT_H_
#define  _ACT_H_


void move(DBL_POS From, MAP map, int able);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);

void delarm(DBL_POS dpos, MAP map);
void nxt_round(MAP map, Battleinfo* info, int* pside);
void next_r_banner(int side);

void base_func(MAP map, unsigned* source, int side);
void levelup(DBL_POS dpos, MAP map, unsigned* source);
void buildarm(MAP map, unsigned* source, int side);


#endif