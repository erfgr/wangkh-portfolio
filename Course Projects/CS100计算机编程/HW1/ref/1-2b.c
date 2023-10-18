//
// Created by suhang on 2022/2/21.
//
#include <stdio.h>
#define IS_VALID(X) ((X) < 1.8*1.8)
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define DIST(X, Y) (((X) * (X)) + ((Y) * (Y)))

void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    double red1_x, red1_y, red2_x, red2_y, red3_x, red3_y;
    double yellow1_x, yellow1_y, yellow2_x, yellow2_y, yellow3_x, yellow3_y;
    scanf("(%f,%f)\n", &red1_x, &red1_y);
    scanf("(%f,%f)\n", &red2_x, &red2_y);
    scanf("(%f,%f)\n", &red3_x, &red3_y);
    scanf("(%f,%f)\n", &yellow1_x, &yellow1_y);
    scanf("(%f,%f)\n", &yellow2_x, &yellow2_y);
    scanf("(%f,%f)\n", &yellow3_x, &yellow3_y);
    /* Calculate the square of distance */
    double red_near, red_middle, red_far;
    double yellow_near, yellow_middle, yellow_far;
    /* Sort the stones in order */
    red_near = DIST(red1_x, red1_y);
    red_middle = DIST(red2_x, red2_y);
    red_far = DIST(red3_x, red3_y);
    yellow_near = DIST(yellow1_x, yellow1_y);
    yellow_middle = DIST(yellow2_x, yellow2_y);
    yellow_far = DIST(yellow3_x, yellow3_y);
    if(red_near > red_far) swap(&red_near, &red_far);
    if(red_near > red_middle) swap(&red_near, &red_middle);
    if(red_middle > red_far) swap(&red_middle, &red_far);
    if(yellow_near > yellow_far) swap(&yellow_near, &yellow_far);
    if(yellow_near > yellow_middle) swap(&yellow_near, &yellow_middle);
    if(yellow_middle > yellow_far) swap(&yellow_middle, &yellow_far);
    int score = 1;
    if(red_near < yellow_near){
        if(!IS_VALID(red_near)){
            printf("BLANK END\n");
        }
        else{
            if(red_middle < yellow_near && IS_VALID(red_middle)) ++score;
            if(red_far < yellow_near && IS_VALID(red_far)) ++score;
            printf("RED SCORES %d\n", score);
        }
    }else{
        if(!IS_VALID(yellow_near)){
            printf("BLANK END\n");
        }
        else{
            if(yellow_middle < red_near && IS_VALID(yellow_middle)) ++score;
            if(yellow_far < red_near && IS_VALID(yellow_far)) ++score;
            printf("YELLOW SCORES %d\n", score);
        }
    }
    return 0;
}
