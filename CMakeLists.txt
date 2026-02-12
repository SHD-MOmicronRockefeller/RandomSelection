cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED TARGET_NAME)
    set(TARGET_NAME "RandomSelection")
endif()

project(${TARGET_NAME} LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/DownApp/QtManager/6.10.2/mingw_64")

# 添加项目根目录为包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ========== 第一步：先收集所有文件（不做过滤） ==========
file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB_RECURSE FORMS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

file(GLOB_RECURSE RESOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)

# ========== 第二步：终极过滤规则（精准匹配所有构建目录文件） ==========
# 核心优化：
# 1. .*cmake-build-.* 匹配任意路径中包含cmake-build-的文件（无论嵌套多深）
# 2. .*CMakeFiles/.* 匹配所有CMakeFiles目录下的文件
# 3. .*CMakeCXXCompilerId\\.cpp 显式排除编译器检测文件（兜底）
set(EXCLUDE_REGEX
        .*moc_.*\\.cpp|.*qrc_.*\\.cpp|.*ui_.*\\.h|.*cmake-build-.*|.*CMakeFiles/.*|.*CMakeCXXCompilerId\\.cpp|.*CMakeCCompilerId\\.c|.*build.*
)

# 过滤文件列表（单行正则，避免解析歧义）
list(FILTER SOURCES EXCLUDE REGEX "${EXCLUDE_REGEX}")
list(FILTER HEADERS EXCLUDE REGEX "${EXCLUDE_REGEX}")
list(FILTER FORMS EXCLUDE REGEX "${EXCLUDE_REGEX}")
list(FILTER RESOURCES EXCLUDE REGEX "${EXCLUDE_REGEX}")

# 正确打印列表长度和内容（验证过滤效果）
list(LENGTH SOURCES SOURCES_COUNT)
message(STATUS "最终编译的源文件数量: ${SOURCES_COUNT}")
message(STATUS "源文件列表: ${SOURCES}")

# 后续代码不变...
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

qt_add_executable(${TARGET_NAME}
        ${SOURCES}
        ${HEADERS}
        ${FORMS}
        ${RESOURCES}
)

target_link_libraries(${TARGET_NAME} PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

# 自动复制依赖
# 自动复制依赖（修复PATH拼接错误）
if(WIN32)
    # 1. 明确windeployqt的绝对路径（避免PATH解析错误）
    set(WINDEPLOYQT_PATH "${CMAKE_PREFIX_PATH}/bin/windeployqt.exe")

    # 2. 修复POST_BUILD命令：简化语法，避免引号嵌套
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            # 先检查windeployqt是否存在
            COMMAND if not exist "${WINDEPLOYQT_PATH}" (echo "Error: windeployqt not found at ${WINDEPLOYQT_PATH}") else (
            # 直接调用绝对路径的windeployqt，无需拼接复杂PATH
            "${WINDEPLOYQT_PATH}" --no-translations --no-opengl-sw --no-system-d3d-compiler "$<TARGET_FILE:${TARGET_NAME}>"
    )
            COMMENT "Running windeployqt to copy dependencies..."
            # 确保命令在exe生成后执行
            VERBATIM
    )
endif()