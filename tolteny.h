#ifndef TOLTENY_H
#define TOLTENY_H
#include "map.h"
#include "player.h"

//------------------
typedef struct t{
	int _x;
	int _y;
	direction irany;
	struct t*kov;
	struct t* akt;
	struct t* elso;
}tolt, *ptolt;
ptolt elso;
ptolt akt;
//-------------------
//--------------------
ptolt toltinit(pkigyo);
void toltmozgat(char **map, pkigyo p1, pkigyo p2);
void tolttorol(ptolt);
void shoot(pkigyo k);

#endif