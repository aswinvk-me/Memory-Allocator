#include "header.h"

extern Header *head;
size_t align(size_t size)
{
    return (size + ALIGN - 1) & ~(ALIGN - 1);
}

void print_heap()
{
    Header *curr = head;
    int i = 0;
    while (curr != NULL)
    {
        printf("Block %d: addr=%p size=%zu is_free=%d\n",
               i++, (void *)curr, curr->size, curr->is_free);
        curr = curr->next;
    }
    printf("---\n");
}

void *my_malloc(int size)
{
    // align the size
    size = align(size);

    // walk the list
    Header *block = head;
    while (block != NULL)
    {
        // if block is free and have enough size mark as not free
        // and return pointer after header
        if ((block->is_free == 1) && block->size >= size)
        {
            block->is_free = 0;

            // if the block is big enough to carry one more header and minimum byte, split into two
            if (block->size >= size + sizeof(Header) + 1)
            {
                Header *newblock = (Header *)((char *)(block + 1) + size);

                newblock->size = block->size - sizeof(Header) - size;
                newblock->next = block->next;
                newblock->is_free = 1;
                block->next = newblock;
                block->size = size;
            }

            return (void *)(block + 1); // return pointre after header
        }
        block = block->next;
    }
    // if not found call sbrk
    void *mem = sbrk(sizeof(Header) + size);
    if (mem == (void *)-1)
        return NULL;

    Header *newblock = (Header *)mem;
    newblock->next = NULL;
    newblock->size = size;
    newblock->is_free = 0;

    // add new block to the end of list

    if (head == NULL)
        head = newblock;
    else
    {
        Header *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newblock;
    }
    return (void *)(newblock + 1);
}

void my_free(void *ptr)
{
    if (ptr == NULL)
        return;
    Header *tofree = (Header *)ptr - 1;
    tofree->is_free = 1;

    // coelescing: merge small free blocks to large one
    Header *temp = head;
    while (temp != NULL)
    {
        if (temp->is_free == 1 && temp->next != NULL && temp->next->is_free == 1)
        {
            temp->size = temp->size + temp->next->size + sizeof(Header);
            temp->next = temp->next->next;
        }
        else
        {
            temp = temp->next;
        }
    }
}

void *my_realloc(void *ptr, size_t newsize)
{
    // align the size
    newsize = align(newsize);

    if (ptr == NULL)
    {
        return my_malloc(newsize);
    }
    else if (newsize == 0)
    {
        my_free(ptr);
        return NULL;
    }

    // malloc new block of memory
    void *newmem = my_malloc(newsize);

    // copy the memory of the old block to new
    size_t oldsize = ((Header *)ptr - 1)->size;

    size_t rsize = oldsize < newsize ? oldsize : newsize;
    memcpy(newmem, ptr, rsize);

    // free the old block
    my_free(ptr);

    return newmem;
}

void *my_calloc(size_t num, size_t size)
{
    void *ptr = my_malloc(num * size);
    if (ptr == NULL)
        return NULL;
    memset(ptr, 0, num * size);
    return ptr;
}