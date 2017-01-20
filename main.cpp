//Jaanvir, Go Diego, Go, and Kaanstantinople
#include <iostream>
#include <stdio.h>//ALLOWS USER TO INPUT FUNCTIONS FROM A USER THROUGH USE OF CONTROLLER (TMP FILE, PRINT, OPEN AND SCAN)
#include <windows.h>//GET ASNY KEY DEFINES MOVEMENT
#include <vector>

using namespace std;
char dab_map[18][32];

char map[18][32] = {
	" _____________________________ ",
	"|              | |            |",
	"| ,__,  ,___,  | |  ,___,     |",
	"| |__|  |___|  |_|  |___|     |",
	"|                             |",
	"| ,__,          ,_______,     |",
	"| |__|          |_______|     |",
	"|       ,___,                 |",
	"|       |___|                 |",
	"|  ,_,              ,_____,   |",
	"|  |_|      ,___,   |_____|   |",
	"|           |___|             |",
	"|                             |",
	"|      ,_______________,      |",
	"|      |_______________|      |",
	"|                             |",
	"|             | |             |",
	" _____________|_|_____________ "
	};

void ShowMap()
{
	for(int i = 0; i < 18; i++) {
		printf("%s\n",map[i] );
	}
}

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

class communism {
public:
	communism( int x, int y ){
		this ->x = x;
		this ->y = y;
	}

	void move_x( int p ){
		if( map[y][x+p] == ' ' ) x += p;
	}

	void move_y( int p ){
		if( map[y+p][x] == ' ' ) y += p;
	}

	void move( int p, int q ){
		x += p;
		y += q;
	}

	int get_x(){ return x; }
	int get_y(){ return y; }

	void draw( char p ){
		map[x][y] = p;
		gotoxy( x, y ); printf( "%c", p );
	}

private:
	int x;
	int y;
};

struct sanic {
	short sanic_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};

vector<target> sanic_queue;

vector<sanic> MEXArray;

void AddArray( int x, int y, int wc , int back ){
	if( dab_map[y][x] == ' ' || dab_map[y][x] == '.' ){
		dab_map[y][x] = '#';
		sanic dab;
		dab.x = x;
		dab.y = y;
		dab.sanic_count = wc;
		dab.back = back;
		MEXArray.push_back( dab );
	}
}

void FindPath( int sx, int sy, int x, int y ){
	memcpy( dab_map, map, sizeof(map) );
	MEXArray.clear();
	sanic dab;
	dab.x = sx;
	dab.y = sy;
	dab.sanic_count = 0;
	dab.back = -1;
	MEXArray.push_back( dab );

	int i = 0;
	while( i < MEXArray.size() ){
		if( MEXArray[i].x == x && MEXArray[i].y == y ){
			sanic_queue.clear();
			target dab2;
			while( MEXArray[i].sanic_count != 0 ){
				dab2.x = MEXArray[i].x;
				dab2.y = MEXArray[i].y;
				sanic_queue.push_back( dab2 );

				i = MEXArray[i].back;
			}

			break;
		}

		AddArray( MEXArray[i].x+1, MEXArray[i].y, MEXArray[i].sanic_count+1, i );
		AddArray( MEXArray[i].x-1, MEXArray[i].y, MEXArray[i].sanic_count+1, i );
		AddArray( MEXArray[i].x, MEXArray[i].y+1, MEXArray[i].sanic_count+1, i );
		AddArray( MEXArray[i].x, MEXArray[i].y-1, MEXArray[i].sanic_count+1, i );


		i++;
	}

	MEXArray.clear();
}


int main()
{
    bool running = true;
	int x = 15;
	int y = 16;
	int old_x;
	int old_y;

	int ex = 1;
	int ey = 1;


	int pts = 0;

	cout<< "Instruction:\n1. Arrow Keys to move Shrek\n2. Eat the dots from Lord Farquaad to gain points\n3. Don't get caught by Lord Farquaad\n\n" << endl;
	printf("H -> Hard\nN -> Normal\nE -> EZ/Noob level\n\nInput : ");

	char diffi;
	int speedmod = 3;

	cin >> diffi;

	if( diffi == 'N' ){
		speedmod = 2;
	}else if( diffi == 'H' ){
		speedmod = 1;
	}

	system("cls");
    ShowMap();

	gotoxy( x, y ); cout << "H";

	int frame = 0;

	FindPath( ex,ey,x,y );

	while( running ){
		gotoxy( x, y ); cout << " ";

		old_x = x;
		old_y = y;

		if ( GetAsyncKeyState( VK_UP ) ){
			if( map[y-1][x] == '.' ){ y--; pts++; } else
			if( map[y-1][x] == ' ' ) y--;
		}
		if ( GetAsyncKeyState( VK_DOWN ) ){
			if( map[y+1][x] == '.' ){ y++; pts++; } else
			if( map[y+1][x] == ' ' ) y++;
		}
		if ( GetAsyncKeyState( VK_LEFT ) ){
			if( map[y][x-1] == '.' ){ x--; pts++; } else
			if( map[y][x-1] == ' ' ) x--;
		}
		if ( GetAsyncKeyState( VK_RIGHT ) ){
			if( map[y][x+1] == '.' ){ x++; pts++; } else
			if( map[y][x+1] == ' ' ) x++;
		}

		if( old_x != x || old_y != y ){
			FindPath( ex,ey,x,y );
		}

		gotoxy( x,y ); cout << "S";

		map[ey][ex] = '.';
		gotoxy( ex, ey ); cout << ".";

		if( frame%speedmod == 0 && sanic_queue.size() != 0 ){
			ex = sanic_queue.back().x;
			ey = sanic_queue.back().y;
			sanic_queue.pop_back();
		}

		gotoxy( ex, ey ); cout << "F";

		if( ex == x && ey == y ){
			break;
		}


		gotoxy( 32, 18 );
		gotoxy( 32, 1 ); cout << pts;
		Sleep( 100 );
		frame++;
	}

	system("cls");
	printf("You Lost?!? What the Shrek my dood?!?\nThanks to you, Farquad has taken ogre!\nWay to go, dorc.\nYour dank score is : %i ", pts );
	cin.get();
	cin.get();

	return 0;
}
