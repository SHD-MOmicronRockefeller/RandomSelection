#include "rs_version.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <optional>
#include <stdexcept>

_vs::_vs &_vs::_vs::operator<<(const std::string &_str)
{
    this->_m_version = _str;
    this->_split_version(_str);
    return *this;
}

std::optional<std::tuple<int, int, int>> _vs::_vs::_split_version(const std::string &_version)
{
    std::vector<std::string> parts;
    std::stringstream ss(_version);
    std::string part;

    // 按'.'分割字符串
    while (std::getline(ss, part, '.'))
    {
        parts.push_back(part);
    }

    // 校验：必须恰好3个部分（两个点，三个数值）
    if (parts.size() != 3)
    {
        return std::nullopt;
    }

    try
    {
        // 转换为int，非数字会抛出std::invalid_argument/std::out_of_range
        int major = std::stoi(parts[0]);
        int minor = std::stoi(parts[1]);
        int patch = std::stoi(parts[2]);

        this->m_first_version = major;
        this->m_second_version = minor;
        this->m_third_version = patch;

        return std::make_tuple(major, minor, patch);
    }
    catch (const std::exception&)
    {
        return std::nullopt;
    }
}

RS_Version* RS_Version::m_instance = nullptr;

RS_Version *RS_Version::getInstance()
{
    if (RS_Version::m_instance == nullptr)
    {
        RS_Version::m_instance = new RS_Version();
    }
    return RS_Version::m_instance;
}

RS_Version &RS_Version::getVersion()
{
    if (RS_Version::m_instance == nullptr)
    {
        RS_Version::m_instance = new RS_Version();
    }
    return *RS_Version::m_instance;
}

std::string RS_Version::getVersionStr()
{
    if (RS_Version::m_instance == nullptr)
        return "";
    return RS_Version::m_instance->m_version._m_version;
}

void RS_Version::deleteInstance()
{
    if (RS_Version::m_instance != nullptr)
    {
        delete RS_Version::m_instance;
        RS_Version::m_instance = nullptr;
    }
}

_vs::_vs &RS_Version::setVersion()
{
    return this->m_version;
}

bool RS_Version::operator==(const std::string &_version_str) const
{
    _vs::_vs _version;   /*转换为_vs::_vs类型*/ _version << _version_str;
    return m_version.m_first_version  == _version.m_first_version  &&
           m_version.m_second_version == _version.m_second_version &&
           m_version.m_third_version  == _version.m_third_version;
}

std::strong_ordering RS_Version::operator<=>(const std::string &_version_str) const
{
    _vs::_vs _version;   /*转换为_vs::_vs类型*/ _version << _version_str;
    std::strong_ordering cmp_first = m_version.m_first_version <=> _version.m_first_version;
    if (cmp_first != std::strong_ordering::equal)
        return cmp_first;

    std::strong_ordering cmp_second = m_version.m_second_version <=> _version.m_second_version;
    if (cmp_second != std::strong_ordering::equal)
        return cmp_second;

    return m_version.m_third_version <=> _version.m_third_version;
}