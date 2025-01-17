/**********TETRIS_CLONE ver_0.1****************/
/********By AbdElMalek-L on 17.01.25***********/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 700
#define BOARD_WIDTH 20 
#define BOARD_HEIGHT 30

const int TETROMINO_I[4] = {
    1,1,1,1
    };
const int TETROMINO_L[2][4] = {
    {0,0,0,1},
    {1,1,1,1}
    };
const int TETROMINO_S[2][4] = {
    {0,1,1,1},
    {1,1,1,0}
    };
const int TETROMINO_O[2][2] = {
    {1,1},
    {1,1}
    };

   //TODO: the rest of TETROMINOS

void setConsoleSize(int width, int height);
void goToXY(short x, short y);
void drawWelcomePage(int width, int height);


int main() {
    setConsoleSize(SCREEN_WIDTH,SCREEN_HEIGHT);

    drawWelcomePage(BOARD_WIDTH,BOARD_HEIGHT);

    return 0;
}

void setConsoleSize(int width, int height) {
    HWND console = GetConsoleWindow();

    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD newSize;
    newSize.X = width;
    newSize.Y = height;

}

void goToXY(short x, short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_Pos = {x,y};

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void drawWelcomePage(int width, int height) {
    char borders = 178;
    for(int y = 0; y < width; y++){
		for(int x = 0; x < height; x++){
			if( (x == 0) || (y == 0) || (y == width-1) || (x == height-1)){
				goToXY(x,y);
				printf("%c%c",borders, borders);
			}
			
		}
	}
}