#include <containers/vector.h>
#include <stdio.h>

int main(void)
{
    vector numbers;
    vector__init(&numbers, sizeof(int));

    int number = 5;
    numbers.vtable->push_back(&numbers, &number);

    number = 10;
    numbers.vtable->push_back(&numbers, &number);

    int retrieved = *(int *)numbers.vtable->at(&numbers, 0);
    printf("%i\n", retrieved);  // 5
    retrieved = *(int *)numbers.vtable->at(&numbers, 1);
    printf("%i\n", retrieved);  // 10

    // Crashes in debug mode
    // retrieved = *(int *)numbers.vtable->at(&numbers, 2);
}
