#include <stdio.h>
#include "matrix.h"
#include "inputing.h"








void save_or_not(matrix matrix_to_save) {
	printf("\nDo you want to save it? Input 1 to confirm or 0 to cansel\n");

	int save_or_not_matrix;

	scaning_int_with_limits(&save_or_not_matrix, 0, 1);

	if (save_or_not_matrix) {
		printf("\nInput path to file\nIt must include less than 255 symboles\n");

		char path_to_save[255];

		scanf_s("%s", path_to_save, (unsigned int)_countof(path_to_save));
		clean_stdin();

		save_matrix(matrix_to_save, path_to_save);
		return;
	}

	return;
}







void unary_operations() {
	matrix first_matrix = inputing_matrix();

	if (matrix_validator(first_matrix)) {
		printf("\nChoose operation:\n\tinput 1 for calculation the determinant of input matrix;\n\tinput 2 for calculation the inverse matrix.\n");

		int oparation = 0;

		scaning_int_with_limits(&oparation, 1, 2);

		if (oparation == 1) {
			long double det = det_of_matrix(first_matrix);

			if (det != det) {
				printf("\nCalculation the determinant is imposible for this matrix.\n");
			}
			else {
				printf("\nThe determinant of this matrix is %Lf.\n", det);
			}
		}
		else {
			matrix res_matrix = inverse_matrix(first_matrix);

			printf("\nResult:\n");
			print_matrix(res_matrix);

			if (matrix_validator(res_matrix)) {
				save_or_not(res_matrix);
			}

			delete_matrix(res_matrix);
		}

		delete_matrix(first_matrix);
		return;
	}
	else {
		printf("\nYou have input invalid matrix\n");
		return;
	}
}








void binary_operations() {
	printf("\nInputing the first matrix\n");

	matrix first_matrix = inputing_matrix();

	printf("\nInputing the second matrix\n");

	matrix second_matrix = inputing_matrix();

	if (matrix_validator(first_matrix) && matrix_validator(second_matrix)) {
		printf("\nChoose operation:\n\tinput 1 to sum the input matrixes;\n\tinput 2 to multiply the input matrixes.\n");

		int oparation = 0;

		scaning_int_with_limits(&oparation, 1, 2);

		if (oparation == 1) {
			matrix res_matrix = sum_of_matrix(first_matrix, second_matrix);

			printf("\nResult:\n");
			print_matrix(res_matrix);

			if (matrix_validator(res_matrix)) {
				save_or_not(res_matrix);
			}

			delete_matrix(res_matrix);
		}
		else {
			matrix res_matrix = mult_of_matrix(first_matrix, second_matrix);

			printf("\nResult:\n");
			print_matrix(res_matrix);

			if (matrix_validator(res_matrix)) {
				save_or_not(res_matrix);
			}

			delete_matrix(res_matrix);
		}

		delete_matrix(first_matrix);
		delete_matrix(second_matrix);
		return;
	}
	else {
		printf("\nYou have input invalid matrixes.\n");
		return;
	}
}








int main() {
	printf("This programm can operate with matrix with size M x N\n");

	while (1) {
		printf("\nInput 1, if you want to operate with only one matrix, or 2 if you want to operate with two matrixes.\n");
		
		int num_of_matr = 0;
	
		scaning_int_with_limits(&num_of_matr, 1, 2);

		if (num_of_matr == 1) {
			printf("\nYou have chosen unary operations.\n");
			unary_operations();
		}
		else {
			printf("\nYou have chosen binary operation.\n");
			binary_operations();			
		}

		int cont;

		printf("\nIf you want to do it again input 1 else input 0\n");
		scaning_int_with_limits(&cont, 0, 1);

		if (!cont) {
			break;
		}
	}

	return 0;
}