# ========== 基础配置（修复核心） ==========
isEmpty(TARGET_NAME) { TARGET_NAME = RandomSelection }  # 兜底项目名
TEMPLATE = app
CONFIG += c++20
CODECFORTR = UTF-8
CODECFORSRC = UTF-8

# ========== 关键修复：文件扫描（避免生成多余减号） ==========
# 方式1：显式过滤，避免空值导致的减号问题
SOURCES = $$files(*.cpp, true)
SOURCES -= $$files(build/*.cpp, true)
SOURCES -= $$files(build_debug/*.cpp, true)
SOURCES -= $$files(build_release/*.cpp, true)

HEADERS = $$files(*.h, true)
HEADERS -= $$files(build/*.h, true)
HEADERS -= $$files(build_debug/*.h, true)
HEADERS -= $$files(build_release/*.h, true)

FORMS = $$files(*.ui, true)
RESOURCES = $$files(*.qrc, true)

# ========== Debug/Release 模式配置（关闭同时编译） ==========
CONFIG += debug_and_release  # 支持两种模式，但不自动同时编译
# 移除 CONFIG += build_all 

# Debug 模式：保留调试信息，关闭优化
CONFIG(debug, debug|release) {
    TARGET = Application_Debug
    DEFINES += QT_DEBUG
    QMAKE_CXXFLAGS += -g -O0  # 断点生效核心：-g生成调试信息，-O0关闭优化
    QMAKE_LFLAGS += -g        # 链接时也保留调试信息
}

# Release 模式：优化编译，自动打包
CONFIG(release, debug|release) {
    TARGET = $${TARGET_NAME}_Release
    DEFINES += QT_NO_DEBUG
    QMAKE_CXXFLAGS += -O2  # 开启优化
    # 仅 Release 模式执行打包
    win32 {
        ENIGMA_PATH = "D:/DownApp/Enigma Virtual Box/enigmavb.exe"
        ENIGMA_TEMPLATE = $$PWD/MakeBagTarget.evb
        QMAKE_POST_LINK += $$ENIGMA_PATH /pack /silent $$ENIGMA_TEMPLATE  $$escape_expand(\\n\\t)
    }
}

# ========== 其他基础配置 ==========
QT += core widgets gui

# Windows 控制台
win32 { 
    CONFIG -= windows 
    CONFIG += console 
}

# MinGW 编码
win32-g++ { 
    QMAKE_CXXFLAGS += -fexec-charset=utf-8 -finput-charset=utf-8 
}

# 多核编译
win32 { 
    CPU_CORES = $$system(powershell -Command "(Get-CimInstance Win32_Processor).NumberOfLogicalProcessors") 
}
else { 
    CPU_CORES = $$system(sysctl -n hw.logicalcpu 2>/dev/null || nproc) 
}
isEmpty(CPU_CORES) { CPU_CORES = 4 }
win32 { MAKEFLAGS += -j$$CPU_CORES }
else { QMAKE_MAKEFLAGS += -j$$CPU_CORES }