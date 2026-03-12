# Custom Memory Allocator in C

A simple implementation of dynamic memory allocation functions **malloc**, **free**, **realloc**, and **calloc** written from scratch in C.

This project demonstrates how heap memory management works internally by implementing a small memory allocator using **sbrk()**, block headers, free block reuse, block splitting, and coalescing.

Instead of using the system allocator, this project builds a small **heap manager** that keeps track of allocated and free memory blocks using a linked list.

---

# Features

- Custom `malloc` implementation
- Custom `free` implementation
- Custom `realloc` implementation
- Custom `calloc` implementation
- Memory alignment
- Block splitting
- Block coalescing
- Free block reuse
- Heap debugging using `print_heap()`

---

# Memory Layout

Each allocated block contains a **header** followed by the user memory.

```
+-------------------+----------------------+
| Header            | User Memory          |
|-------------------|----------------------|
| size              |                      |
| is_free           |  Memory returned     |
| next pointer      |  to the user         |
+-------------------+----------------------+
```

The pointer returned by `malloc()` points **after the header**.

```
malloc() returns → (header + 1)
```

---

# Header Structure

Each memory block is represented by a metadata structure.

```c
typedef struct header
{
    size_t size;
    int is_free;
    struct header *next;
} Header;
```

Fields:

| Field | Description |
|------|-------------|
| size | size of user memory |
| is_free | indicates whether block is free |
| next | pointer to next block |

---

# Memory Alignment

Memory allocations are aligned using:

```c
size_t align(size_t size)
{
    return (size + ALIGN - 1) & ~(ALIGN - 1);
}
```

This ensures proper memory alignment (typically **16 bytes**) which improves performance and prevents undefined behavior.

---

# How Allocation Works

## my_malloc()

Steps performed:

1. Align the requested size
2. Search the block list for a free block
3. If found:
   - mark block as used
   - split block if large enough
4. If not found:
   - request memory from OS using `sbrk`
5. Append new block to linked list
6. Return pointer to user memory

---

# Block Splitting

If a free block is larger than required, it is split.

Before split:

```
[ Free Block 128 ]
```

After split:

```
[ Used 32 ] -> [ Free 96 ]
```

This improves memory utilization.

---

# Freeing Memory

## my_free()

When memory is freed:

1. Block is marked as free
2. Adjacent free blocks are merged

Example:

Before:

```
[Free 32] -> [Free 64]
```

After coalescing:

```
[Free 96]
```

This reduces heap fragmentation.

---

# Reallocation

## my_realloc()

`realloc()` works as follows:

1. Allocate new block
2. Copy old data using `memcpy`
3. Free the old block
4. Return new memory block

This preserves previously stored data.

---

# Zero Initialization

## my_calloc()

`calloc()` allocates memory and initializes it to zero.

```c
void *ptr = my_malloc(num * size);
memset(ptr, 0, num * size);
```

---

# Heap Visualization

The allocator includes a debug tool to inspect the heap:

```c
void print_heap();
```

Example output:

```
Block 0: addr=0x556138859000 size=32 is_free=0
Block 1: addr=0x556138859040 size=32 is_free=1
Block 2: addr=0x556138859080 size=48 is_free=0
---
```

This helps visualize:

- heap structure
- block sizes
- fragmentation
- free block reuse

---

# Example Usage

```c
int *a = my_malloc(sizeof(int));
*a = 42;

my_free(a);

int *b = my_calloc(5, sizeof(int));

b = my_realloc(b, 10 * sizeof(int));

my_free(b);
```

---

# Concepts Demonstrated

This project demonstrates important memory management concepts:

- heap memory management
- memory alignment
- linked list memory tracking
- block splitting
- block coalescing
- fragmentation handling
- dynamic memory allocation

---

# Limitations

This is a **learning implementation**, not a production allocator.

Limitations include:

- not thread safe
- linear search for free blocks
- no segregated free lists
- no mmap for large allocations
- minimal error handling

Real allocators such as **glibc malloc**, **jemalloc**, and **tcmalloc** use more advanced techniques.

---

# Build

Compile using GCC:

```bash
gcc main.c malloc.c -o allocator
```

Run:

```bash
./allocator
```


---

# Learning Goal

The purpose of this project is to understand how memory allocation works internally in operating systems and runtime libraries.

It serves as a foundation for studying advanced memory allocators used in real systems.
