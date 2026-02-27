//
// Created by Administrator on 2026/2/14.
//

#include "readFile.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"
#include "VariablesStore/globalVariables.h"
#include <QDirIterator>

namespace CoreCalculation {
OptionList readFile::readByPath(const QString& _path) {
    GlobalVariables* gv = GLOBAL_VARIABLES;
    OptionList optionList = RsolProcessor(false).readOptionList(_path);

    // 添加选项列表
    gv->base_option_list = optionList;
    gv->current_option_list = optionList;
    gv->active_option_list = optionList;

    // 计算文件量
    gv->total_weight = std::accumulate(optionList.begin(), optionList.end(), 0.0L,
        [](long double sum, const Base::OptionItem& option) {
            return sum + option.getWeight();
    });
    // 标记已导入文件
    gv->is_import_file = true;

    gv->total_select_count = 0;
    gv->memory_list.clear();

    return optionList;
}

void readFile::readByStr(const QString& _str) {
}

QList<readDirt::_file> readDirt::getFilesBySuffix(const QString& folderPath, const QString& suffix, bool recursive) {
    QList<_file> result;

    // ========== 1. 校验文件夹有效性 ==========
    QDir targetDir(folderPath);
    // 校验：路径必须存在、必须是文件夹、有读取权限
    if (!targetDir.exists() || !targetDir.isReadable()) {
        return result; // 无效路径直接返回空列表
    }

    // ========== 2. 统一处理后缀名 ==========
    QString processedSuffix = suffix.trimmed();
    // 自动去掉开头的点，统一格式
    if (processedSuffix.startsWith('.')) {
        processedSuffix = processedSuffix.mid(1);
    }

    // 构建名称过滤器
    QStringList nameFilters;
    if (!processedSuffix.isEmpty()) {
        nameFilters << QString("*.%1").arg(processedSuffix);
    } else {
        nameFilters << "*"; // 后缀为空时匹配所有文件
    }

    // ========== 3. 遍历文件，生成结果 ==========
    constexpr auto fileFilter = QDir::Files | QDir::NoDotAndDotDot; // 只取文件，排除.和..

    if (recursive) {
        // 递归遍历子文件夹
        QDirIterator dirIter(
            targetDir.absolutePath(),
            nameFilters,
            fileFilter,
            QDirIterator::Subdirectories
        );
        while (dirIter.hasNext()) {
            dirIter.next();
            const QFileInfo& fileInfo = dirIter.fileInfo();

            _file fileItem;
            fileItem.filePath = fileInfo.absoluteFilePath(); // 绝对路径
            fileItem.fileName = fileInfo.fileName();         // 带后缀的文件名
            fileItem.fileExtension = fileInfo.suffix();      // 不带点的后缀
            result.append(fileItem);
        }
    } else {
        // 仅遍历当前文件夹
        targetDir.setNameFilters(nameFilters);
        targetDir.setFilter(fileFilter);
        const QFileInfoList fileInfoList = targetDir.entryInfoList();

        for (const QFileInfo& fileInfo : fileInfoList) {
            _file fileItem;
            fileItem.filePath = fileInfo.absoluteFilePath();
            fileItem.fileName = fileInfo.fileName();
            fileItem.fileExtension = fileInfo.suffix();
            result.append(fileItem);
        }
    }

    return result;
}
} // CoreCalculation