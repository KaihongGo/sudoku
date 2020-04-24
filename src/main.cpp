#include <iostream>
#include <string>
#include "scene.h"
#include "input.h"
#include "test.h"

#define _TEST_ 1

int main()
{
#if _TEST_ //调起测试程序
    test_case1();
    getchar();
#else
    CScene scene;

    int erase_grid_number = inputDifficulty();

    scene.generate();

    scene.eraseRandomGrids(erase_grid_number);
    scene.play();

#endif

    return 0;
}