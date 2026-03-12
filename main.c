/*
 * Name: Aswin chandra M A
 * Date: 17/01/2026
 * Description: heap memmory allocator clone
 * */
#include "header.h"

Header *head = NULL;

int main()
{
    printf("\n===== CUSTOM MALLOC DEMO =====\n");

    printf("\nStep 1: Allocate three blocks\n");

    int *a = my_malloc(sizeof(int));
    int *b = my_malloc(sizeof(int));
    int *c = my_malloc(sizeof(int));

    *a = 10;
    *b = 20;
    *c = 30;

    printf("a=%d  b=%d  c=%d\n", *a, *b, *c);

    print_heap();


    printf("\nStep 2: Free middle block (creates fragmentation)\n");

    my_free(b);

    print_heap();


    printf("\nStep 3: Allocate again (allocator reuses free block)\n");

    int *d = my_malloc(sizeof(int));
    *d = 99;

    printf("d=%d\n", *d);

    print_heap();


    printf("\nStep 4: Realloc example\n");

    int *arr = my_malloc(2 * sizeof(int));

    arr[0] = 5;
    arr[1] = 6;

    arr = my_realloc(arr, 6 * sizeof(int));

    arr[2] = 7;
    arr[3] = 8;

    printf("Array after realloc: ");
    for(int i = 0; i < 4; i++)
        printf("%d ", arr[i]);

    printf("\n");

    print_heap();


    printf("\nStep 5: Free everything (coalescing happens)\n");

    my_free(a);
    my_free(c);
    my_free(d);
    my_free(arr);

    print_heap();

    printf("\nHeap merged back to single block.\n");

    printf("\nHeader size = %zu bytes\n", sizeof(Header));

    return 0;
}
