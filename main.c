#include <stdio.h>
#include <unistd.h>
#include "joystick.h"
#include <fcntl.h>
#define BUTTON_DATA_MAX 12
#define STICK_DATA_MAX 6
#define MAX_STICK 1 
#define BUTTON_X 0
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_Y 3
#define BUTTON_LB 4
#define BUTTON_RB 5
#define BUTTON_LT 6
#define BUTTON_RT 7
#define BUTTON_BACK 8
#define BUTTON_START 9
#define BUTTON_STICKLEFT 10
#define BUTTON_STICKRIGHT 11
#define LEFT_STICK_X 0
#define LEFT_STICK_Y 1
#define RIGHT_STICK_X 2
#define RIGHT_STICK_Y 3
#define CROSS_STICK_X 4
#define CROSS_STICK_Y 5

void dbg_cmd_view(unsigned char btn[],float stk[]){
    int i;
    for(i = 0;i < BUTTON_DATA_MAX;i++){
        printf("(%.2d)",btn[i]);
    }
    printf("\n");
    for(i = 0;i < STICK_DATA_MAX;i++){
        printf("(%6.2f)",stk[i]);
    }
    printf("\n");
}

void dbg_cmd_view_2(unsigned char btn[],float stk[])
{
        printf("X = %d\t",btn[BUTTON_X]);
        printf("A = %d\t",btn[BUTTON_A]);
        printf("B = %d\t",btn[BUTTON_B]);
        printf("Y = %d\t",btn[BUTTON_Y]);
        printf("LB = %d\t",btn[BUTTON_LB]);
        printf("RB = %d\t",btn[BUTTON_RB]);
        printf("LT = %d\t",btn[BUTTON_LT]);
        printf("RT = %d\t",btn[BUTTON_RT]);
        printf("Back = %d\t",btn[BUTTON_BACK]);
        printf("Start = %d\n",btn[BUTTON_START]);
        printf("ButtonLeft = %d\t",btn[BUTTON_STICKLEFT]);
        printf("ButtonRight = %d\t",btn[BUTTON_STICKRIGHT]);
        printf("Left_X = %.2f\t",stk[LEFT_STICK_X]);
        printf("Left_Y = %.2f\t",stk[LEFT_STICK_Y]);
        printf("Right_X = %.2f\t",stk[RIGHT_STICK_X]);
        printf("Right_Y = %.2f\t",stk[RIGHT_STICK_Y]);
        printf("Cross_X = %.2f\t",stk[CROSS_STICK_X]);
        printf("Cross_Y = %.2f\n",stk[CROSS_STICK_Y]);
}
int main(void)
{
        
    int fd;

    fd = open( "/dev/input/js0", O_RDONLY );

      unsigned char  ButtonData[BUTTON_DATA_MAX];
   // signed int     StickData[STICK_DATA_MAX];
      float StickData[STICK_DATA_MAX];
      

    for(;;){
        struct js_event  event;
        if( read( fd, &event, sizeof(struct js_event) ) >= sizeof(struct js_event) ){
            switch( event.type & 0x7f ){
            case JS_EVENT_BUTTON:
                if( event.number < BUTTON_DATA_MAX ){
                    ButtonData[ event.number ]= event.value;
                }
                break;
            case JS_EVENT_AXIS:
                if( event.number < STICK_DATA_MAX ){
                    StickData[ event.number ]= event.value;
                }
                break;
            }
        }
       // dbg_cmd_view(ButtonData,StickData);       //debug


        StickData[LEFT_STICK_Y] *= -1;
        StickData[RIGHT_STICK_Y] *= -1;
        StickData[CROSS_STICK_Y] *= -1;
        
        StickData[LEFT_STICK_X] /= MAX_STICK;
        StickData[LEFT_STICK_Y] /= MAX_STICK;
        StickData[LEFT_STICK_X] /= MAX_STICK;
        StickData[LEFT_STICK_Y] /= MAX_STICK;
        StickData[CROSS_STICK_X] /= MAX_STICK;
        StickData[CROSS_STICK_Y] /= MAX_STICK;

        dbg_cmd_view_2(ButtonData,StickData);
        
    }
    close( fd );

    return 0;
}

