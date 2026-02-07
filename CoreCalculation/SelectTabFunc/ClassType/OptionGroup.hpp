#pragma once

#include "OptionItem.hpp"

#include <algorithm>

class OptionGroup : public QVector<OptionItem*> {
    // 组名
    private: QString groupName = "";
    public:  QString getGroupName () const { return groupName; }
    public:  QString setGroupName (const QString& _baseName) {
        this->groupName = _baseName;
        return _baseName;
    }

    // 加入选项
    public: void append(OptionItem _item){
        // 复制一份OptionItem
        OptionItem* item = new OptionItem(_item);

        // 加入组
        this->QVector<OptionItem*>::append(item);
        item->joinGroups(groupName);
    }

    // 移除索引选项
    public: void remove(unsigned int index) {
        // 定义删除条件
        auto delCondition = [index](OptionItem* _option) {
            if (!_option) return false;
            return _option->getIndex() == index;};
        // 遍历释放
        for (OptionItem* option : *this){
            if (delCondition(option)) {
                delete option; }}
        // 调用父类删除
        erase_if(*this, delCondition);
    }

    // 移除相同索引选项
    public: void cleanSameIndex() {
        std::sort(this->begin(), this->end(), [](OptionItem* a, OptionItem* b) {
            return a->getIndex() < b->getIndex(); });
        QVector<OptionItem*>::iterator it = this->begin();
        while (it!= this->end()){
            if (it + 1 != this->end() && (*it)->getIndex() == (*(it + 1))->getIndex()){
                delete *it;
                it = this->QVector<OptionItem*>::erase(it);
            } else {
                ++it;
            }
        }
    }

};
