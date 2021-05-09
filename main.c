#include "rubiks.h"
#include <stdio.h>

int main(){
    RUBIKS_SIDE * rubikscube;
    rubikscube = create_rubiks();
    init_rubiks(rubikscube);
    display_rubiks(rubikscube);
    move_rubiks(rubikscube);
    display_rubiks(rubikscube);
    return 0;
}