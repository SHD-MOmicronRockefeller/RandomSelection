#pragma once

#include "StringCodec.hpp"

class Group{
    private: QString _groupName = "__UNDEFINED__";
    // public: QString operator()() const { return _groupName; }
    public: QString group() const { return _groupName; }
    public: bool isUndefined() const { return _groupName == "__UNDEFINED__"; }
    
    private: QString _encodeGroupName = "__UNDEFINED__";
    public: void setGroupName(QString groupName) { 
        _groupName = groupName;
        _encodeGroupName = StringCodec() << groupName; }
    public: QString encodeGroupName() const { return _encodeGroupName; }
    
    private: bool _isEnable  = true;
    public: bool isEnable() const { return _isEnable; }
    public: void setEnable(bool isEnable) { _isEnable = isEnable; }

    public: Group() = default;
    public: Group(const QString& groupName) :_groupName(groupName), _encodeGroupName(StringCodec() << groupName) {}
    public: Group(const char* groupName) : _groupName(QString(groupName)), _encodeGroupName(StringCodec() << QString(groupName)) {}
    public: Group(const Group& other)           = default;
    public: Group(Group&& other)                = default;
    public: Group& operator=(const Group& other)= default;
    public: Group& operator= (Group&& other)    = default;
    public: ~Group()                            = default;

    public: Group& operator=(const char* groupName) {
        _groupName = QString(groupName);
        _encodeGroupName = StringCodec() << QString(groupName);
        return *this;
    }

    public: Group& operator=(const QString& groupName) {
        _groupName = groupName;
        _encodeGroupName = StringCodec() << groupName;
        return *this;
    }

    public: operator QString() const {
        return _groupName;
    }

    bool operator==(const Group& other) const {
        return _encodeGroupName == other._encodeGroupName;
    }
};

class OptionItem {

    // 是否有效
    public: bool isValid() const { return this->_content != "__UNDEFINED__"; }

    // 单元索引
    private: unsigned int _index = 0;
    public: inline unsigned int getIndex() const { return _index; }
    public: inline unsigned int setIndex(unsigned int index) { this->_index = index; return index; }

    // 单元内容
    private: QString _content = "__UNDEFINED__";  
    public: inline QString getContent() const { return _content; }
    public: inline void setContent(const QString& content) { this->_content = content; }

    // 单元权重
    private: unsigned long long _weight = 0;
    public: inline unsigned long long getWeight() const { return _weight; }
    public: inline void setWeight(unsigned long long weight) { this->_weight = weight; }

    // 单元是否被选取
    private: bool _isSelected = false;
    public: inline bool getIsSelected() const { return _isSelected; }
    public: inline void setIsSelected(bool isSelected) { this->_isSelected = isSelected; }

    // 单元被选取次数
    private: unsigned int _selectedTimes = 0;
    public: inline unsigned int& selectedTimes() { return _selectedTimes; }
    public: inline unsigned int getSelectedTimes() const { return _selectedTimes; }
    public: inline void setSelectedTimes(unsigned int selectedTimes) { this->_selectedTimes = selectedTimes; }

    // 单元所属组
    private: QVector<Group> _ownGroups;
    public: inline QVector<Group>&   ownGroups() { return _ownGroups; }
    public: inline QVector<Group> getOwnGroups() const { return _ownGroups; }
    // 加入组
    public: inline bool joinGroup(Group _group) { 
        if (_ownGroups.contains(_group)) return false;
        _ownGroups.append(_group);
        return true; }
    // 离开组
    public: inline bool leaveGroup(Group _group) { 
        return _ownGroups.removeOne(_group); }

    public: OptionItem(unsigned int index, QString content = "__UNDEFINED__", unsigned long long weight = 0) : _index(index), _content(content), _weight(weight) {}
    public: OptionItem()                                            = default;
    public: OptionItem(const OptionItem& other)                     = default;
    public: OptionItem(OptionItem&& other)                          = default;
    public: OptionItem& operator=(const OptionItem& other)          = default;
    public: OptionItem& operator=(OptionItem&& other)               = default;
    public: ~OptionItem()                                           = default;
};