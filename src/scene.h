#ifndef _SUDOKU_SCENE_H_
#define _SUDOKU_SCENE_H_

#include <iostream>
#include <vector>
#include "command.h"
#include "block.h"
#include "common.h"

//速度场景类

class CScene
{
public:
    CScene(int index = 3);
    virtual ~CScene(); //虚析构函数

    void generate();
    void show() const;

    bool setCurValue(const int nCurValue, int &nLastValue);
    bool setPointValue(const point_t &, const int);
    point_t getCurPoint();

    void eraseRandomGrids(const int count);
    bool isComplete();

    void play();

private:
    void init();              //将每个格子的指针放到block里面
    void setValue(const int); //函数重载
    void setValue(const point_t &, const int);
    void printUnderline(int line_no = -1) const;

private:
    int _index;
    int _max_column;
    point_t _cur_point; //当前光标的位置
    CBlock _column_block[9];
    CBlock _row_block[9];
    CBlock _xy_block[3][3];
    point_value_t _map[81]; //以为存储整张图

    std::vector<CCommand> _vCommand;
};

#endif