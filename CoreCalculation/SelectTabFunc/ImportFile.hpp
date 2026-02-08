#pragma once

#include <QVector>

#include "OptionList.hpp"

class ImportFile{
    public: ImportFile(){};

    public: static OptionList importFile(const QString& fileName){}

    // 获取整个文件内容
    private: static QString importStrings(const QString& fileName) {}

    // 切割字符串 一排一排的分割
    private: static QVector<QString> cutStrings(QString _str) {}

    // 格式化字符串 去除空格等
    private: static QVector<QString> formatString(QVector<QString> _strArr) {}
};