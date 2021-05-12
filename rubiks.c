#include <stdio.h>
#include "rubiks.h"
#include <windows.h>
#include <time.h>

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
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
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
            SetConsoleTextAttribute(H,15);

        }
        printf("\n");
    }
    printf("\n");
}

void blank_rubiks(RUBIKS_SIDE* rubikscube){
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                rubikscube[i].face[j][k] = LG;
            }
        }
    }
}

void fill_rubiks(RUBIKS_SIDE* rubikscube){
    int i, j, k;
    int cptR = 0, cptB = 0, cptG = 0, cptW = 0, cptY = 0, cptO = 0;
    char val;

    for(int cpt = 0; cpt < 54; ++cpt){
        printf("Quelle face voulez vous modifier ? :\n");
        scanf("%d", &i);

        printf("Quelle case voulez vous modifier ? (ligne et colonne entre 0 et 2) :\n");
        scanf("%d %d", &j, &k);

        printf("quelle couleur? :\n");
        scanf(" %c", &val);



        switch (val) {
                case 'R':
                    if (cptR >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = R;

                    if (((rubikscube[0].face[0][0] == R)&&(rubikscube[1].face[0][0] == R))||((rubikscube[0].face[0][1] == R)&&(rubikscube[1].face[1][0] == R))||((rubikscube[0].face[0][2] == R)&&(rubikscube[1].face[2][0] == R))||((rubikscube[5].face[0][2] == R)&&(rubikscube[1].face[0][0] == R))||((rubikscube[5].face[0][1] == R)&&(rubikscube[1].face[0][1] == R))||((rubikscube[5].face[0][0] == R)&&(rubikscube[1].face[0][2] == R))||((rubikscube[4].face[0][0] == R)&&(rubikscube[1].face[2][2] == R))||((rubikscube[4].face[0][1] == R)&&(rubikscube[1].face[1][2] == R))||((rubikscube[4].face[0][2] == R)&&(rubikscube[1].face[0][2] == R))||((rubikscube[2].face[0][0] == R)&&(rubikscube[1].face[2][0] == R))||((rubikscube[2].face[0][1] == R)&&(rubikscube[1].face[2][1] == R))||((rubikscube[2].face[0][2] == R)&&(rubikscube[1].face[2][2] == R))||((rubikscube[2].face[0][0] == R)&&(rubikscube[0].face[0][2] == R))||((rubikscube[2].face[1][0] == R)&&(rubikscube[0].face[1][2] == R))||((rubikscube[2].face[2][0] == R)&&(rubikscube[0].face[2][2] == R))||((rubikscube[2].face[2][0] == R)&&(rubikscube[3].face[0][0] == R))||((rubikscube[2].face[2][1] == R)&&(rubikscube[3].face[0][1] == R))||((rubikscube[2].face[2][2] == R)&&(rubikscube[3].face[0][2] == R))||((rubikscube[2].face[0][2] == R)&&(rubikscube[4].face[0][0] == R))||((rubikscube[2].face[1][2] == R)&&(rubikscube[4].face[1][0] == R))||((rubikscube[2].face[2][2] == R)&&(rubikscube[4].face[2][0] == R))||((rubikscube[3].face[0][0] == R)&&(rubikscube[0].face[2][2] == R))||((rubikscube[3].face[1][0] == R)&&(rubikscube[0].face[2][1] == R))||((rubikscube[3].face[2][0] == R)&&(rubikscube[0].face[2][0] == R))||((rubikscube[3].face[0][2] == R)&&(rubikscube[4].face[2][0] == R))||((rubikscube[3].face[1][2] == R)&&(rubikscube[4].face[1][0] == R))||((rubikscube[3].face[2][2] == R)&&(rubikscube[4].face[2][0] == R))||((rubikscube[3].face[2][0] == R)&&(rubikscube[5].face[2][2] == R))||((rubikscube[3].face[2][1] == R)&&(rubikscube[5].face[2][1] == R))||((rubikscube[3].face[2][2] == R)&&(rubikscube[5].face[2][0] == R))||((rubikscube[5].face[0][0] == R)&&(rubikscube[4].face[0][2] == R))||((rubikscube[5].face[1][0] == R)&&(rubikscube[4].face[1][2] == R))||((rubikscube[5].face[2][0] == R)&&(rubikscube[4].face[2][2] == R))||((rubikscube[5].face[0][2] == R)&&(rubikscube[0].face[0][0] == R))||((rubikscube[5].face[1][2] == R)&&(rubikscube[0].face[1][0] == R))||((rubikscube[5].face[2][2] == R)&&(rubikscube[0].face[2][0] == R))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptR = cptR+1;
                    break;
                case 'B':
                    if (cptB >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = B;

                    if (((rubikscube[0].face[0][0] == B)&&(rubikscube[1].face[0][0] == B))||((rubikscube[0].face[0][1] == B)&&(rubikscube[1].face[1][0] == B))||((rubikscube[0].face[0][2] == B)&&(rubikscube[1].face[2][0] == B))||((rubikscube[5].face[0][2] == B)&&(rubikscube[1].face[0][0] == B))||((rubikscube[5].face[0][1] == B)&&(rubikscube[1].face[0][1] == B))||((rubikscube[5].face[0][0] == B)&&(rubikscube[1].face[0][2] == B))||((rubikscube[4].face[0][0] == B)&&(rubikscube[1].face[2][2] == B))||((rubikscube[4].face[0][1] == B)&&(rubikscube[1].face[1][2] == B))||((rubikscube[4].face[0][2] == B)&&(rubikscube[1].face[0][2] == B))||((rubikscube[2].face[0][0] == B)&&(rubikscube[1].face[2][0] == B))||((rubikscube[2].face[0][1] == B)&&(rubikscube[1].face[2][1] == B))||((rubikscube[2].face[0][2] == B)&&(rubikscube[1].face[2][2] == B))||((rubikscube[2].face[0][0] == B)&&(rubikscube[0].face[0][2] == B))||((rubikscube[2].face[1][0] == B)&&(rubikscube[0].face[1][2] == B))||((rubikscube[2].face[2][0] == B)&&(rubikscube[0].face[2][2] == B))||((rubikscube[2].face[2][0] == B)&&(rubikscube[3].face[0][0] == B))||((rubikscube[2].face[2][1] == B)&&(rubikscube[3].face[0][1] == B))||((rubikscube[2].face[2][2] == B)&&(rubikscube[3].face[0][2] == B))||((rubikscube[2].face[0][2] == B)&&(rubikscube[4].face[0][0] == B))||((rubikscube[2].face[1][2] == B)&&(rubikscube[4].face[1][0] == B))||((rubikscube[2].face[2][2] == B)&&(rubikscube[4].face[2][0] == B))||((rubikscube[3].face[0][0] == B)&&(rubikscube[0].face[2][2] == B))||((rubikscube[3].face[1][0] == B)&&(rubikscube[0].face[2][1] == B))||((rubikscube[3].face[2][0] == B)&&(rubikscube[0].face[2][0] == B))||((rubikscube[3].face[0][2] == B)&&(rubikscube[4].face[2][0] == B))||((rubikscube[3].face[1][2] == B)&&(rubikscube[4].face[1][0] == B))||((rubikscube[3].face[2][2] == B)&&(rubikscube[4].face[2][0] == B))||((rubikscube[3].face[2][0] == B)&&(rubikscube[5].face[2][2] == B))||((rubikscube[3].face[2][1] == B)&&(rubikscube[5].face[2][1] == B))||((rubikscube[3].face[2][2] == B)&&(rubikscube[5].face[2][0] == B))||((rubikscube[5].face[0][0] == B)&&(rubikscube[4].face[0][2] == B))||((rubikscube[5].face[1][0] == B)&&(rubikscube[4].face[1][2] == B))||((rubikscube[5].face[2][0] == B)&&(rubikscube[4].face[2][2] == B))||((rubikscube[5].face[0][2] == B)&&(rubikscube[0].face[0][0] == B))||((rubikscube[5].face[1][2] == B)&&(rubikscube[0].face[1][0] == B))||((rubikscube[5].face[2][2] == B)&&(rubikscube[0].face[2][0] == B))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptB = cptB+1;
                    break;
                case 'G':
                    if (cptG >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = G;
                    if (((rubikscube[0].face[0][0] == G)&&(rubikscube[1].face[0][0] == G))||((rubikscube[0].face[0][1] == G)&&(rubikscube[1].face[1][0] == G))||((rubikscube[0].face[0][2] == G)&&(rubikscube[1].face[2][0] == G))||((rubikscube[5].face[0][2] == G)&&(rubikscube[1].face[0][0] == G))||((rubikscube[5].face[0][1] == G)&&(rubikscube[1].face[0][1] == G))||((rubikscube[5].face[0][0] == G)&&(rubikscube[1].face[0][2] == G))||((rubikscube[4].face[0][0] == G)&&(rubikscube[1].face[2][2] == G))||((rubikscube[4].face[0][1] == G)&&(rubikscube[1].face[1][2] == G))||((rubikscube[4].face[0][2] == G)&&(rubikscube[1].face[0][2] == G))||((rubikscube[2].face[0][0] == G)&&(rubikscube[1].face[2][0] == G))||((rubikscube[2].face[0][1] == G)&&(rubikscube[1].face[2][1] == G))||((rubikscube[2].face[0][2] == G)&&(rubikscube[1].face[2][2] == G))||((rubikscube[2].face[0][0] == G)&&(rubikscube[0].face[0][2] == G))||((rubikscube[2].face[1][0] == G)&&(rubikscube[0].face[1][2] == G))||((rubikscube[2].face[2][0] == G)&&(rubikscube[0].face[2][2] == G))||((rubikscube[2].face[2][0] == G)&&(rubikscube[3].face[0][0] == G))||((rubikscube[2].face[2][1] == G)&&(rubikscube[3].face[0][1] == G))||((rubikscube[2].face[2][2] == G)&&(rubikscube[3].face[0][2] == G))||((rubikscube[2].face[0][2] == G)&&(rubikscube[4].face[0][0] == G))||((rubikscube[2].face[1][2] == G)&&(rubikscube[4].face[1][0] == G))||((rubikscube[2].face[2][2] == G)&&(rubikscube[4].face[2][0] == G))||((rubikscube[3].face[0][0] == G)&&(rubikscube[0].face[2][2] == G))||((rubikscube[3].face[1][0] == G)&&(rubikscube[0].face[2][1] == G))||((rubikscube[3].face[2][0] == G)&&(rubikscube[0].face[2][0] == G))||((rubikscube[3].face[0][2] == G)&&(rubikscube[4].face[2][0] == G))||((rubikscube[3].face[1][2] == G)&&(rubikscube[4].face[1][0] == G))||((rubikscube[3].face[2][2] == G)&&(rubikscube[4].face[2][0] == G))||((rubikscube[3].face[2][0] == G)&&(rubikscube[5].face[2][2] == G))||((rubikscube[3].face[2][1] == G)&&(rubikscube[5].face[2][1] == G))||((rubikscube[3].face[2][2] == G)&&(rubikscube[5].face[2][0] == G))||((rubikscube[5].face[0][0] == G)&&(rubikscube[4].face[0][2] == G))||((rubikscube[5].face[1][0] == G)&&(rubikscube[4].face[1][2] == G))||((rubikscube[5].face[2][0] == G)&&(rubikscube[4].face[2][2] == G))||((rubikscube[5].face[0][2] == G)&&(rubikscube[0].face[0][0] == G))||((rubikscube[5].face[1][2] == G)&&(rubikscube[0].face[1][0] == G))||((rubikscube[5].face[2][2] == G)&&(rubikscube[0].face[2][0] == G))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptG = cptG+1;
                    break;
                case 'W':
                    if (cptW >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = W;
                    if (((rubikscube[0].face[0][0] == W)&&(rubikscube[1].face[0][0] == W))||((rubikscube[0].face[0][1] == W)&&(rubikscube[1].face[1][0] == W))||((rubikscube[0].face[0][2] == W)&&(rubikscube[1].face[2][0] == W))||((rubikscube[5].face[0][2] == W)&&(rubikscube[1].face[0][0] == W))||((rubikscube[5].face[0][1] == W)&&(rubikscube[1].face[0][1] == W))||((rubikscube[5].face[0][0] == W)&&(rubikscube[1].face[0][2] == W))||((rubikscube[4].face[0][0] == W)&&(rubikscube[1].face[2][2] == W))||((rubikscube[4].face[0][1] == W)&&(rubikscube[1].face[1][2] == W))||((rubikscube[4].face[0][2] == W)&&(rubikscube[1].face[0][2] == W))||((rubikscube[2].face[0][0] == W)&&(rubikscube[1].face[2][0] == W))||((rubikscube[2].face[0][1] == W)&&(rubikscube[1].face[2][1] == W))||((rubikscube[2].face[0][2] == W)&&(rubikscube[1].face[2][2] == W))||((rubikscube[2].face[0][0] == W)&&(rubikscube[0].face[0][2] == W))||((rubikscube[2].face[1][0] == W)&&(rubikscube[0].face[1][2] == W))||((rubikscube[2].face[2][0] == W)&&(rubikscube[0].face[2][2] == W))||((rubikscube[2].face[2][0] == W)&&(rubikscube[3].face[0][0] == W))||((rubikscube[2].face[2][1] == W)&&(rubikscube[3].face[0][1] == W))||((rubikscube[2].face[2][2] == W)&&(rubikscube[3].face[0][2] == W))||((rubikscube[2].face[0][2] == W)&&(rubikscube[4].face[0][0] == W))||((rubikscube[2].face[1][2] == W)&&(rubikscube[4].face[1][0] == W))||((rubikscube[2].face[2][2] == W)&&(rubikscube[4].face[2][0] == W))||((rubikscube[3].face[0][0] == W)&&(rubikscube[0].face[2][2] == W))||((rubikscube[3].face[1][0] == W)&&(rubikscube[0].face[2][1] == W))||((rubikscube[3].face[2][0] == W)&&(rubikscube[0].face[2][0] == W))||((rubikscube[3].face[0][2] == W)&&(rubikscube[4].face[2][0] == W))||((rubikscube[3].face[1][2] == W)&&(rubikscube[4].face[1][0] == W))||((rubikscube[3].face[2][2] == W)&&(rubikscube[4].face[2][0] == W))||((rubikscube[3].face[2][0] == W)&&(rubikscube[5].face[2][2] == W))||((rubikscube[3].face[2][1] == W)&&(rubikscube[5].face[2][1] == W))||((rubikscube[3].face[2][2] == W)&&(rubikscube[5].face[2][0] == W))||((rubikscube[5].face[0][0] == W)&&(rubikscube[4].face[0][2] == W))||((rubikscube[5].face[1][0] == W)&&(rubikscube[4].face[1][2] == W))||((rubikscube[5].face[2][0] == W)&&(rubikscube[4].face[2][2] == W))||((rubikscube[5].face[0][2] == W)&&(rubikscube[0].face[0][0] == W))||((rubikscube[5].face[1][2] == W)&&(rubikscube[0].face[1][0] == W))||((rubikscube[5].face[2][2] == W)&&(rubikscube[0].face[2][0] == W))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptG = cptG+1;
                    break;
                case 'Y':
                    if (cptY >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = Y;
                    if (((rubikscube[0].face[0][0] == Y)&&(rubikscube[1].face[0][0] == Y))||((rubikscube[0].face[0][1] == Y)&&(rubikscube[1].face[1][0] == Y))||((rubikscube[0].face[0][2] == Y)&&(rubikscube[1].face[2][0] == Y))||((rubikscube[5].face[0][2] == Y)&&(rubikscube[1].face[0][0] == Y))||((rubikscube[5].face[0][1] == Y)&&(rubikscube[1].face[0][1] == Y))||((rubikscube[5].face[0][0] == Y)&&(rubikscube[1].face[0][2] == Y))||((rubikscube[4].face[0][0] == Y)&&(rubikscube[1].face[2][2] == Y))||((rubikscube[4].face[0][1] == Y)&&(rubikscube[1].face[1][2] == Y))||((rubikscube[4].face[0][2] == Y)&&(rubikscube[1].face[0][2] == Y))||((rubikscube[2].face[0][0] == Y)&&(rubikscube[1].face[2][0] == Y))||((rubikscube[2].face[0][1] == Y)&&(rubikscube[1].face[2][1] == Y))||((rubikscube[2].face[0][2] == Y)&&(rubikscube[1].face[2][2] == Y))||((rubikscube[2].face[0][0] == Y)&&(rubikscube[0].face[0][2] == Y))||((rubikscube[2].face[1][0] == Y)&&(rubikscube[0].face[1][2] == Y))||((rubikscube[2].face[2][0] == Y)&&(rubikscube[0].face[2][2] == Y))||((rubikscube[2].face[2][0] == Y)&&(rubikscube[3].face[0][0] == Y))||((rubikscube[2].face[2][1] == Y)&&(rubikscube[3].face[0][1] == Y))||((rubikscube[2].face[2][2] == Y)&&(rubikscube[3].face[0][2] == Y))||((rubikscube[2].face[0][2] == Y)&&(rubikscube[4].face[0][0] == Y))||((rubikscube[2].face[1][2] == Y)&&(rubikscube[4].face[1][0] == Y))||((rubikscube[2].face[2][2] == Y)&&(rubikscube[4].face[2][0] == Y))||((rubikscube[3].face[0][0] == Y)&&(rubikscube[0].face[2][2] == Y))||((rubikscube[3].face[1][0] == Y)&&(rubikscube[0].face[2][1] == Y))||((rubikscube[3].face[2][0] == Y)&&(rubikscube[0].face[2][0] == Y))||((rubikscube[3].face[0][2] == Y)&&(rubikscube[4].face[2][0] == Y))||((rubikscube[3].face[1][2] == Y)&&(rubikscube[4].face[1][0] == Y))||((rubikscube[3].face[2][2] == Y)&&(rubikscube[4].face[2][0] == Y))||((rubikscube[3].face[2][0] == Y)&&(rubikscube[5].face[2][2] == Y))||((rubikscube[3].face[2][1] == Y)&&(rubikscube[5].face[2][1] == Y))||((rubikscube[3].face[2][2] == Y)&&(rubikscube[5].face[2][0] == Y))||((rubikscube[5].face[0][0] == Y)&&(rubikscube[4].face[0][2] == Y))||((rubikscube[5].face[1][0] == Y)&&(rubikscube[4].face[1][2] == Y))||((rubikscube[5].face[2][0] == Y)&&(rubikscube[4].face[2][2] == Y))||((rubikscube[5].face[0][2] == Y)&&(rubikscube[0].face[0][0] == Y))||((rubikscube[5].face[1][2] == Y)&&(rubikscube[0].face[1][0] == Y))||((rubikscube[5].face[2][2] == Y)&&(rubikscube[0].face[2][0] == Y))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptY = cptY+1;
                    break;
                case 'O':
                    if (cptO >= 9){
                        printf("Vous ne pouvez pas placer plus de 9 fois cette couleur !\n");
                        break;
                    }
                    rubikscube[i].face[j][k] = O;
                    if (((rubikscube[0].face[0][0] == O)&&(rubikscube[1].face[0][0] == O))||((rubikscube[0].face[0][1] == O)&&(rubikscube[1].face[1][0] == O))||((rubikscube[0].face[0][2] == O)&&(rubikscube[1].face[2][0] == O))||((rubikscube[5].face[0][2] == O)&&(rubikscube[1].face[0][0] == O))||((rubikscube[5].face[0][1] == O)&&(rubikscube[1].face[0][1] == O))||((rubikscube[5].face[0][0] == O)&&(rubikscube[1].face[0][2] == O))||((rubikscube[4].face[0][0] == O)&&(rubikscube[1].face[2][2] == O))||((rubikscube[4].face[0][1] == O)&&(rubikscube[1].face[1][2] == O))||((rubikscube[4].face[0][2] == O)&&(rubikscube[1].face[0][2] == O))||((rubikscube[2].face[0][0] == O)&&(rubikscube[1].face[2][0] == O))||((rubikscube[2].face[0][1] == O)&&(rubikscube[1].face[2][1] == O))||((rubikscube[2].face[0][2] == O)&&(rubikscube[1].face[2][2] == O))||((rubikscube[2].face[0][0] == O)&&(rubikscube[0].face[0][2] == O))||((rubikscube[2].face[1][0] == O)&&(rubikscube[0].face[1][2] == O))||((rubikscube[2].face[2][0] == O)&&(rubikscube[0].face[2][2] == O))||((rubikscube[2].face[2][0] == O)&&(rubikscube[3].face[0][0] == O))||((rubikscube[2].face[2][1] == O)&&(rubikscube[3].face[0][1] == O))||((rubikscube[2].face[2][2] == O)&&(rubikscube[3].face[0][2] == O))||((rubikscube[2].face[0][2] == O)&&(rubikscube[4].face[0][0] == O))||((rubikscube[2].face[1][2] == O)&&(rubikscube[4].face[1][0] == O))||((rubikscube[2].face[2][2] == O)&&(rubikscube[4].face[2][0] == O))||((rubikscube[3].face[0][0] == O)&&(rubikscube[0].face[2][2] == O))||((rubikscube[3].face[1][0] == O)&&(rubikscube[0].face[2][1] == O))||((rubikscube[3].face[2][0] == O)&&(rubikscube[0].face[2][0] == O))||((rubikscube[3].face[0][2] == O)&&(rubikscube[4].face[2][0] == O))||((rubikscube[3].face[1][2] == O)&&(rubikscube[4].face[1][0] == O))||((rubikscube[3].face[2][2] == O)&&(rubikscube[4].face[2][0] == O))||((rubikscube[3].face[2][0] == O)&&(rubikscube[5].face[2][2] == O))||((rubikscube[3].face[2][1] == O)&&(rubikscube[5].face[2][1] == O))||((rubikscube[3].face[2][2] == O)&&(rubikscube[5].face[2][0] == O))||((rubikscube[5].face[0][0] == O)&&(rubikscube[4].face[0][2] == O))||((rubikscube[5].face[1][0] == O)&&(rubikscube[4].face[1][2] == O))||((rubikscube[5].face[2][0] == O)&&(rubikscube[4].face[2][2] == O))||((rubikscube[5].face[0][2] == O)&&(rubikscube[0].face[0][0] == O))||((rubikscube[5].face[1][2] == O)&&(rubikscube[0].face[1][0] == O))||((rubikscube[5].face[2][2] == O)&&(rubikscube[0].face[2][0] == O))) {
                        rubikscube[i].face[j][k] = LG;
                        printf("Deux cases adjacentes ne doivent pas avoir la meme couleur !\n");
                        break;
                    }
                    cptO = cptO+1;
                    break;
                    }
            display_rubiks(rubikscube);

        }


}

void scramble_rubiks(RUBIKS_SIDE* rubikscube){
        srand(time(NULL));
        int loop = rand();

    for (int i = 0; i < loop; ++i) {

        int move = rand();
        do {
            move = move/10;
        }while (move > 11);
        switch (move) {
            case 0:
                front_clockwise(rubikscube,1);
                break;
            case 1:
                front_anticlockwise(rubikscube,1);
                break;
            case 2:
                back_clockwise(rubikscube,1);
                break;
            case 3:
                back_anticlockwise(rubikscube,1);
                break;
            case 4:
                left_clockwise(rubikscube,1);
                break;
            case 5:
                left_anticlockwise(rubikscube,1);
                break;
            case 6:
                right_clockwise(rubikscube,1);
                break;
            case 7:
                right_anticlockwise(rubikscube,1);
                break;
            case 8:
                up_clockwise(rubikscube,1);
                break;
            case 9:
                up_anticlockwise(rubikscube,1);
                break;
            case 10:
                down_clockwise(rubikscube,1);
                break;
            case 11:
                down_anticlockwise(rubikscube,1);
                break;
        }
    }
}

void free_rubiks(RUBIKS_SIDE* rubikscube){
    free(rubikscube);
}

void front_clockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(LEFT)].face[i][2];
        rubikscube[side_to_index(LEFT)].face[i][2] = rubikscube[side_to_index(DOWN)].face[0][i];
        rubikscube[side_to_index(DOWN)].face[0][i]= rubikscube[side_to_index(RIGHT)].face[2-i][0];
        rubikscube[side_to_index(RIGHT)].face[2-i][0] = rubikscube[side_to_index(UP)].face[2][2-i];
        rubikscube[side_to_index(UP)].face[2][2-i] = tmp;
    }

    if (type == 2){
        type = 1;
        front_clockwise(rubikscube,type);
    }
}

void back_clockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(LEFT)].face[2-i][0];
        rubikscube[side_to_index(LEFT)].face[2-i][0] = rubikscube[side_to_index(UP)].face[0][i];
        rubikscube[side_to_index(UP)].face[0][i]= rubikscube[side_to_index(RIGHT)].face[i][2];
        rubikscube[side_to_index(RIGHT)].face[i][2] = rubikscube[side_to_index(DOWN)].face[2][2-i];
        rubikscube[side_to_index(DOWN)].face[2][2-i] = tmp;
    }
    if (type == 2){
        type = 1;
        back_clockwise(rubikscube,type);
    }

}

void right_clockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(FRONT)].face[i][2];
        rubikscube[side_to_index(FRONT)].face[i][2] = rubikscube[side_to_index(DOWN)].face[i][2];
        rubikscube[side_to_index(DOWN)].face[i][2]= rubikscube[side_to_index(BACK)].face[2-i][0];
        rubikscube[side_to_index(BACK)].face[2-i][0] = rubikscube[side_to_index(UP)].face[i][2];
        rubikscube[side_to_index(UP)].face[i][2] = tmp;
    }
    if (type == 2){
        type = 1;
        right_clockwise(rubikscube,type);
    }
}

void left_clockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[i][2];
        rubikscube[side_to_index(BACK)].face[i][2] = rubikscube[side_to_index(DOWN)].face[2-i][0];
        rubikscube[side_to_index(DOWN)].face[2-i][0]= rubikscube[side_to_index(FRONT)].face[2-i][0];
        rubikscube[side_to_index(FRONT)].face[2-i][0] = rubikscube[side_to_index(UP)].face[2-i][0];
        rubikscube[side_to_index(UP)].face[2-i][0] = tmp;
    }
    if (type == 2){
        type = 1;
        left_clockwise(rubikscube,type);
    }
}

void up_clockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[0][i];
        rubikscube[side_to_index(BACK)].face[0][i] = rubikscube[side_to_index(DOWN)].face[0][i];
        rubikscube[side_to_index(DOWN)].face[0][i]= rubikscube[side_to_index(FRONT)].face[0][i];
        rubikscube[side_to_index(FRONT)].face[0][i] = rubikscube[side_to_index(UP)].face[0][i];
        rubikscube[side_to_index(UP)].face[0][i] = tmp;
    }
    if (type == 2){
        type = 1;
        up_clockwise(rubikscube,type);
    }
}

void down_clockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[2][2-i];
        rubikscube[side_to_index(BACK)].face[2][2-i] = rubikscube[side_to_index(DOWN)].face[2][2-i];
        rubikscube[side_to_index(DOWN)].face[2][2-i]= rubikscube[side_to_index(FRONT)].face[2][2-i];
        rubikscube[side_to_index(FRONT)].face[2][2-i] = rubikscube[side_to_index(UP)].face[2][2-i];
        rubikscube[side_to_index(UP)].face[2][2-i] = tmp;
    }
    if (type == 2){
        type = 1;
        down_clockwise(rubikscube,type);
    }
}


void front_anticlockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(LEFT)].face[2-i][2];
        rubikscube[side_to_index(LEFT)].face[2-i][2] = rubikscube[side_to_index(DOWN)].face[0][2-i];
        rubikscube[side_to_index(DOWN)].face[0][2-i]= rubikscube[side_to_index(RIGHT)].face[i][0];
        rubikscube[side_to_index(RIGHT)].face[i][0] = rubikscube[side_to_index(UP)].face[2][i];
        rubikscube[side_to_index(UP)].face[2][i] = tmp;
    }

    if (type == 2){
        type = 1;
        front_anticlockwise(rubikscube,type);
    }
}

void back_anticlockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(LEFT)].face[i][0];
        rubikscube[side_to_index(LEFT)].face[i][0] = rubikscube[side_to_index(UP)].face[0][2-i];
        rubikscube[side_to_index(UP)].face[0][2-i]= rubikscube[side_to_index(RIGHT)].face[2-i][2];
        rubikscube[side_to_index(RIGHT)].face[2-i][2] = rubikscube[side_to_index(DOWN)].face[2][i];
        rubikscube[side_to_index(DOWN)].face[2][i] = tmp;
    }
    if (type == 2){
        type = 1;
        back_anticlockwise(rubikscube,type);
    }

}

void left_anticlockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[2-i][2];
        rubikscube[side_to_index(BACK)].face[2-i][2] = rubikscube[side_to_index(DOWN)].face[i][0];
        rubikscube[side_to_index(DOWN)].face[i][0]= rubikscube[side_to_index(FRONT)].face[i][0];
        rubikscube[side_to_index(FRONT)].face[i][0] = rubikscube[side_to_index(UP)].face[i][0];
        rubikscube[side_to_index(UP)].face[i][0] = tmp;
    }
    if (type == 2){
        type = 1;
        left_anticlockwise(rubikscube,type);
    }
}

void right_anticlockwise(RUBIKS_SIDE* rubikscube,int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(FRONT)].face[2-i][2];
        rubikscube[side_to_index(FRONT)].face[2-i][2] = rubikscube[side_to_index(DOWN)].face[2-i][2];
        rubikscube[side_to_index(DOWN)].face[2-i][2]= rubikscube[side_to_index(BACK)].face[i][0];
        rubikscube[side_to_index(BACK)].face[i][0] = rubikscube[side_to_index(UP)].face[2-i][2];
        rubikscube[side_to_index(UP)].face[2-i][2] = tmp;
    }
    if (type == 2){
        type = 1;
        right_anticlockwise(rubikscube,type);
    }
}

void up_anticlockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[0][2-i];
        rubikscube[side_to_index(BACK)].face[0][2-i] = rubikscube[side_to_index(DOWN)].face[0][2-i];
        rubikscube[side_to_index(DOWN)].face[0][2-i]= rubikscube[side_to_index(FRONT)].face[0][2-i];
        rubikscube[side_to_index(FRONT)].face[0][2-i] = rubikscube[side_to_index(UP)].face[0][2-i];
        rubikscube[side_to_index(UP)].face[0][2-i] = tmp;
    }
    if (type == 2){
        type = 1;
        up_anticlockwise(rubikscube,type);
    }
}

void down_anticlockwise(RUBIKS_SIDE* rubikscube, int type){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        tmp = rubikscube[side_to_index(BACK)].face[2][i];
        rubikscube[side_to_index(BACK)].face[2][i] = rubikscube[side_to_index(DOWN)].face[2][i];
        rubikscube[side_to_index(DOWN)].face[2][i]= rubikscube[side_to_index(FRONT)].face[2][i];
        rubikscube[side_to_index(FRONT)].face[2][i] = rubikscube[side_to_index(UP)].face[2][i];
        rubikscube[side_to_index(UP)].face[2][i] = tmp;
    }
    if (type == 2){
        type = 1;
        down_anticlockwise(rubikscube,type);
    }
}

void vertical_rotation(RUBIKS_SIDE* rubikscube){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tmp = rubikscube[side_to_index(FRONT)].face[i][j];
            rubikscube[side_to_index(FRONT)].face[i][j] = rubikscube[side_to_index(BACK)].face[i][j];
            rubikscube[side_to_index(BACK)].face[i][j] = tmp;
            tmp = rubikscube[side_to_index(UP)].face[i][j];
            rubikscube[side_to_index(UP)].face[i][j] = rubikscube[side_to_index(DOWN)].face[i][j];
            rubikscube[side_to_index(DOWN)].face[i][j] = tmp;
        }
    }
}

void horizontal_rotation(RUBIKS_SIDE* rubikscube){
    T_COLOR tmp;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tmp = rubikscube[side_to_index(FRONT)].face[i][j];
            rubikscube[side_to_index(FRONT)].face[i][j] = rubikscube[side_to_index(BACK)].face[i][j];
            rubikscube[side_to_index(BACK)].face[i][j] = tmp;
            tmp = rubikscube[side_to_index(LEFT)].face[i][j];
            rubikscube[side_to_index(LEFT)].face[i][j] = rubikscube[side_to_index(RIGHT)].face[i][j];
            rubikscube[side_to_index(RIGHT)].face[i][j] = tmp;
        }
    }
}

void move_rubiks(RUBIKS_SIDE* rubikscube){
    for (int i = 0; i < 80; ++i) {
        printf("-");
    }
    printf("\n");
    printf("1: Choisir une face     2: rotation horizontal     3: rotation vertical\n");
    for (int i = 0; i < 80; ++i) {
        printf("-");
    }
    int choix;
    printf("\nAction: ");
    scanf("%d",&choix);
    printf("\n");
    switch (choix) {
        case 1:
            for (int i = 0; i < 80; ++i) {
                printf("-");
            }
            printf("\n");
            printf("1: Left    2: Front     3: Up    4: Down    5: Right     6: Back\n");
            for (int i = 0; i < 80; ++i) {
                printf("-");
            }
            printf("\nAction: ");
            scanf("%d",&choix);
            printf("\n");
            switch (choix) {
                case 1:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            left_clockwise(rubikscube,1);
                            break;
                        case 2:
                            left_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            left_clockwise(rubikscube,2);
                            break;
                        case 4:
                            left_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;
                case 2:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            front_clockwise(rubikscube,1);
                            break;
                        case 2:
                            front_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            front_clockwise(rubikscube,2);
                            break;
                        case 4:
                            front_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;

                case 3:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            up_clockwise(rubikscube,1);
                            break;
                        case 2:
                            up_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            up_clockwise(rubikscube,2);
                            break;
                        case 4:
                            up_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;


                case 4:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            down_clockwise(rubikscube,1);
                            break;
                        case 2:
                            down_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            down_clockwise(rubikscube,2);
                            break;
                        case 4:
                            down_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;

                case 5:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            right_clockwise(rubikscube,1);
                            break;
                        case 2:
                            right_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            right_clockwise(rubikscube,2);
                            break;
                        case 4:
                            right_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;
                case 6:
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\n");
                    printf("1: quart clockwise    2: quart anticlockwise    3: demi clockwise    4: demi anticlockwise\n");
                    for (int i = 0; i < 80; ++i) {
                        printf("-");
                    }
                    printf("\nAction: ");
                    scanf("%d",&choix);
                    printf("\n");
                    switch (choix) {
                        case 1:
                            back_clockwise(rubikscube,1);
                            break;
                        case 2:
                            back_anticlockwise(rubikscube,1);
                            break;
                        case 3:
                            back_clockwise(rubikscube,2);
                            break;
                        case 4:
                            back_anticlockwise(rubikscube,2);
                            break;
                    }
                    break;
            }
            break;
        case 2:
            horizontal_rotation(rubikscube);
            break;
        case 3:
            vertical_rotation(rubikscube);
            break;

    }

}