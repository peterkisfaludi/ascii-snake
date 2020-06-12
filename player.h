#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"
typedef enum{
	jobb,bal,fel,le
}direction;
typedef struct testresz {
	int _x;
	int _y;
	struct testresz *kov;
}elem, *pelem;
typedef struct {
	int ID;
	int ammo;
	int meret;
	int *gombok;
	pelem fej,farok;
	char fejgraph;
	char testgraph;
	direction irany;
}kigyo, *pkigyo;
pkigyo PL1;
pkigyo PL2;
//-----------------------
void mozgat(pkigyo,char **);
void hozzaad(int,int,pkigyo);
pkigyo plinit(direction,int,int,int,int,int,int,char **);
void gombelkap(int*,int,pkigyo);
void csokken(pkigyo);
void felszab(pkigyo);
void ammofelv(pkigyo);
#endif