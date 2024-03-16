def stack(matrix):
    new_matrix = [[0] * 4 for _ in range(4)]
    for i in range(4):
        fill_position = 0
        for j in range(4):
            if matrix[i][j] != 0:
                new_matrix[i][fill_position] = matrix[i][j]
                fill_position += 1
    return new_matrix


def combine(matrix):
    score = 0
    new_matrix = matrix
    for i in range(4):
        for j in range(3):
            if new_matrix[i][j] != 0 and new_matrix[i][j] == new_matrix[i][j + 1]:
                new_matrix[i][j] *= 2
                new_matrix[i][j + 1] = 0
                score += new_matrix[i][j]
    return new_matrix, score


def reverse(matrix):
    new_matrix = []
    for i in range(4):
        new_matrix.append([])
        for j in range(4):
            new_matrix[i].append(matrix[i][3 - j])
    return new_matrix


def transpose(matrix):
    new_matrix = [[0] * 4 for _ in range(4)]
    for i in range(4):
        for j in range(4):
            new_matrix[i][j] = matrix[j][i]
    return new_matrix


def left(matrix):
    new_matrix = matrix
    new_matrix = stack(new_matrix)
    new_matrix, score = combine(new_matrix)
    new_matrix = stack(new_matrix)
    return new_matrix, score


def right(matrix):
    new_matrix = matrix
    new_matrix = reverse(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix, score = combine(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix = reverse(new_matrix)
    return new_matrix, score


def up(matrix):
    new_matrix = matrix
    new_matrix = transpose(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix, score = combine(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix = transpose(new_matrix)
    return new_matrix, score


def down(matrix):
    new_matrix = matrix
    new_matrix = transpose(new_matrix)
    new_matrix = reverse(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix, score = combine(new_matrix)
    new_matrix = stack(new_matrix)
    new_matrix = reverse(new_matrix)
    new_matrix = transpose(new_matrix)
    return new_matrix, score
