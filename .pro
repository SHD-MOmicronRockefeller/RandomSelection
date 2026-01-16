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
CONFIG += c++17
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

# Qt 模块配置（按需添加）
QT += core widgets gui

# Windows 显示控制台窗口
win32 {
    CONFIG -= windows
    CONFIG += console
}

# MinGW 编译选项
win32-g++ {
    QMAKE_CXXFLAGS += -fexec-charset=utf-8 -finput-charset=utf-8
}
