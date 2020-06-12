#include "map.h"
#include <stdio.h>
#include "econio.h"
#include <time.h>
char ** mapinit() {
	int i;
	char **map=(char**)malloc(sizeof(char*)*mapW);
	for(i=0;i<mapW;i++) {
		map[i]=(char*)malloc(sizeof(char)*mapH);
	}
	torol(map);
	return map;
}
//-------------------------------------------
void torol(char **map) {
	int i,j;
	for(j=0;j<mapH;j++){
		for(i=0;i<mapW;i++){
			if(map[i][j]==WALLGRAPH || map[i][j]==KAJAGRAPH || map[i][j]==AMMOGRAPH)continue;
			map[i][j]=' ';
		}
	}
}
//-------------------------------------------
void kirajzol(char **map) {
	int i,j;
	for(i=0;i<mapW+2;i++) {
		putchar(WALLGRAPH);
	}
	putchar('\n');
	for(j=0;j<mapH;j++) {
		putchar(WALLGRAPH);
		for(i=0;i<mapW;i++) {
			
			putchar(map[i][j]);
		}putchar(WALLGRAPH);putchar('\n');
	}
	for(i=0;i<mapW+2;i++) {
		putchar(WALLGRAPH);
	}
}
//-----------------------------------------
void kajarak(char **map){
	int OK=0;
	int oszl, sor;
	srand((unsigned)time(NULL));
	while(!OK) {
		oszl=(rand()%mapW);
		sor=(rand()%mapH);
		if(map[oszl][sor]!=' ')OK=0;
		else OK=1;
	}
	map[oszl][sor]=KAJAGRAPH;
	
}




//---------------------------------------
void ammorak(char **map){
	int OK=0;
	int oszl, sor;
	srand((unsigned)time(NULL));
	while(!OK) {
		oszl=(rand()%(mapW-4))+2;
		sor=(rand()%(mapH-4))+2;
		if(map[oszl][sor]!=' ')OK=0;
		else OK=1;
	}
	map[oszl][sor]=AMMOGRAPH;
	
}
//-----------------------------------
void szellemirto(char **map) {
	int i, j;
	for (j=0;j<mapH;j++) {
		for(i=0;i<mapW;i++) {
			switch(map[i][j]) {
			case '-':map[i][j]=' ';break;
			case '+':map[i][j]=' ';break;
			case '|':map[i][j]=' ';break;
			}
		}
	}
}