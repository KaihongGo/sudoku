#include <iostream>
#include <sstream>
#include <string>
#include "common.h"
#include "utility.inl"

//return erase grid number
int inputDifficulty()
{
    cls();  //清除屏幕

    std::string cmd;
    while (1)
    {
        std::cout << "设置难度：1简单 2普通 3困难" << std::endl;
        std::cin >> cmd;
        int difficulty = stoi(cmd);
        //int difficulty = atoi(cmd.c_str());
        //此处可能有BUG；输入健壮？
        switch (difficulty)
        {
        case EASY:  //用枚举量意义明显
            return 20;
        case NORMAL:
            return 35;
        case HARD:
            return 50;
        default:
            std::cout << "输入错误！" << std::endl;
            continue;
        }
    }
    return 0;
}