//
// Created by suhang on 2022/2/21.
//
#include <stdio.h>

int main(){
    int num;
    double distance = 0;
    double prev_velocity = 3, curr_velocity = 3;
    double acceleration = 0.2;
    double prev_time = 0, curr_time = 0;
    char command;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%f - %c", &curr_time, &command);
        curr_velocity = prev_velocity - acceleration * (curr_time - prev_time);
        if(curr_velocity > 0){
            /* Stone doesn't stop */
            distance += 0.5 * (curr_velocity + prev_velocity) * (curr_time - prev_time);
        }
        else{
            /* Stone stops */
            distance += 0.5 * prev_velocity * (prev_velocity / acceleration);
            printf("The stone has slided for %.3fm\n", distance);
            return 0;
        }
        prev_time = curr_time;
        prev_velocity = curr_velocity;
        if(command == 'H') {
            acceleration = 0.1;
        }
        if(command == 'W'){
            acceleration = 0.2;
        }
    }
    distance += 0.5 * prev_velocity * (prev_velocity / acceleration);
    printf("The stone has slided for %.3lfm\n", distance);
    return 0;
}
