/*
 * Name: Aswin chandra M A
 * Date: 17/01/2026
 * Description: heap memmory allocator clone
 * */

#include "header.h"
Header *head = NULL;
int main()
{
	// malloc
	int *a = my_malloc(sizeof(int));
	*a = 42;
	printf("malloc: %d\n", *a);
	my_free(a);

	// calloc
	int *b = my_calloc(3, sizeof(int));
	printf("calloc zeros: %d %d %d\n", b[0], b[1], b[2]);
	my_free(b);

	// realloc
	int *c = my_realloc(NULL, sizeof(int));
	*c = 99;
	c = my_realloc(c, 100);
	printf("realloc: %d\n", *c);
	my_free(c);

	print_heap();
	printf("sizeof(Header) = %zu\n", sizeof(Header));
	int *d = my_malloc(1);
	printf("address = %p\n", d);
	printf("aligned? %s\n", (size_t)d % 16 == 0 ? "YES ✅" : "NO ❌");
	return 0;
}
