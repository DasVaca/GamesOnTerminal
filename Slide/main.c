#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Input {
  int value;
  char direction;
} Input;

void print_instructions();
void fill_matrix(int ** matrix, int size, int * empty_cell);
void print_matrix(int ** matrix, int size);
void get_input(int ** matrix, Input * input, int size, int * row, int * col, int empty_cell);
void make_move(int ** matrix, char dir, int row, int co, int empty_cell);
void swap(int *a, int *b);
int is_solved(int ** matrix, int size, int empty_cell);

int main() {
  print_instructions();
  int size;
  int ** matrix;
  Input * input;
  int row, col; // position of cell to slide
  int empty_cell = 0;

  do {
    printf("size > ");
    scanf("%i", &size);
  } while( size > 10 || size < 2);

  input = malloc(sizeof(Input));
  matrix = malloc(sizeof(int *)*size);
  for(int i = 0; i < size; i++)
    matrix[i] = malloc(sizeof(int)*size);

  fill_matrix(matrix, size, &empty_cell);
  do {
    print_matrix(matrix, size);
    get_input(matrix, input, size, &row, &col, empty_cell);
    make_move(matrix, input->direction, row, col, empty_cell);
  } while(is_solved(matrix, size, empty_cell));

  for(int i = 0; i < size; i++)
    free(matrix[i]);
  free(matrix);
  free(input);
  return 0;
}

void print_instructions() {
  system("clear");

  FILE * instructions;

  instructions = fopen("how2play.txt", "r");

  int c = fgetc(instructions);

  while(c != EOF)
  {
    printf("%c", c);
    c = fgetc(instructions);
  }

  fclose(instructions);
}

void fill_matrix(int ** matrix, int size, int * empty_cell) {

  // fill ordered
  for (int row = 0, inc = 1; row < size; row++) {
    for (int col = 0; col < size; col++, inc++)
      matrix[row][col] = inc;
  }
  // swap random cells
  for(int changes = 0; changes < size*size - 2; changes++)
  {
    int Rrow1, Rcol1, Rrow2, Rcol2; // random cells to swap
    Rrow1 = rand() % size;
    Rcol1 = rand() % size;
    Rrow2 = rand() % size;
    Rcol2 = rand() % size;
    swap(&matrix[Rrow1][Rcol1], &matrix[Rrow2][Rcol2]);
  }
  // set empty cell
  int Rrow = rand() % size;
  int Rcol = rand() % size;
  *empty_cell = matrix[Rrow][Rcol];
  matrix[Rrow][Rcol] = 0;
}

void print_matrix(int ** matrix, int size) {
    for(int row = 0; row < size; row++)
    {
      for (int col = 0; col < size; col++)
      {
        if( matrix[row][col] )
          printf("%3i ", matrix[row][col]);
        else
          printf("%3s ", " ");
      }
      putchar('\n');
    }
}

void get_input(int ** matrix, Input * input, int size, int * row, int * col, int empty_cell) {
  int value_valid = 0;
  int dir_valid = 0;

    Again:
    printf("\nmov > ");
    scanf("%i %c", &(input->value), &(input->direction));
    if (input->value > 0 && input->value <= size*size && input->value != empty_cell)
      value_valid = 1;

    if(!value_valid) goto Default;

    // find position of value to move
    for(*row = 0; *row < size; *row += 1)
    {
      for (*col = 0; *col < size; *col += 1)
      {
        if (matrix[*row][*col] == input->value)
          goto check;
      }
    }
    check:
    // check is direction submited is valid
    input->direction = tolower(input->direction);
    switch (input->direction) {
      case 'u': if (*row > 0 && matrix[*row-1][*col] == 0) dir_valid = 1;
        break;
      case 'd': if (*row < size-1 && matrix[*row+1][*col] == 0) dir_valid = 1;
        break;
      case 'r': if (*col < size-1 && matrix[*row][*col+1] == 0) dir_valid = 1;
        break;
      case 'l': if (*col > 0 && matrix[*row][*col-1] == 0) dir_valid = 1;
        break;
      default: Default: puts("Move not allowed : invalid direction, value or impossible to execute"); goto Again; break;
    }

    if(!dir_valid) goto Default;
}

void make_move(int ** matrix, char dir, int row, int col, int empty_cell) {
  switch (dir) {
    case 'u': swap(&matrix[row-1][col], &matrix[row][col]); break;
    case 'd': swap(&matrix[row+1][col], &matrix[row][col]); break;
    case 'r': swap(&matrix[row][col+1], &matrix[row][col]); break;
    case 'l': swap(&matrix[row][col-1], &matrix[row][col]); break;
  }
}

void swap(int *a, int *b) {
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

int is_solved(int ** matrix, int size, int empty_cell) {
  for(int row = 0, counter = 1; row < size; row++)
  {
    for(int col = 0; col < size; col++, counter++)
    {

      if(counter != empty_cell && matrix[row][col] != counter)
        return 0;
    }
  }

  return 1;
}
