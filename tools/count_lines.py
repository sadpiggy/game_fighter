import os
"""
计算有效的.cpp和.hpp文件的代码行数. 忽略注释和空行
"""


def count_code_lines(file_path):
    count = 0
    in_block_comment = False
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            stripped = line.strip()
            if not stripped:
                continue  # 跳过空行
            if in_block_comment:
                if '*/' in stripped:
                    in_block_comment = False
                continue  # 跳过块注释中的行
            if stripped.startswith('//'):
                continue  # 跳过行注释
            if stripped.startswith('/*'):
                in_block_comment = not '*/' in stripped
                continue  # 跳过块注释行
            count += 1
    return count

def count_lines_in_dir(root='.'):
    total_lines = 0
    for dirpath, _, filenames in os.walk(root):
        # print(f"dirpath={dirpath}")
        if ".git" in dirpath or "./build" in dirpath:
            continue
        for filename in filenames:
            if filename.endswith(('.cpp', '.hpp')):
                path = os.path.join(dirpath, filename)
                file_lines = count_code_lines(path)
                print(f"{path}: {file_lines} lines")
                total_lines += file_lines
    print(f"\nTotal code lines: {total_lines}")

if __name__ == "__main__":
    count_lines_in_dir()
