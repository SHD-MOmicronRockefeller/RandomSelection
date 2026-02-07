#pragma once
#include "QtPrecompiled.h"

class OptionItem {

    // 单元索引
    private: int index = -1;
    public:  int getIndex() const { return index; }
    public:  int setIndex(int index) { this->index = index; return index; }

    // 单元内容
    private: QString content = "";
    public:  QString getContent() const { return content; }
    public:  QString setContent(const QString& content) { this->content = content; return content; }

    // 单元权重
    private: unsigned long long weight = 0;
    public:  unsigned long long getWeight() const { return weight; }
    public:  unsigned long long setWeight(unsigned long long weight) { this->weight = weight; return weight; }

    // 单元所属组
    private: QVector<QString> ownGroups;
    public:  QString joinGroups(QString _groupName) { ownGroups.append(_groupName); return _groupName; }
};