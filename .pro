# ========== 核心：自动获取当前文件夹名称作为项目名 ==========
# _PRO_FILE_PWD_ 是 .pro 文件所在目录的绝对路径
# dirname 提取路径的最后一级（即文件夹名）
TARGET = $$TARGET_NAME

# 兜底：防止传参失败
isEmpty(TARGET) {
    TARGET = RandomSelection
}

# 生成可执行文件
TEMPLATE = app

# C++ 标准
#CONFIG += c++17
CONFIG += c++20
# 强制 UTF-8 编码
CODECFORTR = UTF-8
CODECFORSRC = UTF-8

# 自动扫描源文件、头文件、UI、资源文件
SOURCES += $$files(*.cpp, true)
HEADERS += $$files(*.h, true)
FORMS   += $$files(*.ui, true)
RESOURCES += $$files(*.qrc, true)

# 排除 build 目录
SOURCES -= $$files(build/*.cpp, true)
HEADERS -= $$files(build/*.h, true)

# Qt 模块配置
QT += core widgets gui

# 资源文件
#add_executable($$TARGET $$SOURCES $$HEADERS $$FORMS $$RESOURCES)

# Windows 显示控制台窗口
win32 {
    CONFIG -= windows
    CONFIG += console
}

# MinGW 编译选项
win32-g++ {
    QMAKE_CXXFLAGS += -fexec-charset=utf-8 -finput-charset=utf-8
}

win32 { # 仅在Windows下执行打包逻辑
    ENIGMA_PATH = "D:/DownApp/Enigma Virtual Box/enigmavb.exe"

    # 2. 定位项目根目录下的.evb模板文件（关键：$$PWD就是项目根目录）
    # 替换「your_app_template.evb」为你实际的.evb文件名
    ENIGMA_TEMPLATE = $$PWD/random_selection.evb

    # 3. 打包输出路径（编译输出目录，和生成的exe同目录）
    #OUTPUT_PACKAGE = $$OUT_PWD/random_selection.exe

    # 4. 编译完成后自动打包（/silent 可选，静默打包不弹窗口）
    #QMAKE_POST_LINK += $$ENIGMA_PATH /pack /silent $$ENIGMA_TEMPLATE $$OUTPUT_PACKAGE $$escape_expand(\\n\\t)
    QMAKE_POST_LINK += $$ENIGMA_PATH /pack /silent $$ENIGMA_TEMPLATE  $$escape_expand(\\n\\t)
}