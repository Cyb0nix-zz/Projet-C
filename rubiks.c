#include <stdio.h>
#include "rubiks.h"
#include <windows.h>

void select_color(T_COLOR color){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color) {
        case R:
            SetConsoleTextAttribute(H,12);
            break;
        case B:
            SetConsoleTextAttribute(H,9);
            break;
        case G:
            SetConsoleTextAttribute(H,10);
            break;
        case W:
            SetConsoleTextAttribute(H,15);
            break;
        case Y:
            SetConsoleTextAttribute(H,14);
            break;
        case O:
            SetConsoleTextAttribute(H,13);
            break;
        case LG:
            SetConsoleTextAttribute(H,7);
            break;
        default:
            break;

    }


}

int side_to_index(T_SIDE side){

    switch (side) {

        case LEFT:
            return 0;
        case UP:
            return 1;
        case FRONT:
            return 2;
        case DOWN:
            return 3;
        case RIGHT:
            return 4;
        case BACK:
            return 5;
        default:
            return 0;
    }
}

char color_to_char(T_COLOR color) {
    switch (color) {
        case R:
            return 'R';
        case B:
            return 'B';
        case G:
            return 'G';
        case W:
            return 'W';
        case Y:
            return 'Y';
        case O:
            return 'O';
        case LG:
            return 'X';
        default:
            break;
    }
}

rubiks* create_rubiks(){
   rubiks *rubikscube = (rubiks*) malloc(sizeof(rubiks));

    return rubikscube;
}



void init_rubiks(rubiks* rubikscube){
    T_COLOR val;
    for (int i = 0; i < 6; ++i) {
        switch (side_to_index(rubikscube[i]->Type_face)) {
            case LEFT:
                val = O;
                break;
            case UP:
                val = W;
                break;
            case FRONT:
                val = G;
                break;
            case DOWN:
                val = Y;
                break;
            case RIGHT:
                val = R;
                break;
            case BACK:
                val = B;
                break;
            default:
                break;

        }
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                rubikscube[i]->Face[j][k] = val;
            }
        }
    }
}

void display_rubiks(rubiks* rubikscube){
    T_COLOR display[9][12];
    T_SIDE face;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 12; ++j) {
            display[i][j] = ' ';
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            display[i][3+j] = rubikscube[side_to_index(UP)]->Face[i][j];
        }

        for (int j = 0; j < 3; ++j) {
            display[6+i][3+j] = rubikscube[side_to_index(DOWN)]->Face[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0:
                face = LEFT;
                break;
            case 1:
                face = FRONT;
                break;
            case 2:
                face = RIGHT;
                break;
            case 3:
                face = BACK;
                break;
            default:
                break;
        }
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                display[3+j][i*3+k] = rubikscube[side_to_index(face)]->Face[j][k];
            }
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 12; ++j) {
            select_color(display[i][j]);
            printf(" %c ",color_to_char(display[i][j]));
        }
        printf("\n");
    }
}


