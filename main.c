#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro_stuff.h"

int main(int argc, char **argv){

    allegro_stuff a;

    Init(&a);

    while(a.closed == false){
        Update(&a);
    }

    return 0;
}
