#include <stdio.h>
#include "joystick.h"
#include <fcntl.h>
#define BUTTON_DATA_MAX 12
#define STICK_DATA_MAX 6

void dbg_cmd_view(unsigned char btn[],float stk[]){
    int i;
    for(i = 0;i < BUTTON_DATA_MAX;i++){
        printf("(%d)",btn[i]);
    }
    printf("\n");
    for(i = 0;i < STICK_DATA_MAX;i++){
        printf("(%6.2f)",stk[i]);
    }
    printf("\n");
}

int main(void)
{
        
    int fd;
    fd = open( "/dev/input/js0", O_RDONLY );

    unsigned char  ButtonData[BUTTON_DATA_MAX];
    float    StickData[STICK_DATA_MAX];

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
        dbg_cmd_view(ButtonData,StickData);       //debug

    }
    close( fd );

    return 0;
}


