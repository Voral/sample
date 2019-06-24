#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char EMPTY = '-';
const char SHIP = '+';
const char RANGE_Y[10] = "abcdefghkl";
const char RANGE_DIRECT[4] = "rlud";
const char DIRECT_UP = 'u';
const char DIRECT_DOWN = 'd';
const char DIRECT_LEFT = 'l';
const char DIRECT_RIGHT = 'r';

char desk[10][10] = {};

int checkCoord(int x, int y, char direct, int size);
int checkAndSetShip(char cx, char cy, char direct, int size);
void addShip();
void setShips();
void draw();
void setShip(int x, int y, char direct, int size);
void addShipsForSize(int size, int count);


int main(int argc, char **argv)
{
	memset(desk, EMPTY, sizeof(desk));
	setShips();
	draw();
    return 0;
}

void setShips(){
	addShipsForSize(1, 4);
	addShipsForSize(2, 3);
	addShipsForSize(3, 2);
	addShipsForSize(4, 1);
}

void addShipsForSize(int size, int count) {
	int i;
	for (i=0; i<count; ++i) {
		addShip(i, size);
	}
}

void addShip(int number,int size) {
	char a[5] = {'-','-','-','-','-'}, first = 1;
	do{
		if (!first) {
			puts("Wrong params. Enter again...");
		}
		first = 0;
		printf("Enter params for ship %d size %d <x>.<y>[.<direct>]\r\n",number,size);
		scanf("%c.%c.%c", &a[0], &a[2], &a[4]);
	}while (checkAndSetShip(a[0],a[2],a[4],size) == 0);
}

int checkAndSetShip(char cx, char cy, char direct, int size){
	int x = cx - '0' - 1;
	char posY = strchr (RANGE_Y,cy);	

	if (posY==NULL || x<0 || x>9 || (size>1 && strchr(RANGE_DIRECT,direct) == NULL)) return 0;
		
	int	y = strchr (RANGE_Y,cy) - RANGE_Y;
	
	if (direct == DIRECT_UP) {
		x -= (size - 1);
		direct = DIRECT_DOWN;
	} else if (direct == DIRECT_LEFT) {
		y -= (size - 1);
		direct = DIRECT_RIGHT;
	}
	
	if (checkCoord(x,y,direct,size) == 0) {
		return 0;
	}
	
	setShip(x,y,direct,size);
	
	return 1;
}

void draw(){
	int i,j;
	for (i=0; i<10; ++i) {
		for (j=0; j<10; ++j) {
			printf("%c", desk[i][j]);
		}
		printf("\r\n");
	}
}

void setShip(int x, int y, char direct, int size){
	int i;
	if (direct == DIRECT_DOWN) {
		for (i=0; i<size; ++i){
			desk[x+i][y] = SHIP;
		}
	} else {
		for (i=0; i<size; ++i){
			desk[x][y+i] = SHIP;
		}
	}	
}

int checkCoord(int x, int y, char direct, int size){
	int cX, cY, minX, minY, maxX, maxY;
	size -= 1;
	if (direct == DIRECT_DOWN) {
		if (x + size > 9) return 0;
		minX = x - 1;
		if (minX < 0) minX = 0;
		maxX = x + size + 1;
		if (maxX > 9) maxX = 9;
		minY = y - 1;
		if (minY < 0) minY = 0;
		maxY = x + 1;
		if (maxY > 9) maxY = 8;
	} else {
		if (y + size > 9) return 0;
		minX = x-1;
		if (minX < 0) minX = 0;
		maxX = x + 1;
		if (maxX > 9) maxX = 9;
		minY = y - 1;
		if (minY < 0) minY = 0;
		maxY = x + size + 1; 
		if (maxY > 9) maxY = 9;
	}
	for (cX=minX; cX<=maxX; ++cX){
		for (cY=minY; cY<=maxY; ++cY){
			if (desk[cX][cY] != EMPTY) {
				return 0;
			}
		}
	}
	return 1;
}
// gcc -Wall -o test_c test.c && test_c
