/**********TETRIS_CLONE ver_0.1****************/
/********By AbdElMalek-L on 17.01.25***********/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 600
#define BOARD_HEIGHT 32 
#define BOARD_WIDTH 60 // normalment hna khasha tkon 30 walakin the 178 character am working with is too thin.{}

#define RECT_CHAR 178

#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_BLUE    9
#define COLOR_MAGENTA 5
#define COLOR_DEFAULT 7 // Default console color

typedef struct {
    int shape[3][3]; // 3x3 grid for each Tetromino
    int color;       // Color index
} Tetromino;

Tetromino tetrominos[7] = {
    { { {0,1,0}, 
        {0,1,0},
        {0,1,0} }, 1 }, // I
    { { {0,1,0},
        {1,1,1},
        {0,0,0} }, 2 }, // T
    { { {0,1,1},
        {1,1,0},
        {0,0,0} }, 3 }, // S
    { { {1,1,0},
        {0,1,1},
        {0,0,0} }, 4 }, // Z
    { { {0,0,1},
        {1,1,1},
        {0,0,0} }, 5 }, // L
    { { {1,1,1},
        {0,0,1},
        {0,0,0} }, 6 }, // J
    { { {1,1,0},
        {1,1,0},
        {0,0,0} }, 6 }, // O
};

Tetromino cureent_tetromino = { { {0,0,0}, 
                                  {0,0,0},
                                  {0,0,0} }, 6 };

short game_matrix[20][15] = {
    {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 1, 3, 4, 4, 4, 3, 0, 0, 0, 0, 0, 0,},
    {0, 2, 0, 1, 3, 3, 5, 4, 3, 3, 0, 0, 0, 0, 0,},
    {2, 2, 2, 1, 0, 3, 5, 5, 5, 3, 0, 0, 0, 1, 4,}
};

void setConsoleSize(int width, int height);
void goToXY(short x, short y);
void drawBorders(int width, int height);
void drawWelcomePage(int width, int height);
void waitForNextFrame(short hz);
void setTextColor(short color);
void drawTetromino(Tetromino tetromino, short x, short y); //DELET THIS
void clearScreen();
void drawBorders(int width, int height);
void drawPlayBoard();
void drawGame();
void resetGame();
void rotateTetromino();
void placeTetromino(int vertical_position,int horizontal_position);
void drawNext();

int score = 0;
int next = 3;

int main() {

    setConsoleSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    int time = clock(); // Initialize timing
    int horizontal_position = 0;
    int vertical_position = 0; // Initialize Tetromino position
    next = rand()%7;

    cureent_tetromino = tetrominos[3];

    boolean game_exit = 0;
    boolean game_over = 0;

    drawWelcomePage(BOARD_WIDTH, BOARD_HEIGHT);

    while(!game_exit){
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            clearScreen();
            drawPlayBoard();
            resetGame();


            while (!game_over) {

                if (vertical_position < 17 && clock() > time + 600) {
                    time = clock(); // Reset the timer
                    vertical_position += 1; // Move Tetromino down
                    drawGame();
                    drawNext();
                    drawTetromino(cureent_tetromino, vertical_position, horizontal_position);
                }
                if(GetAsyncKeyState(VK_UP) & 0x8000){
                    rotateTetromino();
                    drawGame();
                    drawTetromino(cureent_tetromino, vertical_position, horizontal_position);

                }
                if(GetAsyncKeyState(VK_LEFT) & 0x8000 && horizontal_position > 0 ){
                    horizontal_position--;
                    drawGame();
                    drawTetromino(cureent_tetromino, vertical_position, horizontal_position);

                }
                if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && horizontal_position < 12){
                    horizontal_position++;
                    drawGame();
                    drawTetromino(cureent_tetromino, vertical_position, horizontal_position);

                }
                waitForNextFrame(10); // Control frame rate
            }
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

void drawBorders(int width, int height){
    for(int x = 0; x <= height; x++){
        for(int y = 0; y < width ; y++){
            if( (x == 0) || (y == 0) || (y == width-1) || (x == height)){
                //DONE: Borders 
                goToXY(x,y);
                printf("%c%c",RECT_CHAR, RECT_CHAR);
            }
        }
    }
}

void drawTetrisLogo(){
    short TETRIS_LOGO[5][23] = {
        {1,1,1,0,2,2,2,0,1,1,1,0,3,3,0,0,4,4,4,0,2,2,2},
        {0,1,0,0,2,0,0,0,0,1,0,0,3,0,3,0,0,4,0,0,2,0,0},
        {0,1,0,0,2,2,0,0,0,1,0,0,3,3,0,0,0,4,0,0,2,2,2},
        {0,1,0,0,2,0,0,0,0,1,0,0,3,0,3,0,0,4,0,0,0,0,2},
        {0,1,0,0,2,2,2,0,0,1,0,0,3,0,3,0,4,4,4,0,2,2,2}
    };
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 23; y++){
            if(0 != TETRIS_LOGO[x][y]){
                switch (TETRIS_LOGO[x][y]) {
                    case 1: setTextColor(COLOR_BLUE ); break;
                    case 2: setTextColor(COLOR_GREEN); break;
                    case 3: setTextColor(COLOR_MAGENTA); break;
                    case 4: setTextColor(COLOR_RED); break;
                    case 5: setTextColor(COLOR_YELLOW); break;
                }
                goToXY(y*2+8,x+6 );
                printf("%c%c" ,RECT_CHAR, RECT_CHAR);
                setTextColor(COLOR_DEFAULT); // Reset to default color
            }
        }
    }
}

void drawPlayBoard() {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (
                (y >= 3 && y <= 5 && x >= 22 && x <= 42) ||   // score box
                (y >= 8 && y <= 27 && x >= 6 && x <= 36) ||   // play box
                (y >= 11 && y <= 17 && x >= 40 && x <= 58) || // next icon box
                (y >= 19 && y <= 21 && x >= 42 && x <= 56)    // next text box
            ) {
                printf("  "); // Draw rectangle
            } else {
                goToXY(x, y);
                printf("%c%c", RECT_CHAR, RECT_CHAR);
            }
        }
    }
}

void drawGame(){
    for(int y = 0; y < 20; y++){
        for(int x = 0;x < 15; x++){
            if(game_matrix[y][x] != 0 ){
                switch (game_matrix[y][x]) {
                    case 1: setTextColor(COLOR_MAGENTA ); break;
                    case 2: setTextColor(COLOR_GREEN ); break;
                    case 3: setTextColor(COLOR_BLUE ); break;
                    case 4: setTextColor(COLOR_RED ); break;
                    case 5: setTextColor(COLOR_YELLOW ); break;
                }
                goToXY(x*2+7,y+8 );
                printf("%c%c" ,RECT_CHAR, RECT_CHAR);
                setTextColor(COLOR_DEFAULT); // Reset to default color
            } else {
                goToXY(x*2+7,y+8 );
                printf("  ");
            }
        }
    }
    goToXY(28,4);
    printf("Score: %d", score);

    goToXY(45,20);
    printf("Next: %d", next);
}

void drawNext(){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            if(tetrominos[next].shape[x][y] != 0){
                switch (tetrominos[next].color) {
                    case 1: setTextColor(COLOR_MAGENTA ); break;
                    case 2: setTextColor(COLOR_GREEN ); break;
                    case 3: setTextColor(COLOR_BLUE ); break;
                    case 4: setTextColor(COLOR_RED ); break;
                    case 5: setTextColor(COLOR_YELLOW ); break;
                }
                goToXY(x*2+47,y+13 );
                printf("%c%c" ,RECT_CHAR, RECT_CHAR);
                setTextColor(COLOR_DEFAULT); // Reset to default color
            } else {
                goToXY(x*2+47,y+13 );
                printf("  ");
            }
        }
    }
}

void resetGame(){
    for(int y = 0; y < 20; y++){
        for(int x = 0;x < 15; x++){
            game_matrix[y][x] = 0;
        }
    }
}

void rotateTetromino(){
    Tetromino temp_tetromino;

    // Rotate the Tetromino 90 degrees clockwise
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            temp_tetromino.shape[y][2 - x] = cureent_tetromino.shape[x][y];
        }
    }
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            cureent_tetromino.shape[x][y] = temp_tetromino.shape[x][y];
        }
    }
}

void placeTetromino(int vertical_position,int horizontal_position){
    for(int y = 0; y < 20; y++){
        for(int x = 0;x < 15; x++){
            if(y == vertical_position && x == horizontal_position){
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        game_matrix[y+i][x+j] = cureent_tetromino.shape[i][j];
                        // if(game_matrix[y-1][x+j] == cureent_tetromino.color){
                            game_matrix[y-1][x+j] =  0;
                        // }

                    }
                }
            }
        }
    }
}

void drawWelcomePage(int height, int width) {
    drawBorders(width, height);
    drawTetrisLogo();
    goToXY(5,15);
    printf("Enter:          To start the game.");
    goToXY(5,16);
    printf("Left Arrow:     Move the Tetromino left.");
    goToXY(5,17);
    printf("Right Arrow:    Move the Tetromino right.");
    goToXY(5,18);
    printf("Down Arrow:     Speed up the Tetromino's fall.");
    goToXY(5,19);
    printf("Up Arrow:       Rotate the Tetromino.");
    goToXY(5,20);
    printf("Q:              Quit the game.");
    goToXY(BOARD_WIDTH - 31,BOARD_HEIGHT-2);
    setTextColor(COLOR_BLUE );    
    printf("~Made by ");
    setTextColor(COLOR_DEFAULT); 
    printf("@AbdElMalek-L ");
    setTextColor(COLOR_BLUE );    
    printf("with ");
    setTextColor(COLOR_RED);
    printf("<3");
    setTextColor(COLOR_DEFAULT); // Reset to default color
}

void drawTetromino(Tetromino tetromino, short x, short y){
    x += 8;
    y = y*2+7;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(tetromino.shape[i][j] != 0){
                switch (tetromino.color) {
                    case 1: setTextColor(COLOR_MAGENTA ); break;
                    case 2: setTextColor(COLOR_GREEN ); break;
                    case 3: setTextColor(COLOR_BLUE ); break;
                    case 4: setTextColor(COLOR_RED ); break;
                    case 5: setTextColor(COLOR_YELLOW ); break;
                }
                goToXY(j*2+y,i+x);
                printf("%c%c" ,RECT_CHAR, RECT_CHAR);

                setTextColor(COLOR_DEFAULT); // Reset to default color
            }else{
                goToXY(j*2+y,i+x);
                printf("  ");
            }
        }
    }
}

void clearScreen() {
    system("cls"); // Clears the console screen (Windows-specific)
}
/*

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓0
▓▓                                                          ▓▓1
▓▓                                                          ▓▓2
▓▓                                                          ▓▓3
▓▓                                                          ▓▓4
▓▓                                                          ▓▓5
▓▓      ▓▓▓▓▓▓  ▓▓▓▓▓▓  ▓▓▓▓▓▓  ▓▓▓▓    ▓▓▓▓▓▓  ▓▓▓▓▓▓      ▓▓6
▓▓        ▓▓    ▓▓        ▓▓    ▓▓  ▓▓    ▓▓    ▓▓          ▓▓7
▓▓        ▓▓    ▓▓▓▓      ▓▓    ▓▓▓▓      ▓▓    ▓▓▓▓▓▓      ▓▓8
▓▓        ▓▓    ▓▓        ▓▓    ▓▓  ▓▓    ▓▓        ▓▓      ▓▓9
▓▓        ▓▓    ▓▓▓▓▓▓    ▓▓    ▓▓  ▓▓  ▓▓▓▓▓▓  ▓▓▓▓▓▓      ▓▓10
▓▓                                                          ▓▓11
▓▓                                                          ▓▓12
▓▓                                                          ▓▓13
▓▓                                                          ▓▓14
▓▓   Enter:          To start the game.                     ▓▓15
▓▓   Left Arrow:     Move the Tetromino left.               ▓▓16
▓▓   Right Arrow:    Move the Tetromino right.              ▓▓17
▓▓   Down Arrow:     Speed up the Tetromino's fall.         ▓▓18
▓▓   Up Arrow:       Rotate the Tetromino.                  ▓▓19
▓▓   Q:              Quit the game.                         ▓▓20
▓▓                                                          ▓▓21
▓▓                                                          ▓▓22
▓▓                                                          ▓▓23
▓▓                                                          ▓▓24
▓▓                                                          ▓▓25
▓▓                                                          ▓▓26
▓▓                                                          ▓▓27
▓▓                                                          ▓▓28
▓▓                                                          ▓▓29
▓▓                                                          ▓▓30
▓▓                                                          ▓▓31
▓▓                                                          ▓▓32
▓▓                                                          ▓▓33
▓▓                                                          ▓▓34
▓▓                                                          ▓▓35
▓▓                                                          ▓▓36
▓▓                                                          ▓▓37
▓▓                                      by AbdElMalek-L     ▓▓38
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓39

▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓0  
▓▓                                                          ▓▓11
▓▓                                                          ▓▓12
▓▓                                                          ▓▓13
▓▓                                                          ▓▓14
▓▓                                                          ▓▓15
▓▓        00                                                ▓▓16
▓▓        99                                                ▓▓17
▓▓        88                                                ▓▓18
▓▓        77                                                ▓▓19
▓▓        66                                                ▓▓20
▓▓        55                                                ▓▓21
▓▓        44                                                ▓▓22
▓▓        33                                                ▓▓23
▓▓        22                                                ▓▓24
▓▓        11                                                ▓▓25
▓▓        00                                                ▓▓26
▓▓        99                                                ▓▓27
▓▓        88                                                ▓▓28
▓▓        77                                                ▓▓29
▓▓        66                                                ▓▓30
▓▓        55                                                ▓▓31
▓▓        44                                                ▓▓32
▓▓        33                                                ▓▓33
▓▓        22                                                ▓▓34
▓▓        112233445566778899001122334455                    ▓▓35
▓▓                                                          ▓▓36
▓▓                                                          ▓▓37
▓▓                                      by AbdElMalek-L     ▓▓38
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓39
1234567890123456789012345678901234567890123456789012345678912
      10        20        30        40        50        60


▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                     ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    Score: 9999999   ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                     ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓                  ▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓              ▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓   Next:      ▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓              ▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓                              ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓




*/
