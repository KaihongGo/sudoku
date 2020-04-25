
# sudoku

C++ 实现的跨平台数独游戏，命令行操作易上手，可以在开发间隙用来放松身心。数百行代码，初学者也可以轻松掌握。
欢迎通过pull request的方式来添加功能或修复缺陷。

## 特性

1. 跨平台 : Linux/Windows

## 依赖

1. cmake 3.12及以上

## 构建

1. Windows 下一键编译: `build.bat`
2. Linux 下一键构建: `sh build.sh`

## 运行

1. 运行构建步骤生成的 `bin/sudoku` 文件

## 后续计划

1. 保存进度功能

## 操作说明

- w 光标上移↑
- a 光标左移←
- s 光标下移↓
- d 光标右移→
- 0 删除已填入数字
- u 撤销上一步操作
- enter 尝试通关
- esc 退出游戏

## 游戏规则

每一行、每一列、**每一个粗线宫（3*3）**内的数字均含1-9，不重复

### 项目结构

```bash
│  .gitignore  
│  build.bat        // Windows 一键编译脚本  
│  build.sh         // Linux 一键编译脚本  
│  CMakeLists.txt   // CMake 项目文件  
│  README.md  
│
└─src               //源代码目录  
                block.cpp   //数独格子组合类，可代表行、列、九宫格  
                block.h  
                color.h     //颜色类  
                command.cpp //命令类，实现了撤销功能  
                command.h  
                common.h    //公共头文件  
                input.cpp   //输入类  
                input.h  
                main.cpp    //入口文件  
                scene.cpp   //游戏场景类  
                scene.h  
                test.cpp    //测试文件  
                test.h  
                utility.inl //一些实用的全局函数  
```

common.h
block.h
command.h
scene.h

color.h

[ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code#graphics)

[How do I output coloured text to a Linux terminal?](https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal)

BUG:

1. `#ifndef`预处理错写成`#ifdef`
