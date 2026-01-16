cmake_minimum_required(VERSION 3.16)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== 核心修复：精准扫描源码，排除 build 目录 ==========
# # 方式1：手动指定源码文件（推荐，稳定不踩坑）
# set(SOURCES
#     ${CMAKE_SOURCE_DIR}/main.cpp
#     # 其他业务源码文件手动加在这里，比如：
#     # ${CMAKE_SOURCE_DIR}/downloader.cpp
#     # ${CMAKE_SOURCE_DIR}/threadpool.cpp
# )

#方式2（备选）：自动扫描但排除 build 目录（如果不想手动列文件）
file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.h"
    "${CMAKE_SOURCE_DIR}/*.hpp"
    #"${CMAKE_SOURCE_DIR}/*.ui"
)
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/.*")

# 链接 Qt 核心和网络模块
find_package(Qt6 REQUIRED COMPONENTS Core Network)
qt_standard_project_setup()

# 自动MOC/RCC/UIC（关键：拆分文件后MOC自动处理）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 生成可执行文件，仅关联业务源码
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Network)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Network
)

# Windows 控制台程序，避免运行时无窗口
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        WIN32_EXECUTABLE OFF
        # 额外优化：防止 Qt 自动生成的文件冲突
        AUTOGEN_BUILD_DIR "${CMAKE_BINARY_DIR}/autogen"
    )
endif()

if (MINGW)
    # MinGW 兼容的 UTF-8 编码
    target_compile_options(${PROJECT_NAME} PRIVATE -fexec-charset=utf-8 -finput-charset=utf-8)
endif()

set_property(SOURCE downloadtask.h PROPERTY SKIP_AUTOMOC OFF)

# ========== 额外优化：清理编译临时文件 ==========
# 添加 clean 目标，删除 build 目录外的临时文件
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Clean all build files"
)