#include <cassert>
#include <iostream>
#include "common.h"
#include "block.h"
#include "color.h"

//block类存储9宫格--》

bool CBlock::isValid() const
{
    assert(MAX_COUNT == _count);
    //assert aborts the program if the user-specified condition is not true. (function macro)
    for (int i = 0; i < _count - 1; ++i)
    {
        //不理解
        //1 2 3 4 5 6 7 8 9
        //1                  --> i
        //  2 3 4 5 6 7 8 9  --> j
        for (int j = i + 1; j < _count; ++j)
        {
            if (UNSELECTED == _numbers[i]->value || UNSELECTED == _numbers[j]->value)
                continue;
            if (_numbers[i]->value == _numbers[j]->value)
                return false;   // BUGs;
        }
    }
    return true;
}

//该block是否填满
bool CBlock::isFull() const
{
    for (int i = 0; i < _count; ++i)
    {
        point_value_t *p_point_value = _numbers[i];
        if (nullptr == p_point_value || UNSELECTED == p_point_value->value)
            return false;
    }
    return true;
}

//单行打印输出block
void CBlock::print() const
{
    std::cout << "| ";
    for (int i = 0; i < _count; ++i)
    {
        auto number = *(_numbers[i]); //point_value_tll类型；包含值与状态
        if (0 == number.value)
            //数字为0; 删除已经填入的数字，输出为空
            std::cout << " "
                      << " | ";
        else
        {
            //当前数state
            if (ERASED == number.state)
                std::cout << Color::Modifier(Color::FG_GREEN) << number.value << Color::Modifier(Color::RESET) << " | ";
            else
                std::cout << number.value << " | ";
        }
    }
    std::cout << std::endl; //换行
}

//point_value_t 传入 _numbers存储预处理；再进行输出
void CBlock::push_back(point_value_t *point)
{
    assert(nullptr != point);
    _numbers[_count++] = point;
}

// _numbers[]存储单行数字
// _count下标计数索引