#pragma once

#include "OptionItem.hpp"

class OptionList : public QVector<OptionItem*>
{
    public: ~OptionList() {
        for (OptionItem* item : *this) {
            delete item;
        }
        this->QVector<OptionItem*>::clear();
    }

    private: QVector<Group> _groups;
    public:  QVector<Group> getGroups() const { return _groups; }

    // 增加组
    public: bool addGroup(Group _group) {
        // 判断是否已经存在相同的组名
        for (Group group : _groups) {
            if (group == _group) {
                return false;}}
        // 若不存在相同的组名，则加入新的组
        _groups.append(_group);
        return true;
    }

    // 移除组
    bool removeGroup(Group _group) {
        if (_group.isUndefined()) return false;
        bool removed = _groups.removeOne(_group);
        if (!removed) return false;
        for (OptionItem* item : *this) {
            if (item) {
                item->leaveGroup(_group); } }
        return true;
    }

    // 增加OptionItem
    public: inline bool append(unsigned int index, QString content, unsigned long long weight) {
        return this->append(OptionItem(index, content, weight));
    }
    public: inline bool append(OptionItem _item) {
        // 判断是否已经存在相同的索引
        unsigned int index = _item.getIndex();
        for (OptionItem* item : *this) {
            if (item && item->getIndex() == index) {
                return false;}}
        // 若不存在相同的索引，则添加新的OptionItem
        OptionItem* item = new OptionItem(_item);
        this->QVector<OptionItem*>::append(item);
        return true;
    }

    // 移除指定索引的OptionItem
    public: inline bool remove(unsigned int index) {
        for (OptionItem* item : *this){
            if (item && item->getIndex() == index) {
                this->QVector<OptionItem*>::remove(this->indexOf(item));
                delete item;
                return true;}}
        return false;
    }

    // 获取指定索引的OptionItem
    public: inline OptionItem* findByIndex(unsigned int index) const {
        for (OptionItem* item : *this) {
            if (item && item->getIndex() == index) {
                return item;}}
        return nullptr;
    }

    // 获取指定索引的OptionItem的组
    public: inline QVector<Group> getGroups(unsigned int index) {
        OptionItem* item = this->findByIndex(index);
        if (item) {
            return item->getOwnGroups();
        }
        return QVector<Group>();
    }

    // 加入组
    bool joinGroup(unsigned int index, Group _group) {
        this->addGroup(_group);
        OptionItem* item = this->findByIndex(index);
        if (!item) return false;
        return item->joinGroup(_group);
    }

    // 离开组
    public: inline bool leaveGroup(unsigned int index, Group _group) {
        OptionItem* item = this->findByIndex(index);
        if (item) {
            return item->leaveGroup(_group);}
        return false;
    }

    // 按照权重排序
    public: void sortByWeight() {
        std::sort(this->begin(), this->end(), [](OptionItem* a, OptionItem* b) {
            return a->getWeight() > b->getWeight();
        });
    }
    // 按照索引排序
    public: void sortByIndex() {
        std::sort(this->begin(), this->end(), [](OptionItem* a, OptionItem* b) {
            return a->getIndex() < b->getIndex();
        });
    }
    // 按照选择次数排序
    public: void sortBySelectedTimes() {
        std::sort(this->begin(), this->end(), [](OptionItem* a, OptionItem* b) {
            return a->getSelectedTimes() > b->getSelectedTimes();
        });
    }

};