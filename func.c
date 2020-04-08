#include <stdio.h>
#include<windows.h>
#include "tetris.h"


extern unsigned char base[SIZE_HIGH][SIZE_WIDTH];
extern unsigned char display[SIZE_HIGH][SIZE_WIDTH];
extern unsigned char previous[SIZE_HIGH][SIZE_WIDTH];
extern Blocks blockType[NUM_BLOCK][4][4];



void init(){
	int i,k;//base setting
	//기준 좌표값 초기화
	bRow=1;
	bColumn=SIZE_WIDTH/2;

	for(i=0;i<SIZE_HIGH; i++){
		for(k=0; k<SIZE_WIDTH; k++){
			base[i][k]=B_SPACE;
			display[i][k]=B_SPACE;
			previous[i][k]=B_SPACE;
		}
	}

	//벽 만들기
	for(i=0;i<SIZE_WIDTH;i++){
		base[0][i]=B_WALL;
		base[SIZE_HIGH-1][i]=B_WALL;
		display[0][i]=B_WALL;
		display[SIZE_HIGH-1][i]=B_WALL;
	}

	for(k=0;k<SIZE_HIGH;k++){
		base[k][0]=B_WALL;
		base[k][SIZE_WIDTH-1]=B_WALL;
		display[k][0]=B_WALL;
		display[k][SIZE_WIDTH-1]=B_WALL;
	}
	
}

void show(){
	int i,k;

	//display print
	for(i=0;i<SIZE_HIGH;i++){
		for(k=0; k<SIZE_WIDTH;k++){
			if(display[i][k] != previous[i][k]){
				gotoxy(2*k, i);
				switch(display[i][k]){
					case B_SPACE:
						printf(" ");
						break;
					case B_WALL:  
						printf("□");
						break;
					case B_BLCOK_A:	
						printf("■");
						break;
					case B_BLCOK_B:		
						printf("■");
						break;
					case B_BLCOK_C:
						printf("■");
						break;
					case B_BLCOK_D:
						printf("■");
						break;
					case B_BLCOK_E:
						printf("■");
						break;
					default:
						break;
				}//좌표이동,프린트
			}
		}
	}
	for(i=0;i<SIZE_WIDTH;i++){
		for(k=0;k<SIZE_HIGH;k++){
			previous[i][k]=display[i][k];
		}
	}
}
void newBlock(){
	bType=rand()%NUM_BLOCK;
	bDir=rand()%4;
}
/*int getKey(){

}*/
void gotoxy (int x,int y){

	static HANDLE h = NULL;
	COORD c = { x, y };

	if (!h){
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);

}
void moveBlock(int row, int column, int dir){
	int i,k;
	int x,y;
	//base copy
	for(i=0;i<SIZE_HIGH;i++){
		for(k=0;k<SIZE_WIDTH;k++){
			display[i][k]=base[i][k];
		}
	}
	//add block
	for(i=0;i<4;i++){
		x=bColumn+blockType[bType][bDir][i].x;
		y=bRow+blockType[bType][bDir][i].y;

		display[y][x]=bType;
	}
}