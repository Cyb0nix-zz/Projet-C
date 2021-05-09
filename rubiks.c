#include <stdio.h>
#include "rubiks.h"
#include <windows.h>

char select_color(T_COLOR color){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color) {

        case R:
            SetConsoleTextAttribute(H,12);
            return 'R';
        case B:
            SetConsoleTextAttribute(H,9);
            return 'B';
        case G:
            SetConsoleTextAttribute(H,10);
            return 'G';
        case W:
            SetConsoleTextAttribute(H,15);
            return 'W';
        case Y:
            SetConsoleTextAttribute(H,14);
            return 'Y';
        case O:
            SetConsoleTextAttribute(H,13);
            return 'O';
        case LG:
            SetConsoleTextAttribute(H,7);
            return 'X';
        default:
            return ' ';

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

RUBIKS_SIDE* create_rubiks(){

    RUBIKS_SIDE* rubikscube = (RUBIKS_SIDE*) malloc(sizeof(RUBIKS_SIDE)*6);

    rubikscube[0].type_face = LEFT;
    rubikscube[1].type_face = UP;
    rubikscube[2].type_face = FRONT;
    rubikscube[3].type_face = DOWN;
    rubikscube[4].type_face = RIGHT;
    rubikscube[5].type_face = BACK;

    return rubikscube;
}



void init_rubiks(RUBIKS_SIDE* rubikscube){
    T_COLOR val;
    for (int i = 0; i < 6; ++i) {
        switch (rubikscube[i].type_face) {
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
                rubikscube[i].face[j][k] = val;
            }
        }
    }
}

void display_rubiks(RUBIKS_SIDE * rubikscube){
    T_COLOR display[9][12];
    T_SIDE face;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 12; ++j) {
            display[i][j] = ' ';
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            display[i][3+j] = rubikscube[side_to_index(UP)].face[i][j];
        }

        for (int j = 0; j < 3; ++j) {
            display[6+i][3+j] = rubikscube[side_to_index(DOWN)].face[i][j];
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
                display[3+j][i*3+k] = rubikscube[side_to_index(face)].face[j][k];
            }
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 12; ++j) {
            printf(" %c ",select_color(display[i][j]));
        }
        printf("\n");
    }
    printf("\n");
}

void blank_rubiks(RUBIKS_SIDE* rubiscube){
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                rubiscube[i].face[j][k] = LG;
            }
        }
    }
}

void fill_rubiks(RUBIKS_SIDE* rubikscube){

}

void scramble_rubiks(RUBIKS_SIDE* rubiscube){

}

void free_rubiks(RUBIKS_SIDE* rubiscube){
    free(rubiscube);
}

void front_clockwise(RUBIKS_SIDE* rubiscube){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubiscube[side_to_index(LEFT)].face[i][2];
        rubiscube[side_to_index(LEFT)].face[i][2] = rubiscube[side_to_index(DOWN)].face[0][i];
        rubiscube[side_to_index(DOWN)].face[0][i]= rubiscube[side_to_index(RIGHT)].face[2-i][0];
        rubiscube[side_to_index(RIGHT)].face[2-i][0] = rubiscube[side_to_index(UP)].face[2][2-i];
        rubiscube[side_to_index(UP)].face[2][2-i] = tmp;
    }
    
}

void back_clockwise(RUBIKS_SIDE* rubiscube){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubiscube[side_to_index(LEFT)].face[2-i][0];
        rubiscube[side_to_index(LEFT)].face[2-i][0] = rubiscube[side_to_index(UP)].face[0][i];
        rubiscube[side_to_index(UP)].face[0][i]= rubiscube[side_to_index(RIGHT)].face[i][2];
        rubiscube[side_to_index(RIGHT)].face[i][2] = rubiscube[side_to_index(DOWN)].face[2][2-i];
        rubiscube[side_to_index(DOWN)].face[2][2-i] = tmp;
    }

}



