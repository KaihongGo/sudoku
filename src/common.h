#ifndef _SUDOKU_COMMON_H_
#define _SUDOKU_COMMON_H_

static const unsigned int UNSELECTED = 0; //不理解

enum difficulty_e
{
    EASY = 1,
    NORMAL,
    HARD
};

enum state_e
{
    INITED = 0,
    ERASED
};

typedef struct stPoint
{
    int x;
    int y;
} point_t;

typedef struct stPointValue
{
    int value;
    int state;
} point_value_t;

class CpointSort
{
public:
    bool operator()(const point_t &lhs, const point_t &rhs) const
    {
        //函数对象？？如何调用
        if((lhs.x == rhs.x) && (lhs.y == rhs.y))
            return false;
        else
            return true;
    }
};

#endif