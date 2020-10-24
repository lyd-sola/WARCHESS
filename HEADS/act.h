#ifndef  _ACT_H_
#define  _ACT_H_


void move(DBL_POS From, MAP map, int able);
void stay(DBL_POS dpos, MAP map);
void attack(DBL_POS dpos, MAP map);
void next_round(MAP map, unsigned* round);

void delarm(DBL_POS dpos, MAP map);


#endif