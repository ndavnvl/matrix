#include <stdlib.h>
#include <malloc.h>
#include "matrix.h"

matrix create_matrix(size_t height_of_matrix, size_t width__of_matrix) {
	matrix matrix_;

	matrix_.height_of_matrix = height_of_matrix;
	matrix_.width__of_matrix = width__of_matrix;
	matrix_.matrix = (long double **)malloc(height_of_matrix * sizeof(long double *));

	for (size_t i = 0; i < height_of_matrix; i++) {
		matrix_.matrix[i] = (long double *)malloc(width__of_matrix * sizeof(long double));
	}

	return matrix_;
}

void delet_matrix(matrix matrix_) {

	for (size_t i = 0; i < matrix_.height_of_matrix; i++) {
		free(matrix_.matrix[i]);
	}

	free(matrix_.matrix);
	return;
}

long double get_matrix_el(matrix matrix_, size_t str_coord, size_t col_coord) {
	if (matrix_.matrix == NULL) {
		return sqrt(-1);
	}

	return matrix_.matrix[str_coord - 1][col_coord - 1];
}

void set_matrix_el(matrix *matrix_ptr, size_t str_coord, size_t col_coord, \
	long double value) {

	if (matrix_ptr->matrix == NULL) {
		return create_matrix(0, 0);
	}

	matrix_ptr->matrix[str_coord - 1][col_coord - 1] = value;
	return;
}

matrix sum_of_matrix(matrix first_matrix, matrix second_matrix) {
	if (first_matrix.matrix == NULL && second_matrix.matrix == NULL) {
		return create_matrix(0, 0);
	}

	if (first_matrix.height_of_matrix != second_matrix.height_of_matrix && \
		first_matrix.width__of_matrix != second_matrix.width__of_matrix) {

		return create_matrix(0, 0);
	}

	matrix result_matr = create_matrix(first_matrix.height_of_matrix, \
		first_matrix.width__of_matrix);

	for (int i = 0; i < first_matrix.height_of_matrix; i++) {
		for (int j = 0; j < first_matrix.width__of_matrix; j++) {
			result_matr.matrix[i][j] = first_matrix.matrix[i][j] + \
				second_matrix.matrix[i][j];
		}
	}

	return result_matr;
}

matrix mult_of_matrix(matrix first_matrix, matrix second_matrix) {
	return matrix();
}

matrix det_of_matrix(matrix matrix_) {
	return matrix();
}

matrix inverse_matrix(matrix matrix_) {
	return matrix();
}

