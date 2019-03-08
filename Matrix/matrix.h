#pragma once

typedef struct {
	long double **matrix;
	size_t height_of_matrix;
	size_t width__of_matrix;
} matrix;

matrix create_matrix(size_t height_of_matrix, size_t width__of_matrix);

void delet_matrix(matrix matrix_);

long double get_matrix_el(matrix matrix_, size_t str_coord, size_t col_coord);

void set_matrix_el(matrix *matrix_ptr, size_t str_coord, size_t col_coord, \
	long double value);

matrix sum_of_matrix(matrix first_matrix, matrix second_matrix);

matrix mult_of_matrix(matrix first_matrix, matrix second_matrix);

matrix det_of_matrix(matrix matrix_);

matrix inverse_matrix(matrix matrix_);
