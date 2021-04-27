#include <stdio.h>
#include "rubiks.h"

int select_color(T_COLOR color){
//TODO
}

int side_to_index(T_SIDE side){
    
    if (side == LEFT){
        return 0;
    }else if (side == UP){
        return 1;
    }else if (side == FRONT)
    {
        return 2;
    }else if (side == DOWN)
    {
        return 3;
    }else if (side == RIGHT)
    {
        return 4;
    }else if (side == BACK)
    {
        return 5;
    }
}

