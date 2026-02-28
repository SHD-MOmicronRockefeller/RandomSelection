//
// Created by Administrator on 2026/2/14.
//

#ifndef READFILE_H
#define READFILE_H

#include "ImportFile.h"

namespace CoreCalculation {



class readFile {
    public: OptionList readByPath(const QString& _path); // 通过路径读取文件
    public: void readByStr(const QString& _str); // 通过字符串读取文件
};




class readDirt {
    public: struct _file {
        public: QString fileName; // 文件名
        public: QString filePath; // 文件路径
        public: QString fileExtension; // 文件扩展名
    };
    public: QList<_file> getFilesBySuffix(const QString& folderPath, const QString& suffix, bool recursive = false); // 通过路径读取文件
    public: _file pathToFile(const QString& filePath); // 通过路径获取文件信息
};


} // CoreCalculation

Q_DECLARE_METATYPE(CoreCalculation::readDirt::_file)

#endif //READFILE_H