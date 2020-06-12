#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "econio.h"
#include "map.h"
#include "tolteny.h"
#include "player.h"
#include "fuggv.h"
//j�t�k v�ge
void gameover(int kinyert) {
	int c;
	clrscr();
	if(kinyert!=0) {
	printf("Az %d-s jatekos nyert\n",kinyert);
	}else {
		printf("dontetlen\n");
	}
	printf("nyomjon meg barmit\n");
	c=getch();
	showmenu();
}
//toplist�hoz
void nevbeker(pkigyo k) {
	FILE *fp;
	unsigned int i,pos=9;
	int beirva=0;
	char nev[7];
	int nevek[10][7];
	int meretek[10];
	clrscr();
	fp=fopen("toplista.dat","r");
	for(i=0;i<10;i++) {
		fscanf(fp,"%s",nevek[i]);
		fscanf(fp,"%d",&meretek[i]);
	}
	fclose(fp);
	if(k->meret>meretek[9]) {
		printf("\n\nIrja be a nicknevet ( 7-nel kevesebb karakter )\n");
		while(scanf("%7s",nev)!=1) {
			fflush(stdin);
			

			printf("Adja meg ujra\n");
		}
		fp=fopen("toplista.dat","w");
		for(i=0;i<9;i++) {
			if(meretek[i]<=k->meret && !beirva) {
				fprintf(fp,"%s %d\n",nev,k->meret);
				beirva=1;
			}
			fprintf(fp,"%s %d\n",nevek[i],meretek[i]);
		}
		fclose(fp);
	}
	toplista();
	showmenu();
}
//fejl�c
void fejlec(pkigyo p1, pkigyo p2) {
	printf("\tplayer1\t\t\tplayer2\n");
	printf("  ammo: %d  meret: %d\t\tammo: %d  meret:%d\n",p1->ammo,p1->meret,p2->ammo,p2->meret);
}
//menu
void showmenu(void) {
	fflush(stdin);
	clrscr();
	printf("\n\n");
	printf("1:jatek\n");
	printf("2:maganyos\n");
	printf("3:beallitasok\n");
	printf("4:toplista\n");
	printf("5:kilep\n");
	valkez();
	felszab(PL1);
	felszab(PL2);
	PL1=NULL;
	PL2=NULL;
}
//v�laszt�skezel�
void valkez(void) {
	int a;
	printf("Irja be a valasztott funkciot es nyomjon entert!\n");
	while(scanf("%d",&a)!=1) {
		fflush(stdin);
		printf("Helytelen, adja meg ujra!\n");
		
	}
	switch(a) {
	case 1: jatek();break;
	case 2: maganyos();break;
	case 3: beallitasok();break;
	case 4: toplista();break;
	case 5: kilep();break;
	default: valkez();
	}
}
//falbet�lt�
void faltolto(char** map) {
	int x,y;
	FILE *fp;
	fp=fopen("fal.dat","r");
	
	while(fscanf(fp,"%d",&x)==1) {
		fscanf(fp,"%d",&y);
		map[x][y]=WALLGRAPH;
	}
	fclose(fp);
}
//2 szem�lyes j�t�k
void jatek(void) {
	//init
	int speed;//sebess�g min�l nagyobb,ann�l lassabb, fileb�l olvassuk
	int toltspeed=4;
	int c,i=0, j;
	FILE *fp;
	//ir�ny�t� gombok
	int p1gomb[]={'i','j','k','l','o'};
	int p2gomb[]={'w','a','s','d','e'};
	//t�rk�p inicializ�l�s
	char **map=mapinit(mapW,mapH);	
	//kigyo l�trehoz�sa
	pkigyo player1=plinit(jobb,1,'X','0',5,2,10,map);
	pkigyo player2=plinit(bal,2,'@','O',70,18,10,map);
	PL1=player1;
	PL2=player2;
	//testr�szek hozz�ad�sa pl1
	hozzaad(4,2,player1);
	hozzaad(3,2,player1);
	hozzaad(2,2,player1);
	//testr�szek hozz�ad�sa pl2
	hozzaad(71,18,player2);
	hozzaad(72,18,player2);
	hozzaad(73,18,player2);
	//falak
	faltolto(map);
	fp=fopen("config.dat","r");
	fscanf(fp,"%d",&speed);
	fclose(fp);
	//glob�lis v�ltoz�k inicializ�l�sa
	elso=NULL; akt=NULL;
	vanammo=0;
	vankaja=0;
	egyjatekos=0;
	//-------------------------------------------------------
	//j�t�k
	while(1) {
		while(!kbhit()){
			torol(map);
			if(!vankaja){
				kajarak(map);
				vankaja=1;
			}
			if(!vanammo) {
				ammorak(map);
				vanammo=1;
			}
			if(i%speed==0) {
				for(j=0;j<toltspeed;j++) {
					//
					szellemirto(map);
					toltmozgat(map,player1,player2);
				}
				
				mozgat(player1,map);
				mozgat(player2,map);
				clrscr();
				fejlec(player1,player2);
				kirajzol(map);
			}
			i++;
		}
		//ha megnyomott vmit
		c=getch();
		//ha r�tenyerelt volna a billenty�zetre
		fflush(stdin);
		//megfelel� m�velet v�grehajt�sa
		gombelkap(p1gomb,c,player1);
		gombelkap(p2gomb,c,player2);
		//ha kil�pett
		if(c=='t') showmenu();
	}
	//j�t�k v�ge
	
}
//mag�nyos j�t�k
void maganyos(void) {
	//init
	int speed;
	int toltspeed=4;
	int c,i=0;
	FILE *fp;
	//ir�ny�t� gombok
	int p1gomb[]={'w','a','s','d','e'};
	//t�rk�p inicializ�l�s
	char **map=mapinit(mapW,mapH);
	//kigyo l�trehoz�sa
	pkigyo player1=plinit(jobb,1,'X','0',5,0,0,map);
	PL1=player1;
	//testr�szek hozz�ad�sa
	hozzaad(4,0,player1);
	hozzaad(3,0,player1);
	hozzaad(2,0,player1);
	//falak
	faltolto(map);
	
	fp=fopen("config.dat","r");
	fscanf(fp,"%d",&speed);
	fclose(fp);
	//j�t�kosokat t�rol� t�mb felt�lt�se
	//players[0]=player1;
	//glob�lis v�ltoz�k inicializ�l�sa
	elso=NULL; akt=NULL;
	vanammo=1;//ne l�v�ld�zz�n
	vankaja=0;
	egyjatekos=1;

	
	
	
	//-------------------------------------------------------
	//j�t�k
	while(1) {
		while(!kbhit()){
			torol(map);
			if(!vankaja){
				kajarak(map);
				vankaja=1;
			}
			if(i%speed==0) {

				mozgat(player1,map);
				clrscr();
				printf("\t\tmeret: %d\n",player1->meret);
				kirajzol(map);
			}
			i++;
		}
		
		//ha megnyomott vmit
		c=getch();
		//ha r�tenyerelt volna a billenty�zetre
		fflush(stdin);
		//megfelel� m�velet v�grehajt�sa
		gombelkap(p1gomb,c,player1);
		//ha kil�pett
		if(c=='t'){nevbeker(player1);free(player1);}
	}
	//j�t�k v�ge
	

}
//beallitasok
void beallitasok(void) {
	FILE *fp;
	int a,uj;
	fp=fopen("config.dat","r");
	fscanf(fp,"%d",&a);
	fclose(fp);
	clrscr();
	printf("\nA jatek jelenlegi sebessege: %d\n",a);
	printf("Irj be egy nagyobb szamot, ha lassitani, kisebbet, ha gyorsitani akarod, 0-t ha ne valtozzon\n");
	printf("Az ertek ne haladja meg a 32000-t\n");
	printf("uj sebesseg: ");
	while(scanf("%d",&uj)!=1) {
		fflush(stdin);
		printf("\nAdja meg ujra:");
	}
	if(uj>0 && uj<=32000) {
		fp=fopen("config.dat","w");
		fprintf(fp,"%d",uj);
		fclose(fp);
	}
	showmenu();


}
//toplista
void toplista(void) {
	FILE *fp;
	int i,c;
	int nevek[10][8];
	int meretek[10];
	clrscr();
	fp=fopen("toplista.dat","r");
	printf("\nNEV\tPONT\n");
	for(i=0;i<10;i++) {
		fscanf(fp,"%s",nevek[i]);
		fscanf(fp,"%d",&meretek[i]);
		printf("%s\t%d\n",nevek[i],meretek[i]);
	}
	fclose(fp);
	printf("\n\nNyomjon meg barmit\n");
	c=getch();
	showmenu();

	

}
//kil�p�s
void kilep(void) {
	exit(0);
}

