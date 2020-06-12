#include "tolteny.h"
#include "econio.h"
#include "fuggv.h"
#include "player.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------
ptolt toltinit(pkigyo k) {
	// a t�lt�ny a k�gy� feje el�tt jelenik meg
	ptolt t=(ptolt)malloc(sizeof(tolt));
	t->irany=k->irany;
	t->_x=k->fej->_x;
	t->_y=k->fej->_y;
	/*switch(t->irany) {
	case fel:t->_y--;break;
	case le:t->_y++;break;
	case bal:t->_x--;break;
	case jobb:t->_x++;break;
	
	}*/
	t->kov=NULL;
	if(akt!=NULL) akt->kov=t;
	if(elso==NULL) elso=t;
	akt=t;
	return t;
}
//------------------------------------------------
void shoot(pkigyo k) {
	if(k->ammo!=0) {
		ptolt t=toltinit(k);
		k->ammo--;
		//vmilyen hang lej�tsz�sa
	}
}
//-----------------------------------------------
void tolttorol(ptolt t) {
	//ha az els�
	if(t==elso) {
		elso=t->kov;
	} else {
		ptolt lemarado;
		for(lemarado=elso;lemarado->kov!=t;lemarado=lemarado->kov);
		lemarado->kov=t->kov;
		if(t==akt) akt=lemarado;
	}
	//ha m�gsem tudn� felszabad�tani, legal�bb der�lj�n ki
	t=NULL;
	free(t);
}
//-------------------------------------------------
void toltmozgat(char **map, pkigyo p1, pkigyo p2) {
	ptolt mozog;
	pelem a;
	
	for(mozog=elso;mozog!=NULL;mozog=mozog->kov) {
		switch(mozog->irany) {
		case bal:mozog->_x--;break;
		case jobb:mozog->_x++;break;
		case fel:mozog->_y--;break;
		case le:mozog->_y++;break;
		}

		//�tk�z�svizsg�lat �s kirajzol�s
		//fal
		if(mozog->_x<0 || mozog->_x>mapW-1 || mozog->_y<0 || mozog->_y>mapH) {
			tolttorol(mozog);
			break;
		}
		//player 1

		for(a=p1->farok;a!=NULL;a=a->kov){
			if(a->_x==mozog->_x && a->_y==mozog->_y) {
			tolttorol(mozog);
			csokken(p1);
			break;
			}
		}
		//player 2
		for(a=p2->farok;a!=NULL;a=a->kov){
			if(a->_x==mozog->_x && a->_y==mozog->_y) {
			tolttorol(mozog);
			csokken(p2);
			break;
			}
		}
		switch(map[mozog->_x][mozog->_y]) {
			//nem keresztez
		case ' ' :
			if(mozog->irany==fel || mozog->irany==le) map[mozog->_x][mozog->_y]='|';
			if(mozog->irany==bal || mozog->irany==jobb) map[mozog->_x][mozog->_y]='-';
			break;
			//keresztez
		case '-':
			if(mozog->irany==fel || mozog->irany==le) map[mozog->_x][mozog->_y]='+';
			break;
		case '|':
			if(mozog->irany==bal || mozog->irany==jobb) map[mozog->_x][mozog->_y]='+';
			break;
		
		}
		//tov�bbi dolgok nem konstans kifejez�sekkel
		//fal
		if(map[mozog->_x][mozog->_y]==WALLGRAPH){
			tolttorol(mozog);
			break;
		}
		
	}
}
			




