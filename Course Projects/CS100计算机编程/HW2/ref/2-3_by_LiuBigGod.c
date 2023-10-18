int **MagicSquare(int n) {
  int **a = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; ++i)
    a[i] = (int *)malloc(sizeof(int) * n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      a[i][j] = ((i + j + (n + 1) / 2) % n) * n + (i + 2 * j + 1) % n + 1;
  return a;
}

void FreeMagicSquare(int **magicSquare, int n) {
  for (int i = 0; i < n; ++i)
    free(magicSquare[i]);
  free(magicSquare);
}
