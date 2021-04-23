//
// Created by Cedric on 23/04/2021.
//

#ifndef PROJET_C_RUBIKS_H
#define PROJET_C_RUBIKS_H

typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;
typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;
typedef struct {}rubiks;

int select_color(T_COLOR color);
int side_to_index(T_SIDE side);

int create_rubiks();
void init_rubiks(rubiks);
void display_rubiks(rubiks);
void blank_rubiks();


#endif //PROJET_C_RUBIKS_H
