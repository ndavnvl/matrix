#pragma once


#include <stdlib.h>
#include <malloc.h>
#include "inputing.h"


typedef struct {
	long double **matrix;
	size_t height_of_matrix;
	size_t width_of_matrix;
} matrix;


matrix create_matrix(size_t height_of_matrix, size_t width__of_matrix);

void delete_matrix(matrix matrix_);

long double get_matrix_el(matrix matrix_, size_t str_coord, size_t col_coord);

void set_matrix_el(matrix *matrix_ptr,
	size_t str_coord,
	size_t col_coord,
	long double value);

long double *get_matrix_str(matrix matrix_, size_t str_coord);

matrix sum_of_matrix(matrix first_matrix, matrix second_matrix);

matrix mult_of_matrix(matrix first_matrix, matrix second_matrix);

long double det_of_matrix(matrix matrix_);

matrix inverse_matrix(matrix matrix_);

matrix inputing_matrix();

int matrix_validator(matrix matrix_);

void print_matrix(matrix matrix_);

int save_matrix(matrix matrix_, char *file_name);