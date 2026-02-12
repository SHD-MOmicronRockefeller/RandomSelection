#include "ImportFile.h"
#include <QRegularExpressionMatchIterator>
#include <algorithm>

#include "CoreCalculation/SelectTabFunc/OptionList.hpp"


#define NUM(_num)   QString::number(_num)


namespace CoreCalculation{


// 构造函数：初始化调试模式，清空旧的debug.txt
RsolProcessor::RsolProcessor(bool debugMode) : m_debugMode(debugMode) {
    if (m_debugMode) {
        QFile debugFile("debug.txt");
        if (debugFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            debugFile.close();
        }
    }
}

// 设置调试模式
void RsolProcessor::setDebugMode(bool debugMode) {
    m_debugMode = debugMode;
}

// 写入调试日志
void RsolProcessor::writeDebug(const QString& content) {
    if (!m_debugMode) return;

    QFile debugFile("debug.txt");
    if (debugFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&debugFile);
        out << content << "\n";//<< "\n----------------------------------------\n";
        debugFile.close();
    }
}

// 第一步：预处理
QString RsolProcessor::preprocess(const QString& inputContent, const QString& originalFilePath) {
    writeDebug("[预处理-开始] 原始内容：\n" + inputContent);
    QString content = inputContent;
    writeDebug("---------------------------------------------------------------------------------------------");

    QStringList lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    QStringList processedLines;

    // 1. 处理#import：补全路径 + 替换为文件内容
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    QRegularExpression importRegex(R"xx(\s*#import\s*["<]([^">]+\.rsol)[">])xx");
    writeDebug(QString("[预处理-处理#import] 共%1行").arg(lines.size()));
    QFileInfo originalFileInfo(originalFilePath);
    if (!originalFileInfo.exists()) {
        qWarning() << "原始文件不存在：" << originalFilePath;
        return content;
    }
    QString originalFileDir = originalFileInfo.absoluteDir().path(); // 从完整路径提取目录
    for (int i = lines.size() - 1; i >= 0; --i) {
        QString line = lines.at(i);
        QRegularExpressionMatch match = importRegex.match(line);
        
        if (match.hasMatch()) {
            QString importRelOrAbsPath = match.captured(1);
            QString fullImportPath;
            QFileInfo importFileInfo(importRelOrAbsPath);
            if (importFileInfo.isAbsolute()) {
                fullImportPath = importRelOrAbsPath;
                writeDebug("    发现绝对路径 ：" + importRelOrAbsPath);
            } else {
                fullImportPath = QDir(originalFileDir).absoluteFilePath(importRelOrAbsPath);
                writeDebug("    发现相对路径 ：" + importRelOrAbsPath + " -> " + fullImportPath);
            }
            
            // 2. 读取.rsol文件内容
            QFile importFile(fullImportPath);
            if (!importFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                writeDebug("【预处理-警告】无法打开导入文件（路径：" + fullImportPath + "），保留原#import语句");
                qWarning() << "无法打开导入文件（路径：" << fullImportPath << "），保留原#import语句";
                continue;
            }
            QString importContent = importFile.readAll();
            importFile.close();
            lines.replace(i, importContent);
        }
    }
    content = lines.join("\n");
    writeDebug("[预处理-完成]处理#import后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    // 2.处理//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[预处理-处理注释] 共%1行").arg(lines.size()));
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i];
        int commentIndex = line.indexOf("//");
        if (commentIndex != -1) {
            line = line.left(commentIndex);
            writeDebug(QString("    发现注释行第%1行(处理后)：%2").arg(i + 1).arg(processedLines.last()));
        }
        processedLines.append(line);
    }
    content = processedLines.join("\n");
    writeDebug("[预处理-完成]移除//注释后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    //3. 处理#ifndef #define #endif 条件编译
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    QRegularExpression ifndefRegex(R"xx(\s*#ifndef\s+([a-zA-Z_][a-zA-Z0-9_\.]*))xx");
    QRegularExpression defineRegex(R"xx(\s*#define\s+([a-zA-Z_][a-zA-Z0-9_\.]*))xx");
    QRegularExpression endifRegex(R"xx(\s*#endif\s*)xx");
    writeDebug(QString("[预处理-处理#ifndef #define #endif] 共%1行").arg(lines.size()));
    QSet<QString> definedMacros;   // 已定义宏
    int i = 0;                     // 遍历索引
    while (i < lines.size()) {
        QString line = lines[i];
        QString trimLine = line.trimmed();
        // 1. 匹配到#ifndef：处理整个条件块
        if (ifndefRegex.match(trimLine).hasMatch()) {
            QRegularExpressionMatch match = ifndefRegex.match(trimLine);
            QString macro = match.captured(1);
            int level = 1;  // 嵌套层级
            int blockStart = i;
            int blockEnd = i;
            i++;  // 跳过当前#ifndef行
            // 找匹配的#endif
            while (i < lines.size() && level > 0) {
                QString t = lines[i].trimmed();
                if (ifndefRegex.match(t).hasMatch()) {
                    level++;
                } else if (endifRegex.match(t).hasMatch()) {
                    level--;
                    if (level == 0) {
                        blockEnd = i;
                        break;}
                }
                i++;
            }
            // 2. 宏未定义：
            if (!definedMacros.contains(macro)) {
                definedMacros.insert(macro);
                writeDebug(QString("    宏%1首次定义，保留业务代码").arg(macro));
                // 遍历块内所有行（跳过#ifndef/#define/#endif）
                for (int j = blockStart + 1; j < blockEnd; j++) {
                    QString innerLine = lines[j];
                    // 跳过#define行，其余业务行全部保留
                    if (!defineRegex.match(innerLine.trimmed()).hasMatch()) {
                        processedLines.append(innerLine);
                    }}
            } 
            // 3. 宏已定义：直接跳过整个块
            else {
                writeDebug(QString("    宏%1重复定义，裁剪整个块").arg(macro));
            }
            i = blockEnd + 1;
        } 
        // 非条件编译行：直接保留
        else {
            processedLines.append(line);
            i++;
        }
    }
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]处理#ifndef #define #endif后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    // 处理 #replace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    QRegularExpression replaceRegex(R"xx(#replace\s*"([^"]+)"\s*->\s*"([^"]*)")xx");
    QList<QPair<QString, QString>> replaceRules;
    writeDebug(QString("[预处理-处理#replace] 共%1行，开始解析替换规则").arg(lines.size()));
    // 第一步：解析所有#replace规则，同时过滤掉#replace指令行
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i);
        QRegularExpressionMatch match = replaceRegex.match(line);
        
        if (match.hasMatch()) {
            QString srcStr = match.captured(1);
            QString dstStr = " " + match.captured(2) + " ";
            replaceRules.append(QPair<QString, QString>(srcStr, dstStr));
            writeDebug(QString("[预处理] 解析#replace规则：\"%1\" -> \"%2\"").arg(srcStr).arg(dstStr));
            continue;
        }
        processedLines.append(line);
    }
    if (!replaceRules.isEmpty()) {
        writeDebug(QString("[预处理] 开始应用%1条替换规则").arg(replaceRules.size()));
        for (int i = 0; i < processedLines.size(); ++i) {
            QString line = processedLines.at(i);
            QString newLine = line;
            for (const QPair<QString, QString>& rule : replaceRules) {
                newLine.replace(rule.first, rule.second);
            }
            processedLines.replace(i, newLine);
        }
    }

    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]处理#replace规则后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    // 处理 空格 去掉开头空格；多个空格合并为一个空格
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    QRegularExpression leadingSpaceRegex(R"xx(^\s+)xx");
    QRegularExpression multiSpaceRegex(R"xx(\s+)xx");
    writeDebug(QString("[预处理-处理空格] 共%1行，开始清理空格").arg(lines.size()));
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i);
        line = line.replace(leadingSpaceRegex, "");
        line = line.replace(multiSpaceRegex, " ");
        line = line.trimmed();
        if (!line.isEmpty()) {
            processedLines.append(line);
        }
    }
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]处理空格后：\n" + content);
    return content;
}

// 第二步：格式化
QString RsolProcessor::formatContent(const QString& preprocessedContent) {
    writeDebug("[格式化-开始] 原始内容：\n" + preprocessedContent);
    QString content = preprocessedContent;
    writeDebug("---------------------------------------------------------------------------------------------");

    QStringList lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    QStringList processedLines;
    // 1. 合并create_make/create_end块并删除关键字
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 将create_make(包括)和create_end(包括)之间的所有内容合并为一行，删除所有create_make/create_end关键字
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[格式化-合并块] 共%1行").arg(lines.size()));

    int nestedLevel = 0;
    QString currentBlock;
    bool inOuterBlock = false;
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        // 匹配create_make
        if (line == "create_make") {
            nestedLevel++;
            // 仅最外层create_make开启块合并，内部的直接跳过
            if (nestedLevel == 1) {
                inOuterBlock = true;
            }
            continue;
        }
        // 匹配create_end
        if (line == "create_end") {
            nestedLevel--;
            // 仅最外层create_end完成块合并，内部的直接跳过
            if (nestedLevel == 0) {
                inOuterBlock = false;
                // 清理块内容的多余空格
                currentBlock = currentBlock.trimmed().replace(QRegularExpression("\\s+"), " ");
                // 过滤空块
                if (!currentBlock.isEmpty()) {
                    processedLines.append(currentBlock);
                }
                currentBlock.clear(); // 清空临时块
            }
            continue;
        }
        // 处理块内/块外的普通行
        if (inOuterBlock) {
            // 块内普通行：去除首尾空格后追加
            if (!line.isEmpty()) {
                currentBlock += " " + line;
            }
        } else {
            // 块外普通行：直接保留
            processedLines.append(line);
        }
    }
    // 容错处理：若文件结束时仍在块内，则强制输出清理后的块
    if (inOuterBlock && !currentBlock.isEmpty()) {
        currentBlock = currentBlock.trimmed().replace(QRegularExpression("\\s+"), " ");
        processedLines.append(currentBlock);
        writeDebug("[格式化-合并块] 警告：存在未闭合的create_make/create_end块");
    }
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]合并create_make/create_end块并删除关键字后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");
    // 2. 转化为易读格式
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[格式化-转化易读] 共%1行").arg(lines.size()));
    QRegularExpression keyValueRegex(R"xx((\w+)\s*=\s*([\w\(\)\s,]+))xx");
    QRegularExpression joinGroupRegex(R"xx(joinGroup\s*\(([^)]*)\))xx");
    QRegularExpression boolRegex(R"xx(\b(true|false)\b)xx", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression numberRegex(R"xx(\b\d+\b)xx");
    QRegularExpression hasWeightRegex(R"xx(\bweight\b)xx");
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        if (line.isEmpty()) continue;
        QString originalLine = line;
        QStringList lineParts = originalLine.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (lineParts.isEmpty()) continue;
        QString namePart = lineParts.first(); // 第一部分永远是名称，强制保留
        // ========== 步骤1：处理 joinGroup(参数) 格式 ==========
        QRegularExpressionMatch joinGroupMatch = joinGroupRegex.match(line);
        if (joinGroupMatch.hasMatch()) {
            QString paramsStr = joinGroupMatch.captured(1).trimmed();
            QStringList params = paramsStr.replace(",", "").split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            QString replaceStr = QString("joinGroup %1 %2").arg(params.size()).arg(params.join(" "));
            line.replace(joinGroupRegex, replaceStr);
        }
        // ========== 步骤2：拆分 key=value 为 key value ==========
        while (keyValueRegex.match(line).hasMatch()) {
            line = line.replace(keyValueRegex, "\\1 \\2");
        }
        // ========== 步骤3：布尔值(true/false)转为数字1/0 ==========
        QRegularExpressionMatchIterator boolIt = boolRegex.globalMatch(line);
        while (boolIt.hasNext()) {
            QRegularExpressionMatch match = boolIt.next();
            QString boolVal = match.captured(1).toLower();
            line.replace(match.captured(0), boolVal == "true" ? "1" : "0");
        }
        // ============ 步骤4：处理weight字段 ============
        QStringList processedParts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        bool hasWeight = hasWeightRegex.match(line).hasMatch();
        int weightValue = -1;
        int weightIndex = -1;
        // 遍历找weight值（跳过名称列，排除joinGroup后的参数数）
        if (!hasWeight && processedParts.size() > 1) {
            for (int j = 1; j < processedParts.size(); ++j) { // j从1开始，跳过名称列
                QString part = processedParts[j];
                if (numberRegex.match(part).hasMatch() && !(j > 1 && processedParts[j-1] == "joinGroup")) {
                    weightValue = part.toInt();
                    weightIndex = j;
                    break;
                }}
        }
        // 补全weight字段（保留名称）
        if (weightValue != -1 && weightIndex != -1) {
            processedParts.removeAt(weightIndex);
            processedParts.insert(weightIndex, QString::number(weightValue));
            processedParts.insert(weightIndex, "weight");
        }
        if (!processedParts.isEmpty() && processedParts.first() != namePart) {
            processedParts.insert(0, namePart);
        }
        line = processedParts.join(" ");
        // ========== 步骤5：清理多余空格 ==========
        line = line.replace(QRegularExpression("\\s+"), " ");
        processedLines.append(line);
    }
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]转化为易读格式后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    // 3. 补全index
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[格式化-补全index] 共%1行").arg(lines.size()));
    QRegularExpression hasIndexRegex(R"xx(\bindex\s+\d+\b)xx");          // 匹配index 数字
    QRegularExpression indexValueRegex(R"xx(index\s+(\d+))xx");         // 提取index数值
    QRegularExpression createGroupRegex(R"xx(^create_group\s+)xx");     // 匹配create_group行
    // ========== 步骤1：扫描所有行，收集已使用的index值 ==========
    QSet<int> usedIndexes; // 存储所有已使用的index
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        if (createGroupRegex.match(line).hasMatch() || line.isEmpty()) {
            continue; // 跳过create_group行和空行
        }
        QRegularExpressionMatch indexMatch = indexValueRegex.match(line);
        if (indexMatch.hasMatch()) {
            int idx = indexMatch.captured(1).toInt();
            if (idx > 0) {
                usedIndexes.insert(idx); // 收集有效index
            }
        }
    }
    // ========== 步骤2：找到从1开始的第一个未使用的index ==========
    int currentIndex = 1;
    while (usedIndexes.contains(currentIndex)) {
        currentIndex++; // 跳过已使用的index，找到第一个可用值
    }
    // ========== 步骤3：遍历行，补全缺失的index ==========
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        if (line.isEmpty()) continue;
        // 跳过create_group行
        if (createGroupRegex.match(line).hasMatch()) {
            processedLines.append(line);
            continue;
        }
        // 检查是否已有有效index
        bool hasValidIndex = false;
        QRegularExpressionMatch indexMatch = indexValueRegex.match(line);
        if (indexMatch.hasMatch()) {
            int existingIndex = indexMatch.captured(1).toInt();
            if (existingIndex > 0) {
                hasValidIndex = true;
            }
        }
        // 为无index的条目分配唯一index
        if (!hasValidIndex) {
            // 确保分配的index未被使用
            while (usedIndexes.contains(currentIndex)) {
                currentIndex++;
            }
            // 追加index字段
            line += QString(" index %1").arg(currentIndex);
            writeDebug(QString("[格式化-补全index] 为条目[%1]分配index=%2").arg(line.split(QRegularExpression("\\s+")).first()).arg(currentIndex));
            // 将新分配的index加入已使用集合，避免后续重复分配
            usedIndexes.insert(currentIndex);
            currentIndex++; // 准备下一个可用index
        }
        line = line.replace(QRegularExpression("\\s+"), " ");
        processedLines.append(line);
    }
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]补全index后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

    // 4. 合并create_group块
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[格式化-合并组] 共%1行").arg(lines.size()));
    QRegularExpression createGroupRegex1(R"xx(^create_group\s+(.+)$)xx");
    QStringList groupParams;
    QStringList normalLines;
    // ========== 步骤1：分离create_group行和普通行，收集分组参数 ==========
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        if (line.isEmpty()) continue;
        QRegularExpressionMatch cgMatch = createGroupRegex1.match(line);
        if (cgMatch.hasMatch()) {
            // 提取create_group后的所有参数
            QString paramsStr = cgMatch.captured(1).trimmed();
            QStringList params = paramsStr.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            // 初始化：第一个create_group行的参数直接存入
            if (groupParams.isEmpty()) {
                groupParams = params;
            } else {
                // 后续create_group行：仅追加未出现过的参数
                for (int j = 1; j < params.size(); ++j) { // j=2跳过create_group和list
                    QString param = params[j];
                    if (!groupParams.contains(param)) {
                        groupParams.append(param);
                    }
                }
            }
        } else {
            normalLines.append(line);
        }
    }
    if (!groupParams.isEmpty()) {
        QString mergedCgLine = QString("create_group %1").arg(groupParams.join(" "));
        mergedCgLine = mergedCgLine.replace(QRegularExpression("\\s+"), " ");
        processedLines.append(mergedCgLine);
        writeDebug(QString("[格式化-合并组] 合并后create_group行：%1").arg(mergedCgLine));
    }
    processedLines.append(normalLines);
    QStringList finalLines;
    for (const QString& line : processedLines) {
        if (!line.trimmed().isEmpty()) {
            finalLines.append(line);
        }
    }
    lines = finalLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]合并create_group块后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");

// 4. 排序
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    lines = content.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    processedLines.clear();
    writeDebug(QString("[格式化-排序] 共%1行").arg(lines.size()));

    // 正则定义
    QRegularExpression createGroupRegex2(R"xx(^create_group\s+)xx"); // 匹配create_group行
    QRegularExpression indexRegex(R"xx(\bindex\s+(\d+)\b)xx");       // 提取index值
    QRegularExpression weightRegex(R"xx(\bweight\s+(\d+)\b)xx");     // 提取weight值
    QRegularExpression isEnableRegex(R"xx(\bisEnable\s+(\d+)\b)xx"); // 提取isEnable值
    QRegularExpression joinGroupRegex2(R"xx(\bjoinGroup\s+\d+\s+(.*)$)xx"); // 提取joinGroup参数部分（跳过数量）
    QRegularExpression joinGroupFullRegex(R"xx(\bjoinGroup\s+.+$)xx"); // 匹配完整joinGroup段

    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines.at(i).trimmed();
        if (line.isEmpty()) continue;

        // ========== 步骤1：create_group行直接保留 ==========
        if (createGroupRegex2.match(line).hasMatch()) {
            processedLines.append(line);
            continue;
        }

        // ========== 步骤2：提取核心字段值（并移除原行中的对应字段，避免重复） ==========
        QString originalLine = line;
        QString namePart = originalLine.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).first(); // 提取名称（第一个部分）
        
        // 提取index并移除原行中的index段
        QString indexVal = "";
        QRegularExpressionMatch indexMatch = indexRegex.match(originalLine);
        if (indexMatch.hasMatch()) {
            indexVal = indexMatch.captured(1);
            originalLine = originalLine.replace(indexRegex, ""); // 移除原行的index段
        }

        // 提取weight并移除原行中的weight段
        QString weightVal = "";
        QRegularExpressionMatch weightMatch = weightRegex.match(originalLine);
        if (weightMatch.hasMatch()) {
            weightVal = weightMatch.captured(1);
            originalLine = originalLine.replace(weightRegex, ""); // 移除原行的weight段
        }

        // 提取isEnable并移除原行中的isEnable段
        QString isEnableVal = "";
        QRegularExpressionMatch isEnableMatch = isEnableRegex.match(originalLine);
        if (isEnableMatch.hasMatch()) {
            isEnableVal = isEnableMatch.captured(1);
            originalLine = originalLine.replace(isEnableRegex, ""); // 移除原行的isEnable段
        }

        // 提取joinGroup并修正数量，移除原行中的joinGroup段
        QString joinGroupPart = "";
        QRegularExpressionMatch joinGroupMatch = joinGroupRegex2.match(originalLine);
        if (joinGroupMatch.hasMatch()) {
            QString joinParams = joinGroupMatch.captured(1).trimmed();
            QStringList paramsList = joinParams.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            int paramCount = paramsList.size(); // 重新计算参数数量，保证准确
            joinGroupPart = QString("joinGroup %1 %2").arg(paramCount).arg(joinParams);
            originalLine = originalLine.replace(joinGroupFullRegex, ""); // 移除原行的joinGroup段
        }

        // ========== 步骤3：按指定顺序重组行内容 ==========
        QStringList sortedParts;
        // 1. index段
        if (!indexVal.isEmpty()) {
            sortedParts.append(QString("index %1").arg(indexVal));
        }
        // 2. content段+名称段
        sortedParts.append(QString("content %1").arg(namePart));
        // 3. weight段
        if (!weightVal.isEmpty()) {
            sortedParts.append(QString("weight %1").arg(weightVal));
        }
        // 4. isEnable段
        if (!isEnableVal.isEmpty()) {
            sortedParts.append(QString("isEnable %1").arg(isEnableVal));
        }
        // 5. joinGroup段
        if (!joinGroupPart.isEmpty()) {
            sortedParts.append(joinGroupPart);
        }

        // ========== 步骤4：清理格式并添加到结果 ==========
        QString finalLine = sortedParts.join(" ");
        finalLine = finalLine.replace(QRegularExpression("\\s+"), " "); // 合并多余空格

        processedLines.append(finalLine);
        writeDebug(QString("[格式化-排序] 原行：%1 → 新行：%2").arg(line).arg(finalLine));
    }

    // 重新拼接内容
    lines = processedLines;
    content = lines.join("\n");
    writeDebug("[预处理-完成]排序后：\n" + content);
    writeDebug("---------------------------------------------------------------------------------------------");
    return content;
}

// 第三步：生成机器代码
QString RsolProcessor::generateMachineCode(const QString& formattedContent) {
    writeDebug("【生成机器码-开始】格式化内容：\n" + formattedContent);
    QStringList lines = formattedContent.split(QRegularExpression("\\n"), Qt::SkipEmptyParts);
    QStringList machineCode;
    QSet<QString> allGroups;
    allGroups.insert("__BASELIST__"); // 基础组必须存在
    machineCode.append(QString("__GROUP__ __BASELIST__"));
    // 正则定义
    QRegularExpression createGroupRegex(R"xx(^create_group\s+(.+)$)xx"); // 匹配create_group行
    QRegularExpression indexRegex(R"xx(^index\s+(\d+)\s+)xx");           // 提取条目行的index值（行首）
    QRegularExpression contentRegex(R"xx(content\s+([^\s]+))xx");          // 提取content后的名称
    QRegularExpression weightRegex(R"xx(weight\s+(\d+))xx");            // 提取weight值
    QRegularExpression isEnableRegex(R"xx(isEnable\s+(\d+))xx");        // 提取isEnable值
    QRegularExpression joinGroupRegex(R"xx(joinGroup\s+\d+\s+(.*)$)xx"); // 提取joinGroup后的参数列表（跳过数量）

    // ========== 第一步：解析create_group行，生成__GROUP__指令 ==========
    for (const QString& line : lines) {
        QString trimLine = line.trimmed();
        if (trimLine.isEmpty()) continue;

        QRegularExpressionMatch cgMatch = createGroupRegex.match(trimLine);
        if (cgMatch.hasMatch()) {
            // 提取create_group后的所有组参数（如 "list A0 A T B C AA BB CC GG"）
            QString paramsStr = cgMatch.captured(1).trimmed();
            QStringList groupParams = paramsStr.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            
            // 收集组名并生成__GROUP__指令
            for (const QString& group : groupParams) {
                if (!group.isEmpty()) {
                    allGroups.insert(group); // 加入全局组集合
                    machineCode.append(QString("__GROUP__ %1").arg(group)); // 一条一行加入机器码
                }
            }
            // 强制添加基础组的__GROUP__指令（确保基础组指令存在）
            machineCode.append(QString("__GROUP__ %1").arg("__BASELIST__"));
            writeDebug(QString("[生成机器码] 解析create_group，生成%1条__GROUP__指令（含基础组）").arg(groupParams.size() + 1));
            break; // 只处理第一个create_group行（已合并为唯一行）
        }
    }

    // ========== 第二步：解析每个条目行，生成属性指令 ==========
    for (const QString& line : lines) {
        QString trimLine = line.trimmed();
        if (trimLine.isEmpty()) continue;

        // 跳过create_group行（已处理）
        if (createGroupRegex.match(trimLine).hasMatch()) {
            continue;
        }

        // 1. 提取index值（核心标识，所有属性关联此index）
        QString indexVal = "";
        QRegularExpressionMatch indexMatch = indexRegex.match(trimLine);
        if (indexMatch.hasMatch()) {
            indexVal = indexMatch.captured(1);
        }
        if (indexVal.isEmpty()) {
            writeDebug(QString("[生成机器码] 警告：条目行[%1]无有效index，跳过").arg(trimLine));
            continue;
        }

        // 2. 生成__INDEX__指令
        machineCode.append(QString("__INDEX__ %1").arg(indexVal));

        // 3. 提取content名称，生成__CONTENT__指令
        QString contentName = "";
        QRegularExpressionMatch contentMatch = contentRegex.match(trimLine);
        if (contentMatch.hasMatch()) {
            contentName = contentMatch.captured(1);
            machineCode.append(QString("__CONTENT__ %1 %2").arg(indexVal).arg(contentName));
        }

        // 4. 提取weight值，生成__WEIGHT__指令
        QString weightVal = "";
        QRegularExpressionMatch weightMatch = weightRegex.match(trimLine);
        if (weightMatch.hasMatch()) {
            weightVal = weightMatch.captured(1);
            machineCode.append(QString("__WEIGHT__ %1 %2").arg(indexVal).arg(weightVal));
        }

        // 5. 提取isEnable值，生成__ISENABLE__指令（无则不生成）
        QString isEnableVal = "";
        QRegularExpressionMatch isEnableMatch = isEnableRegex.match(trimLine);
        if (isEnableMatch.hasMatch()) {
            isEnableVal = isEnableMatch.captured(1);
            machineCode.append(QString("__ISENABLE__ %1 %2").arg(indexVal).arg(isEnableVal));
        }

        // 6. 提取joinGroup参数，生成多条__JOINGROUP__指令
        QRegularExpressionMatch joinGroupMatch = joinGroupRegex.match(trimLine);
        if (joinGroupMatch.hasMatch()) {
            QString joinParamsStr = joinGroupMatch.captured(1).trimmed();
            QStringList joinParams = joinParamsStr.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
            for (const QString& group : joinParams) {
                if (!group.isEmpty()) {
                    machineCode.append(QString("__JOINGROUP__ %1 %2").arg(indexVal).arg(group));
                }
            }
        }

        // ========== 新增核心逻辑：所有content强制关联基础组__BASELIST__ ==========
        machineCode.append(QString("__JOINGROUP__ %1 %2").arg(indexVal).arg("__BASELIST__"));
        writeDebug(QString("[生成机器码] 解析条目[index=%1]，生成属性指令完成").arg(indexVal));
    }
    machineCode.append(QString("__END__"));
    // ========== 最终拼接机器码（一行一条指令） ==========
    QString finalMachineCode = machineCode.join("\n");
    writeDebug("【生成机器码-完成】最终机器码：\n" + finalMachineCode);
    return finalMachineCode;
}


CoreCalculation::OptionList RsolProcessor::packList(QString machineCode)
{
    QTextStream CodeIN = QTextStream(&machineCode);
    CoreCalculation::OptionList optionList;
    int index = 0;
    QString _word_ = "";
    while (CodeIN >> _word_) {
        if (_word_ == "__GROUP__" && (CodeIN >> _word_)) {
            optionList.addGroup(_word_);
        }
        else if (_word_ == "__INDEX__" && (CodeIN >> index)) {
            optionList.addOption(index);
        }
        else if (_word_ == "__CONTENT__" && (CodeIN >> index) && (CodeIN >> _word_)) {
            optionList.setContent(index, _word_);
        }
        else if (_word_ == "__WEIGHT__" && (CodeIN >> index) && (CodeIN >> _word_)) {
            optionList.setWeight(index, _word_.toInt());
        }
        else if (_word_ == "__ISENABLE__" && (CodeIN >> index) && (CodeIN >> _word_)) {
            optionList.setIsSelected(index, _word_.toInt());
        }
        else if (_word_ == "__JOINGROUP__" && (CodeIN >> index) && (CodeIN >> _word_)) {
            optionList.joinGroup(index, _word_);
        }
        else if (_word_ == "__END__") {
            return optionList;
        }
    }
    return optionList;
}

// 核心函数：读取文件 + 全流程处理
CoreCalculation::OptionList RsolProcessor::readOptionList(const QString& filePath) {
    // 读取文件内容
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        writeDebug("【错误】无法打开文件：" + filePath);
        return {};
    }
    QByteArray rawData = file.readAll();
    QString fileContent = QString::fromUtf8(rawData);
    file.close();

    // 三步处理
    QString preprocessed = preprocess(fileContent, filePath);
    QString formatted = formatContent(preprocessed);
    QString machineCode = generateMachineCode(formatted);
    CoreCalculation::OptionList optionList = packList(machineCode);
    return optionList;
}

} // namespace CoreCalculation