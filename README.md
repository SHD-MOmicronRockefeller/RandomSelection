# RandomSelection（随机选择器）
> 一个可以自定义的选择器，或许不是最好的:(
>
> 一个开发者努力做到最好的选择器，也许永远不会被人看到:)

[TOC]

- [RandomSelection（随机选择器）](#randomselection随机选择器)
  - [项目介绍](#项目介绍)
    - [技术栈](#技术栈)
  - [核心功能](#核心功能)
  - [环境依赖](#环境依赖)
    - [编译环境（必装）](#编译环境必装)
    - [运行环境（用户侧）](#运行环境用户侧)
  - [编译 \& 运行](#编译--运行)
    - [步骤 1：克隆代码](#步骤-1克隆代码)
    - [步骤 2：配置 QMake 工程](#步骤-2配置-qmake-工程)
    - [步骤 3：编译项目](#步骤-3编译项目)
    - [步骤 4：运行程序](#步骤-4运行程序)
  - [使用指南](#使用指南)
    - [基础使用流程](#基础使用流程)
    - [高级功能](#高级功能)
    - [开发规范](#开发规范)
  - [许可证](#许可证)
  - [待办事项（开发中）](#待办事项开发中)
  - [致谢](#致谢)
  - [无脑本地部署](#无脑本地部署)
  - [项目结构（参考）](#项目结构参考)


## 项目介绍
RandomSelection 是一款基于 Qt 框架开发的跨平台随机选择工具，旨在提供灵活、可定制的随机选择能力。你可以通过它实现带权重的随机抽取、分组选择、平衡抽取（避免重复高频选中）等场景，满足日常决策、随机分配、抽奖等多种使用需求。

### 技术栈
- 编译环境：MinGW 13.1.0
- 开发语言：C++20
- UI 框架：Qt 6.10.2
- 构建工具：QMake 3.1

## 核心功能
✅ **自定义选择列表**：自由添加、删除、编辑待选择项，支持导入/导出列表  
✅ **权重配置**：为不同选项设置自定义权重，权重越高被选中概率越大  
✅ **平衡抽取**：可选开启「平衡模式」，降低高频选中项的重复选中概率，保证抽取公平性  
✅ **分组选择**：支持将选项分组管理，可针对指定分组执行随机选择  
✅ **跨平台兼容**：基于 Qt 6 开发，理论支持 Windows/macOS/Linux 系统（当前优先适配 Windows）  

## 环境依赖
### 编译环境（必装）
1. MinGW 13.1.0（或兼容的 MinGW-w64 版本）
2. Qt 6.10.2（需包含 Qt Core/Qt Widgets 模块）
3. QMake 3.1（Qt 自带，无需单独安装）
4. CMake（可选，若需替换构建工具）

### 运行环境（用户侧）
- Windows：需安装 Qt 6.10.2 对应的运行时库（`Qt6Core.dll`、`Qt6Widgets.dll`、`libgcc_s_seh-1.dll` 等），或打包为独立可执行文件。
- Windows：或者等待开发者打包release版本，无需额外安装运行环境。
- macOS/Linux：需安装 Qt 6 运行时依赖（如 `libQt6Core.so.6`、`libQt6Widgets.so.6`）。

## 编译 & 运行
### 步骤 1：克隆代码
```bash
git clone https://github.com/SHD-MOmicronRockefeller/RandomSelection.git
cd RandomSelection
```

### 步骤 2：配置 QMake 工程
1. 打开 Qt Creator，导入项目根目录的 `RandomSelection.pro` 文件
2. 在 Qt Creator 中选择「构建套件」：确认编译器为 MinGW 13.1.0，Qt 版本为 6.10.2

### 步骤 3：编译项目
- 方式 1（Qt Creator）：点击「构建」按钮（锤子图标），等待编译完成
- 方式 2（命令行）：
  ```bash
  # 生成 Makefile
  qmake .pro -spec win32-g++ CONFIG+=release
  # 编译
  mingw32-make -j4
  ```

### 步骤 4：运行程序
- Qt Creator 中点击「运行」按钮（绿色三角图标）
- 或直接运行编译产物目录（如 `release/RandomSelection.exe`）

## 使用指南
### 基础使用流程
1. ...

### 高级功能
- ...


### 开发规范
- 代码遵循 C++20 标准，尽量使用 Qt 原生接口，减少第三方依赖
- 新增功能需附带简单测试用例，保证核心逻辑稳定
- 界面风格保持统一，遵循 Qt 设计规范

## 许可证
本项目暂采用 MIT 许可证。

## 待办事项（开发中）
- [ ] 完善「平衡抽取」算法的边界条件处理
- [ ] 支持列表批量导入/导出（Excel/CSV 格式）
- [ ] 增加历史选择记录的可视化统计
- [ ] 打包为免安装的独立可执行文件
- [ ] 适配 macOS/Linux 系统

## 致谢
感谢 Qt 框架提供的跨平台能力，以及开源社区的各类参考资料。  
如果你有任何问题、建议或 Bug 反馈，欢迎提交 Issue 或联系开发者。

## 无脑本地部署
1. Qt社区版下载链接：[https://d13lb3tujbc8s0.cloudfront.net/onlineinstallers/qt-online-installer-windows-x64-4.10.0.exe](https://d13lb3tujbc8s0.cloudfront.net/onlineinstallers/qt-online-installer-windows-x64-4.10.0.exe)
2. 登陆后，选择安装路径，点击下一步，选择安装组件，勾选 Qt 6.10.2 MinGW 13.1.0 编译器，点击下一步，等待安装完成。
 
   > Qt一般安装比较慢，可换源
    ```bash
    qt-unified-windows-x64.exe --mirror https://mirrors.tuna.tsinghua.edu.cn/qt
    ```
3. 需要环境变量：
    ```bash
    ...\6.10.2\mingw_64
    ...\6.10.2\mingw_64\bin
    ...\Tools\CMake_64\bin
    ...\Tools\Ninja
    ...\Tools\QtCreator\bin
    ```
4. 需要VS Code：
    [https://code.visualstudio.com/](https://code.visualstudio.com/)
5. 通过VS Code打开项目，编译运行。


## 项目结构（参考）
```
RandomSelection/
├── ApplicationClass/
│   ├── Application/
│   │   ├── SignalSource.cpp
│   │   ├── SignalSource.h
│   │   ├── rs_version.cpp
│   │   └── rs_version.h
│   ├── applicationShell.cpp
│   └── applicationShell.h
├── BaseWidgets/
│   ├── BaseCoreWidget/
│   │   ├── TinyWidget/
│   │   │   ├── AutoFitButton.cpp
│   │   │   ├── AutoFitButton.h
│   │   │   ├── AutoFitLabel.cpp
│   │   │   └── AutoFitLabel.h
│   │   ├── AspectRatioWidget.cpp
│   │   ├── AspectRatioWidget.h
│   │   ├── MessageTipWidget.cpp
│   │   └── MessageTipWidget.h
│   ├── BaseTab/
│   │   ├── BaseTab.cpp
│   │   ├── BaseTab.h
│   │   ├── ControlList.cpp
│   │   └── ControlList.h
│   └── TitleFunc/
│       ├── titleFunc.cpp
│       └── titleFunc.h
├── Console/
│   └── console.h
├── CoreCalculation/
│   ├── DoubleFileClass/
│   │   ├── ErrorCheck/
│   │   │   └── CutString.h
│   │   └── ReadFile/
│   │       ├── ImportFile.cpp
│   │       ├── ImportFile.h
│   │       └── target.rsol
│   ├── FileEditFunc/
│   └── SelectTabFunc/
│       ├── ClassType/
│       │   ├── OptionItem.hpp
│       │   └── word.hpp
│       ├── OptionList.hpp
│       └── StringCodec.hpp
├── CoreControlWidgets/
│   ├── AboutTab/
│   │   ├── aboutTab.cpp
│   │   └── aboutTab.h
│   ├── FileTab/
│   │   ├── fileTab.cpp
│   │   └── fileTab.h
│   ├── MainWindow/
│   │   ├── CustomTitleBar/
│   │   │   ├── CustomTitleBar.cpp
│   │   │   └── CustomTitleBar.h
│   │   ├── StatusBar/
│   │   │   ├── statusBar.cpp
│   │   │   └── statusBar.h
│   │   ├── mainWindow.cpp
│   │   └── mainWindow.h
│   ├── MinWindowShell/
│   │   ├── minWindowShell.cpp
│   │   └── minWindowShell.h
│   ├── ModWidgets/
│   │   ├── ToggleTopmost.cpp
│   │   └── ToggleTopmost.h
│   ├── SelectTab/
│   │   ├── BasicSet_P/
│   │   │   ├── basicSet.cpp
│   │   │   └── basicSet.h
│   │   ├── Hello_P/
│   │   │   ├── hello.cpp
│   │   │   └── hello.h
│   │   ├── ImportFile_P/
│   │   │   ├── IPT_base.cpp
│   │   │   ├── IPT_base.h
│   │   │   ├── importFiles.cpp
│   │   │   └── importFiles.h
│   │   ├── ListSet_P/
│   │   │   ├── listSet.cpp
│   │   │   └── listSet.h
│   │   ├── SelectFile_P/
│   │   │   ├── selectFile.cpp
│   │   │   └── selectFile.h
│   │   ├── Select_P/
│   │   │   ├── select_P.cpp
│   │   │   ├── select_P.h
│   │   │   ├── slc_midWidget.cpp
│   │   │   └── slc_midWidget.h
│   │   ├── selectTab.cpp
│   │   └── selectTab.h
│   └── SettingTab/
│       ├── settingTab.cpp
│       └── settingTab.h
├── PythonTool/
│   ├── FileTree.py
│   ├── FindClass.py
│   └── lineStatistics.py
├── VariablesStore/
│   ├── Initialization.cpp
│   ├── Initialization.h
│   ├── globalVariables.cpp
│   └── globalVariables.h
├── icons/
│   ├── MainTabIcons/
│   │   ├── AboutTabIcon.png
│   │   ├── FileEditTabIcon.png
│   │   ├── RandomSelectTabIcon.png
│   │   └── SettingTabIcon.png
│   ├── TitleIcons/
│   │   ├── _CloseButton.png
│   │   ├── _MaximizeButtonM.png
│   │   ├── _MaximizeButtonN.png
│   │   ├── _MinWindowButtonM.png
│   │   ├── _MinWindowButtonN.png
│   │   └── _MinimizeButton.png
│   ├── ApplicationIcon.png
│   └── ApplicationIconIco.ico
├── App_Main.cpp
├── ClassSpace.h
├── HowUse.md
├── MakeBagTarget.evb
├── QtPrecompiled.h
├── README.md
└── resources.qrc
```