#pragma once
#include <QMetaType>

#include "CoreCalculation/SelectTabFunc/ClassType/OptionItem.hpp"


namespace CoreCalculation{


class OptionList : public QVector<Base::OptionItem>
{
    public: ~OptionList() {
        this->QVector<Base::OptionItem>::clear();
    }

    private: QVector<Base::Group> _groups;
    public:  QVector<Base::Group> getGroups() const { return _groups; }



    // 增加组
    public: bool addGroup(Base::Group _group) {
        // 判断是否已经存在相同的组名
        for (Base::Group group : _groups) {
            if (group == _group) {
                return false;}}
        // 若不存在相同的组名，则加入新的组
        _groups.append(_group);
        return true;
    }

    // 移除组
    bool removeGroup(Base::Group _group) {
        if (_group.isUndefined()) return false;
        bool removed = _groups.removeOne(_group);
        if (!removed) return false;
        for (Base::OptionItem item : *this) {
                item.leaveGroup(_group); } 
        return true;
    }

    // 增加Base::OptionItem
    public: inline bool addOption(unsigned int index, QString content = "__UNDEFINED__", unsigned long long weight = 0) {
        return this->addOption(Base::OptionItem(index, content, weight));}
    public: inline bool addOption(Base::OptionItem _item) {
        // 判断是否已经存在相同的索引
        unsigned int index = _item.getIndex();
        for (Base::OptionItem item : *this) {
            if (item.getIndex() == index) {
                return false;}}
        // 若不存在相同的索引，则添加新的Base::OptionItem
        this->QVector<Base::OptionItem>::append(_item);
        return true;}
    public: inline bool setContent(unsigned int index, QString content) {
        Base::OptionItem* item = this->findByIndex(index);
        if (not item) return false;
            item->setContent(content);
            return true;
        }
    public: inline bool setWeight(unsigned int index, unsigned long long weight) {
        Base::OptionItem* item = this->findByIndex(index);
        if (not item) return false;
            item->setWeight(weight);
            return true;
        }
    public: inline bool setSelectedTimes(unsigned int index, unsigned int selectedTimes) {
        Base::OptionItem* item = this->findByIndex(index);
            if (not item) return false;
            item->setSelectedTimes(selectedTimes);
            return true;
        }
    public: inline bool setIsSelected(unsigned int index, bool isSelected) {
        Base::OptionItem* item = this->findByIndex(index);
            if (not item) return false;
            item->setIsSelected(isSelected);
            return true;
        }

    // 移除指定索引的Base::OptionItem
    public: inline bool remove(unsigned int index) {
        for (Base::OptionItem item : *this){
            if (item.getIndex() == index) {
                this->QVector<Base::OptionItem>::remove(this->indexOf(item));
                return true;}}
        return false;
    }

    // 获取指定索引的Base::OptionItem
    public: inline Base::OptionItem* findByIndex(unsigned int index) {
        for (auto it = this->begin(); it!= this->end(); ++it){
            if (it->getIndex() == index){
                return &(*it);
            }
        }
        return nullptr;
    }

    // 获取指定索引的Base::OptionItem的组
    public: inline QVector<Base::Group> getGroups(unsigned int index) {
        Base::OptionItem* item = this->findByIndex(index);
        if (not item) return QVector<Base::Group>();
        return item->getOwnGroups();
    }

    // 加入组
    bool joinGroup(unsigned int index, Base::Group _group) {
        this->addGroup(_group);
        Base::OptionItem* item = this->findByIndex(index);
        if (not item) return false;
        return item->joinGroup(_group);
    }

    // 离开组
    public: inline bool leaveGroup(unsigned int index, Base::Group _group) {
        Base::OptionItem* item = this->findByIndex(index);
        if (not item) return false;
        return item->leaveGroup(_group);
    }

    // 按照权重排序
    public: void sortByWeight() {
        std::sort(this->begin(), this->end(), [](Base::OptionItem a, Base::OptionItem b) {
            return a.getWeight() > b.getWeight();
        });
    }
    // 按照索引排序
    public: void sortByIndex() {
        std::sort(this->begin(), this->end(), [](Base::OptionItem a, Base::OptionItem b) {
            return a.getIndex() < b.getIndex();
        });
    }
    // 按照选择次数排序
    public: void sortBySelectedTimes() {
        std::sort(this->begin(), this->end(), [](Base::OptionItem a, Base::OptionItem b) {
            return a.getSelectedTimes() > b.getSelectedTimes();
        });
    }

    // 打印
    public: void print() const {
        if (not this->isEmpty()) {
            auto qd = qDebug() << "[" << _groups[0].group();
            for (int i = 1; i < _groups.size(); i++) {
                qd << ", " << _groups[i].group();
            }
            qd << "]";
        } else {
            qDebug()<< "[]";
        }
        for (Base::OptionItem item : *this) {
            qDebug()<< "Index: "          << item.getIndex()                      << "\t"
                    << " Content: "       << item.getContent()                    << "\t"
                    << " Weight: "        << item.getWeight()                     << "\t"
                    << " IsSelected: "    <<(item.getIsSelected()?"true":"false") << "\t"
                    << " SelectedTimes: " << item.getSelectedTimes()              << "\t"
                    << " Groups: "        << item.getOwnGroups()                  << "\t";
            }
        return;
    }

};

} // namespace CoreCalculation

Q_DECLARE_METATYPE(CoreCalculation::OptionList)