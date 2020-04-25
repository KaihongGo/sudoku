#include "scene.h"
#include "command.h"

CCommand::CCommand(CScene *pOwner) : _pOwner(pOwner)
{
}

CCommand::CCommand(const CCommand &rhs)
    : _pOwner(rhs._pOwner), _stPoint(rhs._stPoint), _nPreValue(rhs._nPreValue), _nCurValue(rhs._nCurValue)
{
    //拷贝构造函数
}

CCommand::~CCommand() {}

bool CCommand::excute(int nInputValue)
{
    if (!_pOwner) //如果_pOwner为空指针;cscene创建失败
        return false;
    //_pOwner场景类
    _stPoint = _pOwner->getCurPoint();
    return _pOwner->setCurValue(nInputValue, _nPreValue);
    //_nPreValue前一个值
}

void CCommand::undo()
{
    if (_pOwner)
    {
        _pOwner->setPointValue(_stPoint, _nPreValue);
        //场景->设置点坐标；传入点坐标，需要设置的值；_npreValue存储先前的值
    }
    return;
}