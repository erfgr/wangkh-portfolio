import random
from operate import *

def addtile(Map):  # 模拟随机生成格子
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

def calculate(Map, depth, value):
    if depth <= 4:
        maxvalue = 0
        newMap, leftvalue = left(Map)
        if Map != newMap:
            newMap = addtile(newMap)
            newvalue = value + leftvalue
            if ((not any(0 in row for row in newMap) and (move_exists(newMap) == False))
                    or any(2048 in row for row in newMap)):
                if maxvalue < newvalue:
                    maxvalue = newvalue
            else:
                fvalue = calculate(newMap, depth + 1, newvalue)
                if fvalue > maxvalue:
                    maxvalue = fvalue
        newMap, rightvalue = right(Map)
        if Map != newMap:
            newMap = addtile(newMap)
            newvalue = value + rightvalue
            if ((not any(0 in row for row in newMap) and (move_exists(newMap) == False))
                    or any(2048 in row for row in newMap)):
                if maxvalue < newvalue:
                    maxvalue = newvalue
            else:
                fvalue = calculate(newMap, depth + 1, newvalue)
                if fvalue > maxvalue:
                    maxvalue = fvalue
        newMap, upvalue = up(Map)
        if Map != newMap:
            newMap = addtile(newMap)
            newvalue = value + upvalue
            if ((not any(0 in row for row in newMap) and (move_exists(newMap) == False))
                    or any(2048 in row for row in newMap)):
                if maxvalue < newvalue:
                    maxvalue = newvalue
            else:
                fvalue = calculate(newMap, depth + 1, newvalue)
                if fvalue > maxvalue:
                    maxvalue = fvalue
        newMap, downvalue = down(Map)
        if Map != newMap:
            newMap = addtile(newMap)
            newvalue = value + downvalue
            if ((not any(0 in row for row in newMap) and (move_exists(newMap) == False))
                    or any(2048 in row for row in newMap)):
                if maxvalue < newvalue:
                    maxvalue = newvalue
            else:
                fvalue = calculate(newMap, depth + 1, newvalue)
                if fvalue > maxvalue:
                    maxvalue = fvalue
        return maxvalue
    else:
        return value

def dfs(Map):

    matrix, AddScore = left(Map)
    if matrix != Map:
        value = calculate(matrix, 1, 0) + AddScore
    else:
        value = -1

    matrix_right, rightscore = right(Map)
    if matrix_right != Map:
        value_right = calculate(matrix_right,1,0) + rightscore
        if value_right > value:
            matrix = matrix_right
            value = value_right + rightscore
            AddScore = rightscore

    matrix_up, upscore = up(Map)
    if matrix_up != Map:
        value_up = calculate(matrix_up,1,0) + upscore
        if value_up > value:
            matrix = matrix_up
            value = value_up + upscore
            AddScore = upscore

    matrix_down, downscore = down(Map)
    if matrix_down != Map:
        value_down = calculate(matrix_down,1,0) + downscore
        if value_down > value:
            matrix = matrix_down
            value = value_down + downscore
            AddScore = downscore

    return matrix, AddScore
