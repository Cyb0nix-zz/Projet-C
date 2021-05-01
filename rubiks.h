#ifndef PROJET_C_RUBIKS_H
#define PROJET_C_RUBIKS_H

typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;
typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;
typedef struct {
    T_SIDE Type_face;
    char Face[3][3];
    } rubiks_side;

typedef rubiks_side rubiks[6];

int select_color(T_COLOR color);
int side_to_index(T_SIDE side);

rubiks* create_rubiks();
void init_rubiks(rubiks);
void display_rubiks(rubiks);
void blank_rubiks(rubiks);
void fill_rubiks(rubiks);
void scramble_rubiks(rubiks);
void free_rubiks(rubiks);


#endif //PROJET_C_RUBIKS_H
