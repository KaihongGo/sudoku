#ifndef _SUDOKU_COMMAND_H_
#define _SUDOKU_COMMAND_H_

#include <memory>
#include "common.h"

//命令类
//执行特定命令

class CScene;
class CCommand
{
public:
    CCommand(CScene *pOwner) : _pOwner(pOwner) {}
    //CCommand(const CCommand &rhs) : _pOwner(rhs._pOwner), _stPoint(rhs._stPoint), _nPreValue(rhs._nPreValue), _nCurValue(rhs._nCurValue) {}
    //使用默认构造函数；不需要深拷贝
    ~CCommand();

    bool excute(int nInputValue);
    void undo();

private:
    CScene *_pOwner; //当前场景
    point_t _stPoint;
    int _nPreValue; //前一个点
    int _nCurValue; //当前点
};

#endif