#ifndef MAP_H
#define MAP_H

//pálya méretei
#define mapW 77
#define mapH 20
#define WALLGRAPH '#'
#define KAJAGRAPH 'Q'
#define AMMOGRAPH '&'
int egyjatekos;
int vankaja;
int vanammo;
//------------------------------
char **mapinit();
void torol(char **map);
void szellemirto(char **map);
void kirajzol(char **map);
void kajarak(char **map);
void ammorak(char **map);
#endif