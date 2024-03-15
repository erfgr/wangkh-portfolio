from snownlp import SnowNLP
import pandas as pd
import os

# 读取文件夹danmu_text下的文件danmu1.csv每一行的弹幕内容
folder_path = 'danmu_text'
file_path = os.path.join(folder_path, 'danmu3.csv')
with open(file_path, 'r', encoding='utf-8') as file:
    content = file.readlines()

# 使用SnowNLP库进行情感分析
sentiments_list = []
for sentence in content:
    s = SnowNLP(sentence)
    sentiments_list.append(s.sentiments)

# 将情感分析结果写在对应的句子后面
sentiments_df = pd.DataFrame(sentiments_list, columns=['sentiments'])
content_df = pd.DataFrame(content, columns=['content'])
result = pd.concat([content_df, sentiments_df], axis=1)
result.to_csv('sentiments.csv', index=False, encoding='utf-8-sig')
# 根据情感分析结果进行标注，大于0.666的为正向，标记为1；小于0.333的为负向，标记为-1；其余为中性，标记为0
result['label'] = result['sentiments'].map(lambda x: 1 if x > 0.666 else (-1 if x < 0.333 else 0))
result.to_csv(f'right_label3.csv', index=False, encoding='utf-8-sig')