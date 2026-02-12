import os

if __name__ == "__main__":

    # -------------------------- 只改这一行！ --------------------------
    ROOT_DIR = r".."  # 示例：Windows填r"D:\我的代码文件夹"，Mac填r"/Users/xxx/我的代码文件夹"
    # -----------------------------------------------------------------

    # 要统计的文件类型（按需增删，比如只留.py就删其他）
    INCLUDE_EXTS = [".py", ".h", ".evb", ".qrc", ".java", ".cpp", ".md"]
    # 要忽略的文件夹名（直接写文件夹名，不要加../前缀）
    EXCLUDE_DIRS = ["cmake-build-debug", "cmake-build-release","PythonTool", "DLL"]

    # 初始化统计值
    total_lines = 0    # 总行数（含空行/注释）
    valid_lines = 0    # 有效代码行（排除空行+单行注释+仅行尾注释的空行）

    # 遍历文件夹
    for dirpath, dirnames, filenames in os.walk(ROOT_DIR):
        # 过滤要忽略的文件夹
        dirnames[:] = [d for d in dirnames if d not in EXCLUDE_DIRS]
        for filename in filenames:
            # 只统计指定类型文件
            if not any(filename.endswith(ext) for ext in INCLUDE_EXTS):
                continue
            file_path = os.path.join(dirpath, filename)

            # 读取文件（兼容中文编码）
            try:
                with open(file_path, "r", encoding="utf-8") as f:
                    lines = f.readlines()
            except:
                with open(file_path, "r", encoding="gbk") as f:
                    lines = f.readlines()

            # 逐行统计（优化：剔除行尾注释后判断）
            for line in lines:
                total_lines += 1
                line_strip = line.strip()

                # 1. 先剔除行尾的 // 注释（注意区分C++的整除//和注释//）
                # 规则：找到第一个 // 且不是紧跟在数字/字母后（避免把x=5//2当成注释）
                code_part = line_strip
                # 简单判断：如果//前面是空格/开头，才视为注释分隔符
                if "//" in code_part:
                    split_idx = code_part.index("//")
                    # 检查//前面是否是空白（开头或空格）
                    if split_idx == 0 or code_part[split_idx-1].isspace():
                        code_part = code_part[:split_idx].strip()

                # 2. 剔除行尾的 # 注释
                if "#" in code_part:
                    split_idx = code_part.index("#")
                    if split_idx == 0 or code_part[split_idx-1].isspace():
                        code_part = code_part[:split_idx].strip()

                # 3. 剔除注释后为空，则不算有效行
                if not code_part:
                    continue
                valid_lines += 1

    # 只输出核心结果（数字）
    print("======= 统计结果 =======")
    print(f"总行数（含空行/注释）：{total_lines}")
    print(f"有效代码行数：{valid_lines}")