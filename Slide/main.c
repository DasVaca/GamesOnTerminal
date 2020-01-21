#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Input {
  int value;
  int direction;
} Input;

enum Directions { UP, DOWN, RIGHT, LEFT };

void print_instructions();
int ** create_matrix(int size, int * blank);
void print_matrix(int ** matrix, int size);
void get_input(Input * input, int blank, int upper_limit);
void make_move(int ** matrix, int size, int blank, Input input);

int main(int argc, char const * argv[]) {
  int size = atoi(argv[1]);

  if (argc == 1)
  {
    puts("Use ./main <matrix size>");
    puts("Size must be between 2 and 10");
    exit(0);
  }

	if(size < 2 || size > 10)
	{
		puts("Error: size must be between 2 and 10");
		exit(0);
  }

  print_instructions();

  int blank;
  int ** matrix = create_matrix(size, &blank);
  Input * input;
  input = malloc(sizeof(Input));

  print_matrix(matrix, size);
  get_input(input, blank, size*size);
  make_move(matrix, size, blank, input);
  print_matrix(matrix, size);


  // free memory
  for(int row = 0; row < size; row++)
	   free(matrix[row]);

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

  getchar();
  system("clear");
  fclose(instructions);
}

int ** create_matrix(int size, int * blank) {
  int ** matrix;

  *blank = (rand() % size*size) + 1;

  matrix = malloc( size*sizeof(int *));

  for (int row = 0, inc = 1; row < size; row++)
  {
    matrix[row] = malloc(size*sizeof(int));

    for (int col = 0; col < size; col++, inc++)
    {
      if(inc != *blank)
    	   matrix[row][col] = inc;
      else
        matrix[row][col] = 0; // blank space
    }
  }

  return matrix;
}

void print_matrix(int ** matrix, int size) {
    for(int row = 0; row < size; row++)
    {
      for (int col = 0; col < size; col++)
      {
        if( matrix[row][col] )
          printf("%2i ", matrix[row][col]);
        else
          printf("%2s ", " ");
      }
      putchar('\n');
    }
}

void get_input(Input * input, int blank, int upper_limit) {
  int is_i_int_valid = 0;
  int is_i_dir_valid = 0;

  do {
    printf("\n> ");
    scanf("%i %i", &(input->value), &(input->direction));

    // check is int value entered is valid
    if( input->value != blank)
      is_i_int_valid = 1;
    else if ( input->value > 0 && input->value <= upper_limit)
      is_i_int_valid = 1;

    // check is direction submited is valid
    // direction is stored following definition of enum Directions
    if (input->direction >= UP && input->direction <= LEFT)
      is_i_char_valid = 1;

  } while(!is_i_int_valid && !is_i_char_valid);
}

void make_move(int ** matrix, int size, int blank, Input input) {
  // finding row and col of selected value
  int row, col;
  int found = 0;
  for(row = 0; row < size || found; row++)
  {
    for (col = 0; col < size; col++) {
      if (matrix[row][col] == input.value)
      {
        found = 1; // exit outer loop
        return ; // exit inner loop
      }
    }
  }

  // check if move can be applied
  switch(input.direction)
  {
		case UP:
		case DOWN:
		case RIGHT:
		case LEFT:
	}
}
