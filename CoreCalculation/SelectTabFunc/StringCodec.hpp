#pragma once
#ifndef STRINGCODEC_HPP
#define STRINGCODEC_HPP
#include <QString>
#include <QChar>
#include <QStringList>
#include <cstdint>
#include <stdexcept>
#include <QDebug>
#include <utility>

#if __cplusplus < 202002L
#error "StringCodec requires C++20 or later! Add CONFIG += c++20 to .pro."
#endif

namespace CoreCalculation{


class StringCodec{
    public: inline QString operator()(const QString& input) const{  
        return encode(input);
    }

    public: inline QString operator<<(const QString& input) const{  
        return encode(input);
    }

    public: inline QString encode(const QString& input, bool _write = false) const{
        if (input.isEmpty()) return "A";
        QString result = "A";
        for (int i = 0; i < input.size();){
            char32_t codepoint = 0;
            const QChar ch = input.at(i);
            // 解析代理对
            if (ch.unicode() >= 0xD800 && ch.unicode() <= 0xDBFF && i+1 < input.size()){
                QChar low = input.at(i+1);
                if (low.unicode() >= 0xDC00 && low.unicode() <= 0xDFFF){
                    codepoint = 0x10000 + ((static_cast<uint32_t>(ch.unicode()) - 0xD800) * 0x400) + 
                                (static_cast<uint32_t>(low.unicode()) - 0xDC00);
                    i += 2;}
                else{
                    codepoint = static_cast<char32_t>(ch.unicode());
                    i += 1;}}
            else{
                codepoint = static_cast<char32_t>(ch.unicode());
                i += 1;}
            // 源头校验码点有效性
            if (codepoint > 0x10FFFF){
                throw std::invalid_argument("Invalid codepoint in input: 0x" + QString::number(codepoint, 16).toStdString());}
            QString seg = _toBase63(codepoint);
            // 核心修复：前导补A到4位
            while (seg.length() < 4){seg.prepend('A');}
            result.append(seg);
        }
        if (_write){ StringCodec::ENCODE_TEXT = result; }
        return result;
    }

    public: inline QString decode(const QString& encoded) const{
        if (encoded.isEmpty() || encoded == "A") return "";
        if (encoded.at(0) != 'A') throw std::invalid_argument("Encoded string must start with 'A'");
        QString original;
        QString content = encoded.mid(1);
        const int FIXED_SEGMENT_LEN = 4;
        if (content.length() % FIXED_SEGMENT_LEN != 0){
            throw std::invalid_argument("Encoded content length is not multiple of 4: " + QString::number(content.length()).toStdString());
        }
        for (int pos = 0; pos < content.length(); pos += FIXED_SEGMENT_LEN){
            QString seg = content.mid(pos, FIXED_SEGMENT_LEN);
            int firstNonA = 0;
            while (firstNonA < seg.length() && seg.at(firstNonA) == 'A'){firstNonA++;}
            // 截取非A部分
            if (firstNonA >= seg.length()){seg = "A";}
            else{seg = seg.mid(firstNonA);}
            char32_t codepoint = _fromBase63(seg);
            // 码点校验
            if (codepoint > 0x10FFFF){
                throw std::invalid_argument("Codepoint overflow: 0x" + QString::number(codepoint, 16).toStdString() + " (segment: " + seg.toStdString() + ")");
            }
            // 码点转QString（处理代理对）
            if (codepoint <= 0xFFFF){
                original.append(QChar(static_cast<quint16>(codepoint)));
            }
            else{
                uint32_t ucs4 = codepoint - 0x10000;
                quint16 high = static_cast<quint16>(0xD800 + (ucs4 / 0x400));
                quint16 low = static_cast<quint16>(0xDC00 + (ucs4 % 0x400));
                original.append(QChar(high)).append(QChar(low));
            }}
        return original;
    }

    // 63进制字符集（仅A-Za-z0-9_）
    private: inline static const QString BASE63_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
    private: inline static QString ENCODE_TEXT = "";
    public:  inline QString getEncodeText(){ return ENCODE_TEXT; }
    public:  inline void setEmptyEncodeText(){ ENCODE_TEXT = ""; }

    // 63进制转回码点
    private: inline char32_t _fromBase63(const QString& s) const{
        if (s.isEmpty()) return 0;
        char32_t result = 0;
        const uint32_t MAX_UNICODE = 0x10FFFF;
        for (const QChar& ch : s){
            int idx = BASE63_CHARS.indexOf(ch);
            if (idx == -1){
                throw std::invalid_argument("Invalid char in base63: " + QString(ch).toStdString() + " (0x" + QString::number(ch.unicode(),16).toStdString() + ")");
            }
            // 无符号转换+溢出校验
            uint32_t uidx = static_cast<uint32_t>(idx);
            if (result > (MAX_UNICODE / 63) || (result == (MAX_UNICODE / 63) && uidx > (MAX_UNICODE % 63))){
                throw std::invalid_argument("Segment overflows Unicode: " + s.toStdString());
            }
            result = result * 63 + static_cast<char32_t>(idx);
        }
        return result;
    }

    // 码点转63进制
    private: inline QString _toBase63(char32_t num) const{
        if (num == 0) return BASE63_CHARS.at(0);
        QString result;
        const uint32_t BASE = 63;
        uint32_t n = static_cast<uint32_t>(num);
        while (n > 0){
            uint32_t remainder = n % BASE;
            result.prepend(BASE63_CHARS.at(static_cast<int>(remainder)));
            n = n / BASE;
        }
        return result;
    }
};

inline StringCodec& operator>>(const QString& input, StringCodec& codec){
    codec.encode(input, true);
    return codec;
}

inline StringCodec&& operator>>(const QString& input, StringCodec&& codec){
    codec.encode(input, true);
    return std::move(codec);
}

inline StringCodec& operator>>(StringCodec& codec, QString& input){
    input = codec.getEncodeText();
    codec.setEmptyEncodeText();
    return codec;
}

inline StringCodec&& operator>>(StringCodec&& codec, QString& input){
    input = codec.getEncodeText();
    return std::move(codec);
}

} // namespace CoreCalculation

#endif // STRINGCODEC_HPP