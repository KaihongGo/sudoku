#include <cmath>
#include <iostream>
#include <memory.h>
#include <map>
#include <vector>
#include "common.h"
#include "scene.h"
#include "utility.inl"

//构造函数
//_index无用
CScene::CScene()
    : _cur_point({0, 0})
{
    //用UNSELECTED空状态填充数组
    memset(_map, UNSELECTED, sizeof(_map));
    //column_block 所有列；按单一列存储
    for (int column = 0; column < 9; ++column)
    {
        //一次循环解决一个
        CBlock column_block;
        for (int row = 0; row < 9; ++row)
        {
            //column_block.push_back(&_map[row * 9 + column]);
            column_block.push_back(_map + row * 9 + column);
        }
        _column_block[column] = column_block;
    }

    //row_block 所有行
    for (int row = 0; row < 9; ++row)
    {
        CBlock row_block;
        for (int column = 0; column < 9; ++column)
        {
            row_block.push_back(_map + row * 9 + column);
        }
        _row_block[row] = row_block;
    }

    //xy_block 所有九宫格,[行][列]
    for (int block_index = 0; block_index < 9; ++block_index)
    {
        CBlock xy_block;
        //3*3 九宫格的下标
        int row_index = block_index / 3;
        int col_index = block_index % 3;
        int xy_begin = row_index * 27 + col_index * 3;
        //断定9空格对应开始的一维下标
        //  index       r  c  row_i   col_i
        //    0 -- 0    0  0    0       0
        //    1 -- 3    0  3    0       1
        //    2 -- 6    0  6    0       2
        //    3 -- 27   3  0    1       0
        //    4 -- 30   3  3    1       1
        //    5 -- 33   3  6    1       2
        //    6 -- 54   6  0    2       0
        //    7 -- 57   6  3    2       1
        //    8 -- 60   6  6    2       2
        //得到数列通项公式
        for (int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                xy_block.push_back(_map + xy_begin + 9 * i + j);
            }
        }
        _xy_block[row_index][col_index] = xy_block;
    }
    return;
}

CScene::~CScene()
{
}

//打印下方横线
void CScene::printUnderline(int line_no) const
{
    std::string underline;
    for (int column = 0; column < 9; ++column)
    {
        //_cur_point代表光标位置
        if (_cur_point.y == line_no && _cur_point.x == column)
            underline += "--^-";
        else
            underline += "----";
    }
    underline += "-";
    std::cout << underline << std::endl;
}

//打印出棋盘
void CScene::show() const
{
    cls(); //清屏幕
    printUnderline();
    for (int row = 0; row < 9; ++row)
    {
        auto block = _row_block[row]; //按行打印
        block.print();
        printUnderline(row); //打印行线
    }
}

//设置当前结点为nCurValue；引用返回存储前一个值
bool CScene::setCurValue(const int nCurValue, int &nLastValue)
{
    auto point = _map[_cur_point.x + _cur_point.y * 9];
    if (ERASED == point.state)
    {                             //该状态为ERASED删除状态
        nLastValue = point.value; //撤销用；引用传参数
        setValue(nCurValue);
        return true;
    }
    else
        return false;
}

//一个场景可以多次被初始化；产生完整数独图
void CScene::generate()
{
    //9行9列
    //a:1 --> i:9
    static char map_pattern[10][10] = {
        "ighcabfde", //共9个字母
        "cabfdeigh",
        "fdeighcab",
        "ghiabcdef",
        "abcdefghi",
        "defghiabc",
        "higbcaefd",
        "bcaefdhig",
        "efdhigbca"};
    //字母与数字下标正常映射
    std::vector<char> v;
    for (int i = 0; i < 9; ++i)
    {
        v.push_back('a' + i);
    }
    //产生字母到数字下标的随即映射
    std::map<char, int> hash_map;
    for (int i = 1; i <= 9; ++i)
    {
        //此算法经常使用
        //从容器中随机取出一个字母，与下标对应
        int r = random(0, v.size() - 1); //随机下标
        char key = v[r];
        v.erase(v.begin() + r); //v.size() 每次均改变
        //解决两次随机数字相同，元v不变该算法不合理的情况
        hash_map[key] = i; //随机字母对应数字
    }
    //填入场景
    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            point_t point = {row, column};
            char key = map_pattern[row][column]; //获得模式字母
            setValue(point, hash_map[key]);      //利用map已完成字母与数字随机映射
        }
    }
    assert(isComplete());

    return;
}
void CScene::setValue(const point_t &p, const int value)
{
    //再映射过程
    //_map代表grid结构一维
    _map[p.x + p.y * 9].value = value;
}

void CScene::setValue(const int value)
{
    auto p = _cur_point; //当前point
    this->setValue(p, value);
}

bool CScene::isComplete()
{
    //任何一个block未被填满，则肯定未完成
    for (size_t i = 0; i < 81; ++i)
    {
        //UNSELECTED为0；表示状态；_map空默认为0
        if (UNSELECTED == _map[i].value)
            return false;
    }
    //同时block里的数字还要符合规则
    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            if (!_row_block[row].isValid() || !_column_block[column].isValid() || !_xy_block[row / 3][column / 3].isValid())
                return false;
        } //_xy_block是什么???
    }
    return true;
}

//选择count个格子清空
//策略：先构建完成数独，再进行清空
void CScene::eraseRandomGrids(const int count)
{
    point_value_t p = {UNSELECTED, ERASED};
    //p表示空白（未填写），ERASED状态的点
    std::vector<int> v;
    for (int i = 0; i < 81; ++i)
    {
        v.push_back(i);
    }

    //开始删除
    for (int i = 0; i < count; ++i)
    {
        //相同策略，容器改变，从容器中取出元素
        int r = random(0, v.size() - 1);
        _map[v[r]] = p;
        v.erase(v.begin() + r);
    }
}

void CScene::play()
{
    show();
    char key = '\0';
    while (true)
    {
        key = getch(); //前方自定义函数，获取字符
        if ('0' <= key && '9' >= key)
        {
            CCommand oCommand(this);
            //CCommand类；用CScene构造
            if (!oCommand.excute(key - '0'))
            {
                //返回值为bool类型，当前位置不可以修改
                std::cout << "this number can't be modified!" << std::endl;
            }
            else
            {
                //已修改
                //_vCommand:vector<>类型用作栈，实现连续撤销
                _vCommand.push_back(std::move(oCommand)); //C++11右值引用
                show();
                continue;
            }
        }
        switch (key)
        {
        case 0x1B: //ESC
        {
            std::cout << "quit game ? [Y/N]" << std::endl;
            std::string strInput;
            std::cin >> strInput;
            if (strInput[0] == 'y' || strInput[0] == 'Y')
                exit(0); //此处退出程序
            else
            {
                std::cout << "continue." << std::endl;
                break;
            }
        }
        case 0x75: //u 撤销
        {
            if (_vCommand.empty())
            {
                std::cout << "no more action to undo." << std::endl;
            }
            else
            {
                CCommand &oCommand = _vCommand.back();
                oCommand.undo();
                _vCommand.pop_back();
                show();
            }
            break;
        }
        case 0x61: //a
            _cur_point.x = (_cur_point.x - 1) < 0 ? 0 : _cur_point.x - 1;
            show();
            break;
        case 0x64: //d
            _cur_point.x = (_cur_point.x + 1) > 8 ? 8 : _cur_point.x + 1;
            show();
            break;
        case 0x73: //s
            _cur_point.y = (_cur_point.y + 1) > 8 ? 8 : _cur_point.y + 1;
            show();
            break;
        case 0x77: //w
            _cur_point.y = (_cur_point.y - 1) < 0 ? 0 : _cur_point.y - 1;
            show();
            break;

        case 0x0D: //enter
            if (isComplete())
            {
                std::cout << "Congratualtion! YOU WIN!" << std::endl;
                getchar();
                exit(0);
            }
            else
            {
                std::cout << "sorry, not completed."
                          << std::endl;
            }
            break;

        default:
            break;
        }
    }
}

bool CScene::setPointValue(const point_t &stPoint, const int nValue)
{
    auto point = _map[stPoint.x + stPoint.y * 9];
    if (ERASED == point.state)
    {
        _cur_point = stPoint;
        setValue(nValue);
        return true;
    }
    else
        return false;
}

point_t CScene::getCurPoint()
{
    return _cur_point;
}