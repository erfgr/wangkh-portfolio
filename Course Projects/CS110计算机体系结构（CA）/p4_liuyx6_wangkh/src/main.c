#include "lcd/lcd.h"
#include <string.h>
#include "utils.h"

void Inp_init(void)
{
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOC);

    gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6);
    gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

void IO_init(void)
{
    Inp_init(); // inport init
    Lcd_Init(); // LCD init
}

void DrawPlayer(int x, int y){
	int StartX = 8 * x + 2;//Get StartX
	int StartY = 8 * y + 1;//Get StartY
	int EndX = 8 * x + 9;//Get EndX
	int EndY = 8 * y + 9;//Get Endy
	if(x == 19) EndX -= 2;//Make sure that the image is complete
	if(y == 9) EndY -= 2;//Make sure that the image is complete
//	LCD_DrawRectangle(StartX, StartY, EndX, EndY, BLUE);
	LCD_DrawPoint(StartX + 2, StartY + 1, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 2, StartY + 2, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 2, StartY + 3, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 3, StartY + 1, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 3, StartY + 3, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 4, StartY + 1, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 4, StartY + 2, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 4, StartY + 3, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 3, StartY + 4, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 1, StartY + 5, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 2, StartY + 5, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 3, StartY + 5, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 4, StartY + 5, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 5, StartY + 5, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 3, StartY + 6, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 2, StartY + 7, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 4, StartY + 7, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 1, StartY + 8, BLUE);//Draw Player
	LCD_DrawPoint(StartX + 5, StartY + 8, BLUE);//Draw Player
}

void DrawObstacle(int x, int y){
	int StartX = 8 * x + 1;//Get StartX
	int StartY = 8 * y + 1;//Get StartY
	int EndX = 8 * x + 9;//Get EndX
	int EndY = 8 * y + 9;//Get Endy
	if(x == 19) EndX -= 2;//Make sure that the image is complete
	if(y == 9) EndY -= 2;//Make sure that the image is complete
	LCD_DrawRectangle(StartX, StartY, EndX, EndY, RED);
	LCD_DrawLine(StartX, StartY, EndX, EndY, RED);
	LCD_DrawLine(EndX, StartY, StartX, EndY, RED);
}

void DrawTerminal(int x, int y){
	int StartX = 8 * x + 1;//Get StartX
	int StartY = 8 * y + 1;//Get StartY
	int EndX = 8 * x + 9;//Get EndX
	int EndY = 8 * y + 9;//Get Endy
	if(x == 19) EndX -= 2;//Make sure that the image is complete
	if(y == 9) EndY -= 2;//Make sure that the image is complete
	LCD_DrawRectangle(StartX, StartY, EndX, EndY, WHITE);
	LCD_DrawCircle(StartX + 4, StartY + 4, 3, WHITE);
}

void DrawGoal(int x, int y){
	int StartX = 8 * x + 1;//Get StartX
	int StartY = 8 * y + 1;//Get StartY
	int EndX = 8 * x + 9;//Get EndX
	int EndY = 8 * y + 9;//Get Endy
	if(x == 19) EndX -= 2;//Make sure that the image is complete
	if(y == 9) EndY -= 2;//Make sure that the image is complete
	LCD_DrawRectangle(StartX, StartY, EndX, EndY, GREEN);
	LCD_DrawCircle(StartX + 4, StartY + 4, 3, GREEN);
}

void DrawBox(int x, int y){
	int StartX = 8 * x + 1;//Get StartX
	int StartY = 8 * y + 1;//Get StartY
	int EndX = 8 * x + 9;//Get EndX
	int EndY = 8 * y + 9;//Get Endy
	if(x == 19) EndX -= 2;//Make sure that the image is complete
	if(y == 9) EndY -= 2;//Make sure that the image is complete
	LCD_DrawRectangle(StartX, StartY, EndX, EndY, YELLOW);
}

int main(void)
{
	int level = 1, box = 1, step = 0, PlayerX = 0, PlayerY = 0, Cover = 0, Score = 0;
	int a[11][22];
	int BestScore[4][4];
	int ScoreX[4] = {0, 10, 60, 110};
	int ScoreY[4] = {0, 30, 45, 60};
    IO_init();         // init OLED
    // YOUR CODE HERE
    //Initialize Map
    for(int i = 1 ; i <= 3 ; i++)
    	for(int j = 1 ; j <= 3 ; j++)
    		BestScore[i][j] = 999;
    while(1){
	    level = 1, box = 1, step = 0, PlayerX = 0, PlayerY = 0, Cover = 0, Score = 0;
	    for(int i = 0 ; i < 10 ; i++){
	    	for(int j = 0 ; j < 20 ; j++){
	    		a[i][j] = 0;
			}
		}
		//Make room for "Step" display
		for(int j = 11 ; j < 20 ; j++) a[0][j] = a[1][j] = -2;
	    //Initial interface
	    LCD_Clear(BLACK);
	    LCD_ShowString(1, 1, "ctrl/down to choose level, left/right to choose box number, boot0 next", RED);
	    while(1){
	    	delay_1ms(10);
	    	//Press BOOT0 to continue
	    	if(Get_BOOT0()) break;
		}
		LCD_Clear(BLACK);
		//Choose difficulty
		LCD_ShowString(1, 1, "Level:", RED);
		LCD_ShowString(1, 21, "Box number:", RED);
		LCD_ShowString(1, 41, "BOOT0 to continue", RED);
		LCD_ShowNum(60, 1, level, 1, WHITE);//level
		LCD_ShowNum(100, 21, box, 1, WHITE);//box
		delay_1ms(1000);
		while(1){
			delay_1ms(10);
			//Reduce number of boxes
			if(Get_Button(JOY_LEFT)){
				if(box > 1) box--;
				else continue;
				LCD_Clear(BLACK);
				//display information
				LCD_ShowString(1, 1, "Level:", RED);
				LCD_ShowString(1, 21, "Box number:", RED);
				LCD_ShowString(1, 41, "BOOT0 to continue", RED);
				LCD_ShowNum(60, 1, level, 1, WHITE);//level
				LCD_ShowNum(100, 21, box, 1, WHITE);//box
			}
			//Add number of boxes
			if(Get_Button(JOY_RIGHT)){
				if(box < 3) box++;
				else continue;
				LCD_Clear(BLACK);
				//display information
				LCD_ShowString(1, 1, "Level:", RED);
				LCD_ShowString(1, 21, "Box number:", RED);
				LCD_ShowString(1, 41, "BOOT0 to continue", RED);
				LCD_ShowNum(60, 1, level, 1, WHITE);//level
				LCD_ShowNum(100, 21, box, 1, WHITE);//box
			}
			//Add level
			if(Get_Button(JOY_CTR)){
				if(level < 3) level++;
				else continue;
				LCD_Clear(BLACK);
				//display information
				LCD_ShowString(1, 1, "Level:", RED);
				LCD_ShowString(1, 21, "Box number:", RED);
				LCD_ShowString(1, 41, "BOOT0 to continue", RED);
				LCD_ShowNum(60, 1, level, 1, WHITE);//level
				LCD_ShowNum(100, 21, box, 1, WHITE);//box
			}
			//Reduce level
			if(Get_Button(JOY_DOWN)){
				if(level > 1) level--;
				else continue;
				LCD_Clear(BLACK);
				//display information
				LCD_ShowString(1, 1, "Level:", RED);
				LCD_ShowString(1, 21, "Box number:", RED);
				LCD_ShowString(1, 41, "BOOT0 to continue", RED);
				LCD_ShowNum(60, 1, level, 1, WHITE);//level
				LCD_ShowNum(100, 21, box, 1, WHITE);//box
			}
			//Press BOOT0 to continue
	    	if(Get_BOOT0()) break;
		}
		
		//---------------Build Map----------------
		//1:obstacle 2:Terminal 3:Goal 4:Player 5:box 
		if(level == 1){
			//Draw obstacles
			for(int j = 1 ; j < 8 ; j++) a[2][j] = a[7][j] = 1;
			for(int i = 2 ; i < 8 ; i++) a[i][1] = a[i][7] = 1;
			a[4][3] = a[4][6] = a[5][6] = a[6][4] = 1;
			//Set position of Player
			PlayerX = 5; PlayerY = 4;
			//Draw boxes and terminals
			a[3][3] = 2;a[4][4] = 5;
			if(box > 1)	a[5][2] = 2,a[5][4] = 5;
			if(box > 2)	a[6][5] = 2,a[5][5] = 5;
		}
		if(level == 2){
			//Draw obstacles
			for(int j = 1 ; j < 8 ; j++) a[2][j] = a[8][j] = 1;
			for(int i = 2 ; i < 9 ; i++) a[i][1] = a[i][7] = 1;
			a[3][3] = a[3][4] = a[5][3] = a[5][4] = a[7][3] = 1;
			//Set position of Player
			PlayerX = 2; PlayerY = 6;
			//Draw boxes and terminals
			a[3][2] = 2;a[4][5] = 5;
			if(box > 1)	a[5][6] = 2,a[5][2] = 5;
			if(box > 2)	a[7][4] = 2,a[6][3] = 5;
		}
		if(level == 3){
			//Draw obstacles
			a[1][1] = a[1][2] = a[1][3] = a[1][4] = a[1][5] = 1;
			a[2][1] = a[2][5] = a[2][6] = a[2][7] = 1;
			a[3][1] = a[3][3] = a[3][7] = 1;
			a[4][1] = a[4][7] = 1;
			a[5][1] = a[5][6] = a[5][7] = 1;
			a[6][1] = a[6][2] = a[6][3] = a[6][6] = 1;
			a[7][3] = a[7][4] = a[7][5] = a[7][6] = 1;
			//Set position of Player
			PlayerX = 3; PlayerY = 4;
			//Draw boxes and terminals
			a[2][2] = 2;a[3][4] = 5;
			if(box > 1)	a[3][2] = 2,a[4][4] = 5;
			if(box > 2)	a[4][2] = 2,a[5][4] = 5;
		}
		//Set map for Player
		a[PlayerY][PlayerX] = 4;
		//---------------End Build----------------
		while(1){
			LCD_Clear(BLACK);
			//Make room for "step" display
			LCD_ShowString(92, 1, "step:", RED);
			LCD_ShowNum(128, 1, step, 3, WHITE);
			LCD_DrawLine(90, 1, 90, 16, RED);
			LCD_DrawLine(90, 16, 159, 16, RED);
			//Draw map
			for(int i = 0 ; i < 10 ; i++)
				for(int j = 0 ; j < 20 ; j++)
					//Different element of map
					if(a[i][j] == 1) DrawObstacle(j, i); else
					if(a[i][j] == 2) DrawTerminal(j, i); else
					if(a[i][j] == 3) DrawGoal(j, i); else
					if(a[i][j] == 4) DrawPlayer(j, i); else
					if(a[i][j] == 5) DrawBox(j, i);
			//Calculate current score
			Score = 0;
			for(int i = 0 ; i < 10 ; i++)
				for(int j = 0 ; j < 20 ; j++)
					if(a[i][j] == 3) Score++;
			//Game finished
			if(Score == box){
				delay_1ms(2000);
				break;
			}
			//Operations
			while(1){
				//Recover the position of Player
				a[PlayerY][PlayerX] = Cover;
				delay_1ms(200);
				if(PlayerX < 20 && Get_Button(JOY_RIGHT)){
					//Nothing ahead
					if(a[PlayerY][PlayerX + 1] == 0){
						PlayerX++;
						step++;
						Cover = 0;
						break;
					}
					//Meet terminal
					if(a[PlayerY][PlayerX + 1] == 2){
						PlayerX++;
						step++;
						Cover = 2;
						break;
					}
					//Meet box in terminal
					if(a[PlayerY][PlayerX + 1] == 3){
						//Nothing ahead
						if(a[PlayerY][PlayerX + 2] == 0){
							a[PlayerY][PlayerX + 2] = 5;
							PlayerX++;
							step++;
							Cover = 2;
							break;
						}
						//Meet another terminal
						if(a[PlayerY][PlayerX + 2] == 2){
							a[PlayerY][PlayerX + 2] = 3;
							PlayerX++;
							step++;
							Cover = 2;
							break;
						}
					}
					//Meet box
					if(a[PlayerY][PlayerX + 1] == 5){
						//Nothing ahead
						if(a[PlayerY][PlayerX + 2] == 0){
							a[PlayerY][PlayerX + 2] = 5;
							PlayerX++;
							step++;
							Cover = 0;
							break;
						}
						//Meet terminal
						if(a[PlayerY][PlayerX + 2] == 2){
							a[PlayerY][PlayerX + 2] = 3;
							PlayerX++;
							step++;
							Cover = 0;
							break;
						}
					}
					//End Right
				}
				if(PlayerX > 0 && Get_Button(JOY_LEFT)){
					//Nothing ahead
					if(a[PlayerY][PlayerX - 1] == 0){
						
						PlayerX--;
						step++;
						Cover = 0;
						break;
					}
					//Meet terminal
					if(a[PlayerY][PlayerX - 1] == 2){
						PlayerX--;
						step++;
						Cover = 2;
						break;
					}
					//Meet box in terminal
					if(a[PlayerY][PlayerX - 1] == 3){
						//Nothing ahead
						if(a[PlayerY][PlayerX - 2] == 0){
							a[PlayerY][PlayerX - 2] = 5;
							PlayerX--;
							step++;
							Cover = 2;
							break;
						}
						//Meet another terminal
						if(a[PlayerY][PlayerX - 2] == 2){
							a[PlayerY][PlayerX - 2] = 3;
							PlayerX--;
							step++;
							Cover = 2;
							break;
						}
					}
					//Meet box
					if(a[PlayerY][PlayerX - 1] == 5){
						//Nothing ahead
						if(a[PlayerY][PlayerX - 2] == 0){
							a[PlayerY][PlayerX - 2] = 5;
							PlayerX--;
							step++;
							Cover = 0;
							break;
						}
						//Meet terminal
						if(a[PlayerY][PlayerX - 2] == 2){
							a[PlayerY][PlayerX - 2] = 3;
							PlayerX--;
							step++;
							Cover = 0;
							break;
						}
					}
					//End Left
				}
				if(PlayerY < 9 && Get_Button(JOY_DOWN)){
					//Nothing ahead
					if(a[PlayerY + 1][PlayerX] == 0){
						PlayerY++;
						step++;
						Cover = 0;
						break;
					}
					//Meet terminal
					if(a[PlayerY + 1][PlayerX] == 2){
						PlayerY++;
						step++;
						Cover = 2;
						break;
					}
					//Meet box in terminal
					if(a[PlayerY + 1][PlayerX] == 3){
						//Nothing ahead
						if(a[PlayerY + 2][PlayerX] == 0){
							a[PlayerY + 2][PlayerX] = 5;
							PlayerY++;
							step++;
							Cover = 2;
							break;
						}
						//Meet another terminal
						if(a[PlayerY + 2][PlayerX] == 2){
							a[PlayerY + 2][PlayerX] = 3;
							PlayerY++;
							step++;
							Cover = 2;
							break;
						}
					}
					//Meet box
					if(a[PlayerY + 1][PlayerX] == 5){
						//Nothing ahead
						if(a[PlayerY + 2][PlayerX] == 0){
							a[PlayerY + 2][PlayerX] = 5;
							PlayerY++;
							step++;
							Cover = 0;
							break;
						}
						//Meet terminal
						if(a[PlayerY + 2][PlayerX] == 2){
							a[PlayerY + 2][PlayerX] = 3;
							PlayerY++;
							step++;
							Cover = 0;
							break;
						}
					}
					//End Down
				}
				//Replace Up with CTR
				if(PlayerY > 0 && Get_Button(JOY_CTR)){
					//Nothing ahead
					if(a[PlayerY - 1][PlayerX] == 0){
						PlayerY--;
						step++;
						Cover = 0;
						break;
					}
					//Meet terminal
					if(a[PlayerY - 1][PlayerX] == 2){
						PlayerY--;
						step++;
						Cover = 2;
						break;
					}
					//Meet box in terminal
					if(a[PlayerY - 1][PlayerX] == 3){
						//Nothing ahead
						if(a[PlayerY - 2][PlayerX] == 0){
							a[PlayerY - 2][PlayerX] = 5;
							PlayerY--;
							step++;
							Cover = 2;
							break;
						}
						//Meet another terminal
						if(a[PlayerY - 2][PlayerX] == 2){
							a[PlayerY - 2][PlayerX] = 3;
							PlayerY--;
							step++;
							Cover = 2;
							break;
						}
					}
					//Meet box
					if(a[PlayerY - 1][PlayerX] == 5){
						//Nothing ahead
						if(a[PlayerY - 2][PlayerX] == 0){
							a[PlayerY - 2][PlayerX] = 5;
							PlayerY--;
							step++;
							Cover = 0;
							break;
						}
						//Meet terminal
						if(a[PlayerY - 2][PlayerX] == 2){
							a[PlayerY - 2][PlayerX] = 3;
							PlayerY--;
							step++;
							Cover = 0;
							break;
						}
					}
					//End Up
				}
			}
			//Update Player
			a[PlayerY][PlayerX] = 4;
		}
		LCD_Clear(BLACK);
		LCD_ShowString(45, 35, "You Win!", GREEN);
		LCD_ShowString(92, 1, "step:", RED);
		LCD_ShowNum(128, 1, step, 3, GREEN);
		//Compare with previous scores
		if(step <= BestScore[level][1]){
			BestScore[level][3] = BestScore[level][2];
			BestScore[level][2] = BestScore[level][1];
			BestScore[level][1] = step;
		}
		//The second
		else if(step <= BestScore[level][2]){
			BestScore[level][3] = BestScore[level][2];
			BestScore[level][2] = step;
		}
		//The third
		else if(step <= BestScore[level][3]){
			BestScore[level][3] = step;
		}
		//Show score board
		delay_1ms(3000);
		LCD_Clear(BLACK);
		LCD_ShowString(40, 1, "Best Scores", WHITE);
		LCD_ShowString(10, 15, "Lv.1", WHITE);
		LCD_ShowString(60, 15, "Lv.2", WHITE);
		LCD_ShowString(110, 15, "Lv.3", WHITE);
		//Show data
		for(int i = 1 ; i <= 3 ; i++){
			for(int j = 1 ; j <= 3 ; j++){
				if(BestScore[i][j] == 999) LCD_ShowString(ScoreX[i], ScoreY[j], "-", WHITE);
				else LCD_ShowNum(ScoreX[i], ScoreY[j], BestScore[i][j], 3, WHITE);
			}
		}
		//Delay
		delay_1ms(3000);
	}
}