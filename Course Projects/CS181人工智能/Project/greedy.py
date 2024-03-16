import random
from operate import *
import math

def calculatevalue_old(Map):
    num_of_empty = 0  # 空格数量越多越好
    for i in range(4):
        for j in range(4):
            if Map[i][j] == 0:
                num_of_empty += 1
    differ = 0  # 相邻格子差距越小越好
    DirectVector = [[-1, 0],[1, 0],[0,-1],[0,1]]
    for i in range(4):
        for j in range(4):
            minvalue = 1000000
            surrounding_num = 0  # 大的数尽量放在角落
            for k in range(4):
                ti, tj = i, j
                while 0 <= ti + DirectVector[k][0] < 4 and 0 <= tj + DirectVector[k][1] < 4:
                    ti += DirectVector[k][0]
                    tj += DirectVector[k][1]
                    if Map[ti][tj] != 0:
                        break
                if ti != i or tj != j:
                    minvalue = min(minvalue, abs(Map[i][j] - Map[ti][tj]))
                    surrounding_num += 1
            if surrounding_num > 0:
                differ += (1 << surrounding_num) * minvalue
    maxgrid = 0
    for i in range(4):
        for j in range(4):
            if maxgrid < Map[i][j]:
                maxgrid = Map[i][j]
    maxgrid = math.log(maxgrid, 2)
    #单调性 判断四个方向最大的非单调方向
    upcount = 0
    downcount = 0
    leftcount = 0
    rightcount = 0
    for i in range(4):
        for j in range(3):
            n = j + 1
            while (n < 3) and (Map[i][n] == 0):
                n = n + 1
            if Map[i][j] == 0:
                current = 0
            else:
                current = math.log(Map[i][j] ,2)
            if Map[i][n] == 0:
                next = 0
            else:
                next = math.log(Map[i][n] ,2)
            if current > next:
                leftcount += next - current
            else:
                rightcount += current - next
    for i in range(4):
        for j in range(3):
            n = j + 1
            while (n < 3) and (Map[n][i] == 0):
                n = n + 1
            if Map[j][i] == 0:
                current = 0
            else:
                current = math.log(Map[j][i] ,2)
            if Map[n][i] == 0:
                next = 0
            else:
                next = math.log(Map[n][i] ,2)
            if current > next:
                upcount += next - current
            else:
                downcount += current - next
    value = 50000 * num_of_empty - 1.5 * differ + 1 * maxgrid + 1 * (max(leftcount, rightcount) + max(upcount, downcount))
    return value


def evaluate(Map):
    # matrix, AddScore = RandChoice(Map)
    matrix, AddScore = left(Map)
    value = calculatevalue_old(matrix)

    matrix_right, rightscore = right(Map)
    value_right = calculatevalue_old(matrix_right)
    if value_right > value:
        matrix = matrix_right
        value = value_right
        AddScore = rightscore

    matrix_up, upscore = up(Map)
    value_up = calculatevalue_old(matrix_up)
    if value_up > value:
        matrix = matrix_up
        value = value_up
        AddScore = upscore

    matrix_down, downscore = down(Map)
    value_down = calculatevalue_old(matrix_down)
    if value_down > value:
        matrix = matrix_down
        value = value_down
        AddScore = downscore

    return matrix, AddScore


def RandChoice(Map):
    AddScore = -1
    while AddScore == -1:
        rand = random.randint(0, 3)
        if rand == 0:
            TmpMatrix, AddScore = left(Map)
            if TmpMatrix == Map:
                AddScore = -1
            matrix = TmpMatrix
        if rand == 1:
            TmpMatrix, AddScore = right(Map)
            if TmpMatrix == Map:
                AddScore = -1
            matrix = TmpMatrix
        if rand == 2:
            TmpMatrix, AddScore = up(Map)
            if TmpMatrix == Map:
                AddScore = -1
            matrix = TmpMatrix
        if rand == 3:
            TmpMatrix, AddScore = down(Map)
            if TmpMatrix == Map:
                AddScore = -1
            matrix = TmpMatrix
    return matrix, AddScore
