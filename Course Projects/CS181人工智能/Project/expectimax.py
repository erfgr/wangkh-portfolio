from operate import *
import random

def addtile(Map):       # 模拟随机生成格子
    row = random.randint(0, 3)
    col = random.randint(0, 3)
    while (Map[row][col] != 0):
        row = random.randint(0, 3)
        col = random.randint(0, 3)
    Map[row][col] = random.choice([2, 4])
    return Map

def move_exists(Map):
        for i in range(4):
            for j in range(3):
                if Map[i][j] == Map[i][j + 1]:
                    return True
        for i in range(3):
            for j in range(4):
                if Map[i][j] == Map[i + 1][j]:
                    return True
        return False

def calculate(matrix):       #计算在一个状态下进行100次随机游戏后得分的平均值
    score = 0
    Map = [[0 for i in range(4)] for j in range(4)]
    for i in range(100):
        for row in range(4):
            for col in range(4):
                Map[row][col] = matrix[row][col]
        Map = addtile(Map)
        if (not any(0 in row for row in Map) and (move_exists(Map) == False)):
            continue
        value = 0
        theta = 0.9
        while True:
            rand = random.randint(0, 3)
            if rand == 0:
                newMap, addscore = left(Map)
                if newMap != Map:
                    value += theta * addscore
                    theta *= 0.9
                    Map = newMap
                    Map = addtile(Map)
                    if (not any(0 in row for row in Map) and (move_exists(Map) == False)) or any(2048 in row for row in Map):
                        break
            if rand == 1:
                newMap, addscore = right(Map)
                if newMap != Map:
                    value += theta * addscore
                    theta *= 0.9
                    Map = newMap
                    Map = addtile(Map)
                    if (not any(0 in row for row in Map) and (move_exists(Map) == False)) or any(2048 in row for row in Map):
                        break
            if rand == 2:
                newMap, addscore = up(Map)
                if newMap != Map:
                    value += theta * addscore
                    theta *= 0.9
                    Map = newMap
                    Map = addtile(Map)
                    if (not any(0 in row for row in Map) and (move_exists(Map) == False)) or any(2048 in row for row in Map):
                        break
            if rand == 3:
                newMap, addscore = down(Map)
                if newMap != Map:
                    value += theta * addscore
                    theta *= 0.9
                    Map = newMap
                    Map = addtile(Map)
                    if (not any(0 in row for row in Map) and (move_exists(Map) == False)) or any(2048 in row for row in Map):
                        break
        score += value
    return score / 100

def expectimax(Map):
    matrix, AddScore = left(Map)
    if matrix != Map:
        value = calculate(matrix) + AddScore
    else:
        value = -1

    matrix_right, rightscore = right(Map)
    if matrix_right != Map:
        value_right = calculate(matrix_right) + rightscore
        if value_right > value:
            matrix = matrix_right
            value = value_right + rightscore
            AddScore = rightscore

    matrix_up, upscore = up(Map)
    if matrix_up != Map:
        value_up = calculate(matrix_up) + upscore
        if value_up > value:
            matrix = matrix_up
            value = value_up + upscore
            AddScore = upscore

    matrix_down, downscore = down(Map)
    if matrix_down != Map:
        value_down = calculate(matrix_down) + downscore
        if value_down > value:
            matrix = matrix_down
            value = value_down + downscore
            AddScore = downscore

    return matrix, AddScore