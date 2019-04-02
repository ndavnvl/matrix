#include "matrix.h"








matrix create_matrix(size_t height_of_matrix, size_t width_of_matrix) {
	matrix matrix_;

	matrix_.height_of_matrix = height_of_matrix;
	matrix_.width_of_matrix = width_of_matrix;

	if (!height_of_matrix || !width_of_matrix) {
		matrix_.matrix = NULL;
		return matrix_;
	}

	matrix_.matrix = (long double **)malloc(height_of_matrix * sizeof(long double *));

	for (size_t i = 0; i < height_of_matrix; i++) {
		matrix_.matrix[i] = (long double *)malloc(width_of_matrix * sizeof(long double));
	}

	return matrix_;
}








void delete_matrix(matrix matrix_) {

	for (size_t i = 0; i < matrix_.height_of_matrix; i++) {
		free(matrix_.matrix[i]);
	}

	free(matrix_.matrix);
	matrix_.height_of_matrix = 0;
	matrix_.width_of_matrix = 0;
	matrix_.matrix = NULL;
	return;
}








long double get_matrix_el(matrix matrix_, size_t str_coord, size_t col_coord) {
	if (matrix_.matrix == NULL) {
		double zero = 0;
		return (double)0 / zero;
	}

	return matrix_.matrix[str_coord - 1][col_coord - 1];
}








void set_matrix_el(matrix matrix_,
	size_t str_coord,
	size_t col_coord,
	long double value) {

	if (matrix_.matrix == NULL ||
		matrix_.height_of_matrix < str_coord ||
		matrix_.width_of_matrix < col_coord) {

		return;
	}

	matrix_.matrix[str_coord - 1][col_coord - 1] = value;
	return;
}








long double *get_matrix_str(matrix matrix_, size_t str_coord) {
	if (matrix_.matrix == NULL) {
		return NULL;
	}

	return matrix_.matrix[str_coord - 1];
}








matrix sum_of_matrix(matrix first_matrix, matrix second_matrix) {
	if (first_matrix.matrix == NULL ||
		second_matrix.matrix == NULL ||
		first_matrix.height_of_matrix != second_matrix.height_of_matrix ||
		first_matrix.width_of_matrix != second_matrix.width_of_matrix) {

		return create_matrix(0, 0);
	}

	matrix result_matr = create_matrix(first_matrix.height_of_matrix,
		first_matrix.width_of_matrix);

	for (int i = 0; i < first_matrix.height_of_matrix; i++) {
		for (int j = 0; j < first_matrix.width_of_matrix; j++) {
			result_matr.matrix[i][j] = first_matrix.matrix[i][j] +
				second_matrix.matrix[i][j];
		}
	}

	return result_matr;
}








matrix mult_of_matrix(matrix first_matrix, matrix second_matrix) {
	if (first_matrix.matrix == NULL ||
		second_matrix.matrix == NULL ||
		first_matrix.width_of_matrix != second_matrix.height_of_matrix) {

		return create_matrix(0, 0);
	}

	matrix res_matrix = create_matrix(first_matrix.height_of_matrix, \
		second_matrix.width_of_matrix);

	for (int i = 0; i < first_matrix.height_of_matrix; i++) {
		for (int j = 0; j < second_matrix.width_of_matrix; j++) {
			res_matrix.matrix[i][j] = 0;

			for (int k = 0; k < first_matrix.width_of_matrix; k++) {
				res_matrix.matrix[i][j] +=
					first_matrix.matrix[i][k] * second_matrix.matrix[k][j];
			}
		}
	}

	return res_matrix;
}








long double det_of_matrix(matrix matrix_) {
	if (matrix_.matrix == NULL ||
		matrix_.height_of_matrix != matrix_.width_of_matrix) {

		double zero = 0;
		return (double)0 / zero;
	}

	if (matrix_.height_of_matrix == 1) {
		return matrix_.matrix[0][0];
	}
	else {
		long double det = 0;

		for (int i = 0; i < matrix_.height_of_matrix; i++) {
			matrix tmp_matrix;

			tmp_matrix.height_of_matrix = matrix_.height_of_matrix - 1;
			tmp_matrix.width_of_matrix = matrix_.width_of_matrix - 1;
			tmp_matrix.matrix = (long double **)malloc(tmp_matrix.height_of_matrix *
				sizeof(long double *));

			for (int j = 0, offset = 0; j < matrix_.height_of_matrix; j++) {
				if (j == i) {
					offset = -1;
				}
				else {
					tmp_matrix.matrix[j + offset] = matrix_.matrix[j] + 1;
				}
			}

			det += matrix_.matrix[i][0] * (1 - 2 * (i % 2)) * det_of_matrix(tmp_matrix);
			free(tmp_matrix.matrix);
		}

		return det;
	}
}








matrix inverse_matrix(matrix matrix_) {
	if (matrix_.matrix == NULL || matrix_.height_of_matrix != matrix_.width_of_matrix) {
		return create_matrix(0, 0);
	}

	long double det = det_of_matrix(matrix_);

	if (!(det)) {
		return create_matrix(0, 0);
	}

	matrix res_matrix = create_matrix(matrix_.height_of_matrix, matrix_.width_of_matrix);

	if (matrix_.height_of_matrix == 1) {
		set_matrix_el(res_matrix, 1, 1, (long double)1 / get_matrix_el(matrix_, 1, 1));
		return res_matrix;
	}

	for (int i = 0; i < matrix_.height_of_matrix; i++) {
		for (int j = 0; j < matrix_.width_of_matrix; j++) {
			matrix tmp_matrix = create_matrix(matrix_.height_of_matrix - 1, matrix_.width_of_matrix - 1);

			for (int k = 0, offset_str = 0; k < matrix_.height_of_matrix; k++) {
				for (int l = 0, offset_col = 0; l < matrix_.width_of_matrix; l++) {
					if (k == i) {
						offset_str = -1;
					}
					else {
						if (l == j) {
							offset_col = -1;
						}
						else {
							tmp_matrix.matrix[k + offset_str][l + offset_col] = matrix_.matrix[k][l];
						}
					}
					
				}
			}

			res_matrix.matrix[j][i] = (1 - 2 * ((i + j) % 2)) * det_of_matrix(tmp_matrix) / det;
			delete_matrix(tmp_matrix);
		}
	}

	return res_matrix;
}








matrix inputing_matrix() {
	printf("\nInput size of the matrix in the following format \"NUMBER_OF_STRINGS NUMBER_OF COLUMNS\"\n");

	int num_of_str;
	int num_of_col;

	scaning_two_int_with_a_lower_limit(&num_of_str, &num_of_col, 1);
	printf("\nInput 1 if you want to input matrix through the console or 2 if you want to input matrix through a file.\n");

	int input_mode = 0;

	scaning_int_with_limits(&input_mode, 1, 2);

	if (input_mode == 1) {
		matrix output_matrix = create_matrix(num_of_str, num_of_col);

		for (int i = 0; i < num_of_str; i++) {
			printf("\nInput elements of %d string throuhg the gap\n", i + 1);
			scaning_a_string_of_long_doubles(get_matrix_str(output_matrix, i + 1), num_of_col);
		}

		return output_matrix;
	}
	else {
		printf("\nInput a name of file with the matrix (with the path)\nIt must include less than 255 symboles\n");

		char file_name[256];

		scanf_s("%s", file_name, (unsigned int)_countof(file_name));
		clean_stdin();

		FILE *file_with_matr_ptr = NULL;

		if (fopen_s(&file_with_matr_ptr, file_name, "r")) {
			return create_matrix(0, 0);
		}

		matrix output_matrix = create_matrix(num_of_str, num_of_col);

		for (int i = 0; i < num_of_str; i++) {
			for (int j = 0; j < num_of_col; j++) {
				long double el = 0;

				if (fscanf_s(file_with_matr_ptr, "%Lf", &el) != 1) {
					printf("\nIn file there is a mistake. Please, try again...\n");
					delete_matrix(output_matrix);
					return create_matrix(0, 0);
				}

				set_matrix_el(output_matrix, i + 1, j + 1, el);
			}
		}

		fclose(file_with_matr_ptr);
		return output_matrix;
	}
}








int matrix_validator(matrix matrix_) {
	if (matrix_.matrix == NULL) {
		return 0;
	}
	return 1;
}









void print_matrix(matrix matrix_) {
	if (matrix_.matrix == NULL) {
		printf("\nThis is invalid matrix...\n");
		return;
	}

	for (int i = 0; i < matrix_.height_of_matrix; i++) {
		for (int j = 0; j < matrix_.width_of_matrix; j++) {
			printf("%Lf\t", matrix_.matrix[i][j]);
		}
		printf("\n\n");
	}
}








int save_matrix(matrix matrix_, char * file_name) {
	FILE *file_for_matrix_ptr = NULL;

	if (fopen_s(&file_for_matrix_ptr, file_name, "w")) {
		return 1;
	}

	for (int i = 0; i < matrix_.height_of_matrix; i++) {
		for (int j = 0; j < matrix_.width_of_matrix; j++) {
			fprintf_s(file_for_matrix_ptr, "%Lf\t", matrix_.matrix[i][j]);
		}
		
		fprintf(file_for_matrix_ptr, "\n");
	}

	fclose(file_for_matrix_ptr);
	return 0;
}