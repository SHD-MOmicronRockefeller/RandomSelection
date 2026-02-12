import os
import re
import sys
from typing import Dict, Optional, Set, List
# ===================== 核心配置 =====================
DEBUG_MODE = False
DEBUG_FILE_PATH = "debug.txt"
BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
INCLUDE_SUFFIX = (".h", ".hpp")
EXCLUDE_DIRS = {"cmake-build-debug", "cmake-build-release","PythonTool", "DLL"}
EXCLUDE_FILES = {"ClassSpace.h"}#
# ===================== 调试工具 =====================
def write_debug(content: str, is_new_file: bool = False):
    if not DEBUG_MODE:
        return
    mode = "w" if is_new_file else "a"
    with open(DEBUG_FILE_PATH, mode, encoding="utf-8") as f:
        f.write(content + "\n")
# ===================== 数据结构 =====================
class NamespaceNode:
    def __init__(self, name: str, parent: Optional['NamespaceNode'] = None):
        self.name = name
        self.parent = parent
        self.children: Dict[str, NamespaceNode] = {}
        self.classes: Set[str] = set()
    def add_class(self, cls_name: str):
        cls_name = cls_name.strip()
        if cls_name and cls_name.isidentifier() and not cls_name.startswith('_'):
            self.classes.add(cls_name)
    def get_child(self, child_name: str) -> 'NamespaceNode':
        child_name = child_name.strip()
        if child_name not in self.children:
            self.children[child_name] = NamespaceNode(child_name, self)
        return self.children[child_name]
    def has_content(self) -> bool:
        if self.classes:
            return True
        for child in self.children.values():
            if child.has_content():
                return True
        return False
    def get_full_path(self) -> str:
        path_parts = []
        current = self
        while current and current.name:
            path_parts.append(current.name)
            current = current.parent
        return "::".join(reversed(path_parts)) if path_parts else "全局"
root_node = NamespaceNode("")
# ===================== 核心预处理（终极修复：类不丢失+无残留+无冗余括号） =====================
def preprocess_code(raw_code: str, file_path: str) -> str:
    """
    终极修复：修复AttributeError + 完美支持嵌套命名空间
    1. 修正继承关系提取的语法错误（int无replace）；
    2. 逐行解析，严格保持命名空间栈层级，支持嵌套；
    3. 嵌套命名空间100%匹配原始代码结构；
    """
    write_debug(f"\n------ 格式化文件：{file_path} ------")
    # 第一步：深度预处理（保留原始行结构，关键！）
    code = raw_code
    # 1. 清理注释（避免干扰，保留行结构）
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.DOTALL)
    code = re.sub(r'//.*?$', '', code, flags=re.MULTILINE)
    code = re.sub(r'^\s*#.*$', '', code, flags=re.MULTILINE)
    code = re.sub(r'\bQ_OBJECT\b', '', code, flags=re.IGNORECASE)
    # 2. 清理冗余括号和空白（保留换行）
    while '{{' in code:
        code = code.replace('{{', '{')
    while '}}' in code:
        code = code.replace('}}', '}')
    code = re.sub(r'\t+', ' ', code)
    code = re.sub(r' +', ' ', code)
    code = re.sub(r'\n+', '\n', code)

    # 第二步：逐行解析（严格保持命名空间栈层级）
    ns_stack = []  # 命名空间栈，核心：不提前回退
    result = []
    # 按原始行分割（保留空行但过滤纯空白行）
    lines = [line.rstrip() for line in code.split('\n')]
    lines = [line for line in lines if line.strip() != '']

    # 正则定义（兼容换行/空格分隔的命名空间/类）
    # 命名空间开始：匹配 "namespace XXX {" 或 "namespace XXX \n {"
    ns_start_pattern = re.compile(r'^namespace\s+([a-zA-Z_]\w*)\s*\{?\s*$')
    # 命名空间闭合：仅匹配独立的 "}" 或 "} // namespace XXX"
    ns_end_pattern = re.compile(r'^\s*\}\s*(//.*)?$')
    # 类定义：匹配 "class XXX {" 或 "class XXX : 继承 {"
    class_pattern = re.compile(r'^class\s+([a-zA-Z_]\w*)\s*(?::\s*[\w\s:<>*,&/const]*?)?\s*\{?\s*$')

    for line in lines:
        line_stripped = line.strip()
        # 1. 处理命名空间开始（包括换行分隔的 "{")
        ns_start_match = ns_start_pattern.match(line_stripped)
        if ns_start_match:
            ns_name = ns_start_match.group(1)
            ns_stack.append(ns_name)
            result.append(f"namespace {ns_name} {{")
            write_debug(f"→ 进入命名空间：{ns_name} | 栈：{ns_stack}")
            # 处理换行后的 "{"（如果有）
            continue

        # 2. 处理类定义（包括换行分隔的 "{")
        class_match = class_pattern.match(line_stripped)
        if class_match:
            cls_name = class_match.group(1)
            # ========== 修复关键行：先处理字符串，再取长度 ==========
            # 错误原因：len返回int，不能调用replace；先获取匹配字符串，去掉{后再取长度
            match_str = class_match.group(0).replace('{','').strip()
            inherit_part = line_stripped[len(match_str):].strip()
            # ========== 修复结束 ==========
            inherit_str = inherit_part if inherit_part.startswith(':') else ''
            # 类归属当前栈层级
            result.append(f"class {cls_name} {inherit_str} {{ }};")
            write_debug(f"→ 添加类：{cls_name} | 归属栈：{ns_stack}")
            continue

        # 3. 处理命名空间闭合（仅当遇到独立的 "}" 时回退）
        ns_end_match = ns_end_pattern.match(line_stripped)
        if ns_end_match and ns_stack:
            popped_ns = ns_stack.pop()
            result.append("}")
            write_debug(f"→ 退出命名空间：{popped_ns} | 栈：{ns_stack}")
            continue

    # 补全未闭合的命名空间（仅兜底，原始代码会正确闭合）
    while ns_stack:
        popped_ns = ns_stack.pop()
        result.append("}")
        write_debug(f"→ 补全闭合：{popped_ns} | 栈：{ns_stack}")

    # 第三步：格式化缩进（保持嵌套层级）
    def format_with_indent(lines_list):
        indent_level = 0
        indent_step = 4
        formatted = []
        for line in lines_list:
            if line.startswith('}'):
                indent_level = max(0, indent_level - 1)
            current_indent = ' ' * indent_level * indent_step
            formatted.append(f"{current_indent}{line}")
            if line.endswith('{') and 'namespace' in line:
                indent_level += 1
        return '\n'.join(formatted)

    final_code = format_with_indent(result)
    final_code = re.sub(r'\n+', '\n', final_code).strip()
    write_debug(f"【处理后完整代码】\n{final_code}")
    return final_code
# ===================== 其余函数（无修改，保持原样） =====================
def read_file_safely(file_path: str) -> Optional[str]:
    encodings = ["utf-8", "gbk", "gb2312", "latin-1", "utf-16"]
    for enc in encodings:
        try:
            with open(file_path, "r", encoding=enc) as f:
                content = f.read()
                write_debug(f"成功读取文件：{file_path}（编码：{enc}）")
                return content
        except Exception as e:
            write_debug(f"读取失败 {file_path}（编码：{enc}）：{str(e)[:100]}")
            continue
    print(f"[警告] 读取失败：{file_path}")
    return None
def parse_code_to_nodes(processed_code: str, file_path: str):
    """
    重构解析逻辑：精准控制命名空间栈层级，和preprocess_code逻辑完全对齐
    1. 逐行解析，仅识别独立的命名空间{和}，类定义行不触发栈回退；
    2. 严格按行处理命名空间入栈/出栈，避免统计}数量导致的提前回退；
    3. 类严格归属当前栈层级，不丢失；
    """
    write_debug(f"\n------ 解析文件：{file_path} ------")
    ns_stack: List[NamespaceNode] = [root_node]
    # 优化类匹配正则：仅匹配class XXX; 或 class XXX { }; 格式
    class_pattern = re.compile(r'^\s*class\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(?:[:\s][\w\s:<>*,&/const]*?)?\s*\{\s*\};\s*$')
    # 命名空间开始正则：匹配 "namespace XXX {"
    ns_start_pattern = re.compile(r'^\s*namespace\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\{\s*$')
    # 命名空间闭合正则：仅匹配独立的 "}"
    ns_end_pattern = re.compile(r'^\s*\}\s*$')
    
    code_lines = processed_code.split('\n')
    
    for line_num, line in enumerate(code_lines, 1):
        original_line = line.strip()
        if not original_line:
            continue
        write_debug(f"解析行{line_num}：{original_line}")
        
        # 1. 匹配命名空间开始（仅独立的 namespace XXX { 行）
        ns_start_match = ns_start_pattern.match(original_line)
        if ns_start_match:
            ns_name = ns_start_match.group(1)
            current_ns = ns_stack[-1].get_child(ns_name)
            ns_stack.append(current_ns)
            write_debug(f"→ 匹配命名空间：{ns_name} | 当前层级：{current_ns.get_full_path()}")
            continue
        
        # 2. 匹配命名空间闭合（仅独立的 } 行）
        ns_end_match = ns_end_pattern.match(original_line)
        if ns_end_match and len(ns_stack) > 1:
            popped_ns = ns_stack.pop()
            write_debug(f"→ 回退命名空间：{popped_ns.name} | 新层级：{ns_stack[-1].get_full_path()}")
            continue
        
        # 3. 匹配类定义（仅 class XXX { }; 格式）
        class_match = class_pattern.match(original_line)
        if class_match:
            cls_name = class_match.group(1)
            current_ns_path = ns_stack[-1].get_full_path()
            ns_stack[-1].add_class(cls_name)
            write_debug(f"→ 匹配类：{cls_name} | 归属层级：{current_ns_path}")
            continue
    
    write_debug(f"解析完成 | 最终栈状态：{[n.name for n in ns_stack]}")
def scan_all_target_files():
    if not os.path.isdir(BASE_DIR):
        print(f"[错误] 目录不存在：{BASE_DIR}")
        sys.exit(1)
    if DEBUG_MODE:
        write_debug("------ 开始扫描解析 ------\n", is_new_file=True)
        write_debug(f"扫描根目录：{BASE_DIR}")
        write_debug(f"排除文件夹：{EXCLUDE_DIRS}")
        write_debug(f"排除文件：{EXCLUDE_FILES}\n")
    processed_file_count = 0
    for root, dirs, files in os.walk(BASE_DIR):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        for file in files:
            if root == BASE_DIR and file in EXCLUDE_FILES:
                write_debug(f"跳过排除文件：{os.path.join(root, file)}")
                continue
            if file.endswith(INCLUDE_SUFFIX):
                file_path = os.path.join(root, file)
                write_debug(f"\n\n\n========== 开始处理文件：{file_path} ==========")
                
                raw_code = read_file_safely(file_path)
                if not raw_code:
                    continue
                
                processed_code = preprocess_code(raw_code, file_path)
                parse_code_to_nodes(processed_code, file_path)
                processed_file_count += 1
    write_debug(f"\n===== 扫描完成：共解析 {processed_file_count} 个文件 =====")
    print(f"[完成] 解析 {processed_file_count} 个文件")
def clean_duplicate_classes():
    write_debug("\n===== 开始清理重复类 =====\n")
    all_classes = {}
    duplicate_classes = []
    def traverse_collect(node: NamespaceNode):
        for cls in node.classes:
            is_global = node.name == ""
            full_path = node.get_full_path()
            if cls in all_classes:
                duplicate_classes.append((cls, full_path, all_classes[cls][0]))
            else:
                all_classes[cls] = (full_path, node, is_global)
        for child in node.children.values():
            traverse_collect(child)
    traverse_collect(root_node)
    for cls, new_path, old_path in duplicate_classes:
        target_path, target_node, target_is_global = all_classes[cls]
        if cls == "RS_Version":
            for node in [n for n in all_classes.values() if not n[2]]:
                if cls in node[1].classes:
                    node[1].classes.remove(cls)
                    write_debug(f"→ 移除重复类{cls}：{node[0]}（强制保留全局）")
        else:
            if not target_is_global and cls in root_node.classes:
                root_node.classes.remove(cls)
                write_debug(f"→ 移除重复类{cls}：全局（保留{target_path}）")
    write_debug("===== 重复类清理完成 =====")
def print_namespace_tree(node: NamespaceNode, indent: int = 0):
    if not node.has_content() and node.name != "":
        return
    indent_str = "    " * indent
    if node.name:
        print(f"{indent_str}namespace {node.name} {{")
    
    for cls in sorted(node.classes):
        print(f"{indent_str}    class {cls};")
    
    child_nodes = sorted(node.children.values(), key=lambda x: x.name)
    has_class = len(node.classes) > 0
    for idx, child in enumerate(child_nodes):
        if child.has_content():
            if has_class and idx == 0:
                print()
            print_namespace_tree(child, indent + 1)
    
    if node.name:
        print(f"{indent_str}}} // namespace {node.name}")
def print_final_result():
    clean_duplicate_classes()
    print("#ifndef CLASSSPACE_H")
    print("#define CLASSSPACE_H")
    print()
    
    if root_node.classes:
        for cls in sorted(root_node.classes):
            print(f"class {cls};")
        if root_node.children:
            print()
    
    for ns_name in sorted(root_node.children.keys()):
        ns_node = root_node.children[ns_name]
        if ns_node.has_content():
            print_namespace_tree(ns_node)
    
    print()
    print("#endif // CLASSSPACE_H")
if __name__ == "__main__":
    scan_all_target_files()
    print("\n===== 生成的ClassSpace.h =====\n")
    print_final_result()
    
    if DEBUG_MODE:
        abs_debug_path = os.path.abspath(DEBUG_FILE_PATH)
        print(f"\n[调试] 详细日志已写入：{abs_debug_path}")