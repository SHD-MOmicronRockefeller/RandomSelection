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

# ========== 多线程编译配置（修正语法错误） ==========
# 自动获取CPU逻辑核心数（跨平台适配，修正命令执行语法）
win32 {
    # Windows平台：通过wmic命令获取CPU核心数（修正命令拼接语法）
    CPU_CORES = $$system(powershell -Command "(Get-CimInstance Win32_Processor).NumberOfLogicalProcessors")
} else {
    # Linux/macOS平台：通过sysctl/nproc获取核心数
    CPU_CORES = $$system(sysctl -n hw.logicalcpu 2>/dev/null || nproc)
}

# 兜底：获取失败时默认使用4线程（修正条件判断语法）
isEmpty(CPU_CORES) {
    CPU_CORES = 4
}

# 设置多线程编译参数（修正变量赋值语法）
win32 {
    MAKEFLAGS += -j$$CPU_CORES
} else {
    QMAKE_MAKEFLAGS += -j$$CPU_CORES
}

# ========== 自动扫描文件配置 ==========
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

    # 定位项目根目录下的.evb模板文件
    ENIGMA_TEMPLATE = $$PWD/random_selection.evb

    # 编译完成后自动打包
    QMAKE_POST_LINK += $$ENIGMA_PATH /pack /silent $$ENIGMA_TEMPLATE  $$escape_expand(\\n\\t)
}