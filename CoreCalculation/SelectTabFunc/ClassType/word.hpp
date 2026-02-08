#pragma once

#include <QString>
#include <QVector>

class Word{
    public: Word(QString _word, unsigned int _begin) {
        this->word = _word;
        this->begin = _begin;
        this->end = _begin + _word.size();
    }

    public: QString word = "";
    public: unsigned int begin = 0;
    public: unsigned int end = 0;
    
    public: unsigned int size() {
        return end - begin;
    }
};