/**********TETRIS_CLONE ver_0.1****************/
/********By AbdElMalek-L on 17.01.25***********/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_WIDTH 60
#define SCREEN_HEIGHT 30
#define BOARD_HEIGHT 32 
#define BOARD_WIDTH 60

#define RECT_CHAR 178

#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_YELLOW  14
#define COLOR_BLUE    9
#define COLOR_CYAN    11
#define COLOR_MAGENTA 13
#define COLOR_DEFAULT 7


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
void placeTetromino();
void drawNext();
void moveTetromino(int dx, int dy);
bool checkCollision(int new_x, int new_y, Tetromino *t);

Tetromino current_tetromino = { { {0,0,0}, 
                                  {0,0,0},
                                  {0,0,0} }, 6 };
int current_x, current_y;
int next_piece;

int next = 0;

int score = 0;

int main() {
    srand(time(NULL));
    setConsoleSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    resetGame();

    bool game_exit = false;
    bool game_over = false;
    int lastFall = clock();

    drawWelcomePage(BOARD_WIDTH, BOARD_HEIGHT);

    while (!game_exit) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            // Game loop
            while (!game_exit && !game_over) {
                if (clock() > lastFall + 1000) {
                    moveTetromino(0, 1);
                    lastFall = clock();
                }

                // Handle input
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    moveTetromino(-1, 0);
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    moveTetromino(1, 0);
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    moveTetromino(0, 1);
                }
                if (GetAsyncKeyState(VK_UP) & 0x8000) {
                    rotateTetromino();
                }
                if (GetAsyncKeyState('Q') & 0x8000) {
                    game_exit = true;
                }

                // Draw
                clearScreen();
                drawPlayBoard();
                drawGame();
                drawTetromino(current_tetromino, current_x, current_y);
                drawNext();
                waitForNextFrame(30);
            }
        }
        // Handle other cases (menu, exit)
        waitForNextFrame(30);
    }
    return 0;
}

// void setConsoleSize(int width, int height) {
//     HWND console = GetConsoleWindow();

//     RECT r;
//     GetWindowRect(console, &r);
//     MoveWindow(console, r.left, r.top, width, height, TRUE);

//     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

//     COORD newSize;
//     newSize.X = width;
//     newSize.Y = height;
// }

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

void resetGame() {
    memset(game_matrix, 0, sizeof(game_matrix));
    score = 0;
    next_piece = rand() % 7;
    current_tetromino = tetrominos[next_piece];
    current_x = 6; // Centered
    current_y = 0;
    next_piece = rand() % 7;
}

void rotateTetromino() {
    Tetromino temp = current_tetromino;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            temp.shape[y][x] = current_tetromino.shape[3 - x - 1][y];
        }
    }
    // Check if rotation is possible
    if (!checkCollision(current_x, current_y, &temp)) {
        current_tetromino = temp;
    }
}

void placeTetromino() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (current_tetromino.shape[y][x]) {
                if (current_y + y < 0) {
                    // Game Over
                    return;
                }
                game_matrix[current_y + y][current_x + x] = current_tetromino.color;
            }
        }
    }
    // Check for line clears
    // ... [Implement line clearing logic] ...
    // Spawn new piece
    current_tetromino = tetrominos[next_piece];
    next_piece = rand() % 7;
    current_x = 6;
    current_y = 0;
    if (checkCollision(current_x, current_y, &current_tetromino)) {
        // Game Over
        resetGame();
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
    printf("~Made with ");
    setTextColor(COLOR_RED);
    printf("<3 ");    
    setTextColor(COLOR_BLUE );    
    printf("by ");
    setTextColor(COLOR_DEFAULT); 
    printf("@AbdElMalek-L ");


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
                // printf("  ");
            }
        }
    }
}

void clearScreen() {
    system("cls"); // Clears the console screen (Windows-specific)
}

void moveTetromino(int dx, int dy) {
    if (!checkCollision(current_x + dx, current_y + dy, &current_tetromino)) {
        current_x += dx;
        current_y += dy;
    } else if (dy == 1) {
        placeTetromino();
    }
}
bool checkCollision(int new_x, int new_y, Tetromino *t) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (t->shape[y][x]) {
                int board_x = new_x + x;
                int board_y = new_y + y;
                if (board_x < 0 || board_x >= 15 || board_y >= 20)
                    return true;
                if (board_y >= 0 && game_matrix[board_y][board_x])
                    return true;
            }
        }
    }
    return false;
}

/*********************************************************************/

// typedef struct {
//     int shape[4][4]; // Adjusted to 4x4 for 'I' piece
//     int color;
//     int width, height;
// } Tetromino;

// Tetromino tetrominos[7] = {
//     // I-piece (4x4)
//     { { {0,0,0,0}, 
//         {1,1,1,1},
//         {0,0,0,0},
//         {0,0,0,0} }, COLOR_CYAN, 4, 4 },
//     // T-piece
//     { { {0,1,0},
//         {1,1,1},
//         {0,0,0} }, COLOR_MAGENTA, 3, 3 },
//     // S-piece
//     { { {0,1,1},
//         {1,1,0},
//         {0,0,0} }, COLOR_GREEN, 3, 3 },
//     // Z-piece
//     { { {1,1,0},
//         {0,1,1},
//         {0,0,0} }, COLOR_RED, 3, 3 },
//     // L-piece
//     { { {0,0,1},
//         {1,1,1},
//         {0,0,0} }, COLOR_YELLOW, 3, 3 },
//     // J-piece
//     { { {1,1,1},
//         {0,0,1},
//         {0,0,0} }, COLOR_BLUE, 3, 3 },
//     // O-piece
//     { { {1,1},
//         {1,1} }, COLOR_YELLOW, 2, 2 }
// };



// Function prototypes (add any missing)


// ... [Other function prototypes remain the same] ...

void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}











// // Update drawTetromino to handle 4x4 shapes
// void drawTetromino(Tetromino t, int x, int y) {
//     setTextColor(t.color);
//     for (int i = 0; i < t.height; i++) {
//         for (int j = 0; j < t.width; j++) {
//             if (t.shape[i][j]) {
//                 goToXY((x + j) * 2 + 7, y + i + 8);
//                 printf("%c%c", RECT_CHAR, RECT_CHAR);
//             }
//         }
//     }
//     setTextColor(COLOR_DEFAULT);
// }

