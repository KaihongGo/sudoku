#ifndef _SUDOKU_BLOCK_H_
#define _SUDOKU_BLOCK_H_

//CBlock类是 块 的意思；存储块信息
class CBlock
{
    static const int MAX_COUNT = 9; //是否可初始化

public:
    CBlock() : _count(0) {}
    bool isValid() const;                 //该block类是否有效
    bool isFull() const;                  //该block类是否满
    void print() const;                   //打印该block
    void push_back(point_value_t *point); //push进去

private:
    int _count;                         //该类有几个点
    point_value_t *_numbers[MAX_COUNT]; //存储点-->与scene连接
};

#endif