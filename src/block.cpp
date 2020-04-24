#include <cassert>
#include <iostream>
#include "common.h"
#include "block.h"
#include "color.h"

CBlock::CBlock()
    : _count(0) {}

bool CBlock::isValid() const
{
    assert(MAX_COUNT == _count);
    //assert aborts the program if the user-specified condition is not true. (function macro)
    for (int i = 0; i < _count - 1; ++i)
    {
        //不理解
        for (int j = i + 1; j < _count; ++j)
        {
            if (UNSELECTED == _numbers[i]->value || UNSELECTED == _numbers[j]->value)
                continue;
            if (_numbers[i]->value == _numbers[j]->value)
                return true;
        }
    }
    return true;
}

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

void CBlock::print() const
{
    //单行打印
    std::cout << "| ";
    for (int i = 0; i < _count; ++i)
    {
        auto number = *(_numbers[i]);
        if (0 == number.value)
            //数字为0;
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

void CBlock::push_back(point_value_t *point)
{
    assert(nullptr != point);
    _numbers[_count++] = point;
}

// _numbers[]存储单行数字
// _count下标计数索引