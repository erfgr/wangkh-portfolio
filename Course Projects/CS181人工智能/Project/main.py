import time
import tkinter
import color
import random
from dfs import *
from expectimax import *
from minimax import *
from greedy import *
from operate import *
import sys


sys.setrecursionlimit(10000000) #设置递归深度


GlobalScores = []
GlobalEndings = []
GlobalMaxTiles = []


class Game(tkinter.Frame):
    def __init__(self):
        tkinter.Frame.__init__(self)
        self.matrix = [[0] * 4 for _ in range(4)]
        self.GameState = -1
        self.Reach32 = 0
        self.Reach512 = 0
        self.Reach1024 = 0
        self.grid()
        self.master.title("2048")

        self.main_grid = tkinter.Frame(
            self, bg=color.GRID_COLOR, bd=3, width=600, height=600
        )
        self.main_grid.grid(pady=(100, 0))
        self.make_GUI()
        self.start_game()
        #self.matrix = [[1024, 1024,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
        self.master.bind("<Left>", self.MoveLeft)
        self.master.bind("<Right>", self.MoveRight)
        self.master.bind("<Up>", self.MoveUp)
        self.master.bind("<Down>", self.MoveDown)
        self.master.bind("1", self.search_dfs)
        self.master.bind("2", self.search_expectimax)
        self.master.bind("3", self.search_greedy)
        self.master.bind("4", self.search_minimax)
        self.mainloop()

    def Move(self, vector):
        new_matrix = []
        score = 0
        if vector == Direction[0]:
            new_matrix, score = down(self.matrix)
        if vector == Direction[1]:
            new_matrix, score = right(self.matrix)
        if vector == Direction[2]:
            new_matrix, score = up(self.matrix)
        if vector == Direction[3]:
            new_matrix, score = left(self.matrix)
        return new_matrix, score

    def search_dfs(self, event):
        if self.GameState == -1:
            self.GameState = 0
        self.matrix, AddScore = dfs(self.matrix)
        #time.sleep(0.4)
        self.score += AddScore
        if self.GameState == 1:
            return
        self.add_new_tile()
        self.update_GUI()
        self.game_over()
        if self.GameState == 0:
            self.search_dfs(self)

    def search_expectimax(self, event):
        if self.GameState == -1:
            self.GameState = 0
        self.matrix, AddScore = expectimax(self.matrix)
        #time.sleep(0.4)
        self.score += AddScore
        if self.GameState == 1:
            return
        self.add_new_tile()
        self.update_GUI()
        self.game_over()
        if self.GameState == 0:
            self.search_expectimax(self)

    def search_greedy(self, event):
        if self.GameState == -1:
            self.GameState = 0
        self.matrix, AddScore = evaluate(self.matrix)
        #time.sleep(0.4)
        self.score += AddScore
        if self.GameState == 1:
            return
        self.add_new_tile()
        self.update_GUI()
        self.game_over()
        if self.GameState == 0:
            self.search_greedy(self)

    def search_minimax(self, event):
        if self.GameState == -1:
            self.GameState = 0
        depth = 10
        if self.Reach32 == 0:
            depth = 4
            tmp = 0
            for i in range(4):
                for j in range(4):
                    tmp = max(tmp, self.matrix[i][j])
            if tmp >= 32:
                self.Reach32 = 1
        if self.Reach32 == 1 and self.Reach512 == 0:
            depth = 6
            tmp = 0
            for i in range(4):
                for j in range(4):
                    tmp = max(tmp, self.matrix[i][j])
            if tmp >= 512:
                self.Reach512 = 1
        if self.Reach512 == 1 and self.Reach1024 == 0:
            depth = 8
            tmp = 0
            for i in range(4):
                for j in range(4):
                    tmp = max(tmp, self.matrix[i][j])
            if tmp >= 1024:
                self.Reach1024 = 1
        policy = Minimax(self.matrix).search(-1e7, 1e7, depth)
        self.matrix, AddScore = self.Move(policy.move)
        #time.sleep(0.4)
        self.score += AddScore
        if self.GameState == 1:
            return
        self.add_new_tile()
        self.update_GUI()
        self.game_over()
        if self.GameState == 0:
            self.search_minimax(self)

    def make_GUI(self):
        self.cells = []
        for i in range(4):
            row = []
            for j in range(4):
                cell_frame = tkinter.Frame(
                    self.main_grid,
                    bg=color.EMPTY_CELL_COLOR,
                    width=150,
                    height=150
                )
                cell_frame.grid(row=i, column=j, padx=5, pady=5)
                cell_number = tkinter.Label(self.main_grid, bg=color.EMPTY_CELL_COLOR)
                cell_number.grid(row=i, column=j)
                cell_data = {"frame": cell_frame, "number": cell_number}
                row.append(cell_data)
            self.cells.append(row)

            score_frame = tkinter.Frame(self)
            score_frame.place(relx=0.5, y=45, anchor="center")
            tkinter.Label(
                score_frame,
                text="Score",
                font=color.SCORE_LABEL_FONT
            ).grid(row=0)
            self.score_label = tkinter.Label(score_frame, text="0", font=color.SCORE_FONT)
            self.score_label.grid(row=1)

    def start_game(self):
        row = random.randint(0, 3)
        col = random.randint(0, 3)
        self.matrix[row][col] = 2
        self.cells[row][col]["frame"].configure(bg=color.CELL_COLORS[2])
        self.cells[row][col]["number"].configure(
            bg=color.CELL_COLORS[2],
            fg=color.CELL_NUMBER_COLORS[2],
            font=color.CELL_NUMBER_FONTS[2],
            text="2"
        )
        while (self.matrix[row][col] != 0):
            row = random.randint(0, 3)
            col = random.randint(0, 3)
        self.matrix[row][col] = 2
        self.cells[row][col]["frame"].configure(bg=color.CELL_COLORS[2])
        self.cells[row][col]["number"].configure(
            bg=color.CELL_COLORS[2],
            fg=color.CELL_NUMBER_COLORS[2],
            font=color.CELL_NUMBER_FONTS[2],
            text="2"
        )
        self.score = 0

    def stack(self):
        new_matrix = [[0] * 4 for _ in range(4)]
        for i in range(4):
            fill_position = 0
            for j in range(4):
                if self.matrix[i][j] != 0:
                    new_matrix[i][fill_position] = self.matrix[i][j]
                    fill_position += 1
        self.matrix = new_matrix

    def add_new_tile(self):
        row = random.randint(0, 3)
        col = random.randint(0, 3)
        while (self.matrix[row][col] != 0):
            row = random.randint(0, 3)
            col = random.randint(0, 3)
        self.matrix[row][col] = random.choice([2, 4])

    def update_GUI(self):
        for i in range(4):
            for j in range(4):
                cell_value = self.matrix[i][j]
                if cell_value == 0:
                    self.cells[i][j]["frame"].configure(bg=color.EMPTY_CELL_COLOR)
                    self.cells[i][j]["number"].configure(bg=color.EMPTY_CELL_COLOR, text="")
                else:
                    self.cells[i][j]["frame"].configure(bg=color.CELL_COLORS[cell_value])
                    self.cells[i][j]["number"].configure(
                        bg=color.CELL_COLORS[cell_value],
                        fg=color.CELL_NUMBER_COLORS[cell_value],
                        font=color.CELL_NUMBER_FONTS[cell_value],
                        text=str(cell_value)
                    )
        self.score_label.configure(text=self.score)
        self.update_idletasks()

    def MoveLeft(self, event):
        OldMatrix = self.matrix
        self.matrix, AddScore = left(self.matrix)
        print(AddScore)
        if OldMatrix != self.matrix:
            self.add_new_tile()
            self.score += AddScore
        self.update_GUI()
        self.game_over()

    def MoveRight(self, event):
        OldMatrix = self.matrix
        self.matrix, AddScore = right(self.matrix)
        if OldMatrix != self.matrix:
            self.add_new_tile()
            self.score += AddScore
        self.update_GUI()
        self.game_over()

    def MoveUp(self, event):
        OldMatrix = self.matrix
        self.matrix, AddScore = up(self.matrix)
        if OldMatrix != self.matrix:
            self.add_new_tile()
            self.score += AddScore
        self.update_GUI()
        self.game_over()

    def MoveDown(self, event):
        OldMatrix = self.matrix
        self.matrix, AddScore = down(self.matrix)
        if OldMatrix != self.matrix:
            self.add_new_tile()
            self.score += AddScore
        self.update_GUI()
        self.game_over()

    def move_exists(self):
        for i in range(4):
            for j in range(3):
                if self.matrix[i][j] == self.matrix[i][j + 1]:
                    return True
        for i in range(3):
            for j in range(4):
                if self.matrix[i][j] == self.matrix[i + 1][j]:
                    return True
        return False

    def game_over(self):
        if any(8192 in row for row in self.matrix):
            self.GameState = 1
            game_over_frame = tkinter.Frame(self.main_grid, borderwidth=2)
            game_over_frame.place(relx=0.5, rely=0.5, anchor="center")
            tkinter.Label(
                game_over_frame,
                text="You win!",
                bg=color.WINNER_BG,
                fg=color.GAME_OVER_FONT_COLOR,
                font=color.GAME_OVER_FONT
            ).pack()
            GlobalScores.append(self.score)
            GlobalEndings.append(1)
            # self.destroy()
            # self.quit()
        elif not any(0 in row for row in self.matrix) and not self.move_exists():
            self.GameState = 1
            game_over_frame = tkinter.Frame(self.main_grid, borderwidth=2)
            game_over_frame.place(relx=0.5, rely=0.5, anchor="center")
            tkinter.Label(
                game_over_frame,
                text="Game over!",
                bg=color.LOSER_BG,
                fg=color.GAME_OVER_FONT_COLOR,
                font=color.GAME_OVER_FONT
            ).pack()
            GlobalScores.append(self.score)
            GlobalEndings.append(0)
            # self.destroy()
            # self.quit()
        if self.GameState == 1:
            # print(self.matrix[0])
            # print(self.matrix[1])
            # print(self.matrix[2])
            # print(self.matrix[3])
            # print("--------------------")
            tmp = 0
            for i in range(4):
                for j in range(4):
                    tmp = max(tmp, self.matrix[i][j])
            GlobalMaxTiles.append(tmp)
            #print(self.score)
            #print(tmp)
            #print("Recent Trials: ", len(GlobalMaxTiles))

def main():
    n = 1
    for i in range(n):
        Game()
    print("Trials: ", n)
    Wins = 0
    AverageScore = 0
    for i in GlobalEndings:
        Wins += i
    for i in GlobalScores:
        AverageScore += i
    print("Wins: ", Wins)
    print("Average: ", AverageScore / n)
    res = {}
    for i in GlobalMaxTiles:
        if i not in res:
            res[i] = 1
        else:
            res[i] += 1
    print(sorted(res.items(), key=lambda x: x[0]))


if __name__ == "__main__":
    main()
