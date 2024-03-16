import math

from operate import *

Direction = [[1, 0], [0, 1], [-1, 0], [0, -1]]

class state:
    def __init__(self, move, eval):
        self.move = move
        self.eval = eval

class Minimax:
    def __init__(self, matrix):
        self.Map = matrix
        self.flag = [[0] * 4 for _ in range(4)]

    def smooth(self):
        retval = 0
        for i in range(4):
            for j in range(4):
                if self.Map[i][j] != 0:
                    for k in range(2):
                        vector = Direction[k]
                        tx = i + vector[0]
                        ty = j + vector[1]
                        while 0 <= tx < 4 and 0 <= ty < 4:
                            if self.Map[tx][ty] != 0:
                                break
                            tx += vector[0]
                            ty += vector[1]
                        if 0 <= tx < 4 and 0 <= ty < 4:
                            retval -= abs(math.log2(self.Map[i][j]) - math.log2(self.Map[tx][ty]))
        return retval

    def monotonicity(self):
        retval = [0, 0, 0, 0]
        for x in range(4):
            y = 0
            ty = 1
            while ty < 4:
                while ty < 4:
                    if self.Map[x][ty] != 0:
                        break
                    ty += 1
                ty = min(ty, 3)
                if self.Map[x][y] == 0:
                    value1 = 0
                else:
                    value1 = math.log2(self.Map[x][y])
                if self.Map[x][ty] == 0:
                    value2 = 0
                else:
                    value2 = math.log2(self.Map[x][ty])
                if self.Map[x][y] > self.Map[x][ty]:
                    retval[0] -= value1 - value2
                if self.Map[x][y] < self.Map[x][ty]:
                    retval[1] -= value2 - value1
                y = ty
                ty += 1
        for y in range(4):
            x = 0
            tx = 1
            while tx < 4:
                while tx < 4:
                    if self.Map[tx][y] != 0:
                        break
                    tx += 1
                tx = min(tx, 3)
                if self.Map[x][y] == 0:
                    value1 = 0
                else:
                    value1 = math.log2(self.Map[x][y])
                if self.Map[tx][y] == 0:
                    value2 = 0
                else:
                    value2 = math.log2(self.Map[tx][y])
                if self.Map[x][y] > self.Map[tx][y]:
                    retval[2] -= value1 - value2
                if self.Map[x][y] < self.Map[tx][y]:
                    retval[3] -= value2 - value1
                x = tx
                tx += 1
        return max(retval[0], retval[1]) + max(retval[2], retval[3])

    def empty(self):
        zeros = 0
        for i in range(4):
            for j in range(4):
                if self.Map[i][j] == 0:
                    zeros += 1
        if zeros != 0:
            return math.log(zeros)
        return 0

    def MaxNum(self):
        ans = 0
        for i in range(4):
            for j in range(4):
                ans = max(ans, self.Map[i][j])
        return math.log2(ans)

    def dfs(self, x, y):
        self.flag[x][y] = 1
        for vector in Direction:
            tx = x + vector[0]
            ty = y + vector[1]
            if 0 <= tx < 4 and 0 <= ty < 4:
                if self.Map[tx][ty] == self.Map[x][y] and self.flag[tx][ty] == 0:
                    self.dfs(tx, ty)

    def islands(self):
        retval = 0
        self.flag = [[0] * 4 for _ in range(4)]
        for i in range(4):
            for j in range(4):
                if self.Map[i][j] != 0 and self.flag[i][j] == 0:
                    retval += 1
                    self.dfs(i, j)
        return retval

    def evaluate(self):
        SmoothWeight = 0.1
        MonotonicityWeight = 1.3
        EmptyWeight = 2.7
        MaxWeight = 1.0
        return self.smooth() * SmoothWeight + self.monotonicity() * MonotonicityWeight + self.empty() * EmptyWeight + self.MaxNum() * MaxWeight

    def AvailableMove(self, vector):
        for i in range(4):
            for j in range(4):
                if 4 > i + vector[0] >= 0 != self.Map[i][j] and 0 <= j + vector[1] < 4:
                    if self.Map[i + vector[0]][j + vector[1]] == self.Map[i][j] or self.Map[i + vector[0]][j + vector[1]] == 0:
                        return True
        return False

    def Move(self, matrix, vector):
        new_matrix = []
        score = 0
        if vector == Direction[0]:
            new_matrix, score = down(matrix)
        if vector == Direction[1]:
            new_matrix, score = right(matrix)
        if vector == Direction[2]:
            new_matrix, score = up(matrix)
        if vector == Direction[3]:
            new_matrix, score = left(matrix)
        return new_matrix

    def search(self, alpha, beta, depth):
        retval = state([0, 0], -1e7)
        NextState = Minimax(self.Map)
        StateMove = [0, 0]
        if depth % 2 == 0:
            StateScore = alpha
            for vector in Direction:
                if self.AvailableMove(vector):
                    if StateMove == [0, 0]:
                        StateMove = vector
                    NextState.Map = self.Move(self.Map, vector)
                    if depth == 0:
                        retval.move = vector
                        retval.eval = NextState.evaluate()
                    else:
                        retval = NextState.search(alpha, beta, depth - 1)
                    if retval.eval > StateScore:
                        StateScore = retval.eval
                        StateMove = vector
                    if StateScore > beta:
                        return state(StateMove, beta)
        else:
            StateScore = beta
            MaxScore = -1e7
            lst = []
            for i in range(4):
                for j in range(4):
                    if self.Map[i][j] == 0:
                        for k in [2, 4]:
                            self.Map[i][j] = k
                            tmp = -self.smooth() + self.islands()
                            if tmp > MaxScore:
                                MaxScore = tmp
                                lst.clear()
                            if tmp == MaxScore:
                                lst.append([i, j, k])
                            self.Map[i][j] = 0
            for element in lst:
                NextState.Map[element[0]][element[1]] = element[2]
                retval = NextState.search(alpha, StateScore, depth - 1)
                NextState.Map[element[0]][element[1]] = 0
                if retval.eval < StateScore:
                    StateScore = retval.eval
                if StateScore < alpha:
                    return state([0, 0], alpha)
        return state(StateMove, StateScore)