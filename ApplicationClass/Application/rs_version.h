#ifndef RS_VERSION_H
#define RS_VERSION_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include <compare>
#include <string>
#include <optional>
#include <tuple>
#include <sstream>
#include <stdexcept>

class RS_Version;

namespace _vs {
class _vs {
    public: friend class ::RS_Version;
    private: std::string _m_version;

    private: _vs() = default;
    private: ~_vs() = default;
    private: _vs(const _vs&) = delete;
    private: _vs& operator=(const _vs&) = delete;

    public: _vs& operator<<(const std::string& _str);

    private: std::optional<std::tuple<int, int, int>> _split_version(const std::string& _version);
    private: unsigned int m_first_version = 0;
    private: unsigned int m_second_version = 0;
    private: unsigned int m_third_version = 0;
};
}

class RS_Version {
    public: static RS_Version* getInstance();
    public: static RS_Version& getVersion();
    public: static std::string getVersionStr();
    public: static void deleteInstance();

    private: static RS_Version* m_instance;

    private: _vs::_vs m_version;

    // 私有构造、析构、拷贝、赋值
    private: RS_Version() = default;
    private: ~RS_Version() = default;
    private: RS_Version(const RS_Version&) = delete;
    private: RS_Version& operator=(const RS_Version&) = delete;

    public: _vs::_vs& setVersion();

    public: std::strong_ordering operator<=>(const std::string& _version) const;
    public: bool operator==(const std::string& _version_str) const;
};





#endif // RS_VERSION_H