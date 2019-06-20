#include <iostream>
using namespace std;
class Desk
{
 private:
 	const char EMPTY = '-';
	const char SHIP = '+';
	char table[10][10] = {
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY},
 		{this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY,this->EMPTY}
	};
  public:
	void draw(){
		int i, j;
		for (i=0; i<10; ++i) {
			for (j=0; j<10; ++j) {
				cout << this->table[i][j];
			}
			cout << endl;
		}
	}
	void setShips(){
 		this->addShipSize(1, 4);
  		this->addShipSize(2, 3);
  		this->addShipSize(3, 2);
  		this->addShipSize(4, 1);
	}
private:
	
	void addShipSize(int size, int count) {
		int i;
		for (i=0; i<count; ++i) {
			this->addShip(size);
		}
	}
	
	void addShip(int size){
		int x, y, orient, error = 0;
		bool first = true;
		do{
			if (!first) {
				cout << "Wrong coord. Enter again..." << endl;
			}
			first = false;
			cout << "Enter X for ship (1 - 10) size " << to_string(size) << endl;
			cin >> x;
			while (x < 1 || x > 10) {
				cout << "Please 1 - 10" << endl;
				cin >> x;
			}
			x -= 1;
			cout << "Enter Y for ship (1 - 10) size " << to_string(size) << endl;
			cin >> y;
			while (y < 1 || y > 10) {
				cout << "Please 1 - 10" << endl;
				cin >> y;
			}
			y -= 1;
			cout << "Enter orientation for ship (0 - vertial, 1 - horizontal) size " << to_string(size) << endl;
			cin >> orient;
			while (orient < 0 || orient > 1) {
				cout << "Please 0 or 1" << endl;
				cin >> orient;
			}
		}while (!checkCoord(size, x, y, orient));
		this->setShip(size,x,y,orient);
	}
	
	void setShip(int size, int x,int y,int orient){
		int i;
		if (orient == 0) {
			for (i=0; i<size; ++i){
				this->table[x+i][y] = this->SHIP;
			}
		} else {
			for (i=0; i<size; ++i){
				this->table[x][y+i] = this->SHIP;
			}
		}
	}
	bool checkCoord(int size, int x, int y, int orient) {
		int cX, cY, minX, minY, maxX, maxY;
		size -= 1;
		if (orient == 0) {
			if (x + size > 9) {
				return false;
			}
			minX = x-1;
			if (minX < 0) {
				minX = 0;
			}
			maxX = x+size+1;
			if (maxX > 9) {
				maxX = 9;
			}
			minY = y-1;
			if (minY < 0) {
				minY = 0;
			}
			maxY = x+1;
			if (maxY > 9) {
				maxY = 8;
			}
		} else {
			if (y + size > 9) {
				return false;
			}
			minX = x-1;
			if (minX < 0) {
				minX = 0;
			}
			maxX = x+1;
			if (maxX > 9) {
				maxX = 9;
			}
			minY = y-1;
			if (minY < 0) {
				minY = 0;
			}
			maxY = x+size+1;
			if (maxY > 9) {
				maxY = 9;
			}
		}
		for (cX=minX; cX<=maxX; ++cX){
			for (cY=minY; cY<=maxY; ++cY){
				if (this->table[cX][cY] != this->EMPTY) {
					return false;
				}
			}
		}
		return true;
	}
};

int main(int argc, char **argv)
{
	Desk desk;
	desk.setShips();
	desk.draw();
    return 0;
}
// g++ -g -o test1 test.cpp && ./test1 < test1.data
