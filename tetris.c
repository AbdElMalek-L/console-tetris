/**********TETRIS_CLONE ver_0.1****************/
/********By AbdElMalek-L on 17.01.25***********/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 700
#define BOARD_HEIGHT 40 
#define BOARD_WIDTH 60 // normalment hna khasha tkon 30 walakin the 178 character am working with is too thin.{}

#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_BLUE    9
#define COLOR_DEFAULT 7 // Default console color


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

const short TETRIS_LOGO[5][23] = {
    {1,1,1,0,2,2,2,0,1,1,1,0,3,3,0,0,4,4,4,0,2,2,2},
    {0,1,0,0,2,0,0,0,0,1,0,0,3,0,3,0,0,4,0,0,2,0,0},
    {0,1,0,0,2,2,0,0,0,1,0,0,3,3,0,0,0,4,0,0,2,2,2},
    {0,1,0,0,2,0,0,0,0,1,0,0,3,0,3,0,0,4,0,0,0,0,2},
    {0,1,0,0,2,2,2,0,0,1,0,0,3,0,3,0,4,4,4,0,2,2,2}
};

void setConsoleSize(int width, int height);
void goToXY(short x, short y);
void drawWelcomePage(int width, int height);
void waitForNextFrame(short hz);
void setTextColor(short color);

boolean game_exit = 0;


int main() {
    setConsoleSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    
    while(!game_exit){
        drawWelcomePage(BOARD_WIDTH,BOARD_HEIGHT);
        waitForNextFrame(10); // Hz
	}



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

void setTextColor(short color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void goToXY(short x, short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_Pos = {x,y};

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}
void waitForNextFrame(short hz){
    int milli_seconds = 1 / hz * 1000;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds);
}

void drawWelcomePage(int height, int width) {
    char borders = 178;
    for(int x = 0; x < height; x++){
		for(int y = 0; y <width ; y++){
			if( (x == 0) || (y == 0) || (y == width-1) || (x == height-1)){
				//DONE: Borders 
                goToXY(x,y);
				printf("%c%c",borders, borders);
			}
			
		}
	}
    for(int x = 0; x < 5; x++){
		for(int y = 0; y < 23; y++){
			if(0 != TETRIS_LOGO[x][y]){

                switch (TETRIS_LOGO[x][y]) {
                    case 1: setTextColor(COLOR_RED); break;
                    case 2: setTextColor(COLOR_GREEN); break;
                    case 3: setTextColor(COLOR_YELLOW); break;
                    case 4: setTextColor(COLOR_BLUE); break;
                }
                
                goToXY(y*2+8,x+3);
				printf("%c%c" ,borders, borders);
                setTextColor(COLOR_DEFAULT); // Reset to default color
				//TODO: tetris logo

                /*
                
                ▓▓▓▓▓▓  ▓▓▓▓▓▓  ▓▓▓▓▓▓  ▓▓▓▓    ▓▓▓▓▓▓  ▓▓▓▓▓▓
                  ▓▓    ▓▓        ▓▓    ▓▓  ▓▓    ▓▓    ▓▓      
                  ▓▓    ▓▓▓▓      ▓▓    ▓▓▓▓      ▓▓    ▓▓▓▓▓▓  
                  ▓▓    ▓▓        ▓▓    ▓▓  ▓▓    ▓▓        ▓▓  
                  ▓▓    ▓▓▓▓▓▓    ▓▓    ▓▓  ▓▓  ▓▓▓▓▓▓  ▓▓▓▓▓▓  

                1111110011111100111111001111000011111100111111
                0011000011000000001100001100110000110000110000
                0011000011110000001100001111000000110000111111
                0011000011000000001100001100110000110000000011
                0011000011111100001100001100110000110000111111
                
                
                */
                

            }
        }
    }
}


