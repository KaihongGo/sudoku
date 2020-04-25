#include <iostream>
#include <string>
#include "scene.h"
#include "input.h"

#define _TEST_ 0

void test0()
{
    CScene scene;
    time_t begin, end;
    time(&begin);
    scene.generate();
    time(&end);
    scene.show();
    std::cout << end - begin << std::endl;
}

int main()
{
    //main()作为工程入口

#if _TEST_
    test0();
#else
    CScene scene;

    int erase_grid_number = inputDifficulty();

    scene.generate();

    scene.eraseRandomGrids(erase_grid_number);
    scene.play();
#endif
    return 0;
}