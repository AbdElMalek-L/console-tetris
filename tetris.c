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

#define RECT_CHAR 178

#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_BLUE    9
#define COLOR_MAGENTA 5
#define COLOR_DEFAULT 7 // Default console color




typedef struct {
    int shape[4][4]; // 4x4 grid for each Tetromino
    int color;       // Color index
} Tetromino;

Tetromino tetrominos[7] = {
    { { {0,0,0,0}, 
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0} }, 1 }, // I
    { { {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0} }, 2 }, // T
    { { {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0} }, 3 }, // S
    { { {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0},
        {0,0,0,0} }, 4 }, // Z
    { { {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0} }, 5 }, // L
    { { {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0},
        {0,0,0,0} }, 6 }, // J


    // Add other Tetrominos
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
void drawTetromino(Tetromino tetromino, short x, short y);
void clearScreen();

boolean game_exit = 0;


int main() {
    setConsoleSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    int time = clock();
    int topPosition = 0;
    while(!game_exit){
        drawWelcomePage(BOARD_WIDTH,BOARD_HEIGHT);
        waitForNextFrame(10); // Hz
        
        if (topPosition < BOARD_HEIGHT-1 && clock() > time + 300  ){
            clearScreen();
            drawTetromino(tetrominos[0],topPosition,5);
            drawTetromino(tetrominos[4],topPosition,23);
            drawTetromino(tetrominos[1],topPosition,33);
            time += 300;
            topPosition += 1;
        } else {
            ;
        }

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
    int milli_seconds = 1000 / hz;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds);
}

void drawWelcomePage(int height, int width) {
    for(int x = 0; x <= height; x++){
		for(int y = 0; y <= width ; y++){
			if( (x == 0) || (y == 0) || (y == width) || (x == height)){
				//DONE: Borders 
                goToXY(x,y);
				printf("%c%c",RECT_CHAR, RECT_CHAR);
			}
			
		}
	}
    for(int x = 0; x < 5; x++){
		for(int y = 0; y < 23; y++){
			if(0 != TETRIS_LOGO[x][y]){

                switch (TETRIS_LOGO[x][y]) {
                    case 1: setTextColor(COLOR_BLUE ); break;
                    case 2: setTextColor(COLOR_GREEN); break;
                    case 3: setTextColor(COLOR_YELLOW); break;
                    case 4: setTextColor(COLOR_RED); break;
                }
                
                goToXY(y*2+8,x+3);
				printf("%c%c" ,RECT_CHAR, RECT_CHAR);
                setTextColor(COLOR_DEFAULT); // Reset to default color

            }
        }
    }
}

void drawTetromino(Tetromino tetromino, short x, short y){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tetromino.shape[i][j] != 0){

                switch (tetromino.color) {
                    case 1: setTextColor(COLOR_BLUE ); break;
                    case 2: setTextColor(COLOR_GREEN); break;
                    case 3: setTextColor(COLOR_YELLOW); break;
                    case 4: setTextColor(COLOR_RED); break;
                }
                
                goToXY(j*2+y,i+x);
				printf("%c%c" ,RECT_CHAR, RECT_CHAR);
                setTextColor(COLOR_DEFAULT); // Reset to default color

            }
        }
    }
}

void clearScreen() {
    system("cls"); // Clears the console screen (Windows-specific)
}
