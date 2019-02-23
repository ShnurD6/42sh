#include "readline.h"
#include <string.h>
#include <stdlib.h>

void	matrix_erase_line(t_matrix *matrix, int row)
{
	line_del(&matrix->lines[row]);
	matrix->len--;
	if (row != matrix->len)
		memmove(matrix->lines + row, matrix->lines + row + 1,
				(matrix->len - row) * sizeof(t_line *));
}