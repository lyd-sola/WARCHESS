#ifndef  _ACT_H_
#define  _ACT_H_


void move(DBL_POS From, MAP map, int able);
int move_(DBL_POS From, DBL_POS dbto, int able, MAP map, int visit[7][7]);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);
int attack_(Arminfo info, MAP map, DBL_POS dpos, DBL_POS dbto);
void delarm(DBL_POS dpos, MAP map);
void builder_build(DBL_POS dpos, MAP map, Battleinfo* batinfo);

void nxt_round(MAP map, Battleinfo* info, int* pside);
void next_r_banner(int side);

void base_func(MAP map, unsigned* source, int side);
void levelup(DBL_POS dpos, MAP map, unsigned* source);
void buildarm(MAP map, unsigned* source, int side);
#endif