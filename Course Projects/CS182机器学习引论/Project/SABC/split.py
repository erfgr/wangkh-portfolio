import os
import jieba

# 获取文件夹路径
folder_path = 'danmu_text'

# 遍历文件夹中的文件
for filename in os.listdir(folder_path):
    if filename.endswith('.csv'):
        file_path = os.path.join(folder_path, filename)

        # 读取txt文件内容
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

        # 使用jieba库进行词语分割
        words = jieba.cut(content)
        segmented_content = ' '.join(words)

        #删除标点符号
        punctuation = '，,。.！!？?：:；;、\（）()“”""''‘’<>《》[]【】~^{}'
        for p in punctuation:
            segmented_content = segmented_content.replace(p, '')

        # 写入分割后的文件
        segmented_file_path = os.path.join(f'segmented_{filename}')
        with open(segmented_file_path, 'w', encoding='utf-8') as segmented_file:
            segmented_file.write(segmented_content)