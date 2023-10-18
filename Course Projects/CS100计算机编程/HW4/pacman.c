#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200

typedef enum gameState{losing, onGoing, winning} GameState;
typedef enum direction{up, down, left, right, idle} Direction;


typedef struct game {
    int ghostCount;
    int ghosts[MAX_GHOSTS];
    int capsuleDuration;
    char** board;
    char** grid;     // a 2-dimensional array of characters to display the game;
    int rows;        // number of rows of the grid;
    int columns;     // number of columns of the grid;
    int foodCount;   // number of remaining food in the game;
    int score;       // current score;
    GameState state; // the state of the game, one of losing, onGoing, or winning.
} Game;

/* Creates a new game, with given rows and columns.
 * The top-left corner is at row 0 and column 0.
 * Boundary is not included in either rows or columns.
 * You should dynamically allocate space for a Game pointer,
 * dynamically allocate a 2-dimensional char grid,
 * and initialize any other value in your Game structure.
 * Return that pointer to the game you created.
 */
Game* NewGame(int rows, int columns) {
    Game* game = (Game*)malloc(sizeof(Game));
    game->rows = rows;
    game->columns = columns;
    game->foodCount = 0;
    game->score = 0;
    game->state = onGoing;
    game->grid = (char**)malloc(sizeof(char*) * rows);
    game->board = (char**)malloc(sizeof(char*) * rows);
    for (int i = 0; i <= rows; i++) {
        game->grid[i] = (char*)malloc(sizeof(char*) * columns);
        game->board[i] = (char*)malloc(sizeof(char*) * columns);
    }
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            game->grid[i][j] = ' ';
            game->board[i][j] = ' ';
        }
    }
    return game; // This is incorrect.
}

/* Ends your game by freeing any memory
 * you dynamically allocated.
 * After that, free the "game" pointer,
 * since it is also dynamically created.
 */
void EndGame(Game* game) {
    for (int i = 0; i <= game->rows; i++) {
        free(game->grid[i]);
    }
    free(game->grid);
    for (int i = 0; i < game->ghostCount; i++) {
        free(game->board[i]);
    }   
    free(game->board);
    free(game);
    return;
}

/* Adds a wall to the game, at row = r, column = c.
 * Walls should be added only to an empty place.
 * After you successfully add a wall, 
 * you should modify the "grid" to represent
 * the wall by '#'. Then, return true.
 * Return false on failures.
 */
bool AddWall(Game* game, int r, int c) {
    //判断出界
    if (r < 0 || r > game->rows || c < 0 || c > game->columns) {
        return false;
    }
    else 
        if (game->grid[r][c] == ' ') {
            game->grid[r][c] = '#';
            return true;
        }
}

/* Adds a food to the game, at row = r, column = c.
 * Foods should be added only to an empty place.
 * After you successfully add a food, 
 * you should modify the "grid" to represent
 * the food by '.', also update the "foodCount"
 * correctly. Then, return true.
 * Return false on failures.
 */
bool AddFood(Game* game, int r, int c) {
    //判断出界
    if (r < 0 || r >= game->rows || c < 0 || c >= game->columns) {
        return false;
    }
    else
        if(game->grid[r][c] == ' '){
            game->grid[r][c] = '.';
            game->board[r][c] = '.';
            game->foodCount++;
            return true;
        }
}


/* Adds a Pacman to the game! At row = r, column = c.
 * If there is already a Pacman, return false.
 * Pacman should be added only to an empty place.
 * After you successfully add a Pacman,
 * you should modify the "grid" to represent
 * the Pacman by 'C'. Then, return true.
 * Return false on failures.
 */
bool AddPacman(Game* game, int r, int c) {
    for (int i = 0; i <= game->rows; i++) {
        for (int j = 0; j <= game->columns; j++) {
            if (game->grid[i][j] == 'C') {
                return false;
            }
        }
    }
    if (r < 0 || r >= game->rows || c < 0 || c >= game->columns) 
        {return false;}
    if (game->grid[r][c] == ' ') {
        game->grid[r][c] = 'C';
        return true;}
    if (game->grid[r][c] != ' ') {
        return false;
    }
}

/* Moves Pacman in the given direction.
 * The direction will always be valid.
 * Pacman should stay still if this move
 * will let it hit a wall or boundaries.
 * No matter what move is performed, the
 * game's score should decrease by 1.
 * 
 * If Pacman eats a food, the game's score
 * should increase by FOOD_SCORE. If that 
 * food is the last one in the game, you
 * should mark the game's state as "winning".
 *
 * 
 * FOR PART B:
 * 
 * Pacman is allowed to move onto a grid
 * with a ghost. In that case, Pacman loses,
 * and will not be able to eat the food or capsule
 * under that ghost, if any. Score should
 * still decrease by 1, and you should mark the
 * game's state as "losing".
 * 
 * If Pacman eats a capsule, the game's score
 * should increase by CAPSULE_SCORE, and Pacman
 * will gain CAPSULE_DURATION = 10 turns of 
 * superpower. If that capsule is the last food 
 * in the game, mark the game's state as "winning".
 * 
 */
void MovePacman(Game* game, Direction direction){
    int pacmanRow = 0;
    int pacmanCol = 0;
    int panduan = 0;
    game->capsuleDuration=CAPSULE_DURATION;
    for (int i = 0; i <= game->rows; i++) {
        for (int j = 0; j <= game->columns; j++) {
            if (game->grid[i][j] == 'C') {
                pacmanRow = i;
                pacmanCol = j;
                break;
            }
        }
    }
    if (direction == up) {
        if(panduan==0){
            if (pacmanRow - 1 >= 0) {
                if (game->grid[pacmanRow-1][pacmanCol]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                else if (game->grid[pacmanRow-1][pacmanCol]=='@'){
                    game->score--;
                    game->state=losing;}
                else if (game->grid[pacmanRow-1][pacmanCol]=='#')
                    {game->score--;}
                else if (game->grid[pacmanRow-1][pacmanCol]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score--;}
                else if (game->grid[pacmanRow-1][pacmanCol]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                    for (int i = 0; i <= game->rows; i++) {
                        for (int j = 0; j <= game->columns; j++) {
                            if (game->grid[i][j] == '@') {
                                game->grid[i][j] = 'X';
                            }
                        }
                    }
                }
            }
            if(pacmanRow==0){
                game->score--;
            }   
        }
        if(panduan==1){
            if (pacmanRow - 1 >= 0) {
                if (game->grid[pacmanRow-1][pacmanCol]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                if (game->grid[pacmanRow-1][pacmanCol]=='X'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score+=(GHOST_SCORE-1); 
                }
                else if (game->grid[pacmanRow-1][pacmanCol]=='#')
                    {game->score--;
                    game->grid[pacmanRow][pacmanCol]='C';}
                else if (game->grid[pacmanRow-1][pacmanCol]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score--;}
                else if (game->grid[pacmanRow-1][pacmanCol]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow-1][pacmanCol]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                //如果碰到‘@’，显示losing
                else if(game->grid[pacmanRow-1][pacmanCol]=='@'){
                    game->score--;
                    game->state=losing;
                }
            }
            if(pacmanRow==0)
                {game->score--;}
        game->capsuleDuration--;
        }
    }
    if (direction == down) {
        if(panduan==0){
            if (pacmanRow + 1 <= game->rows) {
                if (game->grid[pacmanRow+1][pacmanCol]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                else if (game->grid[pacmanRow+1][pacmanCol]=='@'){
                    game->score--;
                    game->state=losing;}
                else if (game->grid[pacmanRow+1][pacmanCol]=='#')
                    {game->score--;}
                else if (game->grid[pacmanRow+1][pacmanCol]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score--;}
                else if (game->grid[pacmanRow+1][pacmanCol]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                    for (int i = 0; i <= game->rows; i++) {
                        for (int j = 0; j <= game->columns; j++) {
                            if (game->grid[i][j] == '@') {
                                game->grid[i][j] = 'X';
                            }
                        }
                    }
                }
            }
            if(pacmanRow==game->rows)
                {game->score--;}
        }
        if(panduan==1)
        {
            if (pacmanRow + 1 <= game->rows) {
                if (game->grid[pacmanRow+1][pacmanCol]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                if (game->grid[pacmanRow+1][pacmanCol]=='X'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score+=(GHOST_SCORE-1); 
                }
                else if (game->grid[pacmanRow+1][pacmanCol]=='#')
                    {game->score--;
                    game->grid[pacmanRow][pacmanCol]='C';}
                else if (game->grid[pacmanRow+1][pacmanCol]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score--;}
                else if (game->grid[pacmanRow+1][pacmanCol]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow+1][pacmanCol]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                //如果碰到‘@’，显示losing
                else if(game->grid[pacmanRow+1][pacmanCol]=='@'){
                    game->score--;
                    game->state=losing;
                }
            }
            if(pacmanRow==game->rows)
                {game->score--;}
        game->capsuleDuration--;
        }
    }
    if (direction == left) {
        if(panduan==0){
            if (pacmanCol - 1 >= 0) {
                if (game->grid[pacmanRow][pacmanCol-1]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                else if (game->grid[pacmanRow][pacmanCol-1]=='@'){
                    game->score--;
                    game->state=losing;}
                else if (game->grid[pacmanRow][pacmanCol-1]=='#')
                    {game->score--;}
                else if (game->grid[pacmanRow][pacmanCol-1]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score--;}
                else if (game->grid[pacmanRow][pacmanCol-1]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                    for (int i = 0; i <= game->rows; i++) {
                        for (int j = 0; j <= game->columns; j++) {
                            if (game->grid[i][j] == '@') {
                                game->grid[i][j] = 'X';
                            }
                        }
                    }
                }
            }
            if(pacmanCol==0)
                {game->score--;}
        }
        if(panduan==1)
        {
            if (pacmanCol - 1 >= 0) {
                if (game->grid[pacmanRow][pacmanCol-1]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                if (game->grid[pacmanRow][pacmanCol-1]=='X'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score+=(GHOST_SCORE-1); 
                }
                else if (game->grid[pacmanRow][pacmanCol-1]=='#')
                    {game->score--;
                    game->grid[pacmanRow][pacmanCol]='C';}
                else if (game->grid[pacmanRow][pacmanCol-1]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score--;}
                else if (game->grid[pacmanRow][pacmanCol-1]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol-1]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                //如果碰到‘@’，显示losing
                else if(game->grid[pacmanRow][pacmanCol-1]=='@'){
                    game->score--;
                    game->state=losing;
                }
            }
            if(pacmanCol==0)
                {game->score--;}
        game->capsuleDuration--;
        }
    }
    if (direction == right) {
        if(panduan==0){
            if (pacmanCol + 1 <= game->columns) {
                if (game->grid[pacmanRow][pacmanCol+1]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                else if (game->grid[pacmanRow][pacmanCol+1]=='@'){
                    game->score--;
                    game->state=losing;}
                else if (game->grid[pacmanRow][pacmanCol+1]=='#')
                    {game->score--;}
                else if (game->grid[pacmanRow][pacmanCol+1]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score--;}
                else if (game->grid[pacmanRow][pacmanCol+1]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                    for (int i = 0; i <= game->rows; i++) {
                        for (int j = 0; j <= game->columns; j++) {
                            if (game->grid[i][j] == '@') {
                                game->grid[i][j] = 'X';
                            }
                        }
                    }
                }
            }
            if(pacmanCol==game->columns)
                {game->score--;}
        }
        if(panduan==1)
        {
            if (pacmanCol + 1 <= game->columns) {
                if (game->grid[pacmanRow][pacmanCol+1]=='.'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score+=(FOOD_SCORE-1);
                    game->foodCount--;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                if (game->grid[pacmanRow][pacmanCol+1]=='X'){
                    game->grid[pacmanRow][pacmanCol] = ' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score+=(GHOST_SCORE-1); 
                }
                else if (game->grid[pacmanRow][pacmanCol+1]=='#')
                    {game->score--;
                    game->grid[pacmanRow][pacmanCol]='C';}
                else if (game->grid[pacmanRow][pacmanCol+1]==' '){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score--;}
                else if (game->grid[pacmanRow][pacmanCol+1]=='o'){
                    game->grid[pacmanRow][pacmanCol]=' ';
                    game->grid[pacmanRow][pacmanCol+1]='C';
                    game->score+=(CAPSULE_SCORE-1);
                    game->foodCount--;
                    panduan=1;
                    if (game->foodCount == 0) {
                        game->state = winning;
                    }
                }
                //如果碰到‘@’，则显示losing
                else if (game->grid[pacmanRow][pacmanCol+1]=='@'){
                    game->score--;
                    game->state=losing;}    
            }
            if(pacmanCol==game->columns)
                {game->score--;}
        game->capsuleDuration--;
        }
    }
    if(direction=idle)
        {game->score--;
        game->grid[pacmanRow][pacmanCol]='C';}
    if(game->capsuleDuration==0){
        panduan=0;
        for (int i = 0; i <= game->rows; i++) {
            for (int j = 0; j <= game->columns; j++) {
                if (game->grid[i][j] == 'X') {
                    game->grid[i][j] = '@';
                }
            }
        }
    }
    return;  
}

//////////////////////// PART B ////////////////////////


/* Adds a ghost to the game,
 * at row = r, column = c, with given initial direction.
 * you should modify the "grid" to represent the ghost by '@'.
 * Ghosts can be added to an empty place or on a food.
 * For the latter case, the ghost will cover that food on display,
 * represented also by an '@'. 
 * That food must still exist, and that grid should 
 * display '.' when the ghost leaves.
 */
bool AddGhost(Game* game, int r, int c, Direction direction) {
    //判断出界
    if (r < 0 || r >= game->rows || c < 0 || c >= game->columns) {
        return false;
    }
    if (game->grid[r][c] == ' ') {
        game->grid[r][c] = '@';
        game->ghostCount++;
        if (game->ghostCount>MAX_GHOSTS)
            {return false;}
        if (direction==up)
            {game->grid[r-1][c]='@';
             game->grid[r][c]=' ';
             return true;}
        if(direction==down)
            {game->grid[r+1][c]='@';
             game->grid[r][c]=' ';
             return true;}
        if(direction==left)
            {game->grid[r][c-1]='@';
             game->grid[r][c]=' ';
             return true;}
        if(direction==right)
            {game->grid[r][c+1]='@';
             game->grid[r][c]=' ';
             return true;}
        if(direction==idle)
            {game->grid[r][c]='@';
             return true;}
        
    }
    if (game->grid[r][c]=='.'){
        game->grid[r][c]='@';
        game->foodCount--;
        game->ghostCount++;
        if (game->ghostCount>MAX_GHOSTS)
            {return false;}
        if(direction==up)
            {game->grid[r-1][c]='@';
             game->grid[r][c]='.';
             game->foodCount++;
             return true;}
        if(direction==down)
            {game->grid[r+1][c]='@';
             game->grid[r][c]='.';
             game->foodCount++;
             return true;}
        if(direction==left)
            {game->grid[r][c-1]='@';
             game->grid[r][c]='.';
             game->foodCount++;
             return true;}
        if(direction==right)
            {game->grid[r][c+1]='@';
             game->grid[r][c]='.';
             game->foodCount++;
             return true;}
        if(direction==idle)
            {game->grid[r][c]='@';
             return true;}    
    }
    if (game->grid[r][c]=='o'){
        game->grid[r][c]='@';
        game->ghostCount++;
        game->foodCount--;
        if (game->ghostCount>MAX_GHOSTS)
            {return false;}
         if(direction==up)
            {game->grid[r-1][c]='@';
             game->grid[r][c]='o';
             game->foodCount++;
             return true;}
         if(direction==down)
            {game->grid[r+1][c]='@';
             game->grid[r][c]='o';
             game->foodCount++;
             return true;}
         if(direction==left)
            {game->grid[r][c-1]='@';
             game->grid[r][c]='o';
             game->foodCount++;
             return true;}
         if(direction==right)
            {game->grid[r][c+1]='@';
             game->grid[r][c]='o';
             game->foodCount++;
             return true;}
         if(direction==idle)
            {game->grid[r][c]='@';
             return true;}
    }
    return false;
}

/* Moves all ghosts in their own directions.
 * Ghosts should be moved in the order they were added.
 * If a ghost will bump into a wall, another ghost, or a boundary,
 * Its direction will reverse, and it will try to move
 * in the new direction immediately this turn.
 * If it bumps into another wall/ghost/boundary,
 * it won't move for this turn.
 */
void MoveGhosts(Game* game) {
    int ghostRow=0;
    int ghostCol=0;
    for (int i = 0; i < game->ghostCount; i++) {
        for (int j = 0; j <= game->rows; j++) {
            for (int k = 0; k <= game->columns; k++) {
                if (game->grid[j][k] == '@') {
                    ghostRow = j;
                    ghostCol = k;
                }
                if (ghostRow - 1 >= 0) {
                    if (game->grid[ghostRow-1][ghostCol]=='#'){
                        if (ghostRow+1<=game->rows)
                            if (game->grid[ghostRow+1][ghostCol]==' '){
                                game->grid[ghostRow][ghostCol]=' ';
                                game->grid[ghostRow+1][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow+1][ghostCol]=='#'||game->grid[ghostRow+1][ghostCol]=='@'){
                                game->grid[ghostRow][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow+1][ghostCol]=='.'){
                                game->grid[ghostRow+1][ghostCol]='@';
                                game->grid[ghostRow][ghostCol]=' ';
                                game->foodCount--;
                            }
                        else
                            game->grid[ghostRow][ghostCol]='@';
                    }
                    else if (game->grid[ghostRow-1][ghostCol]==' '){
                        game->grid[ghostRow][ghostCol]=' ';
                        game->grid[ghostRow-1][ghostCol]='@';
                    }
                }
                if (ghostRow==0){
                    game->grid[ghostRow][ghostCol]='@';
                }
                if (ghostRow + 1 <= game->rows) {
                    if (game->grid[ghostRow+1][ghostCol]=='#'){
                        if (ghostRow-1>=0)
                            if (game->grid[ghostRow-1][ghostCol]==' '){
                                game->grid[ghostRow][ghostCol]=' ';
                                game->grid[ghostRow-1][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow-1][ghostCol]=='#'||game->grid[ghostRow-1][ghostCol]=='@'){
                                game->grid[ghostRow][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow-1][ghostCol]=='.'){
                                game->grid[ghostRow-1][ghostCol]='@';
                                game->grid[ghostRow][ghostCol]=' ';
                                game->foodCount--;
                            }   
                        else
                            game->grid[ghostRow][ghostCol]='@';
                    }
                    else if (game->grid[ghostRow+1][ghostCol]==' '){
                        game->grid[ghostRow][ghostCol]=' ';
                        game->grid[ghostRow+1][ghostCol]='@';
                    }
                }
                if (ghostRow==game->rows){
                    game->grid[ghostRow][ghostCol]='@';
                }
                if (ghostCol - 1 >= 0) {
                    if (game->grid[ghostRow][ghostCol-1]=='#'){
                        if (ghostCol+1<=game->columns)
                            if (game->grid[ghostRow][ghostCol+1]==' '){
                                game->grid[ghostRow][ghostCol]=' ';
                                game->grid[ghostRow][ghostCol+1]='@';
                            }
                            else if (game->grid[ghostRow][ghostCol+1]=='#'||game->grid[ghostRow][ghostCol+1]=='@'){
                                game->grid[ghostRow][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow][ghostCol+1]=='.'){
                                game->grid[ghostRow][ghostCol+1]='@';
                                game->grid[ghostRow][ghostCol]=' ';
                                game->foodCount--;
                            }
                        else
                            game->grid[ghostRow][ghostCol]='@';
                    }
                    else if (game->grid[ghostRow][ghostCol-1]==' '){
                        game->grid[ghostRow][ghostCol]=' ';
                        game->grid[ghostRow][ghostCol-1]='@';
                    }
                }
                if (ghostCol==0){
                    game->grid[ghostRow][ghostCol]='@';
                }
                if (ghostCol + 1 <= game->columns) {
                    if (game->grid[ghostRow][ghostCol+1]=='#'){
                        if (ghostCol-1>=0)
                            if (game->grid[ghostRow][ghostCol-1]==' '){
                                game->grid[ghostRow][ghostCol]=' ';
                                game->grid[ghostRow][ghostCol-1]='@';
                            }
                            else if (game->grid[ghostRow][ghostCol-1]=='#'||game->grid[ghostRow][ghostCol-1]=='@'){
                                game->grid[ghostRow][ghostCol]='@';
                            }
                            else if (game->grid[ghostRow][ghostCol-1]=='.'){
                                game->grid[ghostRow][ghostCol-1]='@';
                                game->grid[ghostRow][ghostCol]=' ';
                                game->foodCount--;
                            }
                        else
                            game->grid[ghostRow][ghostCol]='@';
                    }
                    else if (game->grid[ghostRow][ghostCol+1]==' '){
                        game->grid[ghostRow][ghostCol]=' ';
                        game->grid[ghostRow][ghostCol+1]='@';
                    }
                }
                if (ghostCol==game->columns){
                    game->grid[ghostRow][ghostCol]='@';
                }
            }
        }
    }
    //如果'@'被替换成了‘X’，则当capsuleDuration为偶数时，‘X’移动，否则不移动
    if (game->capsuleDuration%2==0){
        for (int i = 0; i < game->ghostCount; i++) {
            for (int j = 0; j <= game->rows; j++) {
                for (int k = 0; k <= game->columns; k++) {
                    if (game->grid[j][k] == 'X') {
                        ghostRow = j;
                        ghostCol = k;
                    }
                    if (ghostRow - 1 >= 0) {
                        if (game->grid[ghostRow-1][ghostCol]=='#'){
                            if (ghostRow+1<=game->rows)
                                if (game->grid[ghostRow+1][ghostCol]==' '){
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->grid[ghostRow+1][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow+1][ghostCol]=='#'||game->grid[ghostRow+1][ghostCol]=='X'){
                                    game->grid[ghostRow][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow+1][ghostCol]=='.'){
                                    game->grid[ghostRow+1][ghostCol]='X';
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->foodCount--;
                                }
                            else
                                game->grid[ghostRow][ghostCol]='X';
                        }
                        else if (game->grid[ghostRow-1][ghostCol]==' '){
                            game->grid[ghostRow][ghostCol]=' ';
                            game->grid[ghostRow-1][ghostCol]='X';
                        }
                    }
                    if (ghostRow==0){
                        game->grid[ghostRow][ghostCol]='X';
                    }
                    if (ghostRow + 1 <= game->rows) {
                        if (game->grid[ghostRow+1][ghostCol]=='#'){
                            if (ghostRow-1>=0)
                                if (game->grid[ghostRow-1][ghostCol]==' '){
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->grid[ghostRow-1][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow-1][ghostCol]=='#'||game->grid[ghostRow-1][ghostCol]=='X'){
                                    game->grid[ghostRow][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow-1][ghostCol]=='.'){
                                    game->grid[ghostRow-1][ghostCol]='X';
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->foodCount--;
                                }
                            else
                                game->grid[ghostRow][ghostCol]='X';
                        }
                        else if (game->grid[ghostRow+1][ghostCol]==' '){
                            game->grid[ghostRow][ghostCol]=' ';
                            game->grid[ghostRow+1][ghostCol]='X';
                        }
                    }
                    if (ghostRow==game->rows){
                        game->grid[ghostRow][ghostCol]='X';
                    }
                    if (ghostCol - 1 >= 0) {
                        if (game->grid[ghostRow][ghostCol-1]=='#'){
                            if (ghostCol+1<=game->columns)
                                if (game->grid[ghostRow][ghostCol+1]==' '){
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->grid[ghostRow][ghostCol+1]='X';
                                }
                                else if (game->grid[ghostRow][ghostCol+1]=='#'||game->grid[ghostRow][ghostCol+1]=='X'){
                                    game->grid[ghostRow][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow][ghostCol+1]=='.'){
                                    game->grid[ghostRow][ghostCol+1]='X';
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->foodCount--;
                                }
                            else
                                game->grid[ghostRow][ghostCol]='X';
                        }
                        else if (game->grid[ghostRow][ghostCol-1]==' '){
                            game->grid[ghostRow][ghostCol]=' ';
                            game->grid[ghostRow][ghostCol-1]='X';
                        }
                    }
                    if (ghostCol==0){
                        game->grid[ghostRow][ghostCol]='X';
                    }
                    if (ghostCol + 1 <= game->columns) {
                        if (game->grid[ghostRow][ghostCol+1]=='#'){
                            if (ghostCol-1>=0)
                                if (game->grid[ghostRow][ghostCol-1]==' '){
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->grid[ghostRow][ghostCol-1]='X';
                                }
                                else if (game->grid[ghostRow][ghostCol-1]=='#'||game->grid[ghostRow][ghostCol-1]=='X'){
                                    game->grid[ghostRow][ghostCol]='X';
                                }
                                else if (game->grid[ghostRow][ghostCol-1]=='.'){
                                    game->grid[ghostRow][ghostCol-1]='X';
                                    game->grid[ghostRow][ghostCol]=' ';
                                    game->foodCount--;
                                }
                            else
                                game->grid[ghostRow][ghostCol]='X';
                        }       
                        else if (game->grid[ghostRow][ghostCol+1]==' '){
                            game->grid[ghostRow][ghostCol]=' ';
                            game->grid[ghostRow][ghostCol+1]='X';
                        }
                    }
                    if (ghostCol==game->columns){
                        game->grid[ghostRow][ghostCol]='X';
                    }
                }
            }
        }
    }
    return;
}

/* Adds a capsule to the game, at row = r, column = c.
 * Capsules should be added only to an empty place,
 * or added to a cell with food to upgrade that food.
 * After you successfully add a capsule, return true.
 * Return false on failures.
 *
 * Capsules will grant Pacman CAPSULE_SCORE = 50 and
 * CAPSULE_DURATION = 10 turns of superpower when eaten.
 * 
 * When with superpower, scared ghosts will be displayed in 'x',
 * and will be unable to move every other turn. 
 * (they can move on the turn when Pacman eats a capsule.)
 * When Pacman eats a scared ghost, it earns GHOST_SCORE = 200.
 * 
 * Pacman's superpower activates immediately when it eats a 
 * capsule, and counts down immediately after Pacman's turn,
 * starting from its next turn. In other words, Pacman's superpower
 * ends after 10 turns at the same moment of eating a capsule.
 */
bool AddCapsule(Game *game, int r, int c) {
    //判断出界
    if (r<0||r>game->rows||c<0||c>game->columns){
        return false;
    }
    if (game->grid[r][c]==' '){
        game->grid[r][c]='o';
        game->foodCount++;
        return true;
    }
    if (game->grid[r][c]=='.'){
        game->grid[r][c]='o';
        return true;
    }
    else{
        return false;
    }
}


///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PlayGame(Game* game);

int main(){
    Game* game = NewGame(8, 8);
    // Add walls, foods, and pacman here.
    AddWall(game, 2, 3);
    AddFood(game, 3, 4);
    AddFood(game, 3, 2);
    AddFood(game, 4, 3);
    AddPacman(game, 3, 3);
    PlayGame(game);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game* game){
    if(!game || !game->grid) return;

// If Windows, clear console.
#ifdef _WIN32 
    system("cls");
#else
// Clears terminal screen
    fflush(stdout);
    system("clear");
#endif
    
    // The game grid
    printf(" ");
    for(int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for(int i = 0; i < game->rows; i++){
        printf("|");
        for(int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for(int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch(game->state){
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

/* Plays the game, and calls EndGame on winning or losing.
 */
void PlayGame(Game* game){
    
    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while(true){
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf("%[^\n]", input);
        // Handles the '\n'.
        getchar();
        Direction direction;
        switch(input[0]){
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if(game->state != onGoing){
            break;
        }
        
        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman.
        if(game->state != onGoing){
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}