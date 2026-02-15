//
// Created by Administrator on 2026/2/14.
//

#ifndef READFILE_H
#define READFILE_H

#include "ImportFile.h"

namespace CoreCalculation {
class readFile {
    public: void readByPath(const QString& path); // 通过路径读取文件
    public: void readByStr(const QString& str); // 通过字符串读取文件
};
} // CoreCalculation

#endif //READFILE_H