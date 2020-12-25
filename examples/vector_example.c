#include <cxx/vector.h>

#include <stdio.h>

int main(void)
{
    puts("Plain old data:");
    {
        cxx_vector numbers;
        cxx_vector_init(&numbers, sizeof(int), false);

        int number = 5;
        numbers.vtable->push_back(&numbers, &number);

        number = 10;
        numbers.vtable->push_back(&numbers, &number);

        int *retrieved = numbers.vtable->at(&numbers, 0);
        printf("%i\n", *retrieved);  // 5
        retrieved = numbers.vtable->at(&numbers, 1);
        printf("%i\n", *retrieved);  // 10

        // Should crash in debug mode
        // retrieved = numbers.vtable->at(&numbers, 2);

        numbers.vtable->destroy(&numbers);
    }
    putc('\n', stdout);

    puts("Container:");
    {
        cxx_vector matrix;
        cxx_vector_init(&matrix, sizeof(cxx_vector), true);
        matrix.vtable->set_element_ctor(&matrix, cxx_vector_init);

        CXX_VECTOR_EMPLACE_BACK(&matrix, sizeof(int), false);
        CXX_VECTOR_EMPLACE_BACK(&matrix, sizeof(int), false);
        CXX_VECTOR_EMPLACE_BACK(&matrix, sizeof(int), false);

        // Setting `matrix` to [[0, 1, 2], [3, 4, 5], [6, 7, 8]]
        int number = 0;
        for (size_t i = 0; i < matrix.vtable->size(&matrix); ++i)
        {
            cxx_vector *row = matrix.vtable->at(&matrix, i);
            row->vtable->reserve(row, 3);
            for (size_t j = 0; j < 3; ++j)
            {
                row->vtable->push_back(row, &number);
                ++number;
            }
        }

        // Printing top-left to bottom-right
        for (size_t i = 0; i < matrix.vtable->size(&matrix); ++i)
        {
            cxx_vector *row = matrix.vtable->at(&matrix, i);
            for (size_t j = 0; j < row->vtable->size(row); ++j)
            {
                int *num = row->vtable->at(row, j);
                printf("%d ", *num);
            }
            putc('\n', stdout);
        }

        matrix.vtable->destroy(&matrix);
    }
    putc('\n', stdout);
}
