#include "stdio.h"
#include "string.h"

typedef enum jump_type_ { T, S, Lo, F, Lz, A } JumpType;

static double scoreTable[4][6] = {{0.4, 0.4, 0.5, 0.5, 0.6, 1.1},
                                  {1.3, 1.3, 1.7, 1.8, 2.1, 3.3},
                                  {4.2, 4.3, 4.9, 5.3, 5.9, 8.0},
                                  {9.5, 9.7, 10.5, 11.0, 11.5, 12.5}};

double Score(int rotations, JumpType type) {
  if (rotations < 1 || rotations > 4) {
    return -1;
  }
  return scoreTable[rotations - 1][type];
}

double ParseJump(const char *jump) {
  int rotations = 0;
  JumpType type;
  double multiplier = 1.0;

  // number of rotations
  if (jump[0] < '1' || jump[0] > '4') {
    return -1;
  } else {
    rotations = jump[0] - '0';
  }

  // The position of string, indicating where we are. 
  // Starts from 1 since we have already processed the rotation number.
  int pos = 1;

  if (strncmp(jump + pos, "T", 1) == 0) {
    type = (JumpType)T;
    pos += 1;
  } else if (strncmp(jump + pos, "S", 1) == 0) {
    type = (JumpType)S;
    pos += 1;
  } else if (strncmp(jump + pos, "Lo", 2) == 0) {
    type = (JumpType)Lo;
    pos += 2;
  } else if (strncmp(jump + pos, "F", 1) == 0) {
    type = (JumpType)F;
    pos += 1;
  } else if (strncmp(jump + pos, "Lz", 2) == 0) {
    type = (JumpType)Lz;
    pos += 2;
  } else if (strncmp(jump + pos, "A", 1) == 0) {
    type = (JumpType)A;
    pos += 1;
  } else {
    return -1;
  }

  // annotation 1 for F and Lz jumps only.
  if (strncmp(jump + pos, "e", 1) == 0) {
    if (type != (JumpType)F && type != (JumpType)Lz) {
      return -1;
    } else {
      multiplier *= 0.7;
      pos += 1;
    }
  } else if (strncmp(jump + pos, "!", 1) == 0) {
    if (type != (JumpType)F && type != (JumpType)Lz) {
      return -1;
    } else {
      pos += 1;
    }
  }

  // annotation 2
  if (strncmp(jump + pos, "q", 1) == 0) {
    pos += 1;
  } else if (strncmp(jump + pos, "<<", 2) == 0) {
    rotations--;
    pos += 2;
  } else if (strncmp(jump + pos, "<", 1) == 0) {
    multiplier *= 0.7;
    pos += 1;
  }

  // No more annotations
  if (strncmp(jump + pos, "", 1) != 0) {
    return -1;
  } else {
    if (rotations == 0) {
      return 0;
    } else {
      return Score(rotations, type) * multiplier;
    }
  }
}

int main() {
  char line[100];
  char delim[2] = "+"; // '+' and '\0'
  for (int i = 0; i < 3; i++) {
    scanf("%s", line);
    double sequenceScore = 0.0, sequenceMultiplier = 1.0;
    if (line[strlen(line) - 1] == 'x') {
      sequenceMultiplier = 1.1;
      line[strlen(line) - 1] = '\0';
    }

    char *token = strtok(line, delim);
    while (token != NULL) {
      double jumpScore = ParseJump(token);
      if (jumpScore == -1) {
        sequenceScore = 0;
        break;
      } else {
        sequenceScore += jumpScore;
      }
      token = strtok(NULL, delim);
    }
    sequenceScore *= sequenceMultiplier;
    printf("%.2f\n", sequenceScore);
  }
}
