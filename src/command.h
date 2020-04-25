#ifndef _SUDOKU_COMMAND_H_
#define _SUDOKU_COMMAND_H_

#include <memory>
#include "common.h"

class CScene;
class CCommand
{
public:
    CCommand(CScene *pOwner);
    CCommand(const CCommand &);
    ~CCommand();

    bool excute(int nInputValue);
    void undo();

private:
    CScene *_pOwner;    //当前场景
    point_t _stPoint;   
    int _nPreValue;     //前一个点
    int _nCurValue;     //当前点
};

#endif