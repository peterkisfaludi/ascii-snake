#include "player.h"
#include "tolteny.h"
#include "fuggv.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
void mozgat(pkigyo k,char **map) {
	pelem akt=k->farok;
	pelem mozog;
	if(k->meret==0)gameover((k->ID==1)?2:1);
	for(;akt->kov!=NULL;akt=akt->kov) {
		akt->_x=akt->kov->_x;
		akt->_y=akt->kov->_y;
		map[akt->_x][akt->_y]=k->testgraph;
	}
	//ezután kell megmozdítani a fejet, mert különben lyukas lesz
	switch(k->irany){
	case fel:k->fej->_y--;break;
	case le:k->fej->_y++;break;
	case jobb:k->fej->_x++;break;
	case bal:k->fej->_x--;break;
	}
	//kiment a világból
	if(k->fej->_x<0 || k->fej->_x>mapW-1 || k->fej->_y<0 || k->fej->_y>mapH-1) {
		if(!egyjatekos) {
			gameover((k->ID==1)?2:1);
		}else {
			nevbeker(k);
		}

	}
	//ütközés önmagával, kivéve ha 1 hosszú
	if(k->meret!=1){
		for(mozog=k->farok;mozog->kov!=k->fej;mozog=mozog->kov) {
		
			if(mozog->_x==k->fej->_x && mozog->_y==k->fej->_y) {
				if(!egyjatekos) {
					gameover((k->ID==1)?2:1);
				}else {
					nevbeker(k);
				}
			}
		
		}
	}
	//többiekkel, ha többen vannak
	if(!egyjatekos) {
		if(PL1->fej->_x==PL2->fej->_x && PL1->fej->_y==PL2->fej->_y)gameover(0);
		if(k==PL1) {
			for(mozog=PL2->farok;mozog!=NULL;mozog=mozog->kov) {
				if(mozog->_x==k->fej->_x && mozog->_y==k->fej->_y) {
					gameover(2);
				}
			}
		}
		if(k==PL2) {
			for(mozog=PL1->farok;mozog!=NULL;mozog=mozog->kov) {
				if(mozog->_x==k->fej->_x && mozog->_y==k->fej->_y) {
					gameover(1);
				}
			}
		}
	}
	//fallal
	if(map[k->fej->_x][k->fej->_y]==WALLGRAPH) {
		if(!egyjatekos) {
			gameover((k->ID==1)?2:1);
		}else {
			nevbeker(k);
		}
	}
	//eszik
	switch(map[k->fej->_x][k->fej->_y]){
	case KAJAGRAPH:
		hozzaad(k->farok->_x,k->farok->_y,k);
		vankaja=0;
		break;
	//felvesz töltényt
	case AMMOGRAPH:
		ammofelv(k);
		vanammo=0;
		break;
	}
	map[k->fej->_x][k->fej->_y]=k->fejgraph;
}
//--------------------------------
void hozzaad(int _x,int _y,pkigyo k) {
	pelem a=(pelem)malloc(sizeof(elem));
	a->_x=_x;
	a->_y=_y;
	a->kov=k->farok;
	k->farok=a;
	k->meret++;
}
//-----------------------------------------------
pkigyo plinit(direction irany,int ID, int testgraph,int fejgraph,int _x,int _y,int ammo,char **map) {
	//lefoglalunuk memóriát
	pkigyo k=(pkigyo)malloc(sizeof(kigyo));
	//inicializálás
	k->farok=NULL;
	k->fej=NULL;
	k->fejgraph=fejgraph;
	k->testgraph=testgraph;
	k->irany=irany;
	k->ammo=ammo;
	k->meret=0;
	k->ID=ID;
	hozzaad(_x,_y,k);
	k->fej=k->farok;
	//visszaad egy mutatót
	return k;
	
}
//------------------------------------------------
void gombelkap(int gombok[], int c,pkigyo k) {
	//gombok a tömbben fel balra le jobbra lövés sorrendben vannak
	if(gombok[0]==c){if(k->irany!=le)k->irany=fel;}
	if(gombok[1]==c){if(k->irany!=jobb)k->irany=bal;}
	if(gombok[2]==c){if(k->irany!=fel)k->irany=le;}
	if(gombok[3]==c){if(k->irany!=bal)k->irany=jobb;}
	if(gombok[4]==c)shoot(k);
}
//------------------------------------------------
void csokken(pkigyo k) {
	pelem t=k->farok;
	k->farok=k->farok->kov;
	free(t);
	k->meret--;
}
void felszab(pkigyo k){
	int i,hatar=k->meret;
	for(i=0;i<hatar;i++) {
		csokken(k);
	}
}

//-----------------------------------------------------
void ammofelv(pkigyo k) {
	k->ammo++;
}
