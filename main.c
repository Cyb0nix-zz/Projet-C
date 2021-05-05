#include "rubiks.h"

int main(){
    rubiks* rubikscube = create_rubiks();
    init_rubiks(rubikscube);
    display_rubiks(rubikscube);
    return 0;
}