#include "tools.h"

void print_gsl_spmatrix_uint(gsl_spmatrix_uint* matrix)
{
    for (size_t i = 0; i < matrix->size1; i++) {
        for (size_t j = 0; j < matrix->size2; j++) {
            printf("%u ", gsl_spmatrix_uint_get(matrix, i, j));
        }
        printf("\n");
    }
}
