#ifndef TEST_H
#define TEST_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QRegularExpression>

#include "ClassSpace.h"


namespace CoreCalculation{

class RsolProcessor {

    // 构造函数：默认关闭调试模式
    public: RsolProcessor(bool debugMode = false);

    // 设置调试模式
    public: void setDebugMode(bool debugMode);

    // 核心函数：传入文件路径
    public: CoreCalculation::OptionList readOptionList(const QString& filePath);

    // 调试模式标志
    private: bool m_debugMode;

    // 调试日志写入函数：将内容追加到debug.txt
    private: void writeDebug(const QString& content);

    // 第一步：预处理（注释、导入、替换、删除预处理指令）
    private: QString preprocess(const QString& inputContent, const QString& originalFilePath);

    // 第二步：格式化（合并块、补全属性、统一空格）
    private: QString formatContent(const QString& preprocessedContent);

    // 第三步：生成机器代码
    private: QString generateMachineCode(const QString& formattedContent);

    // 第四步：打包列表
    private: CoreCalculation::OptionList packList(QString machineCode);

};

} // namespace CoreCalculation

#endif // TEST_H