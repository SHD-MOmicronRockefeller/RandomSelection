import os

# ===================== 核心配置项（你可以根据需要修改） =====================
TARGET_PATH = ".."
# 要忽略的文件夹名
IGNORE_FOLDERS = ["build_debug", "build_release",".cache", "DLL"]
# 要忽略的文件后缀（比如.pyc、.log）
IGNORE_SUFFIXES = []
# ==========================================================================

def print_file_tree(start_path, prefix=""):
    """
    递归打印文件树形结构
    :param start_path: 当前遍历的路径
    :param prefix: 层级前缀（控制树形符号）
    """
    # 获取当前路径下的所有文件/文件夹，过滤掉隐藏的.开头文件
    items = [item for item in os.listdir(start_path) if not item.startswith(".")]
    # 按文件夹在前、文件在后排序，保证结构整洁
    items.sort(key=lambda x: (not os.path.isdir(os.path.join(start_path, x)), x))
    
    for idx, item in enumerate(items):
        item_path = os.path.join(start_path, item)
        # 判断是否是最后一个项（控制用└──还是├──）
        is_last = idx == len(items) - 1
        # 树形符号
        symbol = "└── " if is_last else "├── "
        
        # 1. 过滤忽略的文件夹
        if os.path.isdir(item_path):
            if item in IGNORE_FOLDERS:
                continue
            # 打印文件夹
            print(f"{prefix}{symbol}{item}/")
            # 计算下一层的前缀（最后一个文件夹的子项前缀用空格，否则用│   ）
            next_prefix = prefix + ("    " if is_last else "│   ")
            # 递归遍历子文件夹
            print_file_tree(item_path, next_prefix)
        
        # 2. 过滤忽略的文件（按后缀）
        elif os.path.isfile(item_path):
            file_suffix = os.path.splitext(item)[1]
            if file_suffix in IGNORE_SUFFIXES:
                continue
            # 打印文件
            print(f"{prefix}{symbol}{item}")

if __name__ == "__main__":
    # 检查目标路径是否存在
    if not os.path.exists(TARGET_PATH):
        print(f"错误：目标路径 {TARGET_PATH} 不存在！")
    else:
        # 打印根目录
        print(f"{os.path.basename(os.path.abspath(TARGET_PATH))}/")
        # 开始遍历子项
        print_file_tree(TARGET_PATH)